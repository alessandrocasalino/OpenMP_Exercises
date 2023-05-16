#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

int main ( int argc, char *argv[] );

/******************************************************************************/

int main ( int argc, char *argv[] )

/******************************************************************************/

{
    int i;
    int n = 10000000;
    double tick, tock;

    float *a;
    float *b;
    float *c;

    printf ( "\n" );
    printf ( "Vector addition\n" );
    printf ( "  C/OpenMP version\n" );
    printf ( "\n" );
    printf ( "  A program which adds two vector.\n" );

/*
  Allocate the vector data.
*/
    a = ( float * ) malloc ( n * sizeof ( float ) );
    b = ( float * ) malloc ( n * sizeof ( float ) );
    c = ( float * ) malloc ( n * sizeof ( float ) );

    for ( i = 0; i < n; i++ )
    {
        a[i] = ( float ) ( 1 );
        b[i] = ( float ) ( 2 );
        c[i] = ( float ) ( 0 );
    }

    tick = clock();
    for ( i = 0; i < n; i++ )
    {
        c[i] = a[i] + b[i];
    }

    tock = clock();

/*
  Print a few entries.
*/
    printf ( "\n" );
    printf ( "   i        a[i]        b[i]      c[i] = a[i] + b[i]\n" );
    printf ( "\n" );
    for ( i = 0; i < n && i < 10; i++ )
    {
        printf ( "  %2d  %10.4f  %10.4f  %10.4f\n", i, a[i], b[i], c[i] );
    }
/*
  Free memory.
*/
    free ( a );
    free ( b );
    free ( c );
/*
  Terminate.
*/
    printf ( "\n" );
    printf ( "Vector addition\n" );
    printf ( "  Normal end of execution.\n" );

    printf("===================================== \n");
    printf("Work took %f seconds\n", tock - tick);
    printf("===================================== \n");

    return 0;
}
