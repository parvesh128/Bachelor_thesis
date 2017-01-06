//#include"cg.c"
#include"cg.h"

//#include<dcmf.h>

static double seconds_per_cycle = 1.0 / 850000000.0; //8850 MHz default


#define WTIME(TB) TB = 0 //DCMF_Timebase()
#define TCONV_SEC(TB1,TB2) seconds_per_cycle*((double) (TB1 - TB2))
#define TCONV_SEC_ONLY(TB1) seconds_per_cycle * (double) (TB1)
#define TCONV_CYCLES(TB1,TB2) (TB1 - TB2)

int makea(int n, long nz, double* A, int* colidx, int* rowstr, int nonzer,
		int firstrow, int lastrow, int firstcol, int lastcol, double rcond,
		double shift);
void printa(int n, long nz, double* A, int* colidx, int* rowstr, FILE* file);

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
		niter = 5;
	}
}

int main(int argc, char *argv[]) {

	MPI_Init(&argc, &argv); // MPI Initialization
	MPI_Comm_size(MPI_COMM_WORLD, &ntasks); // Determining total number of process
	MPI_Comm_rank(MPI_COMM_WORLD, &taskid); // Determining my rank of taskid

	int i, j;

	nop = 1;
	ws = ntasks;
	if (taskid == 0)
		printf("The number of Places : %d\n", ntasks);

	if (taskid == 0)
		printf("The number of workers : %d\n", nop);

	strcpy(dirpath, "data/class");
	leafmaxcol = 50;
	cls = 'B';

	setup_for_benchmark(cls);

	dirpath[10] = cls;
	dirpath[11] = '/';
	dirpath[12] = '\0';

	pthread_mutex_init(&tid_lock, NULL);

	//pthread_mutex_init(&jobsend_lock, NULL);
	//pthread_mutex_init(&jobrecv_lock, NULL);
	//pthread_mutex_init(&send_q->lock,NULL);

	tid = 1;
	end = 1;
	start = 2;
	//jobsend_count = 1;
	//jobrecv_count = 1;

	iterator = -1;
	//time_sleep.tv_sec = 0;
	//time_sleep.tv_nsec = 10;


	allocateinitial(&local_dt);

	//MPI_Barrier(MPI_COMM_WORLD);

	// Populate all Places
	createworkers(taskid);

	// create thread to handle remote node services


	if (taskid == 0) {

		struct jobinfo *new_job;
		new_job = createJob(NULL);

		new_job->entry_point = 0;
		new_job->retval[0].flag = false;
		new_job->retval[1].flag = false;

		// Assigning job to worker and changing state to Ready
		worker[0]->ptr2job = new_job;
		worker[0]->state1 = READY;
	}

	////////////////////////////

	// Start time measurement on the manager
	start = 0;

	//Put timer


	// Setting Zeroth worker as dedicated worker for main
	/*cpu_set_t mask;
	 CPU_ZERO(&mask);
	 CPU_SET(0,&mask);

	 pthread_attr_t attr;
	 pthread_getattr_np(pthread_self(),&attr);

	 if(pthread_attr_setaffinity_np(&attr,sizeof(mask),&mask ) == -1 )
	 {
	 perror("Failed because");
	 printf("WARNING: Could not set CPU Affinity, continuing...\n");
	 }*/

	/**********************************************************************/
	//end_lock = PTHREAD_MUTEX_INITIALIZER;
	//end_cond = PTHREAD_COND_INITIALIZER;
	double start_time, end_time;
	//WTIME(start_time);
	start_time = readstart_time = MPI_Wtime();
	pthread_cond_wait(&end_cond, &end_lock);
	//WTIME(end_time);
	end_time = MPI_Wtime();
	if (taskid == 0)
		printf("Total Time taken = %f\n", (end_time - start_time - readtime));
	int no_of_workers = nop - 1;
	if (ws > 1)
		no_of_workers++;

	for (i = 0; i <= no_of_workers; i++) {
		printf("killing process id %d\n", i);
		pthread_cancel(worker[i]->wid);
	}
	//MPI_Barrier(MPI_COMM_WORLD);

	MPI_Finalize();

}

/*void printa(int n, long nz, double* A, int* colidx, int* rowstr, FILE * file) {
 int j, k, m;
 double *arow;

 arow = (double*) malloc(sizeof(double) * n);
 assert(arow != NULL);

 fprintf(file, "rowstr=");
 for (k = 0; k <= N; k++)
 fprintf(file, "%3d", rowstr[k]);
 fprintf(file, "\n");
 fprintf(file, "colidx=");
 for (k = 0; k < nz; k++)
 fprintf(file, "%3d", colidx[k]);
 fprintf(file, "\n");
 fprintf(file, "first_row=%d\n", first_row);
 fprintf(file, "last_row=%d\n", last_row);
 fprintf(file, "A=\n");
 for (k = 0; k < nz; k++)
 fprintf(file, "%3.1g\t", A[k]);
 fprintf(file, "\n");

 j = 0;

 for (k = 0; k < n; k++) {
 if (k >= first_row && k < last_row) {
 memset(arow, 0, sizeof(double) * n);
 for (m = rowstr[k - first_row]; m < rowstr[k - first_row + 1]; m++) {
 arow[colidx[m]] = A[j];
 j++;
 }
 for (m = 0; m < n; m++) {
 fprintf(file, "%3.1g\t", arow[m]);
 } // end for m
 fprintf(file, "\n");
 } // end if

 } // end for k
 }

 */
