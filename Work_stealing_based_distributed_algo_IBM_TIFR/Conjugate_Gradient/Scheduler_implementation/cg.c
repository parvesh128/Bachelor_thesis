/*
 * kmeans.c
 *
 *  Created on: 13-May-2011
 *      Author: parvesh
 */
#include"cg.h"

void application_work(struct workerinfo *w) {

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
	case 9:
		function9(w);
		break;
	}
}

void copy_rr_h(struct jobinfo *new_job, struct jobinfo *present_job) {

	/* copy rr and h  to new jobs */
	new_job->dta.h = present_job->dta.h;
	new_job->retval[0].rr = present_job->retval[0].rr;
}

void copy_g(struct jobinfo *new_job, struct jobinfo *present_job) {

	/* copy g to new jobs */

	new_job->retval[0].g = present_job->retval[0].g;
}

void copy_normtemp12(struct jobinfo *new_job, struct jobinfo *present_job) {

	/* copy g to new jobs */

	new_job->retval[0].norm_temp12 = present_job->retval[0].norm_temp12;
}

void allocateinitial(Data* dt) {
	dt->A = (double **) calloc(global_N, sizeof(double *));
	dt->rowstr = (Rowstr*) calloc(global_N, sizeof(Rowstr));
	dt->r = (double**) calloc(global_N, sizeof(double*));
	dt->V = (double**) calloc(global_N, sizeof(double*));
	dt->x = (double**) calloc(global_N, sizeof(double*));
	dt->p = (double*) calloc(global_N, sizeof(double));
	dt->z = (double*) calloc(global_N, sizeof(double));

}
void function0(struct workerinfo *w) {

	w->ptr2job->lb = 0;
	w->ptr2job->ub = global_N;
	w->ptr2job->dta = local_dt;

	w->ptr2job->mode = READ;

	w->ptr2job->counter = 1;
	w->ptr2job->place = 0;
	w->ptr2job->c = 0;
	iterator = 0;

	w->ptr2job->entry_point = 1;

}

