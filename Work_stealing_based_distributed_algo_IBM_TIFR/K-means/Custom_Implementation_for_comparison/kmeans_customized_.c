/*
 * k-means.c
 *
 *  Created on: 29-Apr-2011
 *      Author: parvesh
 */

#define BIGNUM 1.0e12

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include<mpi.h>
#include <sys/times.h>
#include<pthread.h>
#define ALLC       0
#define INIT       1
#define COMP       2
#define NUMCOLS    943
#define NUMCENTROIDS 10
#define randa(y,t) (exp(-2*(t))*sin(y))
#define randb(y,t) (exp(-2*(t))*sin(y+1))

int lb, ub;
int numRowsPerPlace;
int numRows, numCols, numCent, NUMIT, limit;
int ntasks, taskid;
int leafmaxcol;
char* dirpath;
typedef enum {
	FALSE = 0, TRUE
} boolean;
double mpi_elapsed;

typedef struct {
	int* colidx; // indexex of non zero columns
	int num; // No. of non zero columns
} Rowstr;

typedef struct {
	float** x;
	Rowstr* rowstr; // For Storing the index of non zero cols at each row

	float **cent;
	short *bestCent;

} Data;

typedef struct {
	int mode;
	int lb;
	int ub;
	Data dt;
	float **cent_rv; //Array for holding sum of different dimensions for the recomputation for a centroid
	int **totalpts; //Array for holding total no. of points near to a centroid
	float *mean; //Mean for every Attribute based on data points
	int *tp;//FOR CALCULATING MEAN
} divideattr;

int Random(int window) {
	return (int) (random() % window);
}

void factlimit() {
	int i, j, k;
	j = 10;
	i = numRows / j;
	while (i >= 10) {
		j *= 10;
		i = numRows / j;
	}

	limit = j;

}

void appendZeros(char* filename, int row) {

	int temp;
	long fact = limit;
	temp = (row + 1) / fact;

	while (temp == 0) {
		strcat(filename, "0");
		fact = fact / 10;
		temp = (row + 1) / fact;
	}
}

void readandinitializeDataPoints(divideattr* dattr) {
	Data dt = dattr->dt;
	int j;

	int lb, ub, i, col, idx;
	lb = dattr->lb;
	ub = dattr->ub;
	char filename[15], t[15];
	int fact = 10, temp, filelength;
	int* tempcolidx;
	float* tempX;
	tempcolidx = (int*) calloc(numCols, sizeof(int));
	tempX = (float*) calloc(numCols, sizeof(float));
	FILE* fp;

	dattr->mean = (float *) calloc(numCols, sizeof(float));
	dattr->tp = (int *) calloc(numCols, sizeof(int));
	for (i = 0; i < numCols; i++) {
		dattr->mean[i] = 0;
		dattr->tp[i] = 0;
	}

	for (i = lb; i < ub; i++) {
		filelength = 0;

		sprintf(t, "%d", i + 1);
		strcpy(filename, dirpath);

		appendZeros(filename, i);

		strcat(filename, t);

		strcat(filename, ".txt");

		//printf("%s \n",filename);


		fp = fopen(filename, "r");

		while (fscanf(fp, "%d %f\n", &tempcolidx[filelength],
				&tempX[filelength]) != EOF) {

			tempcolidx[filelength]--;
			filelength++;

		}

		fclose(fp);

		dt.rowstr[i].num = filelength;
		dt.x[i] = (float *) calloc(filelength, sizeof(float));
		dt.rowstr[i].colidx = (int*) calloc(filelength, sizeof(int));

		for (j = 0; j < filelength; j++) {
			dt.x[i][j] = tempX[j];
			dt.rowstr[i].colidx[j] = tempcolidx[j];

			dattr->mean[tempcolidx[j]] += dt.x[i][j];
			dattr->tp[tempcolidx[j]]++;

		}



	}
	/*if(taskid==0)
		printf("Completed file reading\n");*/
	free(tempX);
	free(tempcolidx);

}

void initializeCentroids(Data* Dt) {

	int j;
	Data dt = *Dt;
	if (taskid == 0) {

		int k;
		/* read in centroid labels and data points */
		for (j = 0; j < numCent; j++) {

			/* then read in data values */
			for (k = 0; k < numCols; k++) {
				dt.cent[j][k] = randb(j,k);
			}

		}

	}

	for (j = 0; j < numCent; j++) {
		MPI_Bcast(dt.cent[j], numCols, MPI_FLOAT, 0, MPI_COMM_WORLD);
	}

}

