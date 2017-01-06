#include"Sched.h"

//NO DATA DEPENDENCY IN KMEANS PROBLEM
//#include"Dependency.c"

void createworkers(int place) {
	int i, w;
	w = place;

	fab = (struct queue_t*) malloc(sizeof(struct queue_t));
	fab->head = fab->tail = NULL;
	remote_spawns = (struct queue_t*) malloc(sizeof(struct queue_t));
	remote_spawns->head = remote_spawns->tail = NULL;
	remote_enable = (struct queue_t*) malloc(sizeof(struct queue_t));
	remote_enable->head = remote_enable->tail = NULL;
	fab->num = remote_spawns->num = remote_enable->num = 0;

	pthread_mutex_init(&fab->t_lock, NULL);
	pthread_mutex_init(&remote_spawns->t_lock, NULL);
	pthread_mutex_init(&remote_enable->t_lock, NULL);

	for (i = 0; i <= nop; i++) {

		worker[i] = (struct workerinfo*) malloc(sizeof(struct workerinfo));
		worker[i]->ptr2q = (struct queue_t*) malloc(sizeof(struct queue_t));

		worker[i]->ptr2q->head = NULL;
		worker[i]->ptr2q->tail = NULL;
		pthread_mutex_init(&worker[i]->ptr2q->t_lock, NULL);

		worker[i]->ptr2fab = fab;

		worker[i]->amountwork = 0;
		worker[i]->wsatt = 0;
		worker[i]->wssuc = 0;
		worker[i]->time = 0;
		worker[i]->clk_work_time.tv_sec = 0;
		worker[i]->clk_work_time.tv_nsec = 0;
		worker[i]->clk_steal_time.tv_sec = 0;
		worker[i]->clk_steal_time.tv_nsec = 0;
		worker[i]->clk_fab_steal_time.tv_sec = 0;
		worker[i]->clk_fab_steal_time.tv_nsec = 0;
		worker[i]->clk_comp_time.tv_nsec = 0;
		worker[i]->clk_comp_time.tv_sec = 0;

		worker[i]->ptr2q->num = 0;
		worker[i]->state1 = STALL;
		wattr[i] = (struct workerattr *) malloc(sizeof(struct workerattr));
		wattr[i]->winfo = worker[i];
		worker[i]->id = i;
		worker[i]->place = w;

		/*DEFINING ATTRIBUTES*/

		long stacksize;
		pthread_attr_t attr;
		pthread_attr_init(&attr);

		cpu_set_t mask;
		CPU_ZERO(&mask);
		CPU_SET(i, &mask);

		/*if(pthread_attr_setaffinity_np(&attr,sizeof(mask),&mask ) == -1 )
		 {
		 perror("Failed because");
		 printf("WARNING: Could not set CPU Affinity, continuing...\n");
		 }*/

		//printf("creating thread = %d\n",i);
		if (i != nop)
			pthread_create(&worker[i]->wid, &attr, work, (void*) wattr[i]);
		else if (ws > 1)
			pthread_create(&worker[i]->wid, &attr, comm_work, (void*) wattr[i]);

	}

}

//### Assumes single bit set in the mask ###
int getCpu(cpu_set_t* mask) {
	unsigned int i, j;
	int cpuNum = -1;
	for (i = 0; i < 32; i++) {
		if (mask->__bits[i] > 0) {
			long currLong = mask->__bits[i];
			for (j = 0; j < 32; j++) {
				currLong = currLong >> 1;
				if (currLong == 0) {
					break;
				}
			}
			cpuNum = 32 * i + j;
			break;
		}

	}
	return (cpuNum);
}

