/******************************************************************************
* FILE: mpi_hello.c
* DESCRIPTION:
*   MPI tutorial example code: Simple hello world program
* AUTHOR: Blaise Barney
* LAST REVISED: 03/05/10
******************************************************************************/
#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#define  MASTER		0

int main (int argc, char *argv[])
{
   int   numtasks, taskid, len;
   char hostname[MPI_MAX_PROCESSOR_NAME];

   // Initialize the MPI runtime
   MPI_Init(&argc, &argv);
   // Get the size of the MPI world. i.e. number of tasks
   MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
   // Get my current taskID 
   MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
   // Get the hostname
   MPI_Get_processor_name(hostname, &len);

   // Print this information
   printf ("Hello from task %d on %s!\n", taskid, hostname);

   if (taskid == MASTER)
      printf("MASTER: Number of MPI tasks is: %d\n",numtasks);
   
   // Finish the MPI runtime
   MPI_Finalize();

}