void computekMeans(divideattr* dattr) {
	Data dt = dattr->dt;
	int lb = dattr->lb;
	int ub = dattr->ub;

	int j, l;
	short k;

	// calculate distance matrix and minimum
	float rMin;
	double dist;
	//dt.distortion[it] = 0;


	for (j = lb; j < ub; j++) {
		rMin = BIGNUM;

		for (k = 0; k < numCent; k++) {
			int e, idx;
			dist = 0;

			for (e = 0; e < dt.rowstr[j].num; e++) {
				idx = dt.rowstr[j].colidx[e];
				dist += (dt.x[j][e] - dt.cent[k][idx]) * (dt.x[j][e]
						- dt.cent[k][idx]);

			}
			if (dist < rMin) {
				dt.bestCent[j] = k;
				rMin = dist;
			}
		}

	}

	// reestimate centroids
	int idx;
	dattr->cent_rv = (float **) calloc(numCent, sizeof(float*));
	dattr->totalpts = (int**) calloc(numCent, sizeof(int*));

	for (k = 0; k < numCent; k++) {
		dattr->cent_rv[k] = (float*) calloc(numCols, sizeof(float));
		dattr->totalpts[k] = (int*) calloc(numCols, sizeof(int));
		int e;
		for (e = 0; e < numCols; e++) {
			dattr->cent_rv[k][e] = 0;
			dattr->totalpts[k][e] = 0;
		}

		for (j = lb; j < ub; j++) {
			if (dt.bestCent[j] == k) {

				for (e = 0; e < dt.rowstr[j].num; e++) {
					idx = dt.rowstr[j].colidx[e];
					dattr->cent_rv[k][idx] += dt.x[j][e];
					dattr->totalpts[k][idx]++;
				}
			}
		}

	}

}

void combineMeanValues(divideattr dattr1, divideattr dattr2, divideattr* dattr) {

	int k;
	dattr->mean = (float*) calloc(numCols, sizeof(float));
	dattr->tp = (int*) calloc(numCols, sizeof(int));
	for (k = 0; k < numCols; k++) {

		dattr->mean[k] = dattr1.mean[k] + dattr2.mean[k];
		dattr->tp[k] = dattr1.tp[k] + dattr2.tp[k];
	}

	free(dattr1.mean);
	free(dattr2.mean);
	free(dattr1.tp);
	free(dattr2.tp);

}

void combineCentroidValues(divideattr dattr1, divideattr dattr2,
		divideattr* dattr) {
	int k, e;

	dattr->cent_rv = (float**) calloc(numCent, sizeof(float*));
	dattr->totalpts = (int**) calloc(numCent, sizeof(int*));

	for (k = 0; k < numCent; k++) {
		dattr->cent_rv[k] = (float*) calloc(numCols, sizeof(float));
		dattr->totalpts[k] = (int*) calloc(numCols, sizeof(int));
		for (e = 0; e < numCols; e++) {

			dattr->cent_rv[k][e] = dattr1.cent_rv[k][e] + dattr2.cent_rv[k][e];
			dattr->totalpts[k][e] = dattr1.totalpts[k][e]
					+ dattr2.totalpts[k][e];
		}
		free(dattr1.cent_rv[k]);
		free(dattr2.cent_rv[k]);
		free(dattr1.totalpts[k]);
		free(dattr2.totalpts[k]);

	}
	free(dattr1.cent_rv);
	free(dattr2.cent_rv);
	free(dattr1.totalpts);
	free(dattr2.totalpts);

}

void combineSpawnResults(divideattr dattr1, divideattr dattr2,
		divideattr* dattr) {

	switch (dattr->mode) {
	/*case ALLC: {
	 break;
	 }*/
	case INIT: {

		combineMeanValues(dattr1, dattr2, dattr);
		break;
	}
	case COMP: {
		combineCentroidValues(dattr1, dattr2, dattr);

		break;
	}
	}

}

void printResults(Data dt) {

	int lb = taskid * (numRows / ntasks);
	int ub = (taskid + 1) * (numRows / ntasks);
	int j, k;
	/* write clusters to screen */
	printf("Results Rank %d\n=======\n\n", taskid);
	for (k = 0; k < numCent; k++) {
		printf("\nCluster %d\n=========\n", k);
		for (j = lb; j < ub; j++) {
			if (dt.bestCent[j] == k)
				printf("Node%d\n", j);
		}
	}
}

