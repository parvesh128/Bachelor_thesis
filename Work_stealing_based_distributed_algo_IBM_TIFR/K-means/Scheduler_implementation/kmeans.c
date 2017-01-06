/*
 * kmeans.c
 *
 *  Created on: 13-May-2011
 *      Author: parvesh
 */
#include"kmeans.h"
#include<assert.h>

void application_work(struct workerinfo *w) {

	//printf("Application work\n");
	switch (w->ptr2job->entry_point) {
	case 0:
		function0(w);
		break;
	case 1:
		function1(w);
		break;
	case 2:
		function2(w);
		break;
	case 3:
		function3(w);
		break;
	case 4:
		function4(w);
		break;
	case 5:
		function5(w);
		break;
	case 6:
		function6(w);
		break;
	case 7:
		function7(w);
		break;
	case 8:
		function8(w);
		break;
		/*case 9:
		 function9(w);
		 break;
		 */
	}
}

void factlimit() {
	int i, j;
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
	int fact = limit;
	temp = (row + 1) / fact;

	while (temp == 0) {
		strcat(filename, "0");
		fact = fact / 10;
		temp = (row + 1) / fact;
	}
}

void intialize_kmeans_variable() {

	local_dt.x = (float **) calloc(numRows, sizeof(float *));
	local_dt.bestCent = (short *) calloc(numRows, sizeof(short));
	local_dt.rowstr = (Rowstr*) calloc(numRows, sizeof(Rowstr));
	local_dt.cent = (float**) calloc(numCent, sizeof(float*));
	int i;
	for (i = 0; i < numCent; i++) {
		local_dt.cent[i] = (float*) calloc(numCols, sizeof(float));
	}
}

void function0(struct workerinfo *w) {
	//	printf("Rank = %d func0\n", taskid);
	w->ptr2job->lb = 0;
	w->ptr2job->ub = numRows;
	w->ptr2job->dta = local_dt;
	w->ptr2job->mode = INIT;

	w->ptr2job->counter = 1;
	w->ptr2job->place = 0;
	w->ptr2job->c = 1;
	iterator = 1;
	tid = 2;

	w->ptr2job->entry_point = 1;

}

void function1(struct workerinfo *w) // = spawn divide(lb,(ub+lb)/2,data)
{

	//printf("Rank = %d func1 lb = %d ub = %d\n", taskid,w->ptr2job->lb,w->ptr2job->ub);
	int l, r;
	if (w->ptr2job->ub - w->ptr2job->lb > leafmaxcol) // if true go for 2 more spawns
	{

		struct jobinfo *new_job;
		new_job = createJob(w->ptr2job);

		//ASSIGNING NEW JOB'S WORK
		//w->ptr2job->retval[0].flag = 1;
		new_job->lb = w->ptr2job->lb;
		new_job->ub = (w->ptr2job->lb + w->ptr2job->ub) / 2;
		new_job->dta = w->ptr2job->dta;
		new_job->mode = w->ptr2job->mode;

		new_job->c = w->ptr2job->c;
		new_job->entry_point = 1;

		new_job->rv0.flag = false;
		new_job->rv1.flag = false;

		new_job->flag = 1;
		new_job->place = calculate_choice(numRows, new_job->lb, new_job->ub);

		w->ptr2job->entry_point = 2;

		if (new_job->place != w->place) {
			//	  printf("Remote Spawn from Node %d to Node %d thread %d\n",taskid,new_job->place,new_job->jobid);
			enqueue_top(new_job, remote_spawns);
		} else {
			enqueue(w->ptr2job, w->ptr2q);
			w->ptr2job = new_job;
		}

	} else
		w->ptr2job->entry_point = 5;

}