//### Dedicated Worker for Communication across the places ###	
void *comm_work(void *c_attr) {
	struct workerattr *c;
	c = (struct workerattr*) c_attr;

	cpu_set_t mask;
	pthread_attr_t attr;
	pthread_getattr_np(pthread_self(), &attr);
	pthread_attr_getaffinity_np(&attr, sizeof(cpu_set_t), &mask);

	//printf("thread id = %lu , affinty = %lu\n",(unsigned long)pthread_self(),getCpu(&mask));


	int send_comm_info[1000][2];
	int recv_comm_info[1000][2];

	int i;
	for (i = 0; i < ntasks; i++) {
		send_comm_info[i][0] = 0;
		send_comm_info[i][1] = 0;
	}

	for (i = 0; i < ntasks; i++) {
		recv_comm_info[i][0] = 0;
		recv_comm_info[i][1] = 0;
	}

	struct jobinfo send_job;
	struct jobinfo recv_job;
	commdatainfo send_cdi;
	commdatainfo recv_cdi;
	
	int tag;

	MPI_Barrier(MPI_COMM_WORLD);
	while (1) {
		MPI_Request send_request;
		MPI_Status send_status;

		//if(send_comm_info[0][0] != 0) printf("send comm = %d %d\n",send_comm_info[0][0],send_comm_info[0][1]);

		MPI_Allreduce(&send_comm_info, &recv_comm_info, 2 * ntasks, MPI_INT,
				MPI_SUM, MPI_COMM_WORLD);
		//printf("Done All reduce\n");

		//For remote spawn without communication
		if (recv_comm_info[taskid][0] != 0 && recv_comm_info[taskid][1] == 1) {
			//printf("Sending Control thread from Node %d\n",taskid);
			MPI_Isend(&send_job, sizeof(struct jobinfo), MPI_BYTE,
					recv_comm_info[taskid][0] - 1, recv_comm_info[taskid][1],
					MPI_COMM_WORLD, &send_request);
		} else if (recv_comm_info[taskid][0] != 0) {

		
			MPI_Isend(&send_cdi, sizeof(commdatainfo), MPI_BYTE,
					recv_comm_info[taskid][0] - 1, recv_comm_info[taskid][1],
					MPI_COMM_WORLD, &send_request);

		

		}
		int count_recvs = 0;

		for (i = 0; i < ntasks; i++) {
			if (taskid != i && recv_comm_info[i][0] == taskid + 1)
				count_recvs++;
		}

		while (count_recvs > 0) {
			MPI_Status probe_status;
			MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD,
					&probe_status);

			MPI_Status recv_status;
			MPI_Request recv_request;

			// ## Received message is remote spawn to this place ##
			if (probe_status.MPI_TAG == 1) {
				MPI_Recv(&recv_job, sizeof(struct jobinfo), MPI_BYTE,
						MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, &recv_status);
				//printf("Receiving Data on Node %d\n",taskid);

				if (recv_status.MPI_TAG == 1) {
					int temp;
					if (recv_job.c == iterator) {
						pthread_mutex_lock(&tid_lock);
						temp = tid;
						tid++;
						pthread_mutex_unlock(&tid_lock);
					} else {
						iterator = recv_job.c;
						pthread_mutex_lock(&tid_lock);
						tid = 2;
						temp = 1;
						pthread_mutex_unlock(&tid_lock);
						//jobrecv_count = 1;
						//jobsend_count = 1;						

					}

					memcpy(&job[temp], &recv_job, sizeof(struct jobinfo));
					job[temp].jobid = temp;
					job[temp].state = RUNNING;
					job[temp].dta = local_dt;

					pthread_mutex_init(&job[temp].job_state_lock, NULL);
					enqueue_top(&job[temp], fab);
				}
			}
			// ## Received message is remote enable to this place ##
			else if (probe_status.MPI_TAG == 2) {//INIT CASE
				MPI_Status recv_status;
				MPI_Request recv_request;
				MPI_Recv(&recv_cdi, sizeof(commdatainfo), MPI_BYTE,
						MPI_ANY_SOURCE, 2, MPI_COMM_WORLD, &recv_status);

				if (recv_status.MPI_TAG == 2) {
					memcpy(&recv_job, &recv_cdi.job, sizeof(struct jobinfo));
					recv_job.rv0.mean = (float*) calloc(numCols, sizeof(float));
					recv_job.rv0.tp = (int*) calloc(numCols, sizeof(int));

					int i;
					for (i = 0; i < numCols; i++) {
						recv_job.rv0.mean[i] = recv_cdi.cd.mean_dt.mean[i];
						recv_job.rv0.tp[i] = recv_cdi.cd.mean_dt.tp[i];
					}

					local_enable(&recv_job, &job[recv_job.parent_jobid]);
					//printf("Done Local Enable for thread %d\n",recv_job.parent_jobid);
				}
			} else if (probe_status.MPI_TAG == 4) {//COMP CASE
				MPI_Status recv_status;
				MPI_Request recv_request;
				MPI_Recv(&recv_cdi, sizeof(commdatainfo), MPI_BYTE,
						MPI_ANY_SOURCE, 4, MPI_COMM_WORLD, &recv_status);

				if (recv_status.MPI_TAG == 4) {
					memcpy(&recv_job, &recv_cdi.job, sizeof(struct jobinfo));
					recv_job.rv0.cent_rv = (float**) calloc(numCent,
							sizeof(float*));
					recv_job.rv0.totalpts = (int**) calloc(numCent,
							sizeof(int*));

					int i, j;
					for (i = 0; i < numCent; i++) {
						recv_job.rv0.cent_rv[i] = (float*) calloc(numCols,
								sizeof(float));
						recv_job.rv0.totalpts[i] = (int*) calloc(numCols,
								sizeof(int));
						for (j = 0; j < numCols; j++) {
							recv_job.rv0.cent_rv[i][j]
									= recv_cdi.cd.cent_dt.cent_rv[i][j];
							recv_job.rv0.totalpts[i][j]
									= recv_cdi.cd.cent_dt.totalpts[i][j];
						}
					}

					local_enable(&recv_job, &job[recv_job.parent_jobid]);
					//printf("Done Local Enable for thread %d\n",recv_job.parent_jobid);
				}
			} else if (probe_status.MPI_TAG == 3) { //RECEIVING REMOTE SPAWN AND DATA
				MPI_Status recv_status;
				MPI_Request recv_request;

				MPI_Recv(&recv_cdi, sizeof(commdatainfo), MPI_BYTE,
						MPI_ANY_SOURCE, 3, MPI_COMM_WORLD, &recv_status);

				if (recv_status.MPI_TAG == 3) {
					int temp;
					if (recv_cdi.job.c == iterator) {
						pthread_mutex_lock(&tid_lock);
						temp = tid;
						tid++;
						pthread_mutex_unlock(&tid_lock);
					} else {
						iterator = recv_cdi.job.c;
						pthread_mutex_lock(&tid_lock);
						tid = 2;
						temp = 1;
						pthread_mutex_unlock(&tid_lock);
					}

					memcpy(&job[temp], &recv_cdi.job, sizeof(struct jobinfo));
					job[temp].jobid = temp;
					job[temp].state = RUNNING;
					job[temp].dta = local_dt;

					int j, k;

					for (j = 0; j < numCent; j++) {
						for (k = 0; k < numCols; k++) {
							job[temp].dta.cent[j][k] = recv_cdi.cd.cent[j][k];
						}

					}

					pthread_mutex_init(&job[temp].job_state_lock, NULL);
					enqueue_top(&job[temp], fab);

				}
			}
			count_recvs--;
		}

		//## Waiting for previous buffer to get empty ##
		if (recv_comm_info[taskid][0] != 0) {
			MPI_Wait(&send_request, &send_status);
		}

		//## Initializing for type of communication to be held ##
		for (i = 0; i < ntasks; i++) {
			send_comm_info[i][0] = 0;
			send_comm_info[i][0] = 0;
		}
		if (deque(c, remote_enable) != 0) //## Second Choice : Removing control dependency (Remote Enabling) ##
		{
			int j, k;
			switch (c->winfo->ptr2job->mode) {

			case INIT: {
				for (k = 0; k < numCols; k++) {

					if (c->winfo->ptr2job->rv1.flag != false) {
						send_cdi.cd.mean_dt.mean[k]
								= c->winfo->ptr2job->rv0.mean[k]
										+ c->winfo->ptr2job->rv1.mean[k];

						send_cdi.cd.mean_dt.tp[k]
								= c->winfo->ptr2job->rv0.tp[k]
										+ c->winfo->ptr2job->rv1.tp[k];

					} else {
						send_cdi.cd.mean_dt.mean[k]
								= c->winfo->ptr2job->rv0.mean[k];

						send_cdi.cd.mean_dt.tp[k]
								= c->winfo->ptr2job->rv0.tp[k];

					}
				}
				free(c->winfo->ptr2job->rv0.mean);
				free(c->winfo->ptr2job->rv0.tp);
				if (c->winfo->ptr2job->rv1.flag != false) {
					free(c->winfo->ptr2job->rv1.mean);
					free(c->winfo->ptr2job->rv1.tp);
				}
				c->winfo->ptr2job->rv1.flag = false;
				send_comm_info[taskid][1] = 2; ////Using TAG = 2 for data return during remote enable in INIT case
				memcpy(&send_cdi.job, c->winfo->ptr2job, sizeof(struct jobinfo));

				break;
			}
			case COMP: {

				for (j = 0; j < numCent; j++) {
					for (k = 0; k < numCols; k++) {

						if (c->winfo->ptr2job->rv1.flag != false) {
							send_cdi.cd.cent_dt.cent_rv[j][k]
									= c->winfo->ptr2job->rv0.cent_rv[j][k]
											+ c->winfo->ptr2job->rv1.cent_rv[j][k];
							send_cdi.cd.cent_dt.totalpts[j][k]
									= c->winfo->ptr2job->rv0.totalpts[j][k]
											+ c->winfo->ptr2job->rv1.totalpts[j][k];

						} else {
							send_cdi.cd.cent_dt.cent_rv[j][k]
									= c->winfo->ptr2job->rv0.cent_rv[j][k];

							send_cdi.cd.cent_dt.totalpts[j][k]
									= c->winfo->ptr2job->rv0.totalpts[j][k];

						}
					}
					free(c->winfo->ptr2job->rv0.cent_rv[j]);
					free(c->winfo->ptr2job->rv0.totalpts[j]);
					if (c->winfo->ptr2job->rv1.flag != false) {

						free(c->winfo->ptr2job->rv1.cent_rv[j]);
						free(c->winfo->ptr2job->rv1.totalpts[j]);
					}

				}
				free(c->winfo->ptr2job->rv0.cent_rv);
				free(c->winfo->ptr2job->rv0.totalpts);
				if (c->winfo->ptr2job->rv1.flag != false) {

					free(c->winfo->ptr2job->rv1.cent_rv);
					free(c->winfo->ptr2job->rv1.totalpts);
				}

				c->winfo->ptr2job->rv1.flag = false;
				send_comm_info[taskid][1] = 4; ////Using TAG = 4 for data return during remote enable in COMP case
				memcpy(&send_cdi.job, c->winfo->ptr2job, sizeof(struct jobinfo));
				break;
			}
			}

			send_comm_info[taskid][0] = c->winfo->ptr2job->parent_place + 1;
		} else if (deque(c, remote_spawns) != 0) //## Third Choice : Remote Spawn request ##
		{

			if (c->winfo->ptr2job->mode == COMP) { //DATA AND REMOTE SPAWN INFO

				//		printf("Rank = %d Remote spawn started\n",taskid);
				//	copyCentroids(c->winfo->ptr2job->dta.cent, &send_jobdata.cent);
				int j, k;

				for (j = 0; j < numCent; j++) {
					for (k = 0; k < numCols; k++) {
						send_cdi.cd.cent[j][k]
								= c->winfo->ptr2job->dta.cent[j][k];
					}

				}

				send_comm_info[taskid][0] = c->winfo->ptr2job->place + 1;
				send_comm_info[taskid][1] = 3; //Using TAG =3 for data transfer during remote spawn

				memcpy(&send_cdi.job, c->winfo->ptr2job, sizeof(struct jobinfo));
				//		printf("Rank = %d Remote spawn ended\n",taskid);

			} else {
				send_comm_info[taskid][0] = c->winfo->ptr2job->place + 1;
				send_comm_info[taskid][1] = 1;

				memcpy(&send_job, c->winfo->ptr2job, sizeof(struct jobinfo));
			}

		}
		MPI_Barrier(MPI_COMM_WORLD);
		/*********************************************************************/
	}
}

