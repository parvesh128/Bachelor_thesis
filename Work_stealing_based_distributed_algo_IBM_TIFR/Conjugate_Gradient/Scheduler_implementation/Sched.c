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

	//Since no data dependency in k-means problem
	//send_q = (struct dependency_queue*) malloc(sizeof(struct dependency_queue));
	//recv_q = (struct dependency_queue*) malloc(sizeof(struct dependency_queue));


	//send_q->head = send_q->tail = NULL;
	//recv_q->head = recv_q->tail = NULL;
	//send_q->num = recv_q->num = 0;
	pthread_mutex_init(&fab->t_lock, NULL);
	pthread_mutex_init(&remote_spawns->t_lock, NULL);
	pthread_mutex_init(&remote_enable->t_lock, NULL);

	//pthread_mutex_init(&send_q->lock, NULL);
	//pthread_mutex_init(&recv_q->lock, NULL);
	//printf("Send queue %d\n",send_q);

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
	commdatainfo receive_cdi;

	//NO DATA DEPENDENCY IN KMEANS PROBLEM
	/*double *recv_data, *send_data;
	 send_data = (double*) malloc(size * sizeof(double));
	 recv_data = (double*) malloc(size * sizeof(double));*/
	int tag;

	MPI_Barrier(MPI_COMM_WORLD);
	while (1) {
		MPI_Request send_request;
		MPI_Status send_status;

		//if(send_comm_info[0][0] != 0) printf("send comm = %d %d\n",send_comm_info[0][0],send_comm_info[0][1]);

		MPI_Allreduce(&send_comm_info, &recv_comm_info, 2 * ntasks, MPI_INT,
				MPI_SUM, MPI_COMM_WORLD);
		//printf("Done All reduce\n");


		if (recv_comm_info[taskid][0] != 0 && (recv_comm_info[taskid][1] == 1
				|| recv_comm_info[taskid][1] == 2)) {
			//printf("Sending Control thread from Node %d\n",taskid);


			MPI_Isend(&send_job, sizeof(struct jobinfo), MPI_BYTE,
					recv_comm_info[taskid][0] - 1, recv_comm_info[taskid][1],
					MPI_COMM_WORLD, &send_request);
			//if(send_job.mode == READ)
			//		printf("Send done from taskid %d to taskid %d  with tag = %d and mode = %d \n",taskid,recv_comm_info[taskid][0] - 1,recv_comm_info[taskid][1],send_job.mode);
		} else if (recv_comm_info[taskid][0] != 0) {
			//printf("Sending Control thread from Node %d\n",taskid);
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
			//		printf("MPI_TAG = %d\n",probe_status.MPI_TAG);
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
					//if(recv_job.mode == COMP2)
					//printf("Spawn Receive completed at taskid %d with MODE = %d childjob id = %d lb = %d ub = %d parent job id =%d  \n",taskid,recv_job.jobid,recv_job.mode,recv_job.lb,recv_job.ub,recv_job.parent_jobid);

					memcpy(&job[temp], &recv_job, sizeof(struct jobinfo));
					job[temp].jobid = temp;
					job[temp].state = RUNNING;
					job[temp].dta = local_dt;

					pthread_mutex_init(&job[temp].job_state_lock, NULL);
					enqueue_top(&job[temp], fab);
				}
			} else if (probe_status.MPI_TAG == 5) {
				MPI_Recv(&receive_cdi, sizeof(commdatainfo), MPI_BYTE,
						MPI_ANY_SOURCE, 5, MPI_COMM_WORLD, &recv_status);
				//printf("Receiving Data on Node %d\n",taskid);

				if (recv_status.MPI_TAG == 5) {
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

					memcpy(&job[temp], &receive_cdi.job, sizeof(struct jobinfo));
					job[temp].jobid = temp;
					job[temp].state = RUNNING;
					job[temp].dta = local_dt;

					int i;
					for (i = job[temp].lb; i < job[temp].ub; i++)
						job[temp].dta.p[i] = receive_cdi.commdata[i];

					pthread_mutex_init(&job[temp].job_state_lock, NULL);
					enqueue_top(&job[temp], fab);
				}
			} else if (probe_status.MPI_TAG == 6) {
				MPI_Recv(&receive_cdi, sizeof(commdatainfo), MPI_BYTE,
						MPI_ANY_SOURCE, 6, MPI_COMM_WORLD, &recv_status);
				//printf("Receiving Data on Node %d\n",taskid);

				if (recv_status.MPI_TAG == 6) {
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

					memcpy(&job[temp], &receive_cdi.job, sizeof(struct jobinfo));
					job[temp].jobid = temp;
					job[temp].state = RUNNING;
					job[temp].dta = local_dt;

					int i;
					for (i = job[temp].lb; i < job[temp].ub; i++)
						job[temp].dta.z[i] = receive_cdi.commdata[i];

					pthread_mutex_init(&job[temp].job_state_lock, NULL);
					enqueue_top(&job[temp], fab);
				}
			}

			// ## Received message is remote enable to this place ##
			else if (probe_status.MPI_TAG == 2) {
				MPI_Status recv_status;
				MPI_Request recv_request;
				//			printf("Receive started at taskid %d\n",taskid);
				MPI_Recv(&recv_job, sizeof(struct jobinfo), MPI_BYTE,
						MPI_ANY_SOURCE, 2, MPI_COMM_WORLD, &recv_status);
				//				if(recv_job.mode == COMP2)
				//printf("Receive completed at taskid %d with MODE = %d lb = %d ub = %d parent job  lb = %d ub = %d \n",taskid,recv_job.mode,recv_job.lb,recv_job.ub,job[recv_job.parent_jobid].lb,job[recv_job.parent_jobid].ub);
				if (recv_status.MPI_TAG == 2) {
					local_enable(&recv_job, &job[recv_job.parent_jobid]);
					//				printf("Done Local Enable for thread %d\n",recv_job.parent_jobid);
				}
			} else if (probe_status.MPI_TAG == 3) {
				MPI_Status recv_status;
				MPI_Request recv_request;
				MPI_Recv(&receive_cdi, sizeof(commdatainfo), MPI_BYTE,
						MPI_ANY_SOURCE, 3, MPI_COMM_WORLD, &recv_status);
				if (recv_status.MPI_TAG == 3) {
					memcpy(&recv_job, &receive_cdi.job, sizeof(struct jobinfo));
					int i;
					for (i = recv_job.lb; i < recv_job.ub; i++)
						local_dt.p[i] = receive_cdi.commdata[i];
					local_enable(&recv_job, &job[recv_job.parent_jobid]);
					//printf("Done Local Enable for thread %d\n",recv_job.parent_jobid);
				}
			} else if (probe_status.MPI_TAG == 4) {
				MPI_Status recv_status;
				MPI_Request recv_request;
				MPI_Recv(&receive_cdi, sizeof(commdatainfo), MPI_BYTE,
						MPI_ANY_SOURCE, 4, MPI_COMM_WORLD, &recv_status);
				if (recv_status.MPI_TAG == 4) {
					memcpy(&recv_job, &receive_cdi.job, sizeof(struct jobinfo));
					int i;
					for (i = recv_job.lb; i < recv_job.ub; i++)
						local_dt.z[i] = receive_cdi.commdata[i];

					local_enable(&recv_job, &job[recv_job.parent_jobid]);
					//printf("Done Local Enable for thread %d\n",recv_job.parent_jobid);
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

		//NO DATA DEPENDENCY IN KMEANS PROBLEM
		/*if (dequeue_dependency(c, send_q) != 0) //## First Choice : Removing data dependency for next iteration ##
		 {
		 //tag = data->counter;
		 for (i = 0; i < size; i++)
		 send_data[i] = c->winfo->ptr2data->A[i];
		 send_comm_info[taskid][0] = c->winfo->ptr2data->place + 1;
		 send_comm_info[taskid][1] = 3;
		 } else*/
		if (deque(c, remote_enable) != 0) //## Second Choice : Removing control dependency (Remote Enabling) ##
		{
			send_comm_info[taskid][0] = c->winfo->ptr2job->parent_place + 1;
			int i;
			//printf("Remote enable taskid = %d mode = %d \n",taskid , c->winfo->ptr2job->mode);
			switch (c->winfo->ptr2job->mode) {
			case INIT2: {

				for (i = c->winfo->ptr2job->lb; i < c->winfo->ptr2job->ub; i++) {
					send_cdi.commdata[i] = c->winfo->ptr2job->dta.p[i];
				}

				send_comm_info[taskid][1] = 3; ////Using TAG = 3 for data return during remote enable in INIT2 case
				memcpy(&send_cdi.job, c->winfo->ptr2job, sizeof(struct jobinfo));
				//printf("Remote enable taskid = %d mode = %d lb = %d ub = %d \n",taskid , c->winfo->ptr2job->mode,c->winfo->ptr2job->lb,c->winfo->ptr2job->ub);

				break;

			}
			case COMP3: {
				if (c->winfo->ptr2job->c < 25) {
					for (i = c->winfo->ptr2job->lb; i < c->winfo->ptr2job->ub; i++) {
						send_cdi.commdata[i] = c->winfo->ptr2job->dta.p[i];
					}

					send_comm_info[taskid][1] = 3; ////Using TAG = 3 for data return during remote enable in COMP3 case


				} else {
					for (i = c->winfo->ptr2job->lb; i < c->winfo->ptr2job->ub; i++) {
						send_cdi.commdata[i] = c->winfo->ptr2job->dta.z[i];
					}

					send_comm_info[taskid][1] = 4; ////Using TAG = 4 for data return during remote enable in COMP3 case


				}
				memcpy(&send_cdi.job, c->winfo->ptr2job, sizeof(struct jobinfo));

				break;

			}
			default: {
				//				printf("enable comm start from %d to %d\n",taskid,send_comm_info[taskid][0]-1);

				send_comm_info[taskid][1] = 2;

				memcpy(&send_job, c->winfo->ptr2job, sizeof(struct jobinfo));

				//					if(c->winfo->ptr2job->mode == COMP2)
				//	printf("Mode = %d enable comm start from %d to %d\n",c->winfo->ptr2job->mode,taskid,send_comm_info[taskid][0]-1);
				break;

			}

			}

		} else if (deque(c, remote_spawns) != 0) //## Third Choice : Remote Spawn request ##
		{

			int i;
			switch (c->winfo->ptr2job->mode) {
			case COMP1: {
				for (i = c->winfo->ptr2job->lb; i < c->winfo->ptr2job->ub; i++) {
					send_cdi.commdata[i] = c->winfo->ptr2job->dta.p[i];
				}
				//printf("taskid = %d send job lb = %d ub = %d \n",taskid,c->winfo->ptr2job->lb,c->winfo->ptr2job->ub);

				send_comm_info[taskid][1] = 5;

				memcpy(&send_cdi.job, c->winfo->ptr2job, sizeof(struct jobinfo));
				break;
			}
			case COMP4: {
				for (i = c->winfo->ptr2job->lb; i < c->winfo->ptr2job->ub; i++) {
					send_cdi.commdata[i] = c->winfo->ptr2job->dta.z[i];
				}

				send_comm_info[taskid][1] = 6;

				memcpy(&send_cdi.job, c->winfo->ptr2job, sizeof(struct jobinfo));
				break;

			}
			default: {
				send_comm_info[taskid][1] = 1;

				memcpy(&send_job, c->winfo->ptr2job, sizeof(struct jobinfo));
				break;

			}
			}
			send_comm_info[taskid][0] = c->winfo->ptr2job->place + 1;
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

void combineafterCOMP5(struct jobinfo* present_job, Retval* rv) {
	int k, e;

	if (present_job->retval[1].flag != false) {

		rv->norm_temp11 = present_job->retval[0].norm_temp11
				+ present_job->retval[1].norm_temp11;
		rv->norm_temp12 = present_job->retval[0].norm_temp12
				+ present_job->retval[1].norm_temp12;

	} else {
		rv->norm_temp12 = present_job->retval[0].norm_temp12;
		rv->norm_temp11 = present_job->retval[0].norm_temp11;

	}
}

void combineafterCOMP4(struct jobinfo* present_job, Retval* rv) {
	int k, e;

	if (present_job->retval[1].flag != false) {

		rv->rnorm = present_job->retval[0].rnorm + present_job->retval[1].rnorm;

	} else {
		rv->rnorm = present_job->retval[0].rnorm;
	}
}

/*void combineafterCOMP3(struct jobinfo* present_job,struct jobinfo* parent_job) {
 int k, e;

 if (present_job->c < 25) {
 if (present_job->retval[1].flag != 0) {

 for (k = present_job->lb; k < present_job->ub; k++) {
 if (k < ((present_job->lb + present_job->ub) / 2)) {
 rv->p[k] = present_job->retval[0].p[k];
 } else {
 rv->p[k] = present_job->retval[1].p[k];
 }
 }

 free(present_job->retval[0].p);
 free(present_job->retval[1].p);

 } else {
 for (k = present_job->lb; k < present_job->ub; k++) {

 rv->p[k] = present_job->retval[0].p[k];

 }

 free(present_job->retval[0].p);

 }

 } else {
 if (present_job->retval[1].flag != 0) {

 for (k = present_job->lb; k < present_job->ub; k++) {
 if (k < ((present_job->lb + present_job->ub) / 2)) {
 rv->z[k] = present_job->retval[0].z[k];
 } else {
 rv->z[k] = present_job->retval[1].z[k];
 }
 }

 free(present_job->retval[0].z);
 free(present_job->retval[1].z);

 } else {
 for (k = present_job->lb; k < present_job->ub; k++) {

 rv->z[k] = present_job->retval[0].z[k];

 }

 free(present_job->retval[0].z);

 }

 }

 }*/

void combineafterCOMP2(struct jobinfo* present_job, Retval* rv) {
	int k, e;

	if (present_job->retval[1].flag != false) {

		rv->g = present_job->retval[0].g + present_job->retval[1].g;

	} else {
		rv->g = present_job->retval[0].g;
	}
}

void combineafterCOMP1(struct jobinfo* present_job, Retval* rv) {
	int k, e;

	if (present_job->retval[1].flag != false) {

		rv->rr = present_job->retval[0].rr + present_job->retval[1].rr;
		rv->pAp = present_job->retval[0].pAp + present_job->retval[1].pAp;

	} else {
		rv->rr = present_job->retval[0].rr;
		rv->pAp = present_job->retval[0].pAp;

	}
}

/*void combineafterINIT2(struct jobinfo* present_job, Retval* rv) {
 int k, e;

 if (present_job->retval[1].flag != 0) {

 for (k = present_job->lb; k < present_job->ub; k++) {
 if (k < ((present_job->lb + present_job->ub) / 2)) {
 rv->p[k] = present_job->retval[0].p[k];
 } else {
 rv->p[k] = present_job->retval[1].p[k];
 }
 }
 free(present_job->retval[0].p);
 free(present_job->retval[1].p);

 } else {
 for (k = present_job->lb; k < present_job->ub; k++) {

 rv->p[k] = present_job->retval[0].p[k];

 }
 free(present_job->retval[0].p);

 }
 }*/

void combine_job_return_val(struct jobinfo* present_job, Retval* rv) {
	switch (present_job->mode) {
	case READ: {
		break;
	}
	case INIT1: {
		break;

	}
	case INIT2: {

		break;

	}
	case COMP1: {
		combineafterCOMP1(present_job, rv);

		break;
	}
	case COMP2: {
		combineafterCOMP2(present_job, rv);

		break;
	}
	case COMP3: {

		break;
	}
	case COMP4: {
		combineafterCOMP4(present_job, rv);

		break;
	}
	case COMP5: {
		combineafterCOMP5(present_job, rv);

		break;
	}

	}

}

void local_enable(struct jobinfo* present_job, struct jobinfo* parent_job) {

	pthread_mutex_lock(&parent_job->job_state_lock);

	if (present_job->flag == 1) {
		combine_job_return_val(present_job, &parent_job->retval[0]);
		parent_job->retval[0].flag = true;
	}

	else {
		combine_job_return_val(present_job, &parent_job->retval[1]);
		parent_job->retval[1].flag = true;
	}

	parent_job->no_active_children--;
	parent_job->no_child_job--;

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
	if (midsum % 2 == 0)
		j = (mid - 1) / i;
	else
		j = mid / i;
	if (j > ntasks - 1)
		j = ntasks - 1;
	return j;
}

