/*x = initial guess for inv(A)*b
 r = b - A*x ... residual, to be made small
 p = r ... initial "search direction"
 repeat
 V = A*p
 ... matrix-vector multiply
 h = ( r'*r ) / ( p'*V )
 ... dot product
 x = x + h*p
 ... compute updated solution

 new_r = r - h*V
 ... compute updated residual

 g = ( new_r'*new_r ) / ( r'*r )
 ... dot product
 p = new_r + g*p
 ... compute updated search direction

 r = new_r
 until ( new_r'*new_r small enough  and No of Interations is less than order of A)
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include <assert.h>
#include <fcntl.h>
#include <math.h>
#include <mpi.h>
#include<pthread.h>
#include <sys/times.h>

#define READ       0
#define INIT1      1
#define INIT2      2
#define COMP1      3
#define COMP2      4
#define COMP3      5
#define COMP4	   6
#define COMP5	   7
#define COMP6	   8
int ntasks, taskid;
int leafmaxcol;
char dirpath[13];
double mpi_elapsed;
int lb, ub;
typedef enum {
	FALSE = 0, TRUE
} boolean;

typedef struct {
	int* colidx; // indexex of non zero columns
	int num; // No. of non zero columns
} Rowstr;

typedef struct {
	double** A;
	Rowstr* rowstr; // For Storing the index of non zero cols at each row


	double* x;
	double* z;
	double* r;
	double* p;
	//double* b;
	double* V;
	double RR; //For Storing r'r at task level
	double h;
	double g;
	double rnorm;
	double norm_temp11;
	double norm_temp12;
	double zeta;

} Data;

typedef struct {
	int lb;
	int ub;
	Data dt;
	int mode;
	double rr; //For Storing r'r at thread level
	double pAp; //For Storing p'Ap
	double g; //For Storing g at thread level
	double rnorm;//For Storing rnorm at thread level
	double norm_temp11;//For Storing norm_temp11 at thread level
	double norm_temp12;//For Storing norm_temp12 at thread level
} divideattr;

char cls; /* problem class for the benchmark: U, S,W, A ,B or C */
int niter, numNonZeros, nonzer;
double shift, zeta_verify_value;
int global_N;
int numRowsPerPlace;
double epsilon;
boolean verified;

/**
 * Set up problem sizes for the sample benchmark.
 */
void setup_for_benchmark(char class) {

	if (class == 'S') {
		cls = 'S';
		global_N = 1400;
		niter = 15;
		nonzer = 7;
		shift = 10.0; /* ``lambda'' in the NAS CG benchmark spec */
		zeta_verify_value = 8.5971775078648;
	}
	if (class == 'W') {
		cls = 'W';
		global_N = 7000;
		niter = 15;
		nonzer = 8;
		shift = 12.0; /* ``lambda'' in the NAS CG benchmark spec */
		zeta_verify_value = 10.362595087124;
	} else if (class == 'A') {
		cls = 'A';
		global_N = 14000;
		niter = 15;
		nonzer = 11;
		shift = 20.0;
		zeta_verify_value = 17.1302350580784;
	} else if (class == 'B') {
		cls = 'B';
		global_N = 75000;
		niter = 75;
		nonzer = 13;
		shift = 60.0;
		zeta_verify_value = 22.712745482078;
	} else if (class == 'C') {
		cls = 'C';
		global_N = 150000;
		niter = 75;
		nonzer = 15;
		shift = 110.0;
		zeta_verify_value = 28.973605592845;
	} else if(class == 'U'){
		cls = 'U';
		global_N = 5;
		nonzer = 2;
		shift = 10.0;
		niter = 15;
	}
}