void function2(struct workerinfo *w) // spawn divide((ub+lb)/2,ub,data)
{
	//printf("Rank = %d func2 lb = %d ub = %d\n", taskid,w->ptr2job->lb,w->ptr2job->ub);

	struct jobinfo *new_job;
	new_job = createJob(w->ptr2job);

	//ASSIGNING NEW THREAD'S WORK
	//	w->ptr2job->retval[1].flag = 1;
	new_job->lb = (w->ptr2job->lb + w->ptr2job->ub) / 2;
	new_job->ub = w->ptr2job->ub;
	new_job->dta = w->ptr2job->dta;

	new_job->mode = w->ptr2job->mode;

	new_job->c = w->ptr2job->c;
	new_job->rv0.flag = false;
	new_job->rv1.flag = false;

	new_job->flag = 2;
	new_job->entry_point = 1;
	new_job->place = calculate_choice(numRows, new_job->lb, new_job->ub);

	w->ptr2job->entry_point = 3;

	if (new_job->place != w->place) {
		//printf("Remote Spawn from Node %d to Node %d thread %d\n",taskid,new_job->place,new_job->jobid);
		enqueue_top(new_job, remote_spawns);
	} else {
		enqueue(w->ptr2job, w->ptr2q);
		w->ptr2job = new_job;
	}

}

void function3(struct workerinfo *w) // SYNCHRONIZATION = sync;
{
	pthread_mutex_lock(&w->ptr2job->job_state_lock);
	if (w->ptr2job->is_attached && w->ptr2job->no_active_children) //checking that all the children hv returned
	{
		w->ptr2job->state = STALL;
		w->state1 = STALL;
	} else {
		w->ptr2job->entry_point++;
	}
	pthread_mutex_unlock(&w->ptr2job->job_state_lock);

}

void function4(struct workerinfo *w) // return(l+r)
{
	//int n;

	//n = (w->ptr2job->retval[0]) + (w->ptr2job->retval[1]); // = l+r;
	return_func(w);
}

void function5(struct workerinfo *w) {
	//write(1,"5",1);
	switch (w->ptr2job->mode) {
	case COMP: {
		computekMeans(wattr[w->id]);
		break;
	}
		/*case ALLC:
		 allocateDataPoints(wattr[w->id]);
		 break;
		 */
	case INIT: {
		readandinitializeDataPoints(wattr[w->id]);
		break;

	}
	}
	w->ptr2job->entry_point++;

}

void function6(struct workerinfo *w) {

	return_func(w);
}

void reestimateCentroids(struct jobinfo* job) {
	short i;
	for (i = 0; i < numCent; i++) {

		int e;
		for (e = 0; e < numCols; e++) {
			if (job->c == 1)
				job->rv0.mean[e] = (job->rv0.mean[e]) / (job->rv0.tp[e]);
			if (job->rv0.totalpts[i][e] > 0) {
				job->dta.cent[i][e] = (job->rv0.cent_rv[i][e])
						/ (job->rv0.totalpts[i][e]);
			} else {
				job->dta.cent[i][e] = job->rv0.mean[e];
			}
		}

		free(job->rv0.cent_rv[i]);
		free(job->rv0.totalpts[i]);
	}
	free(job->rv0.cent_rv);
	free(job->rv0.totalpts);
	if (job->c == 1)
		free(job->rv0.tp);

}

void combineAtPlace0afterInit(struct jobinfo* present_job) {

	int k;
	//present_job->retval[1].flag != 0
	if (present_job->rv1.flag != false) {
		for (k = 0; k < numCols; k++) {

			present_job->rv0.mean[k] = present_job->rv0.mean[k]
					+ present_job->rv1.mean[k];
			present_job->rv0.tp[k] = present_job->rv0.tp[k]
					+ present_job->rv1.tp[k];

		}
		free(present_job->rv1.mean);
		free(present_job->rv1.tp);
	}

}

void combineAtPlace0afterCOMP(struct jobinfo* present_job) {
	short k, e;

	if (present_job->rv1.flag != false) {

		for (k = 0; k < numCent; k++) {

			for (e = 0; e < numCols; e++) {

				present_job->rv0.cent_rv[k][e] = present_job->rv0.cent_rv[k][e]
						+ present_job->rv1.cent_rv[k][e];

				present_job->rv0.totalpts[k][e]
						= present_job->rv0.totalpts[k][e]
								+ present_job->rv1.totalpts[k][e];
			}
			free(present_job->rv1.cent_rv[k]);
			free(present_job->rv1.totalpts[k]);
		}
		free(present_job->rv1.cent_rv);
		free(present_job->rv1.totalpts);
	}
}