//### Main Job Schedular ###	
void *work(void *wattr) {
	struct workerattr* w;
	w = (struct workerattr*) wattr;

	cpu_set_t mask;
	pthread_attr_t attr;
	pthread_getattr_np(pthread_self(), &attr);
	pthread_attr_getaffinity_np(&attr, sizeof(cpu_set_t), &mask);

	//printf("thread id = %lu , affinty = %lu\n",(unsigned long)pthread_self(),getCpu(&mask));


	while (1) {
		while (start)
			; // Intial start variable activated by assigning 1st thread

		if (w->winfo->state1 == READY) // Work available for worker
		{
			//clock_gettime(CLOCK_REALTIME, &time_1);
			application_work(w->winfo);

			/*clock_gettime(CLOCK_REALTIME, &time_2);
			 if(timer_flag){
			 w->winfo->clk_work_time.tv_sec += diff_time(time_2, time_1).tv_sec;
			 w->winfo->clk_work_time.tv_nsec += diff_time(time_2, time_1).tv_nsec;
			 w->winfo->clk_work_time.tv_sec += (int)(w->winfo->clk_work_time.tv_nsec)/1000000000;
			 w->winfo->clk_work_time.tv_nsec = (int)(w->winfo->clk_work_time.tv_nsec)%1000000000;
			 }*/
		} else if (w->winfo->state1 == STALL) {
			// ### First: Attempt: pick next work-thread from Deque ###
			if (deque(w, w->winfo->ptr2q) == 0) {
				int s_status = 0;
				if (nop > 1) {
					clock_gettime(CLOCK_REALTIME, &time_1);
					s_status = work_stealing_schedular(w);
					/*	clock_gettime(CLOCK_REALTIME, &time_2);
					 if(timer_flag){
					 w->winfo->wsatt++;
					 w->winfo->clk_steal_time.tv_sec += diff_time(time_2, time_1).tv_sec;
					 w->winfo->clk_steal_time.tv_nsec += diff_time(time_2, time_1).tv_nsec;
					 w->winfo->clk_steal_time.tv_sec += (int)(w->winfo->clk_steal_time.tv_nsec)/1000000000;
					 w->winfo->clk_steal_time.tv_nsec = (int)(w->winfo->clk_steal_time.tv_nsec)%1000000000;
					 //			if(s_status && w->winfo->state1 != READY)
					 //			w->winfo->clk_steal_time.tv_nsec += 1000000;
					 w->winfo->clk_steal_time.tv_sec += (int)(w->winfo->clk_steal_time.tv_nsec)/1000000000;
					 w->winfo->clk_steal_time.tv_nsec = (int)(w->winfo->clk_steal_time.tv_nsec)%1000000000;
					 }*/
				}
				if (w->winfo->state1 == READY && timer_flag) {
					w->winfo->wssuc++;
					//			if(s_status)
					//			w->winfo->clk_steal_time.tv_nsec += 2000000;
					w->winfo->clk_steal_time.tv_sec
							+= (int) (w->winfo->clk_steal_time.tv_nsec)
									/ 1000000000;
					w->winfo->clk_steal_time.tv_nsec
							= (int) (w->winfo->clk_steal_time.tv_nsec)
									% 1000000000;
				} else //# Attempt : pick from FAB ##
				{
					if (ws > 1) {
						w->winfo->fab_steal_attempt++;
						//	clock_gettime(CLOCK_REALTIME, &time_1);

						int status = deque(w, w->winfo->ptr2fab);

						/*	clock_gettime(CLOCK_REALTIME, &time_2);
						 if(timer_flag){
						 w->winfo->clk_fab_steal_time.tv_sec += diff_time(time_2, time_1).tv_sec;
						 w->winfo->clk_fab_steal_time.tv_nsec +=diff_time(time_2, time_1).tv_nsec;
						 w->winfo->clk_fab_steal_time.tv_sec += (int)(w->winfo->clk_fab_steal_time.tv_nsec)/1000000000;
						 w->winfo->clk_fab_steal_time.tv_nsec = (int)(w->winfo->clk_fab_steal_time.tv_nsec)%1000000000;

						 if(status) {
						 w->winfo->fab_steal_succ++;
						 //		w->winfo->clk_fab_steal_time.tv_nsec += 1000;
						 //		w->winfo->clk_fab_steal_time.tv_sec += (int)(w->winfo->clk_fab_steal_time.tv_nsec)/1000000000;
						 //		w->winfo->clk_fab_steal_time.tv_nsec = (int)(w->winfo->clk_fab_steal_time.tv_nsec)%1000000000;
						 }
						 }	*/
					}
				}
			}
		}

		/*********************************************/

	}

}