void allocateinitial(Data* dt) {
	int i, j;
	MPI_Status status;
	int rowIndex, numNonZerosAtPlace = 0, offset, newoffset; //No. of rows per task

	if (taskid < (ntasks - 1))
		numRowsPerPlace = global_N / ntasks;
	else
		numRowsPerPlace = global_N - ((ntasks - 1) * (global_N / ntasks));

	dt->A = (double **) calloc(global_N, sizeof(double *));
	dt->rowstr = (Rowstr*) calloc(global_N, sizeof(Rowstr));
	dt->r = (double*) calloc(numRowsPerPlace, sizeof(double));
	//dt.b = (double*) calloc(global_N / ntasks, sizeof(double));
	dt->V = (double*) calloc(numRowsPerPlace, sizeof(double));

	dt->p = (double*) calloc(global_N, sizeof(double));

	dt->x = (double*) calloc(numRowsPerPlace, sizeof(double));
	dt->z = (double*) calloc(global_N, sizeof(double));

}

void appendZeros(char* filename, int row) {

	int temp;
	long fact = 1000000000;
	temp = (row + 1) / fact;

	while (temp == 0) {
		strcat(filename, "0");
		fact = fact / 10;
		temp = (row + 1) / fact;
	}
}

void readandinitializeData(divideattr* dattr) {
	Data dt = dattr->dt;
	int j;

	int lb, ub, i, col, idx;
	lb = dattr->lb;
	ub = dattr->ub;
	char path[27], t[15];
	int fact = 10, temp, filelength;
	int* tempcolidx;
	double* tempA;
	tempcolidx = (int*) calloc(global_N, sizeof(int));
	tempA = (double*) calloc(global_N, sizeof(double));
	FILE* fp;

	for (i = lb; i < ub; i++) {
		filelength = 0;

		sprintf(t, "%d", i + 1);
		strcpy(path, dirpath);

		appendZeros(path, i);

		strcat(path, t);

		strcat(path, ".txt");

	//	printf("%s i = %d\n",path,i+1);

	
		fp = fopen(path, "r");

		while (fscanf(fp, "%d %lf\n", &tempcolidx[filelength],
				&tempA[filelength]) != EOF) {

			tempcolidx[filelength]--;
			filelength++;

		}

		fclose(fp);

		dt.rowstr[i].num = filelength;
		dt.A[i] = (double *) calloc(filelength, sizeof(double));
		dt.rowstr[i].colidx = (int*) calloc(filelength, sizeof(int));

		for (j = 0; j < filelength; j++) {
			dt.A[i][j] = tempA[j];
			dt.rowstr[i].colidx[j] = tempcolidx[j];

		}

	}

}

void initialize1(divideattr* dattr) {

	Data dt = dattr->dt;
	int lb, ub, i;
	lb = dattr->lb;
	ub = dattr->ub;
	int rowIndex;
	rowIndex = taskid * (global_N / ntasks);

	for (i = lb; i < ub; i++) {

		dt.x[i - rowIndex] = 1.0; // Intial Xo solution


	}

}

void initialize_conj_grad(divideattr* dattr) {
	Data dt = dattr->dt;
	int lb, ub, i;
	lb = dattr->lb;
	ub = dattr->ub;
	int rowIndex;
	int idx;
	rowIndex = taskid * (global_N / ntasks);

	for (i = lb; i < ub; i++) {

		idx = i - rowIndex;
		dt.V[idx] = 0.0;
		dt.z[i] = 0.0;
		dt.r[idx] = dt.x[idx];
		dt.p[i] = dt.r[idx];

	}

}

void combineinitialize_conj_grad(Data* Dt) {
	Data dt = *Dt;
	int sendCount, recvCount, rowIndex,remainingRows;
	//if(taskid <(ntasks -1))
	sendCount = recvCount = global_N / ntasks;//numRowsPerPlace;
	rowIndex = taskid * (global_N / ntasks);
	double *temp;
	temp = (double*)calloc(global_N,sizeof(double));
		
	//printf("taskid = %d rowIndex = %d sendCount = %d\n",taskid,rowIndex,sendCount);
	//Gather and Broadcasting p at each place
	MPI_Allgather(&dt.p[rowIndex], sendCount, MPI_DOUBLE, temp, recvCount,
			MPI_DOUBLE, MPI_COMM_WORLD);
	remainingRows = global_N - ((ntasks)*(global_N/ntasks));
	
	int i;
	for(i = 0 ; i < ntasks*(global_N/ntasks) ; i++)
		dt.p[i] = temp[i];

	free(temp);
	

	rowIndex = (ntasks)*(global_N/ntasks);
	if(remainingRows > 0)
	MPI_Bcast(&dt.p[rowIndex],remainingRows,MPI_DOUBLE,ntasks-1,MPI_COMM_WORLD);
	
	*Dt = dt;

}