void return_func(struct workerinfo *w) {
	struct jobinfo *present_job;
	present_job = w->ptr2job;

	if (present_job->parent_place > -1 && present_job->parent_place
			== present_job->place) {
		//## Local Enable ##
		struct jobinfo *parent_job;
		parent_job = &job[present_job->parent_jobid];

		local_enable(present_job, parent_job);

		w->state1 = STALL;
	} else if (present_job->parent_place > -1) {
		//## Remote Enable ##

		//if(w->ptr2job->mode == COMP)
		//printf("Remote Enable from Node %d to Node %d with mode %d\n",taskid,present_job->parent_place,w->ptr2job->mode);
		enqueue(present_job, remote_enable);
		w->state1 = STALL;
	} else {

		w->ptr2job->entry_point = 7; // for computation

		switch (w->ptr2job->mode) {
		case INIT: {
			printf("Rank = %d Init done\n", taskid);
			combineAtPlace0afterInit(w->ptr2job);
			initializeCentroids(w->ptr2job);
			readtime = MPI_Wtime() - readstart_time;
			break;
		}
		case COMP: {
			if (taskid == 0)
				printf("Completed %d iteration\n", w->ptr2job->c - 1);
			//	printf("Rank = %d COMP done\n", taskid);
			combineAtPlace0afterCOMP(w->ptr2job);
			reestimateCentroids(w->ptr2job);

		}
		}

		//restimate centroid algo


	}

}

void function7(struct workerinfo *w) //computation
{
	tid = 2;
	w->ptr2job->mode = COMP;
	w->ptr2job->place = 0;

	//printf("Counter = %d\n", w->ptr2job->c);
	if (w->ptr2job->c <= NUMIT) {
		w->ptr2job->c++;
		iterator++;

		w->ptr2job->counter = 2;
		w->ptr2job->entry_point = 1;

	} else
		w->ptr2job->entry_point++;
}

void function8(struct workerinfo *w) //printing the solution
{
	w->state1 = STALL;
	pthread_cond_signal(&end_cond);
}

int Random(int window) {
	return (int) (random() % window);
}

void readandinitializeDataPoints(struct workerattr *wattr) {
	/*if(taskid==0)
	 printf("Started File reading\n");
	 */
	Data dt = wattr->winfo->ptr2job->dta;
	int j;

	int lb, ub, i, idx;
	lb = wattr->winfo->ptr2job->lb;
	ub = wattr->winfo->ptr2job->ub;
	char *filename, *t;
	char *temp1, *temp2;
	int temp, filelength;
	int* tempcolidx;
	float* tempX;
	filename = (char*) calloc(150, sizeof(char));
	t = (char*) calloc(10, sizeof(char));
	temp1 = (char*) calloc(20, sizeof(char));
	temp2 = (char*) calloc(20, sizeof(char));

	tempcolidx = (int*) calloc(numCols, sizeof(int));
	tempX = (float*) calloc(numCols, sizeof(float));
	FILE* fp;

	//	wattr->winfo->ptr2job->rv0 = (Retval*) calloc(1, sizeof(Retval));
	wattr->winfo->ptr2job->rv0.flag = true;
	wattr->winfo->ptr2job->rv0.mean = (float *) calloc(numCols, sizeof(float));
	wattr->winfo->ptr2job->rv0.tp = (int *) calloc(numCols, sizeof(int));

	for (i = 0; i < numCols; i++) {
		wattr->winfo->ptr2job->rv0.mean[i] = 0;
		wattr->winfo->ptr2job->rv0.tp[i] = 0;
	}
	//wattr->winfo->ptr2job->retval[0].mean[i] = 0;

	for (i = lb; i < ub; i++) {
		filelength = 0;

		sprintf(t, "%d", i + 1);
		strcpy(filename, dp);
		strcat(filename,"custno_000");
		appendZeros(filename, i);

		strcat(filename, t);

		strcat(filename, ".txt");

		//printf("%s \n",filename);


		fp = fopen(filename, "r");
		assert(fp!=NULL);
		while (fscanf(fp, "%s %s\n", temp1, temp2) != EOF) {

			if (atoi(temp1) <= numCols && atoi(temp1) > 0) {
				tempcolidx[filelength] = atoi(temp1);
				tempX[filelength] = atof(temp2);
				tempcolidx[filelength]--;
				filelength++;
			}

		}

		fclose(fp);

		dt.rowstr[i].num = filelength;
		dt.x[i] = (float *) calloc(filelength, sizeof(float));
		dt.rowstr[i].colidx = (int*) calloc(filelength, sizeof(int));

		for (j = 0; j < filelength; j++) {
			dt.x[i][j] = tempX[j];
			dt.rowstr[i].colidx[j] = tempcolidx[j];
			wattr->winfo->ptr2job->rv0.mean[tempcolidx[j]] += dt.x[i][j];
			wattr->winfo->ptr2job->rv0.tp[tempcolidx[j]]++;
			//	wattr->winfo->ptr2job->retval[0].mean[tempcolidx[j]] += dt.x[i][j];

		}

	}

	/*	if(taskid==0)
	 printf("Completed file reading\n");*/
	free(tempX);
	free(tempcolidx);
	free(filename);
	free(t);
	free(temp1);
	free(temp2);
}

