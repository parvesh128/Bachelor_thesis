/*
 * kmeans.h
 *
 *  Created on: 13-May-2011
 *      Author: parvesh
 */

#ifndef KMEANS_H_
#define KMEANS_H_

#include"Sched.h"
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<pthread.h>

// DEFINATION USED IN k-means APPLICATION
#define BIGNUM 1.0e12

#define randa(y,t) (exp(-2*(t))*sin(y))
#define randb(y,t) (exp(-2*(t))*sin(y+1))

/************************************/
double readstart_time;
double readtime;

/*FUNCTIONS USED BY K-MEANS*/
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
void readandinitializeDataPoints(struct workerattr *wattr);
void initializeCentroids(struct jobinfo *job);
void computekMeans(struct workerattr *wattr);
void intialize_kmeans_variable();

/************************/

#endif /* KMEANS_H_ */