void compute1(divideattr* dattr) {
	Data dt = dattr->dt;
	int lb, ub, i, e,idx;
	lb = dattr->lb;
	ub = dattr->ub;
	int rowindex, numRows;
	numRows = global_N / ntasks;
	rowindex = taskid * (numRows);

	dattr->rr = 0;
	dattr->pAp = 0;
	for (i = lb; i < ub; i++) {

		dt.V[i - rowindex] = 0;

		for (e = 0; e < dt.rowstr[i].num; e++) {
			idx = dt.rowstr[i].colidx[e];
			dt.V[i - rowindex] += dt.A[i][e] * dt.p[dt.rowstr[i].colidx[e]];

		}

		dattr->pAp += dt.p[i] * dt.V[i - rowindex]; //p'*A*p
		dattr->rr += dt.r[i - rowindex] * dt.r[i - rowindex]; //r'*r


	}

	//printf("Rank = %d lb = %d ub = %d dattr->pAp = %f \n",taskid,lb ,ub,dattr->pAp);

}

void combineComputation1(Data* Dt, divideattr dattr) {
	Data dt = *Dt;

	int count = 1;
	int dest = 0;
	double temp_pAp = 0.0;
	MPI_Allreduce(&dattr.rr, &dt.RR, count, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

	MPI_Reduce(&dattr.pAp, &temp_pAp, count, MPI_DOUBLE, MPI_SUM, dest,
			MPI_COMM_WORLD);

	if (taskid == dest) {

		dt.h = dt.RR / temp_pAp;
//		printf("Rank = %d dt.RR = %lf\t temp_pAp = %lf \t dt.h = %lf\n",taskid,dt.RR,temp_pAp,dt.h);

	}

	MPI_Bcast(&dt.h, 1, MPI_DOUBLE, dest, MPI_COMM_WORLD);

	*Dt = dt;
	//	printf("Rank = %d \tdt.h = %f\n",taskid,dt.h);

}

void compute2(divideattr* dattr) {
	Data dt = dattr->dt;
	int lb, ub, i;
	lb = dattr->lb;
	ub = dattr->ub;
	int rowindex;
	rowindex = taskid * (global_N / ntasks);
	dattr->g = 0;
	for (i = lb; i < ub; i++) {
		//printf("Rank = %d \tdt.h = %f\n",taskid,dt.h);
		dt.z[i] += dt.h * dt.p[i]; //z = z + h*p
		dt.r[i - rowindex] = dt.r[i - rowindex] - (dt.h * dt.V[i - rowindex]); //new_r = r - h*V
		dattr->g += (dt.r[i - rowindex] * dt.r[i - rowindex]) / (dt.RR);//g = ( new_r'*new_r ) / ( r'*r )
		//printf("Rank = %d Row no %d r = %f h = %f V = %f\n",taskid,i,dt.r[i - rowindex],dt.h , dt.V[i - rowindex]);
	}

}

void combineComputation2(Data* Dt, divideattr dattr) {
	Data dt = *Dt;

	int count = 1;
	dt.g = 0;

	MPI_Allreduce(&dattr.g, &dt.g, count, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

	*Dt = dt;

}

void compute3(divideattr* dattr) {
	Data dt = dattr->dt;
	int lb, ub, i;
	lb = dattr->lb;
	ub = dattr->ub;
	int rowindex;
	rowindex = taskid * (global_N / ntasks);

	
	for (i = lb; i < ub; i++) {
		//printf("Before Rank = %d i = %d  p = %lf\n",taskid,i,dt.p[i]);
		dt.p[i] = dt.r[i - rowindex] + (dt.g * dt.p[i]);
//		printf("After Rank = %d i = %d r = %lf dt.g = %lf  p = %lf\n",taskid,i,dt.r[i - rowindex],dt.g,dt.p[i]);
	}
}

void combineComputation3(Data* Dt) {
	Data dt = *Dt;
	int sendCount, recvCount, rowIndex,remainingRows;

	sendCount = recvCount = global_N / ntasks;//numRowsPerPlace;
	rowIndex = taskid * (global_N / ntasks);

	  double *temp;
        temp = (double*)calloc(global_N,sizeof(double));
	
	//printf("taskid = %d rowIndex = %d sendCount = %d\n",taskid,rowIndex,sendCount);
	//Gather and Broadcasting p at each place
	MPI_Allgather(&dt.p[rowIndex], sendCount, MPI_DOUBLE, temp, recvCount,
			MPI_DOUBLE, MPI_COMM_WORLD);

 int i;
        for(i = 0 ; i < ntasks*(global_N/ntasks) ; i++)
                dt.p[i] = temp[i];

        free(temp);



	remainingRows = global_N - ((ntasks)*(global_N/ntasks));
	rowIndex = (ntasks)*(global_N/ntasks);

	 if(remainingRows > 0)
	MPI_Bcast(&dt.p[rowIndex],remainingRows,MPI_DOUBLE,ntasks-1,MPI_COMM_WORLD);
	
	*Dt = dt;

}

void combinecgiterations(Data* Dt) {
	Data dt = *Dt;
	int sendCount, recvCount, rowIndex,remainingRows;

	sendCount = recvCount = global_N / ntasks;//numRowsPerPlace;
	rowIndex = taskid * (global_N / ntasks);
	
	  double *temp;
        temp = (double*)calloc(global_N,sizeof(double));

	//printf("taskid = %d rowIndex = %d sendCount = %d\n",taskid,rowIndex,sendCount);
	//Gather and Broadcasting p at each place
	MPI_Allgather(&dt.z[rowIndex], sendCount, MPI_DOUBLE,temp, recvCount,
			MPI_DOUBLE, MPI_COMM_WORLD);
 int i;
        for(i = 0 ; i < ntasks*(global_N/ntasks) ; i++)
                dt.z[i] = temp[i];

        free(temp);





	remainingRows = global_N - ((ntasks)*(global_N/ntasks));
	rowIndex = (ntasks)*(global_N/ntasks);
	
	if(remainingRows > 0)
	MPI_Bcast(&dt.z[rowIndex],remainingRows,MPI_DOUBLE,ntasks-1,MPI_COMM_WORLD);
	
	*Dt = dt;

}

void compute4(divideattr* dattr) {
	Data dt = dattr->dt;
	int lb, ub, i, e, idx;
	lb = dattr->lb;
	ub = dattr->ub;
	int rowindex, numRows;
	numRows = global_N / ntasks;
	rowindex = taskid * numRows;
	dattr->rnorm = 0;
	int num, prevnum;
	for (i = lb; i < ub; i++) {

		dt.r[i - rowindex] = 0;

		for (e = 0; e < dt.rowstr[i].num; e++) {
			idx = dt.rowstr[i].colidx[e];
			dt.r[i - rowindex] += dt.A[i][e] * dt.z[dt.rowstr[i].colidx[e]];

		}

		dt.r[i - rowindex] = dt.x[i - rowindex] - dt.r[i - rowindex];
		dattr->rnorm += dt.r[i - rowindex] * dt.r[i - rowindex];
	}

}

void combineComputation4(Data* Dt, divideattr dattr) {
	Data dt = *Dt;

	int count = 1;

	int dest = 0;

	
	MPI_Reduce(&dattr.rnorm, &dt.rnorm, count, MPI_DOUBLE, MPI_SUM, dest,
			MPI_COMM_WORLD);


	if (taskid == dest) {
		//printf("Before %lf \n ",dt.rnorm);
		dt.rnorm = sqrt(dt.rnorm);
		//printf("After %lf \n ",dt.rnorm);
	}

	*Dt = dt;

}

void compute5(divideattr* dattr) {
	Data dt = dattr->dt;
	int lb, ub, i;
	lb = dattr->lb;
	ub = dattr->ub;
	int rowindex;
	rowindex = taskid * (global_N / ntasks);
	dattr->norm_temp11 = 0;
	dattr->norm_temp12 = 0;
	for (i = lb; i < ub; i++) {

		dattr->norm_temp11 += dt.x[i - rowindex] * dt.z[i];
		dattr->norm_temp12 += dt.z[i] * dt.z[i];

	}
}

void combineComputation5(Data* Dt, divideattr dattr) {
	Data dt = *Dt;

	int count = 1;

	int dest = 0;

	dt.norm_temp11 = 0;
	dt.norm_temp12 = 0;
	MPI_Reduce(&dattr.norm_temp11, &dt.norm_temp11, count, MPI_DOUBLE, MPI_SUM,
			dest, MPI_COMM_WORLD);
	MPI_Reduce(&dattr.norm_temp12, &dt.norm_temp12, count, MPI_DOUBLE, MPI_SUM,
			dest, MPI_COMM_WORLD);

	if (taskid == dest) {
		dt.norm_temp12 = (1.0 / sqrt(dt.norm_temp12));

		dt.zeta = shift + (1.0 / dt.norm_temp11);
	}

	MPI_Bcast(&dt.norm_temp12, 1, MPI_DOUBLE, dest, MPI_COMM_WORLD);
	*Dt = dt;

}

void compute6(divideattr* dattr) {
	Data dt = dattr->dt;
	int lb, ub, i;
	lb = dattr->lb;
	ub = dattr->ub;
	int rowindex;
	rowindex = taskid * (global_N / ntasks);

	for (i = lb; i < ub; i++) {

		dt.x[i - rowindex] = dt.norm_temp12 * dt.z[i];
	}
}

void* divide(void *d) {
	divideattr *dattr;
	dattr = (divideattr*) d;

	//printf("Rank = %d lb = %d ub = %d \n",taskid,dattr->lb,dattr->ub);
	if (dattr->ub - dattr->lb > leafmaxcol) {

		pthread_t d1, d2;
		pthread_attr_t attr;
		pthread_attr_init(&attr);

		divideattr dattr1;
		dattr1.lb = dattr->lb;
		dattr1.ub = (dattr->lb + dattr->ub) / 2;
		dattr1.rr = 0;
		dattr1.pAp = 0;
		dattr1.g = 0;
		dattr1.dt = dattr->dt;
		dattr1.mode = dattr->mode;

		pthread_create(&d1, &attr, divide, (void*) &dattr1);

		divideattr dattr2;
		dattr2.lb = (dattr->lb + dattr->ub) / 2;
		dattr2.ub = dattr->ub;
		dattr2.rr = 0;
		dattr2.pAp = 0;
		dattr2.g = 0;
		dattr2.dt = dattr->dt;
		dattr2.mode = dattr->mode;

		pthread_create(&d2, &attr, divide, (void*) &dattr2);

		pthread_join(d1, NULL);
		pthread_join(d2, NULL);

		//Combine two spawns results
		switch (dattr->mode) {
		case READ:
			break;

		case INIT1:
			break;
		case INIT2:
			break;
		case COMP1: {
			dattr->rr = dattr1.rr + dattr2.rr;
			dattr->pAp = dattr1.pAp + dattr2.pAp;
			break;
		}
		case COMP2: {
			dattr->g = dattr1.g + dattr2.g;
			break;

		}
		case COMP3:
			break;
		case COMP4: {
			dattr->rnorm = dattr1.rnorm + dattr2.rnorm;
			break;
		}
		case COMP5: {
			dattr->norm_temp11 = dattr1.norm_temp11 + dattr2.norm_temp11;
			dattr->norm_temp12 = dattr1.norm_temp12 + dattr2.norm_temp12;
			break;
		}
		case COMP6:
			break;
		}
		return 0;

	} else {
		switch (dattr->mode) {
		case READ: {
			readandinitializeData(dattr);
			break;
		}
		case INIT1: {
			initialize1(dattr);
			break;
		}
		case INIT2: {
			initialize_conj_grad(dattr);
			break;
		}
		case COMP1: {
			compute1(dattr);
			break;
		}
		case COMP2: {
			compute2(dattr);
			break;
		}
		case COMP3: {
			compute3(dattr);
			break;
		}

		case COMP4: {
			compute4(dattr);
			break;
		}
		case COMP5: {
			compute5(dattr);
			break;
		}
		case COMP6: {
			compute6(dattr);
			break;
		}

		}
		return 0;

	}

}

void conj_grad(Data* dt) {
	int cgit, cgitmax ;
	if(global_N < 25)
		cgitmax = global_N;
	else
		cgitmax = 25;
	divideattr dattr;
	pthread_t dit;

	pthread_attr_t attr;
	pthread_attr_init(&attr);

	dattr.lb = lb;
	dattr.ub = ub;
	dattr.dt = *dt;
	dattr.mode = INIT2;

	pthread_create(&dit, &attr, divide, (void*) &dattr);
	pthread_join(dit, NULL);
	MPI_Barrier(MPI_COMM_WORLD);
	combineinitialize_conj_grad(dt);

	for (cgit = 1; cgit <= cgitmax; cgit++) {
		dattr.lb = lb;
		dattr.ub = ub;
		dattr.dt = *dt;
		dattr.mode = COMP1;

		pthread_create(&dit, &attr, divide, (void*) &dattr);
		pthread_join(dit, NULL);
		MPI_Barrier(MPI_COMM_WORLD);
		combineComputation1(dt, dattr);

		dattr.lb = lb;
		dattr.ub = ub;
		dattr.dt = *dt;
		dattr.mode = COMP2;
		//		printf("Rank = %d \t dattr.dr.RR = %f \n",taskid,dattr.dt.RR);
		pthread_create(&dit, &attr, divide, (void*) &dattr);
		pthread_join(dit, NULL);
		MPI_Barrier(MPI_COMM_WORLD);
		combineComputation2(dt, dattr);

		dattr.lb = lb;
		dattr.ub = ub;
		dattr.dt = *dt;
		dattr.mode = COMP3;

		pthread_create(&dit, &attr, divide, (void*) &dattr);
		pthread_join(dit, NULL);
		MPI_Barrier(MPI_COMM_WORLD);
		combineComputation3(dt);

	}

	combinecgiterations(dt);
	dattr.lb = lb;
	dattr.ub = ub;
	dattr.dt = *dt;
	dattr.mode = COMP4;

	pthread_create(&dit, &attr, divide, (void*) &dattr);
	pthread_join(dit, NULL);
	MPI_Barrier(MPI_COMM_WORLD);
	combineComputation4(dt, dattr);

}

void conjugateGradient() {
	Data dt;
	allocateinitial(&dt);

	lb = (taskid) * (global_N / ntasks);
	if (taskid < (ntasks - 1))
		ub = (taskid + 1) * (global_N / ntasks);
	else
		ub = global_N;
//	printf("Rank =%d lb = %d ub = %d global_N = %d ntasks = %d \n",taskid,lb,ub,global_N,ntasks);
	divideattr dattr;
	pthread_t dit;

	pthread_attr_t attr;
	pthread_attr_init(&attr);

	dattr.lb = lb;
	dattr.ub = ub;
	dattr.dt = dt;
	dattr.mode = READ;
	
//	printf("Taskid = %d lb = %d ub = %d \n",taskid,lb,ub);
	pthread_create(&dit, &attr, divide, (void*) &dattr);
	pthread_join(dit, NULL);
	
/*	if(taskid == 0)
		printf("FILE READING COMPLETED\n");*/

	mpi_elapsed = MPI_Wtime();
	dattr.lb = lb;
	dattr.ub = ub;
	dattr.dt = dt;
	dattr.mode = INIT1;

	pthread_create(&dit, &attr, divide, (void*) &dattr);
	pthread_join(dit, NULL);
/*	if(taskid == 0)
		printf("INIT1 COMPLETED\n");*/

	dt.zeta = 0;
	conj_grad(&dt);

	dattr.lb = lb;
	dattr.ub = ub;
	dattr.dt = dt;
	dattr.mode = COMP5;

	pthread_create(&dit, &attr, divide, (void*) &dattr);
	pthread_join(dit, NULL);
	MPI_Barrier(MPI_COMM_WORLD);
	combineComputation5(&dt, dattr);


	dattr.lb = lb;
	dattr.ub = ub;
	dattr.dt = dt;
	dattr.mode = COMP6;

	pthread_create(&dit, &attr, divide, (void*) &dattr);
	pthread_join(dit, NULL);

	dattr.lb = lb;
	dattr.ub = ub;
	dattr.dt = dt;
	dattr.mode = INIT1;

	pthread_create(&dit, &attr, divide, (void*) &dattr);
	pthread_join(dit, NULL);

	dt.zeta = 0;
	int it;
	for (it = 1; it <= niter; it++) {
		conj_grad(&dt);

		dattr.lb = lb;
		dattr.ub = ub;
		dattr.dt = dt;
		dattr.mode = COMP5;

		pthread_create(&dit, &attr, divide, (void*) &dattr);
		pthread_join(dit, NULL);
		MPI_Barrier(MPI_COMM_WORLD);
		combineComputation5(&dt, dattr);

		dattr.lb = lb;
		dattr.ub = ub;
		dattr.dt = dt;
		dattr.mode = COMP6;

		pthread_create(&dit, &attr, divide, (void*) &dattr);
		pthread_join(dit, NULL);
		if (taskid == 0) {

			if (it == 1) {
				printf("   iteration           ||r||                 zeta\n");
			}
		printf("    %5d       %20.14e%20.13e\n", it, dt.rnorm, dt.zeta);
		} /* end master */

	}

	if (taskid == 0) {
		printf(" Benchmark completed\n");

		epsilon = 1.0e-10;
		if (cls != 'U') {
			if (fabs(dt.zeta - zeta_verify_value) <= epsilon) {
				verified = TRUE;
				printf(" VERIFICATION SUCCESSFUL\n");
				printf(" Zeta is    %20.12e\n", dt.zeta);
				printf(" Error is   %20.12e\n", dt.zeta - zeta_verify_value);
			} else {
				verified = FALSE;
				printf(" VERIFICATION FAILED\n");
				printf(" Zeta                %20.12e\n", dt.zeta);
				printf(" The correct zeta is %20.12e\n", zeta_verify_value);
			}
		} else {
			verified = FALSE;
			printf(" Problem size unknown\n");
			printf(" NO VERIFICATION PERFORMED\n");
		}

	}

	mpi_elapsed = MPI_Wtime() - mpi_elapsed;


}

int main(int argc, char* argv[]) {

	/* Pick problem size on the command line */
	MPI_Init(&argc, &argv); // MPI Initialization
	MPI_Comm_size(MPI_COMM_WORLD, &ntasks); // Determining total number of process
	MPI_Comm_rank(MPI_COMM_WORLD, &taskid); // Determining my rank of taskid


	strcpy(dirpath, "data/class");
	leafmaxcol = 10;

	cls = 'S';
	setup_for_benchmark(cls);

//	printf("taskid = %d global_N = %d \n",taskid,global_N);
	dirpath[10] = cls;
	dirpath[11] = '/';
	dirpath[12] = '\0';

	conjugateGradient();

	printf("\n cg : Total time taken = %f sec \n", mpi_elapsed);
	printf("Options: granularity = %d\n", leafmaxcol);
	MPI_Barrier(MPI_COMM_WORLD);

	MPI_Finalize();
	return 0;
}

