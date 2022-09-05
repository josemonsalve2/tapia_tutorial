/******************************************************************************
 * FILE: mpi_array.c
 * DESCRIPTION:
 *   MPI Example - Dot (scalar) product of two vectors  - C Version
 *   This program demonstrates a simple data decomposition. The master task
 *   first initializes two  arrays and then distributes an equal portion of each
 *   array to the other tasks. After the other tasks receive their portion
 *   of the arrays, they perform an dot product operation to each array element.
 *   They also maintain a sum for their portion of the array. The master task
 *   does likewise with its portion of the array. As each of the non-master
 *   tasks finish, they send their updated portion of the array to the master.
 *   An MPI collective communication call is used to collect the sums
 *   maintained by each task.
 * AUTHOR: Don Frederick
 * LAST REVISED: 08/13/20
 ****************************************************************************/
#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#define ARRAYSIZE 16000000
#define MASTER 0

double data1[ARRAYSIZE], data2[ARRAYSIZE];

int main(int argc, char *argv[])
{
  int numtasks, taskid, rc, dest, offset, i, j, tag1,
      tag2, tag3, tag4, source, chunksize;
  double mysum, sum, psum, msum;
  double update(int myoffset, int chunk, int myid);
  MPI_Status status;

  /***** Initializations *****/
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

  MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
  printf("MPI task %d has started...\n", taskid);
  chunksize = (ARRAYSIZE / numtasks);
  tag2 = 1;
  tag1 = 2;
  tag3 = 3;
  tag4 = 4;

  /***** Master task only ******/
  if (taskid == MASTER)
  {

    /* Initialize the arrays */
    sum = 0;
    for (i = 0; i < ARRAYSIZE; i++)
    {
      data1[i] = i * 1.0;
      data1[i] = 1.0;
      data2[i] = data1[i] + 1.0;
      sum = sum + data1[i] * data2[i];
    }
    printf("Initialized array serial dot product = %e\n", sum);

    /* Send each task location for its portion of the array - master keeps 1st part */
    offset = chunksize;
    for (dest = 1; dest < numtasks; dest++)
    {
      MPI_Send(&offset, 1, MPI_INT, dest, tag1, MPI_COMM_WORLD);
      MPI_Send(&data1[offset], chunksize, MPI_DOUBLE, dest, tag2, MPI_COMM_WORLD);
      MPI_Send(&data2[offset], chunksize, MPI_DOUBLE, dest, tag3, MPI_COMM_WORLD);
      printf("Sent %d elements to task %d offset= %d\n", chunksize, dest, offset);
      offset = offset + chunksize;
    }

    /* Master does its part of the work */
    offset = 0;
    msum = update(offset, chunksize, taskid);

    /* Wait to receive results from each task */
    psum = 0.0;
    sum = 0.0;
    for (i = 1; i < numtasks; i++)
    {
      source = i;
      MPI_Recv(&psum, 1, MPI_DOUBLE, source, tag4, MPI_COMM_WORLD, &status);

      sum = psum + sum;
    }
    sum = sum + msum;
    /* Get final sum and print sample results */

    printf("*** Parallel Dot-product = %e ***\n", sum);

  } /* end of master section */

  /***** Non-master tasks only *****/

  if (taskid > MASTER)
  {

    /* Receive my portion of array from the master task */
    source = MASTER;
    MPI_Recv(&offset, 1, MPI_INT, source, tag1, MPI_COMM_WORLD, &status);
    MPI_Recv(&data1[offset], chunksize, MPI_DOUBLE, source, tag2,
             MPI_COMM_WORLD, &status);
    MPI_Recv(&data2[offset], chunksize, MPI_DOUBLE, source, tag3,
             MPI_COMM_WORLD, &status);
    mysum = update(offset, chunksize, taskid);

    /* Send my results back to the master task */
    dest = MASTER;
    MPI_Send(&mysum, 1, MPI_DOUBLE, dest, tag4, MPI_COMM_WORLD);

  } /* end of non-master */

  MPI_Finalize();

} /* end of main */

double update(int myoffset, int chunk, int myid)
{
  int i;
  double mysum;
  /* Perform  dotproduct on array elements and return result as  my sum */
  mysum = 0;
  for (i = myoffset; i < myoffset + chunk; i++)
  {

    mysum = mysum + data1[i] * data2[i];
  }
  printf("Task %d mysum = %e\n", myid, mysum);
  return (mysum);
}
