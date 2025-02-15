#include<stdlib.h>
#include<stdio.h>

// multiply A*B and overwrites B 
void mult(double A[rows][cols],double B[rows][cols])
{

 double (*res)[cols] = malloc((rows*cols)*sizeof(double));
 double temp = 0.0;
 int    c    = 0;
 for (int i = 0;i < rows;++i)
 {
    c = 0;
    while (c<cols)
    {
     temp = 0;
     for (int j=0;j<cols;++j)
     {
      temp  =  temp + A[i][j]*B[j][c];
     }
     res[i][c] = temp;
     ++c;
     temp = 0;
    }
   temp = 0;
 }
 // now copy res to B.
 for (int i =0;i<rows;++i)
 {
  for (int j=0;j < cols;++j)
  {
   B[i][j] = res[i][j];
  }
 }
 free(res);
}


// create I of order n=rows=cols 
void create_Identity(double A[rows][cols])
{
 for(int i=0;i<rows;i++)
 {
  for (int j=0;j<cols;j++)
  {
   if (i==j)
   {
     A[i][j]=1.0;
   } else {A[i][j]=0;};
  }
 } 
}
// duplicate a matrix. copy operator overloading.
void copy_matrix(double A[rows][cols],double res[rows][cols]){ 

for (int i =0; i < rows;++i)
 {
  for (int j=0;j < cols;++j)
  {
   res[i][j] = A[i][j];
  }
 }
}