int work_stealing_schedular(struct workerattr* w) {
	int i, a, p;
	i = w->winfo->id;
	p = rand() % nop; // randomization for workstealing
	p = p + (i / nop) * nop;

	a = isQNonEmpty(worker[p]->ptr2q); // checking if queue is empty
	int flag = 0;
	int h = (ws * nop) / 2;

	/*if(ws == 1)
	 {
	 int k = w->winfo->id/h;
	 if(k != (p/h))  flag = 1;
	 }*/

	if (a && (p != i)) {
		workstealing(i, p); // Doing workstealing
	}
	return flag;
}

int isQNonEmpty(struct queue_t *q) {
	if (q->num > 0) {

		return 1;
	} else {
		return 0;
	}

}

#define WS_THRESHOLD 1
void workstealing(int thief, int victim) {

	if (pthread_mutex_trylock(&worker[victim]->ptr2q->t_lock) == 0) {
		if (worker[victim]->ptr2q->num > WS_THRESHOLD) {
			worker[thief]->ptr2job = worker[victim]->ptr2q->head;
			worker[victim]->ptr2q->head = worker[victim]->ptr2q->head->next;
			worker[thief]->state1 = READY;
			worker[thief]->ptr2job->latest_worker = thief;
			worker[victim]->ptr2q->num--;
		}
		pthread_mutex_unlock(&worker[victim]->ptr2q->t_lock);
	}

}

