/*matmult.c */

#include <stdio.h>

#define NRA 60            /* number of rows in matrix A */
#define NCA 12            /* number of columns in matrix A */
#define NRB 12            /* number of rows in matrix B, should equal to NCA */
#define NCB 10            /* number of columns in matrix B */

int main (int argc, char *argv[])
{
int	
   A[NRA][NCA],         /* matrix A to be multiplied */
 	B[NRB][NCB],         /* matrix B to be multiplied */
	C[NRA][NCB];         /* result matrix C */

   /* Do some basic error checking */
      if (NRB != NCA) {
        printf ("Matrix a column size must equal matrix b row size.\n");
        return 1;
      } 
               
      printf("Matrix A: #rows %d; #cols %d\n", NRA, NCA);
      printf("Matrix B: #rows %d; #cols %d\n", NRB, NCB);
      printf ("\n");


   /* Initializing and printing matrix A */
      printf("Initializing matrix A...\n");
      printf ("Contents of matrix A\n");
      for(int i = 0; i < NRA; i++){
         for(int j = 0; j < NCA; j++){
            A[i][j] = i + j;
            if(A[i][j]/10){
               printf("%d ", A[i][j]);
            }
            else{
               printf(" %d ", A[i][j]);
            }
         }
         printf("\n");
      }


   /* Initializing and printing matrix B */
      printf("Initializing matrix B...\n");
      printf ("Contents of matrix B\n");
      for(int i = 0; i < NRB; i++){
         for(int j = 0; j < NCB; j++){
            B[i][j] = i - j;
            if(B[i][j]/10 || B[i][j] < 0){
               printf("%d ", B[i][j]);
            }
            else{
               printf(" %d ", B[i][j]);
            }
         }
         printf("\n");
      }
   int sum = 0, row = 0, col = 0;
   /* Calculate matmult results for C */     
      for(int i = 0; i < NRA; i++){
         for(int j = 0; j < NCB; j++){
            sum = 0;
            for(int iter = 0; iter < NCA; iter++){
               sum = sum + (A[i][iter] * B[iter][j]);
            }
            C[i][j] = sum;
         }
      }
      
   /* Print results */
      printf ("\n");
      printf("******************************************************\n");
      printf("Result Matrix:\n");
      for (int i=0; i<NRA; i++)
      {
         printf("\n"); 
         for (int j=0; j<NCB; j++) 
            printf("%d\t", C[i][j]);
      }
      
      printf("\n******************************************************\n");
      printf ("\n");
}