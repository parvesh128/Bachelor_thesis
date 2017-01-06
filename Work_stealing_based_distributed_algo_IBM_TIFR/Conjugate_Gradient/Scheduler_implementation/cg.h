/*
 * cg.h
 *
 *  Created on: 13-May-2011
 *      Author: parvesh
 */

#ifndef CG_H_
#define CG_H_

#include"Sched.h"


// DEFINATION USED IN CG APPLICATION
//#define BIGNUM 1.0e12

//#define randa(y,t) (exp(-2*(t))*sin(y))
//#define randb(y,t) (exp(-2*(t))*sin(y+1))

/************************************/

double readstart_time;
double readtime;

/*FUNCTIONS USED BY CG*/
void function0(struct workerinfo *);
void function1(struct workerinfo *);
void function2(struct workerinfo *);
void function3(struct workerinfo *);
void function4(struct workerinfo *);
void function5(struct workerinfo *);
void function6(struct workerinfo *);
void function7(struct workerinfo *);
void function8(struct workerinfo *);
void function9(struct workerinfo *);
void return_func(struct workerinfo *);

void allocateinitial(Data* dt);

void readandinitializeData(struct workerattr *wattr);
void initialize1(struct workerattr *wattr);
void initialize2(struct workerattr *wattr);

void compute1(struct workerattr *wattr);
void combineAtPlace0afterCOMP1(struct jobinfo* present_job);
void compute2(struct workerattr *wattr);
void combineAtPlace0afterCOMP2(struct jobinfo* present_job);
void compute3(struct workerattr *wattr);
void compute4(struct workerattr *wattr);
void combineAtPlace0afterCOMP4(struct jobinfo* present_job);
void compute5(struct workerattr *wattr);
void combineAtPlace0afterCOMP5(struct jobinfo* present_job);
void compute6(struct workerattr *wattr);
void printResultsAfterCOMP6(struct jobinfo* present_job);

/************************/

#endif /* CG_H_ */
