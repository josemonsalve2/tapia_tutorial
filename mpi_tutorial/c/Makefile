##############################################################################
# FILE: Makefile.MPI.c
# DESCRIPTION:
#   Makefile for all MPI C Language example codes
# AUTHOR: Blaise Barney
# LAST REVISED:  05/10/16
###############################################################################

#Uncomment your choice of compiler
CC    =   mpicc
#CC    =   mpigcc
#CC    =   mpipgcc

#Add your choice of flags
FLAGS   =   -O2 -w

all:    mpi_array       \
        mpi_mm          \
        mpi_pi_send     \
        mpi_hello       \
        mpi_DotProd

clean:  
	/bin/rm -rf     \
	initial.dat     \
	final.dat       \
	mpi_array       \
	mpi_mm          \
	mpi_pi_send     \
	mpi_array       \
	mpi_DotProd     \
	mpi_hello       \
        *.o
        


mpi_array:  mpi_array.c
	$(CC) $(FLAGS) mpi_array.c -o mpi_array

mpi_DotProd:  mpi_DotProd.c 
	$(CC) $(FLAGS) mpi_DotProd.c -o mpi_DotProd


mpi_mm:  mpi_mm.c
	$(CC) $(FLAGS) mpi_mm.c -o mpi_mm


mpi_pi_send:  mpi_pi_send.c
	$(CC) $(FLAGS) mpi_pi_send.c -o mpi_pi_send

mpi_hello:  mpi_hello.c 
	$(CC) $(FLAGS) mpi_hello.c -o mpi_hello