void enqueue(struct jobinfo *present_job, struct queue_t *q) {
	//ENQUEING PARENT ON QUEUE	
	pthread_mutex_lock(&q->t_lock); // Acquiring lock on tail of queue
	if (q->num == 0) {
		q->head = present_job;
		q->tail = present_job;
	} else {
		q->tail->next = present_job;
		present_job->previous = q->tail;
		q->tail = present_job;
	}
	q->num++;
	pthread_mutex_unlock(&q->t_lock); // Freeing lock

}

int deque(struct workerattr* wattr, struct queue_t *q) {
	int status = 0;
	pthread_mutex_lock(&q->t_lock);
	if (q->num > 0) {
		wattr->winfo->ptr2job = q->tail;
		q->tail = q->tail->previous;
		wattr->winfo->ptr2job->next = wattr->winfo->ptr2job->previous = NULL;
		wattr->winfo->state1 = READY;
		q->num--;
		status = 1;
	}
	pthread_mutex_unlock(&q->t_lock);
	return (status);
}

void enqueue_top(struct jobinfo *present_job, struct queue_t *q) {
	//ENQUEING PARENT ON QUEUE
	pthread_mutex_lock(&q->t_lock); // Acquiring lock
	if (q->num == 0) {
		q->head = present_job;
		q->tail = present_job;
	} else {
		present_job->next = q->head;
		present_job->previous = NULL;
		q->head->previous = present_job;
		q->head = present_job;
	}
	q->num++; // Updating total no of job
	pthread_mutex_unlock(&q->t_lock); // Freeing lock

}

