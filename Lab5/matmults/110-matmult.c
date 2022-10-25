/*mat_mult.c */

#include <stdio.h>
// #include <stdlib.h>
// #include <time.h>
// #include <math.h>


#define NRA 60            /* number of rows in matrix A */
#define NCA 12            /* number of columns in matrix A */
#define NRB 12            /* number of rows in matrix B, should equal to NCA */
#define NCB 10            /* number of columns in matrix B */

int main (int argc, char *argv[])
{
int	i, j, k;           /* misc */
int	A[NRA][NCA],         /* matrix A to be multiplied */
 	B[NRB][NCB],           /* matrix B to be multiplied */
	C[NRA][NCB];           /* result matrix C */

// Do some basic error checking
      if (NRB != NCA) {
        printf ("Matrix a column size must equal matrix b row size.\n");
        return 1;
      } 
               
      printf("Matrix A: #rows %d; #cols %d\n", NRA, NCA);
      printf("Matrix B: #rows %d; #cols %d\n", NRB, NCB);
      printf ("\n");

      printf("Initializing arrays...\n");
      for (j=0; j<NCA; j++)
         for (i=0; i<NRA; i++)
            A[i][j]= i+j; 

      for (j=0; j<NCB; j++)                 
         for (i=0; i<NRB; i++)   
            B[i][j]= i-j;

      

      /* Calculate matmul results for C */     
      for (i=0; i<NRA; i++)
         for (j=0; j<NCB; j++)
         {
           C[i][j] = 0;
           for (k=0; k<NCA; k++)            
              C[i][j] = C[i][j] + A[i][k] * B[k][j];
         }
      
      /* Print results */
      printf ("\n");
      printf("******************************************************\n");
      printf("Result Matrix:\n");
      i = NRA-1;
      {
         printf("\n"); 
         for (j=0; j<NCB; j++) 
            printf("%d\t", C[i][j]);
      }
      
      printf("\n******************************************************\n");
      printf ("\n");
}