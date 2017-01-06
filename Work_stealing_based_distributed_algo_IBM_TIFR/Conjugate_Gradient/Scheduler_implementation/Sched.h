#ifndef SCHED_H_
#define SCHED_H_

#include <math.h>
#include <errno.h>
#include <assert.h>

#include <fcntl.h>
#include <sys/times.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/sysinfo.h>
#include<sys/mman.h>
#include<unistd.h>
//#include<sched.h>
#include<ctype.h>
#include<string.h>
#include<time.h>
#include<pthread.h>
#include<mpi.h>
#include<stdbool.h>

#define READ       0
#define INIT1      1
#define INIT2      2
#define COMP1      3
#define COMP2      4
#define COMP3      5
#define COMP4	   6
#define COMP5	   7
#define COMP6	   8
//#define cgitmax    25
// VARIABLES USED IN CG APPLICATION
int ntasks, taskid;
int leafmaxcol;
char dirpath[13];

char cls; /* problem class for the benchmark: U, S,W, A ,B or C */
int nonzer, niter;
double shift, zeta_verify_value;
int global_N;
double epsilon;


bool verified;

//**********************************


#define MAX 		100
#define TRUE 		1
#define FALSE 		0
#define READY		1
#define RUNNING		2
#define STALL		3
#define DIE		-1
#define NSIZE		75000

typedef struct {
	int* colidx; // indexex of non zero columns
	int num; // No. of non zero columns
} Rowstr;

//Structure for storing Data for CG application

typedef struct {
	double** A;
	Rowstr* rowstr;
	double** x;
	double** r;
	double** V;
	double h;
	double zeta;
	double *p;//
	double *z;//

} Data;

typedef struct { //Structure for storing return values after each spawn
	double rr; //For Storing r'r at thread level
	double pAp; //For Storing p'Ap
	double g; //For Storing g at thread level
	double rnorm;//For Storing rnorm at thread level
	double norm_temp11;//For Storing norm_temp11 at thread level
	double norm_temp12;//For Storing norm_temp12 at thread level

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
	Retval retval[2];
	Retval rv0;
	Retval rv1;
	int counter;
	int c;//Iterator for cg iterations
	int C;//Iterator for inverse power method
	int entry_point;
	int mode;

/*********************************************************/

};

typedef struct {

	double commdata[NSIZE];

	struct jobinfo job;
} commdatainfo;//For Remote enable and Remote spawn


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

//procedures correspondong to combining values at the time of enable
void combineafterCOMP1(struct jobinfo* present_job, Retval* rv);
void combineafterCOMP2(struct jobinfo* present_job, Retval* rv);
void combineafterCOMP4(struct jobinfo* present_job, Retval* rv);
void combineafterCOMP5(struct jobinfo* present_job, Retval* rv);
void combine_job_return_val(struct jobinfo* present_job, Retval* rv);

/****************************/

/*VARIABLES USED IN SCHEDULAR*/
int taskid, ntasks;
int nop;
int ws;
long tid;
struct workerattr *wattr[MAX];
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
struct jobinfo job[40000];
int iterator;
Data local_dt;
int size;

//struct jobinfo *global_memory_head;
struct timespec time_1, time_2, time_sleep;
/****************************/
#endif /* SCHED_H_ */