struct jobinfo *createJob(struct jobinfo *parent_job) {
	pthread_mutex_lock(&tid_lock);
	int temp = tid;
	tid++;
	pthread_mutex_unlock(&tid_lock);

	job[temp].jobid = temp;
	job[temp].state = RUNNING;
	if (parent_job == NULL) {
		job[temp].latest_worker = 0;
		job[temp].parent_jobid = 0;
		job[temp].parent_place = -1;
	} else {
		job[temp].latest_worker = parent_job->latest_worker;
		job[temp].parent_jobid = parent_job->jobid;
		job[temp].parent_place = parent_job->place;

		//## Adding this job to parent job's child ##
		pthread_mutex_lock(&parent_job->job_state_lock);
		parent_job->child_jobid[parent_job->no_child_job] = temp;
		parent_job->no_child_job++;
		parent_job->no_active_children++;
		pthread_mutex_unlock(&parent_job->job_state_lock);

	}
	job[temp].no_child_job = 0;
	job[temp].no_active_children = 0;
	job[temp].is_attached = 1;
	job[temp].child_jobid[0] = -1;
	job[temp].child_jobid[1] = -1;
	job[temp].next = job[temp].previous = NULL;

	pthread_mutex_init(&job[temp].job_state_lock, NULL);

	return &job[temp];
}