void initializeCentroids(struct jobinfo *job) {

	short j;
	int  k;
	/* read in centroid labels and data points */

	for (j = 0; j < numCent; j++) {

		/* then read in data values */
		for (k = 0; k < numCols; k++) {

			job->dta.cent[j][k] = randb(j,k);
			//job->rv0.cent[j][k] = randb(j,k);
		}

	}

}

void computekMeans(struct workerattr *wattr) {
	Data dt = wattr->winfo->ptr2job->dta;
	int lb = wattr->winfo->ptr2job->lb;
	int ub = wattr->winfo->ptr2job->ub;

	int j, l;
	short k;

	// calculate distance matrix and minimum
	float rMin;
	float dist;
	//dt.distortion[it] = 0;


	for (j = lb; j < ub; j++) {
		rMin = BIGNUM;

		for (k = 0; k < numCent; k++) {
			int e, idx;
			dist = 0;

			for (e = 0; e < dt.rowstr[j].num; e++) {
				idx = dt.rowstr[j].colidx[e];
				dist
						+= (dt.x[j][e]
								- wattr->winfo->ptr2job->dta.cent[k][idx])
								* (dt.x[j][e]
										- wattr->winfo->ptr2job->dta.cent[k][idx]);

			}

			if (dist < rMin) {
				dt.bestCent[j] =  k;
				rMin = dist;
			}
		}

	}

	// reestimate centroids

	int idx;
	wattr->winfo->ptr2job->rv0.cent_rv = (float **) calloc(numCent,
			sizeof(float*));

	wattr->winfo->ptr2job->rv0.totalpts = (int**) calloc(numCent, sizeof(int*));

	if (wattr->winfo->ptr2job->rv0.cent_rv == NULL
			|| wattr->winfo->ptr2job->rv0.totalpts == NULL)
		printf("Allocation error in task %d", taskid);

	for (k = 0; k < numCent; k++) {
		wattr->winfo->ptr2job->rv0.cent_rv[k] = (float*) calloc(numCols,
				sizeof(float));
		wattr->winfo->ptr2job->rv0.totalpts[k] = (int*) calloc(numCols,
				sizeof(int));

		if (wattr->winfo->ptr2job->rv0.cent_rv[k] == NULL
				|| wattr->winfo->ptr2job->rv0.totalpts[k] == NULL)
			printf("Allocation error 1 in task %d for %d\n", taskid, k);

		int e;
		for (e = 0; e < numCols; e++) {
			wattr->winfo->ptr2job->rv0.cent_rv[k][e] = 0;
			wattr->winfo->ptr2job->rv0.totalpts[k][e] = 0;
		}
		for (j = lb; j < ub; j++) {
			if (dt.bestCent[j] == k) {

				for (e = 0; e < dt.rowstr[j].num; e++) {
					idx = dt.rowstr[j].colidx[e];
					wattr->winfo->ptr2job->rv0.cent_rv[k][idx] += dt.x[j][e];
					wattr->winfo->ptr2job->rv0.totalpts[k][e]++;
				}

			}
		}

	}

}

