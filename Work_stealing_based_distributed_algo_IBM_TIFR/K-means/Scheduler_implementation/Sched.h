#ifndef SCHED_H_
#define SCHED_H_

#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/sysinfo.h>
#include<sys/mman.h>
#include<unistd.h>
#include<sched.h>
#include<ctype.h>
#include<string.h>
#include<time.h>
#include<pthread.h>
#include<mpi.h>
#include<stdbool.h>
#define ALLC       0
#define INIT       1
#define COMP       2
#define NOOFCENTROIDS 20
#define NOOFCOLS 17770
// VARIABLES USED IN K-MEANS APPLICATION
int numRows, numCols, numCent, NUMIT;
//float sparsity, deviation, sparsitywindowlength, sparsitywindowstart;
int leafmaxcol;

int limit;
char* dp;

//**********************************


#define MAX 		100
#define TRUE 		1
#define FALSE 		0
#define READY		1
#define RUNNING		2
#define STALL		3
#define DIE			-1

typedef struct {
	int* colidx; // indexex of non zero columns
	int num; // No. of non zero columns
} Rowstr;

typedef struct { //Structure for storing Data for k-means application
	float** x;
	Rowstr* rowstr; // For Storing the index and total no. of non zero cols at each row
	short *bestCent;
	float** cent;
} Data;

typedef struct { //Structure for storing return values after each spawn
	float **cent_rv; //Array for holding sum of different dimensions for the recomputation for a centroid
	int **totalpts; //Array for holding total no. of points near to a centroid
	float *mean; //Mean for every Attribute based on data points
	int *tp;
	bool flag; // flag = 0 means not initialized and flag = 1 mean initialized
} Retval;

struct jobinfo {
	int jobid;
	int parent_jobid;
	int child_jobid[2];
	int no_child_job;
	int latest_worker; //last worker on which this thread was in running state
	int state;
	int is_attached;
	int no_active_children;
	pthread_mutex_t job_state_lock;
	int flag;
	int place; //place where it is suppose to run
	int parent_place;
	struct jobinfo *next;
	struct jobinfo *previous;

	//K-means application attributes
	int lb;
	int ub;
	Data dta;
	Retval rv0;
	Retval rv1;
	//	int flag[2];
	int counter;
	int c;
	int entry_point;
	int mode;

/*********************************************************/

};

typedef struct {
	float mean[NOOFCOLS]; //Mean for every Attribute based on data points
	int tp[NOOFCOLS]; //Total points for every dimension for calculating mean

} meandata;

typedef struct {
	float cent_rv[NOOFCENTROIDS][NOOFCOLS]; //Array for holding sum of different dimensions for the recomputation for a centroid

	int totalpts[NOOFCENTROIDS][NOOFCOLS]; //Array for holding total no. of points near to a centroid

} centroiddata;

typedef union {
	meandata mean_dt;
	centroiddata cent_dt;
	float cent[NOOFCENTROIDS][NOOFCOLS];

} commdata;

typedef struct {
	commdata cd;
	struct jobinfo job;
} commdatainfo;

//3. It represents the queue associated with each processor
struct queue_t {
	int num;
	struct jobinfo *head;
	struct jobinfo *tail;
	pthread_mutex_t t_lock; // queue lock used either for enqueing or dequeing it (tail lock);
};

struct queue_t *fab;
struct queue_t *remote_spawns;
struct queue_t *remote_enable;

/************************************/

//4. It represents the worker information 
struct workerinfo {
	int id; //id number of the worker
	int place; //represents to which place it belongs
	pthread_t wid;
	struct jobinfo *ptr2job; //points to the thread currently run by this processor(NULL otherwise)
	struct queue_t *ptr2q; //points to its own queue
	struct queue_t *ptr2fab; //points to its own fab
	struct dependency *ptr2data;
	int state1;
	int amountwork;
	int wsatt;
	int wssuc;
	int fab_steal_attempt;
	int fab_steal_succ;
	clock_t time;
	struct timespec clk_work_time;
	struct timespec clk_steal_time;
	struct timespec clk_fab_steal_time;
	struct timespec clk_comp_time;

}*worker[MAX];

struct workerinfo *communicator;

/***********************************/

//5. It represents work function's parameter
struct workerattr {
	int n;
	struct workerinfo *winfo;
};

/***********************************/

//6. It represents the stack for each thread 
struct stack {
	struct jobinfo *n;
	struct stack *next;
};
/*****************************************/

/*FUNCTIONS USED IN SCHEDULAR*/
void createworkers(int);
//void Common_Memory_Pool();
struct jobinfo *createJob(struct jobinfo *pi);
void local_enable(struct jobinfo* job, struct jobinfo* parent_job);
void *work(void *wattr);
int work_stealing_schedular(struct workerattr* wattr);
void workstealing(int, int);
void remotespawn(struct jobinfo *, int *);
void enqueue(struct jobinfo *, struct queue_t*);
void enabling(struct jobinfo *, struct queue_t*);
void enqueue_top(struct jobinfo *, struct queue_t*);
int deque(struct workerattr* input, struct queue_t *);
int deque_bottom(struct workerattr* input, struct queue_t *);
void application_work(struct workerinfo*);
struct timespec diff_time(struct timespec end, struct timespec start);
int calculate_choice(int, int, int);

//Both functions below are used when synchronization(sync) is to done
void push(struct jobinfo *, struct jobinfo*);
void pop(struct jobinfo *);
void *comm_work(void *);

/****************************/

/*VARIABLES USED IN SCHEDULAR*/
int taskid, ntasks;
int nop;
int ws;
long tid;
struct workerattr *wattr[MAX];
pthread_mutex_t cent_lock;
pthread_mutex_t cent_lock2;
pthread_mutex_t tid_lock;
pthread_mutex_t end_lock;
pthread_cond_t end_cond;
int start;
int end;
unsigned int seed;
clock_t t_time;
clock_t s_time;
int s;
int timer_flag;
//int choice[100000];
struct jobinfo job[4000];
int iterator;
Data local_dt;
int size;

//struct jobinfo *global_memory_head;
struct timespec time_1, time_2, time_sleep;
/****************************/

#endif /* SCHED_H_ */