void combineafterInit(struct jobinfo* present_job, Retval* rv) {

	int k;
	rv->mean = (float *) calloc(numCols, sizeof(float));
	rv->tp = (int *) calloc(numCols, sizeof(int));

	for (k = 0; k < numCols; k++) {
		if (present_job->rv1.flag != false) {
			rv->mean[k] = present_job->rv0.mean[k] + present_job->rv1.mean[k];
			rv->tp[k] = present_job->rv0.tp[k] + present_job->rv1.tp[k];
		} else {
			rv->mean[k] = present_job->rv0.mean[k];
			rv->tp[k] = present_job->rv0.tp[k];

		}

	}
	free(present_job->rv0.mean);
	free(present_job->rv0.tp);
	if (present_job->rv1.flag != false) {
		free(present_job->rv1.mean);
		free(present_job->rv1.tp);
	}

}

void combineafterCOMP(struct jobinfo* present_job, Retval* rv) {
	int k, e;

	rv->cent_rv = (float **) calloc(numCent, sizeof(float*));
	rv->totalpts = (int**) calloc(numCent, sizeof(int*));

	for (k = 0; k < numCent; k++) {
		rv->cent_rv[k] = (float*) calloc(numCols, sizeof(float));
		rv->totalpts[k] = (int*) calloc(numCols, sizeof(int));
		for (e = 0; e < numCols; e++) {
			if (present_job->rv1.flag != false) {
				rv->cent_rv[k][e] = present_job->rv0.cent_rv[k][e]
						+ present_job->rv1.cent_rv[k][e];
				rv->totalpts[k][e] = present_job->rv0.totalpts[k][e]
						+ present_job->rv1.totalpts[k][e];

			} else {
				rv->cent_rv[k][e] = present_job->rv0.cent_rv[k][e];
				rv->totalpts[k][e] = present_job->rv0.totalpts[k][e];

			}

		}

		free(present_job->rv0.cent_rv[k]);
		free(present_job->rv0.totalpts[k]);
		if (present_job->rv1.flag != false) {

			free(present_job->rv1.cent_rv[k]);
			free(present_job->rv1.totalpts[k]);
		}

	}

	free(present_job->rv0.cent_rv);
	free(present_job->rv0.totalpts);
	if (present_job->rv1.flag != false) {

		free(present_job->rv1.cent_rv);
		free(present_job->rv1.totalpts);
	}

}

void combine_job_return_val(struct jobinfo* present_job, Retval* rv) {

	switch (present_job->mode) {
	/*case ALLC: {
	 break;
	 }*/
	case INIT: {

		combineafterInit(present_job, rv);
		break;
	}
	case COMP: {

		combineafterCOMP(present_job, rv);

		break;
	}
	}

}

void local_enable(struct jobinfo* present_job, struct jobinfo* parent_job) {

	pthread_mutex_lock(&parent_job->job_state_lock);

	if (present_job->flag == 1) {

		parent_job->rv0.flag = true;

		combine_job_return_val(present_job, &parent_job->rv0);

	}

	else {

		parent_job->rv1.flag = true;
		combine_job_return_val(present_job, &parent_job->rv1);

	}

	parent_job->no_active_children--;
	parent_job->no_child_job--;
	//printf("parent_job id = %d\n",parent_job->jobid);

	//Checking all child jobs returned and if parent is in stalled state then enable
	if (parent_job->no_active_children == 0 && parent_job->state == STALL) {
		// Enabling the parent job
		enqueue(parent_job, worker[parent_job->latest_worker]->ptr2q);
		parent_job->state = RUNNING;
	}

	pthread_mutex_unlock(&parent_job->job_state_lock);
}

struct timespec diff_time(struct timespec end, struct timespec start) {
	struct timespec temp;
	if ((end.tv_nsec - start.tv_nsec) < 0) {
		temp.tv_sec = end.tv_sec - start.tv_sec - 1;
		temp.tv_nsec = 1000000000 + end.tv_nsec - start.tv_nsec;
	} else {
		temp.tv_sec = end.tv_sec - start.tv_sec;
		temp.tv_nsec = end.tv_nsec - start.tv_nsec;
	}
	return temp;
}

int calculate_choice(int nx, int lb, int ub) {
	int i, j, midsum, mid;
	i = nx / ntasks;
	midsum = lb + ub;
	mid = midsum / 2;
	//	if (midsum % 2 == 0)
	j = (mid - 1) / i;
	//	else
	//		j = mid / i;
	if (j > ntasks - 1)
		j = ntasks - 1;
	return j;
}