void function1(struct workerinfo *w) // = spawn divide(lb,(ub+lb)/2,data)
{

	//		if(w->ptr2job->mode == INIT2)
	//	 printf("Rank = %d function1 lb = %d ub = %d leafmaxcol = %d\n",taskid,w->ptr2job->lb,w->ptr2job->ub,leafmaxcol);

	if (w->ptr2job->ub - w->ptr2job->lb > leafmaxcol) // if true go for 2 more spawns
	{

		struct jobinfo *new_job;
		new_job = createJob(w->ptr2job);

		//ASSIGNING NEW JOB'S WORK
		new_job->lb = w->ptr2job->lb;
		new_job->ub = (w->ptr2job->lb + w->ptr2job->ub) / 2;
		new_job->dta = w->ptr2job->dta;
		new_job->mode = w->ptr2job->mode;

		new_job->c = w->ptr2job->c;
		new_job->entry_point = 1;

		new_job->retval[0].flag = false;
		new_job->retval[1].flag = false;

		new_job->flag = 1;
		new_job->place = w->place;//calculate_choice(global_N, new_job->lb, new_job->ub);

		switch (w->ptr2job->mode) {
		case INIT1:
			break;
		case INIT2:
			break;
		case COMP1: {
			break;

		}
		case COMP2: {
			copy_rr_h(new_job, w->ptr2job);
			break;
		}
		case COMP3: {
			copy_g(new_job, w->ptr2job);
			break;
		}
		case COMP4: {
			break;

		}
		case COMP5:
			break;
		case COMP6: {
			copy_normtemp12(new_job, w->ptr2job);
			break;
		}

		}

		w->ptr2job->entry_point = 2;

		if (new_job->place != w->place) {
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
	 //if(w->ptr2job->mode == INIT2)
	 //printf("Rank = %d function2 lb = %d ub = %d leafmaxcol = %d\n",taskid,w->ptr2job->lb,w->ptr2job->ub,leafmaxcol);
	 
	struct jobinfo *new_job;
	new_job = createJob(w->ptr2job);

	//ASSIGNING NEW THREAD'S WORK
	new_job->lb = (w->ptr2job->lb + w->ptr2job->ub) / 2;
	new_job->ub = w->ptr2job->ub;
	new_job->dta = w->ptr2job->dta;

	new_job->mode = w->ptr2job->mode;

	new_job->c = w->ptr2job->c;
	new_job->retval[0].flag = false;
	new_job->retval[1].flag = false;
	new_job->flag = 2;

	switch (w->ptr2job->mode) {
	case INIT1: {

		break;
	}
	case INIT2: {

		break;
	}
	case COMP1: {
		break;
	}

	case COMP2: {
		copy_rr_h(new_job, w->ptr2job);
		break;
	}
	case COMP3: {
		copy_g(new_job, w->ptr2job);
		break;
	}
	case COMP4: {

		break;

	}
	case COMP5:
		break;
	case COMP6: {
		copy_normtemp12(new_job, w->ptr2job);
		break;
	}

	}

	new_job->entry_point = 1;
	new_job->place = calculate_choice(global_N, new_job->lb, new_job->ub);
	w->ptr2job->entry_point = 3;

	if (new_job->place != w->place) {
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
	return_func(w);
}

void function5(struct workerinfo *w) {
	//write(1,"5",1);

	switch (w->ptr2job->mode) {
	case READ: {
		readandinitializeData(wattr[w->id]);
		break;
	}
	case INIT1: {

		initialize1(wattr[w->id]);
		break;
	}
	case INIT2: {
		initialize2(wattr[w->id]);
		break;
	}
	case COMP1: {
		compute1(wattr[w->id]);
		break;
	}

	case COMP2: {
		compute2(wattr[w->id]);
		break;
	}
	case COMP3: {
		compute3(wattr[w->id]);
		break;
	}
	case COMP4: {
		compute4(wattr[w->id]);
		break;
	}
	case COMP5: {
		compute5(wattr[w->id]);
		break;
	}
	case COMP6: {
		compute6(wattr[w->id]);
		break;
	}

	}
	w->ptr2job->entry_point++;

}

void function6(struct workerinfo *w) {

	return_func(w);

	//printf("Return func done \n");
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
		//printf("Remote Enable from Node %d to Node %d\n",taskid,present_job->parent_place);

		//	if(present_job->mode == COMP2)
		//printf("Rank = %d present job lb = %d ub = %d parent_job lb = %d ub = %d \n",taskid,present_job->lb,present_job->ub,job[present_job->parent_jobid].lb,job[present_job->parent_jobid].ub);	
		enqueue(present_job, remote_enable);

		w->state1 = STALL;
		//printf("taskid = %d COMP2 return func lb = %d ub = %d enq done\n",taskid,present_job->lb,present_job->ub);
	} else {

		//w->ptr2job->entry_point = 7; // for intialization


		//} else if (w->ptr2job->counter == 2) {

		switch (w->ptr2job->mode) {
		case READ: {

		        readtime = MPI_Wtime() - readstart_time;	
			tid = 2;
	//					printf("READ DONE\n");
			w->ptr2job->mode = INIT1;
			w->ptr2job->place = 0;
			w->ptr2job->entry_point = 1;
			break;
		}
		case INIT1: {
		

	//						printf("INIT1 DONE\n");
			//					printf("INIT1 completed counter = %d\n",w->ptr2job->counter);
			if (w->ptr2job->counter == 1) {
				tid = 2;
	//			printf("taskid = %d INIT2 started\n",taskid);
				w->ptr2job->dta.zeta = 0;
				w->ptr2job->mode = INIT2;
				w->ptr2job->place = 0;
				w->ptr2job->entry_point = 1;

			} else {
				//										printf("INIT1 completed\n");
				w->ptr2job->dta.zeta = 0;
				w->ptr2job->entry_point = 8;
				w->ptr2job->C = 1;
			}

			break;

		}
		case INIT2: {
		
	//				printf("INIT2 DONE\n");
			//					printf("INIT2 completed\n");
			//combineAtPlace0afterINIT2(w->ptr2job);
			w->ptr2job->c = 1;
			w->ptr2job->entry_point = 7;

			break;
		}
		case COMP1: {
			
	//					printf("COMP1 DONE\n");
			combineAtPlace0afterCOMP1(w->ptr2job);
			//				printf("COMP1 completed\n");
			w->ptr2job->entry_point = 7; // for compute2
			break;
		}
		case COMP2: {
	//						printf("COMP2 DONE\n");
			combineAtPlace0afterCOMP2(w->ptr2job);
			//				printf("COMP2 completed\n");
			w->ptr2job->entry_point = 7; // for compute3
			break;
		}
		case COMP3: {
	//					 printf("COMP3 DONE\n");
			//combineAtPlace0afterCOMP3(w->ptr2job);
			//printf("COMP3 DONE\n");
			w->ptr2job->entry_point = 7; // for compute1
			break;
		}
		case COMP4: {
			tid = 2;
	//						printf("COMP4 DONE\n");
			combineAtPlace0afterCOMP4(w->ptr2job);
			w->ptr2job->mode = COMP5;
			w->ptr2job->place = 0;
			w->ptr2job->entry_point = 1;
			break;
		}
		case COMP5: {
			tid = 2;
	//						printf("COMP5 DONE\n");
			combineAtPlace0afterCOMP5(w->ptr2job);
			w->ptr2job->mode = COMP6;
			w->ptr2job->place = 0;
			w->ptr2job->entry_point = 1;
			break;

		}
		case COMP6: {
	//					printf("COMP6 DONE\n");

			if (w->ptr2job->counter == 1) {
				tid = 2;
				w->ptr2job->mode = INIT1;
				w->ptr2job->counter = 2;
				w->ptr2job->place = 0;
				w->ptr2job->entry_point = 1;

			} else {
				printResultsAfterCOMP6(w->ptr2job);
				w->ptr2job->entry_point = 8;
			}
			break;

		}

		}

	}

}

void function7(struct workerinfo *w) {

	tid = 2;
	w->ptr2job->place = 0;
	w->ptr2job->entry_point = 1;

	if (w->ptr2job->c <= 25) {

		switch (w->ptr2job->mode) {
		case INIT2: {
			w->ptr2job->mode = COMP1;
			break;
		}
		case COMP1: {
			//printf("iterator = %d COMP2 started\n",w->ptr2job->c );
			w->ptr2job->mode = COMP2;
			break;
		}
		case COMP2: {
			w->ptr2job->mode = COMP3;
			break;
		}
		case COMP3: {
			//	printf("iteration = %d completed\n",w->ptr2job->c);
			w->ptr2job->mode = COMP1;
			w->ptr2job->c++;
			iterator++;

			break;

		}
		}
	} else {

		w->ptr2job->mode = COMP4;

	}

	//printf("Counter = %d\n", w->ptr2job->c);
}

void function8(struct workerinfo *w) //printing the solution
{
	tid = 2;
	w->ptr2job->place = 0;
	w->ptr2job->entry_point = 1;
	//	printf("function8 Counter2 = %d niter = %d\n",w->ptr2job->C,niter);
	if (w->ptr2job->C <= niter) {
		switch (w->ptr2job->mode) {
		case INIT1: {
			w->ptr2job->mode = INIT2;
			break;

		}
		case COMP6: {
			//			printf("Iteration %d completed\n",w->ptr2job->C);
			w->ptr2job->mode = INIT2;
			w->ptr2job->C++;
			break;
		}
		}
	} else
		w->ptr2job->entry_point = 9;

}

void function9(struct workerinfo *w) //printing the solution
{
	printf(" Benchmark completed\n");

	epsilon = 1.0e-10;
	if (cls != 'U') {
		if (fabs(w->ptr2job->dta.zeta - zeta_verify_value) <= epsilon) {
			verified = true;
			printf(" VERIFICATION SUCCESSFUL\n");
			printf(" Zeta is    %20.12e\n", w->ptr2job->dta.zeta);
			printf(" Error is   %20.12e\n", w->ptr2job->dta.zeta
					- zeta_verify_value);
		} else {
			verified = false;
			printf(" VERIFICATION FAILED\n");
			printf(" The correct zeta is %20.12e\n", zeta_verify_value);
		}
	} else {
		verified = false;
		printf(" Problem size unknown\n");
		printf(" NO VERIFICATION PERFORMED\n");
	}
	w->state1 = STALL;
	pthread_cond_signal(&end_cond);
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

void readandinitializeData(struct workerattr *wattr) {

	Data dt = wattr->winfo->ptr2job->dta;
	int j;

	int lb, ub, i, col, idx;
	lb = wattr->winfo->ptr2job->lb;
	ub = wattr->winfo->ptr2job->ub;
	//printf("lb = %d ub = %d taskid = %d\n",lb,ub,taskid);
	char *path, *t;
	char *temp1, *temp2;
	int filelength;
	int* tempcolidx;
	double* tempA;
	tempcolidx = (int*) calloc(global_N, sizeof(int));
	tempA = (double*) calloc(global_N, sizeof(double));

	path = (char*) calloc(27, sizeof(char));
	t = (char*) calloc(10, sizeof(char));
	temp1 = (char*) calloc(20, sizeof(char));
	temp2 = (char*) calloc(20, sizeof(char));

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
		assert(fp!=NULL);
		while (fscanf(fp, "%s %s\n", temp1, temp2) != EOF) {

			if (atoi(temp1) <= global_N && atoi(temp1) > 0) {
				//			printf("%s %s\n",temp1 ,temp2);
				tempcolidx[filelength] = atoi(temp1);
				tempA[filelength] = atof(temp2);
				tempcolidx[filelength]--;
				filelength++;
			}

		}

		fclose(fp);

		dt.rowstr[i].num = filelength;
		dt.A[i] = (double *) calloc(filelength, sizeof(double));
		dt.rowstr[i].colidx = (int*) calloc(filelength, sizeof(int));

		for (j = 0; j < filelength; j++) {
			dt.A[i][j] = tempA[j];
			dt.rowstr[i].colidx[j] = tempcolidx[j];

		}
		dt.V[i] = (double*) calloc(1, sizeof(double));
		dt.r[i] = (double*) calloc(1, sizeof(double));
		dt.x[i] = (double*) calloc(1, sizeof(double));

	}
	/*if (taskid == 0)*/
	//	 printf("Completed file reading\n");

	free(tempA);
	free(tempcolidx);
	free(path);
	free(t);
	free(temp1);
	free(temp2);

}

void initialize1(struct workerattr *wattr) {

	Data dt = wattr->winfo->ptr2job->dta;
	int lb = wattr->winfo->ptr2job->lb;
	int ub = wattr->winfo->ptr2job->ub;

	//printf("Rank = %d Initialize1 lb = %d ub = %d leafmaxcol = %d\n",taskid,lb,ub,leafmaxcol);
	int i, rowIndex;
	rowIndex = taskid * (global_N / ntasks);
	for (i = lb; i < ub; i++) {

		dt.x[i][0] = 1.0; // Intial Xo solution

	}
	wattr->winfo->ptr2job->retval[0].flag = true;

}

void initialize2(struct workerattr *wattr) {

	Data dt = wattr->winfo->ptr2job->dta;
	int lb = wattr->winfo->ptr2job->lb;
	int ub = wattr->winfo->ptr2job->ub;
	int i, rowIndex;
	rowIndex = taskid * (global_N / ntasks);

	int idx;

	for (i = lb; i < ub; i++) {

		//idx = i - rowIndex;
		dt.V[i][0] = 0.0;
		dt.z[i] = 0;
		//wattr->winfo->ptr2job->retval[0].z[i] = 0.0;
		dt.r[i][0] = dt.x[i][0];
		dt.p[i] = dt.r[i][0];
		//wattr->winfo->ptr2job->retval[0].p[i] = dt.r[i][0];

	}
	//printf("Rank = %d lb = %d ub = %d init2 done \n",taskid,lb,ub);

}

void compute1(struct workerattr *wattr) {
	Data dt = wattr->winfo->ptr2job->dta;
	int lb = wattr->winfo->ptr2job->lb;
	int ub = wattr->winfo->ptr2job->ub;
	int i, e, idx;

	wattr->winfo->ptr2job->retval[0].pAp = 0;
	wattr->winfo->ptr2job->retval[0].rr = 0;

	for (i = lb; i < ub; i++) {

		dt.V[i][0] = 0;

		for (e = 0; e < dt.rowstr[i].num; e++) {
			idx = dt.rowstr[i].colidx[e];
			dt.V[i][0] += dt.A[i][e] * dt.p[dt.rowstr[i].colidx[e]];

		}

		wattr->winfo->ptr2job->retval[0].pAp += dt.p[i] * dt.V[i][0]; //p'*A*p
		wattr->winfo->ptr2job->retval[0].rr += dt.r[i][0] * dt.r[i][0]; //r'*r

	}

	wattr->winfo->ptr2job->retval[0].flag = true;
	//printf("Rank = %d compute1 done lb = %d ub = %d \n",taskid,lb,ub);

}

void combineAtPlace0afterCOMP1(struct jobinfo* present_job) {

	if (present_job->retval[1].flag != false) {

		present_job->retval[0].rr = present_job->retval[0].rr
				+ present_job->retval[1].rr;
		present_job->retval[0].pAp = present_job->retval[0].pAp
				+ present_job->retval[1].pAp;

	}

	present_job->dta.h = present_job->retval[0].rr / present_job->retval[0].pAp;

}

void compute2(struct workerattr *wattr) {
	Data dt = wattr->winfo->ptr2job->dta;
	int lb = wattr->winfo->ptr2job->lb;
	int ub = wattr->winfo->ptr2job->ub;
	int i, k;
	wattr->winfo->ptr2job->retval[0].g = 0;
	for (i = lb; i < ub; i++) {
		//printf("Rank = %d \tdt.h = %f\n",taskid,dt.h);
		dt.z[i] += dt.h * dt.p[i]; //z = z + h*p
		dt.r[i][0] -= dt.h * dt.V[i][0]; //new_r = r - h*V
		wattr->winfo->ptr2job->retval[0].g += (dt.r[i][0] * dt.r[i][0])
				/ (wattr->winfo->ptr2job->retval[0].rr);//g = ( new_r'*new_r ) / ( r'*r )

	}
	wattr->winfo->ptr2job->retval[0].flag = true;

	//	printf("taskid = %d compute2 done \n",taskid);

}

void combineAtPlace0afterCOMP2(struct jobinfo* present_job) {

	int k, e;

	if (present_job->retval[1].flag != false) {

		present_job->retval[0].g = present_job->retval[0].g
				+ present_job->retval[1].g;

	}

}

void compute3(struct workerattr *wattr) {
	Data dt = wattr->winfo->ptr2job->dta;
	int lb = wattr->winfo->ptr2job->lb;
	int ub = wattr->winfo->ptr2job->ub;
	int i;

	for (i = lb; i < ub; i++) {

		dt.p[i] = dt.r[i][0] + wattr->winfo->ptr2job->retval[0].g * dt.p[i];
	}
	wattr->winfo->ptr2job->retval[0].flag = true;

}

void compute4(struct workerattr *wattr) {
	Data dt = wattr->winfo->ptr2job->dta;
	int lb, ub, i, e, idx;
	lb = wattr->winfo->ptr2job->lb;
	ub = wattr->winfo->ptr2job->ub;
	wattr->winfo->ptr2job->retval[0].rnorm = 0;
	int num, prevnum;
	for (i = lb; i < ub; i++) {

		dt.r[i][0] = 0;

		for (e = 0; e < dt.rowstr[i].num; e++) {
			idx = dt.rowstr[i].colidx[e];
			dt.r[i][0] += dt.A[i][e] * dt.z[dt.rowstr[i].colidx[e]];

		}
		//		printf("taskid = %d i = %d num = %d prevnum = %d\n",taskid,i,num,prevnum);

		dt.r[i][0] = dt.x[i][0] - dt.r[i][0];
		wattr->winfo->ptr2job->retval[0].rnorm += dt.r[i][0] * dt.r[i][0];
	}

	wattr->winfo->ptr2job->retval[0].flag = true;
}

void combineAtPlace0afterCOMP4(struct jobinfo* present_job) {

	int k, e;

	if (present_job->retval[1].flag != false) {

		present_job->retval[0].rnorm = present_job->retval[0].rnorm
				+ present_job->retval[1].rnorm;

	}
	present_job->retval[0].rnorm = sqrt(present_job->retval[0].rnorm);

}

void compute5(struct workerattr *wattr) {
	Data dt = wattr->winfo->ptr2job->dta;
	int lb, ub, i;
	lb = wattr->winfo->ptr2job->lb;
	ub = wattr->winfo->ptr2job->ub;

	wattr->winfo->ptr2job->retval[0].norm_temp11 = 0;
	wattr->winfo->ptr2job->retval[0].norm_temp12 = 0;
	for (i = lb; i < ub; i++) {

		wattr->winfo->ptr2job->retval[0].norm_temp11 += dt.x[i][0] * dt.z[i];
		wattr->winfo->ptr2job->retval[0].norm_temp12 += dt.z[i] * dt.z[i];

	}
	wattr->winfo->ptr2job->retval[0].flag = true;
}

void combineAtPlace0afterCOMP5(struct jobinfo* present_job) {

	if (present_job->retval[1].flag != false) {

		present_job->retval[0].norm_temp11 = present_job->retval[0].norm_temp11
				+ present_job->retval[1].norm_temp11;
		present_job->retval[0].norm_temp12 = present_job->retval[0].norm_temp12
				+ present_job->retval[1].norm_temp12;

	}

	present_job->retval[0].norm_temp12 = 1.0 / sqrt(
			present_job->retval[0].norm_temp12);

	present_job->dta.zeta = shift + 1.0 / present_job->retval[0].norm_temp11;

}
void compute6(struct workerattr *wattr) {
	Data dt = wattr->winfo->ptr2job->dta;
	int lb, ub, i;
	lb = wattr->winfo->ptr2job->lb;
	ub = wattr->winfo->ptr2job->ub;
	for (i = lb; i < ub; i++) {

		dt.x[i][0] = wattr->winfo->ptr2job->retval[0].norm_temp12 * dt.z[i];
	}
	wattr->winfo->ptr2job->retval[0].flag = true;

}

void printResultsAfterCOMP6(struct jobinfo* present_job) {

	if (present_job->C == 1) {
		printf("   iteration           ||r||                 zeta\n");
	}
	printf("    %5d       %20.14e%20.13e\n", present_job->C,
			present_job->retval[0].rnorm, present_job->dta.zeta);

}