void* divide(void *d) {
	divideattr *dattr;
	dattr = (divideattr*) d;

	if (dattr->ub - dattr->lb > leafmaxcol) {

		pthread_t d1, d2;
		pthread_attr_t attr;
		pthread_attr_init(&attr);

		divideattr dattr1;
		dattr1.lb = dattr->lb;
		dattr1.ub = (dattr->lb + dattr->ub) / 2;

		dattr1.dt = dattr->dt;
		dattr1.mode = dattr->mode;

		pthread_create(&d1, &attr, divide, (void*) &dattr1);

		divideattr dattr2;
		dattr2.lb = (dattr->lb + dattr->ub) / 2;
		dattr2.ub = dattr->ub;

		dattr2.dt = dattr->dt;
		dattr2.mode = dattr->mode;

		pthread_create(&d2, &attr, divide, (void*) &dattr2);

		pthread_join(d1, NULL);
		pthread_join(d2, NULL);

		//Combine two spawns results

		combineSpawnResults(dattr1, dattr2, dattr);
	} else {
		switch (dattr->mode) {

		/*case ALLC: {
		 allocateDataPoints(dattr);
		 break;
		 }*/
		case INIT: {
			readandinitializeDataPoints(dattr);
			break;
		}
		case COMP: {
			computekMeans(dattr);
			break;
		}
		}

	}

}

void k_means() {

	Data dt;

	/* allocate memory */

	lb = taskid * (numRows / ntasks);

	if (taskid < (ntasks - 1))
		ub = (taskid + 1) * (numRows / ntasks);
	else
		ub = numRows;

	numRowsPerPlace = ub - lb;

	dt.x = (float **) calloc(numRows, sizeof(float *));
	dt.rowstr = (Rowstr*) calloc(numRows, sizeof(Rowstr));
	dt.bestCent = (short *) calloc(numRows, sizeof(short));

	int j;

	dt.cent = (float **) calloc(numCent, sizeof(float *));

	for (j = 0; j < numCent; j++) {
		dt.cent[j] = (float *) calloc(numCols, sizeof(float));

	}

	pthread_t dit;
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	divideattr dattr;
	dattr.lb = lb;
	dattr.ub = ub;
	dattr.dt = dt;
	dattr.mode = INIT;

	//Read from file ,allocate and initialize data values

	pthread_create(&dit, &attr, divide, (void*) &dattr);
	pthread_join(dit, NULL);

	initializeCentroids(&dt);
	MPI_Barrier(MPI_COMM_WORLD);

	mpi_elapsed = MPI_Wtime();

	//Computation of K-means
	int it;
	float *sum = (float*) calloc(NUMCOLS, sizeof(float));
	int *totalpts = (int*) calloc(NUMCOLS, sizeof(int));
	float *mean = (float*) calloc(NUMCOLS, sizeof(float));
	int *tp = (int*) calloc(NUMCOLS, sizeof(int));

	for (it = 0; it < NUMIT; it++) {

		dattr.lb = lb;
		dattr.ub = ub;
		dattr.dt = dt;
		dattr.mode = COMP;

		pthread_create(&dit, &attr, divide, (void*) &dattr);

		pthread_join(dit, NULL);

		int i;
		MPI_Barrier(MPI_COMM_WORLD);

		MPI_Allreduce(dattr.mean, mean, numCols, MPI_FLOAT, MPI_SUM,
				MPI_COMM_WORLD);

		MPI_Allreduce(dattr.tp, tp, numCols, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
		for (i = 0; i < numCent; i++) {
			MPI_Allreduce(dattr.totalpts[i], totalpts, numCols, MPI_INT,
					MPI_SUM, MPI_COMM_WORLD);
			MPI_Allreduce(dattr.cent_rv[i], sum, numCols, MPI_FLOAT, MPI_SUM,
					MPI_COMM_WORLD);
			int e;
			for (e = 0; e < numCols; e++) {
				mean[e] = mean[e] / tp[e];
				if (totalpts[e] > 0) {
					(dt).cent[i][e] = (sum[e]) / (totalpts[e]);
				} else {
					(dt).cent[i][e] = mean[e];
				}
			}

		}

		if(taskid == 0)
		printf("Completed %d Iteration \n", it+1);

	}

	int k;
		for(k=0;k<numCent;k++){
			free(dattr.cent_rv[k]);
			free(dattr.totalpts[k]);
		}
		free(dattr.cent_rv);
		free(dattr.totalpts);
		

	mpi_elapsed = MPI_Wtime() - mpi_elapsed;
	//printResults(dt);

}

int main(int argc, char *argv[]) {

	numRows = 1682;
	numCols = NUMCOLS;
	numCent = NUMCENTROIDS;
	leafmaxcol = 25;
	NUMIT = 10;
	limit = 1000;
	dirpath = "movie1/";
	MPI_Init(&argc, &argv); // MPI Initialization
	MPI_Comm_size(MPI_COMM_WORLD, &ntasks); // Determining total number of process
	MPI_Comm_rank(MPI_COMM_WORLD, &taskid); // Determining my rank of taskid

	//	factlimit();

	k_means();

	printf("\n K-Means : Total time taken = %f sec \n", mpi_elapsed);
	printf("Options: granularity = %d\n", leafmaxcol);
	MPI_Barrier(MPI_COMM_WORLD);

	MPI_Finalize();
	return (0);
}



