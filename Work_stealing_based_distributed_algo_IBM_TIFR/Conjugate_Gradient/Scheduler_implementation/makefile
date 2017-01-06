all: exe

exe: main.o cg.o Sched.o 
	mpicc -lpthread main.o cg.o Sched.o -o exe -g -lrt -lm

main.o: main.c cg.o 
	mpicc -c -D_GNU_SOURCE  main.c

cg.o: cg.c
	mpicc -c  cg.c

Sched.o: Sched.c
	mpicc -c -D_GNU_SOURCE Sched.c
	
clean:
	rm -rf *o hello
