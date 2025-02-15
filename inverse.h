#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include"inverse_matrix.h"

// extract column 'c' from matrix A into pointer  *p   
void extract_c(double A[rows][cols],double* p,int c)
{
 for (int i =0;i<rows;++i)
 {
  p[i] = A[i][c];
 }
}

// overwrite a column on a matrix (identity) .
void write_c(double A[rows][cols],double* p,int rows,int c)
{
 double* f = malloc((rows)*sizeof(double));
 const double factor = p[c];
 for (int i=0;i<rows;++i)
 {
  if (i==c && factor<0) f[i] =   1/factor;
  if (i==c && factor>0) f[i] =   1/factor; 
  if (i!=c && factor<0) f[i] =  -p[i]/factor;
  if (i!=c && factor>0) f[i] =  -p[i]/factor;
 }
 for (int i=0;i<rows;++i)
 {
   A[i][c] = f[i];
 } 
}

// return index where absolute value of max occurs.
// fabs() is for double and abs() is for integers.
int max(double* p,int rows)
{
 int i = 0;
 int j = 0;
 double m = fabs(p[0]);
 while (i<rows)
 {
  m = (fabs(p[i])>m) ? fabs(p[i]) : m;
  i = i + 1;
 }
 for (j=0;j<rows;++j) if (fabs(p[j])==m) {break;};
 return j;
} 

void create_Permutation(double A[rows][cols],int r,int c,double val)
{ // r is the index with value 'val'  where the maxium of p accurs. c is the current column.
  if (r<c) {r = c + 1;}
  for(int i=0;i<rows;++i)
  { for (int j=0;j<cols;++j) 
    {
     if (i==j) {A[i][j]=1.0; } else  {A[i][j]=0;}
    }
  } 
 if (val==0)  
 {
 {A[c][r]=1;A[c][c]=0;A[r][r]=0;A[r][c]=1;}   // first column but needs permut.
 }
}

void set_malloc()
{
 double  (*pp1)[cols]   =  malloc((rows*cols)*sizeof(double));
 double  (*pp2)[cols]   =  malloc((rows*cols)*sizeof(double));
 double  (*I)[cols]     =  malloc((rows*cols)*sizeof(double));
 double*    p           =  malloc((rows)*sizeof(double));
}

//main function
void calculate_inverse(double myarr[rows][cols],double Inv[rows][cols])
{

 double  (*pp1)[cols]      =  malloc((rows*cols)*sizeof(double));
 double  (*pp2)[cols]      =  malloc((rows*cols)*sizeof(double));
 double  (*I)[cols]        =  malloc((rows*cols)*sizeof(double));
 //double  myarr[rows][cols] =  {{1,1,0,1},{0,1,1,0},{-1,1,1,1},{0,0,0,1}};

 double* p   = malloc((rows)*sizeof(double));
 double  val =  0;
 int     m   =  0;
 int     x   =  0;

 create_Identity(Inv);   // First initialize the inverse as Identity matrix.
  while (x<cols)
  {
  extract_c(myarr,p,x);  // extract column from myarr. overwrites p.
  m   = max(p,rows);          //  index where maximum occurs.
  val = myarr[x][x];          //  the value on the diagonal.
  create_Permutation(pp1,m,x,val); // creates pp as I or P
  create_Permutation(pp2,m,x,val); // creates pp as I or P
  mult(pp1,myarr);            // overwrites myarr
  mult(pp2,Inv);              // overwrites  Inv
  free(p);
  p = malloc((rows)*sizeof(double));
  extract_c(myarr,p,x);     // extract column x from myarr  into p.
  create_Identity(I);       // creates I matrix to be inverted. 
  write_c(I,p,rows,x);      // add column p to I
  mult(I,Inv);              // overwrites Inv
  mult(I,myarr);            // A*B and returns B 
  free(p);
  free(I);
  free(pp1);
  free(pp2);
  set_malloc(); // function memory allocate several arrays.
  //printf("%s","\n");
  ++x;
  }
}
