all: exe

exe: main.o kmeans.o Sched.o
	mpicc -lpthread -g main.o kmeans.o Sched.o -o kmeans -g -lrt -lm

main.o: main.c kmeans.o Sched.o
	mpicc -c -D_GNU_SOURCE  main.c

kmeans.o: kmeans.c
	mpicc -c kmeans.c

Sched.o: Sched.c
	mpicc -c -D_GNU_SOURCE Sched.c

clean:
	rm -rf *o hello
