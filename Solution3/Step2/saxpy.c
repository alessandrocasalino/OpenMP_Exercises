#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <time.h>
#include <omp.h>
#define ARRAY_SIZE 512 * 512 * 512

#define CHUNKSIZE 16

int main(int argc, char *argv[])
{
  printf("The total memory allocated is %7.3lf GB.\n",
         2.0 * sizeof(double) * ARRAY_SIZE / 1024 / 1024 / 1024);
  int i;
  double scalar = 2.0;
  double *x = NULL;
  double *y = NULL;
  double start_time, end_time;

  printf("\n");
  printf("Vector addition\n");
  printf("  C/OpenMP version\n");
  printf("\n");
  printf("  A program which adds two vector.\n");

  /* ..........Allocate the vector data ............. */
  x = (double *)malloc(sizeof(double) * ARRAY_SIZE);
  y = (double *)malloc(sizeof(double) * ARRAY_SIZE);

  /* .......... initialize on the host ............. */

  for (i = 0; i < ARRAY_SIZE; i++)
  {
    x[i] = 1.0;
    y[i] = 2.0;
  }

  start_time = omp_get_wtime();
#pragma omp parallel for schedule(guided) // NOLINT
  for (i = 0; i < ARRAY_SIZE; i++)
  {
    y[i] = scalar * x[i] + y[i];
  }
  end_time = omp_get_wtime();

  /* .......... Print a few entries ............. */
  printf("\n");
  printf("   i        x[i]        y[i]      y[i] = scalar*x[i] + y[i]\n");
  printf("\n");
  for (i = 0; i < ARRAY_SIZE && i < 10; i++)
  {
    printf("  %2d  %10.4f  %10.4f  %10.4f\n", i, x[i], y[i], y[i]);
  }

  /* .......... Free memory ............. */

  free(x);
  free(y);

  /* .......... Terminate ............. */

  printf("\n");
  printf("===================================== \n");
  printf("SAXPY Time: %f seconds \n", (end_time - start_time));
  printf("===================================== \n");

  return 0;
}

/* ..........Program Listing Completed ............. */
