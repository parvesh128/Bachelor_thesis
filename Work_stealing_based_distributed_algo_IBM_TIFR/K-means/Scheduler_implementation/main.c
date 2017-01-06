//#include"Sched.h"
#include"kmeans.h"
#include<pthread.h>
//#include<dcmf.h>

static double seconds_per_cycle = 1.0 / 850000000.0; //8850 MHz default


#define WTIME(TB) TB = 0 //DCMF_Timebase()
#define TCONV_SEC(TB1,TB2) seconds_per_cycle*((double) (TB1 - TB2))
#define TCONV_SEC_ONLY(TB1) seconds_per_cycle * (double) (TB1)
#define TCONV_CYCLES(TB1,TB2) (TB1 - TB2)

int main(int argc, char *argv[]) {

	MPI_Init(&argc, &argv); // MPI Initialization
	MPI_Comm_size(MPI_COMM_WORLD, &ntasks); // Determining total number of process
	MPI_Comm_rank(MPI_COMM_WORLD, &taskid); // Determining my rank of taskid

	int i, j;

	/*if(argc != 1)
	 {
	 printf("Error Usage: ./heat\n");
	 exit(0);
	 }*/

	//printf("\nBy default affinity for all thread is Place 1\n\n");
	//printf("Enter the number of workers\n");
	//scanf("%d",&nop);

	nop = 2;
	ws = ntasks;
	if (taskid == 0)
		printf("The number of Places : %d\n", ntasks);

	if (taskid == 0)
		printf("The number of workers : %d\n", nop);

	numRows = 20480;
	numCols = NOOFCOLS;
	numCent = NOOFCENTROIDS;
	leafmaxcol = 200;
	NUMIT = 10;
	//dp = "movie1/";
	dp="/gpfs/DDNgpfs1/nagapkat/Clustering_SMP/train_set2/";
	limit = 100000;
	//factlimit();
	//printf("limit = %d\n", limit);

	/*local_dt.x = (float **) calloc(numRows, sizeof(float *));
	 local_dt.dist = (float **) calloc(numRows, sizeof(float *));
	 local_dt.bestCent = (int *) calloc(numRows, sizeof(int));
	 local_dt.rowstr = (Rowstr*) calloc(numRows, sizeof(Rowstr));
	 */
	pthread_mutex_init(&tid_lock, NULL);
	pthread_mutex_init(&cent_lock, NULL);
	pthread_mutex_init(&cent_lock2, NULL);
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

	intialize_kmeans_variable();
	MPI_Barrier(MPI_COMM_WORLD);

	// Populate all Places
	createworkers(taskid);

	// create thread to handle remote node services


	// Initializing Jobs threads
	if (taskid == 0) {

		struct jobinfo *new_job;
		new_job = createJob(NULL);
		new_job->entry_point = 0;
		new_job->rv0.flag = false;
		new_job->rv1.flag = false;

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


	start_time =  readstart_time = MPI_Wtime();
	//printf("Wait started Place %d\n", taskid);

	pthread_cond_wait(&end_cond, &end_lock);

	//printf("Wait ended Place %d\n", taskid);
	//WTIME(end_time);
	end_time = MPI_Wtime();
	if (taskid == 0)
		printf("Total Time taken = %f\n", (end_time - start_time- readtime));

	MPI_Barrier(MPI_COMM_WORLD);
	int no_of_workers = nop - 1;
	if (ws > 1)
		no_of_workers++;

	for (i = 0; i <= no_of_workers; i++) {
		printf("killing worker id %d \n", i);
		pthread_cancel(worker[i]->wid);

	}

	MPI_Finalize();

}
