#include<stdio.h>
#include<stdlib.h>
#include"utils.h"
#include"inverse.h"
#include"print.h"

void STOPSIMPLEX(char s[100])
{ 
 printf("%s\n",s);
}


char vars[4][2] = {"x1","x2","x3","x4"};
void swap_chars(char A[rows][2],int entry,int exit)
{
  char en[2] = "00";
  char ex[2] = "00";
  ex[0]  =    A[exit][0];
  ex[1]  =    A[exit][1];
  en[0]  =    A[entry][0];
  en[1]  =    A[entry][1];

  A[exit][0]   =  en[0];
  A[exit][1]   =  en[1];
  A[entry][0]  =  ex[0];
  A[entry][1]  =  ex[1];

}

// Calculate ci-zi and zi = c^b*y_i

void calc_zi_ci(double c_j[cols],double c_b[rows],double c_n[cols],double Y[rows][cols])
{
 double temp = 0;
 for (int j=0;j<rows;++j)
 {
  for (int i =0;i<rows;++i)
  { 
   temp = temp + c_b[i]*Y[i][j]; // calculat zi = c_b[j]*y[j]
   //printf("%f\n",temp);
  } 
  c_j[j] = temp - c_n[j]; // c_n coefficients of non basic variables in target function
  temp=0;
 }

}

double calc_cb_xb(double c_b[rows],double* xb)
{
 double s=0;
 for  (int i=0;i<rows;++i)
 {
  for (int j=0;j<rows;++j) 
  {
   s = s + c_b[i]*xb[i];
  }
 }
return s;
}

void initialize_matrix(double (*A)[10],double B[rows][cols],double N[rows][cols],char vars[6][2])
{
   int B_arr[3] = {0,0};
   int N_arr[3] = {0,0};
   int newc;
   int kb=0;
   int kn=0;
   for (int z=0;z<2*cols;++z)
   {
    if (vars[z][1] == '1') newc=0;
    if (vars[z][1] == '2') newc=1;
    if (vars[z][1] == '3') newc=2;
    if (vars[z][1] == '4') newc=3;
    if (z<rows)
    {
     B_arr[z] = newc;
    }
    if (z>(rows-1))
    {
     N_arr[z-cols] = newc;
    }
   }
    // initialze B from A
    int w;
    int cb=0;
    for (int j=0;j<cols;++j)
    {
     w = B_arr[j];
     for (int k=0;k<rows;++k)
     {
      B[k][cb]  = A[k][w];
     }
     ++cb;
    }
   //// initialize N from A
   int xx;
   int c=0;
    for (int j=0;j<cols;++j)
    {
    xx = N_arr[j];
     for (int k=0;k<rows;++k)
     {
      N[k][c]  = A[k][xx];
     }
     ++c;
    }
}

void update_A(double (*A)[10],double B[rows][cols],double N[rows][cols],double b[rows],double z[rows],int enter,int exit,double pivot)
{
 printf("%s\t%d\t%d\n","Pivot in A is at: ",exit,enter);
 //divide A by the pivot value. Make sure the pivot is +1!.
 double temp = 0;
 double b_temp = 0;
 b_temp = b[exit]/pivot; // divide by the pivot.
 b[exit] = b_temp;
 for (int j=0;j<2*cols;++j) // divide every column on line exit by the pivot value.
 {
  temp       =  A[exit][j]/pivot;  
  A[exit][j] =  temp; 
 }

 // Now make zeros on the pivot column.
 for (int i =0;i<rows;++i)
 {
  double val,old_v,old_b,temp2;
  if (i!=exit)
  {
   val = A[i][enter]; // find value of row i in entrycolumn.
   old_b = b[i] + -1*val*b[exit];
   b[i] =  old_b;
   for (int j=0;j<2*cols;++j)
   {
    old_v = A[i][j];
    temp2 = -1*val*A[exit][j];
    A[i][j] = old_v + temp2; // new value
   }
  }
 } 
 // update de zi-ci vector
 double f = -z[enter];
 double val1,val2;
 for (int i=0;i<2*cols;++i)
 {
  val1 = f*A[exit][i];
  val2 = z[i];
  z[i] = val1 + val2;
  if ( (z[i]>=0) && (z[i] < 0.02) ) z[i]=0;
  val1 =0;
  val2 =0;
 } 

 // update B and N from A.
 initialize_matrix(A,B,N,vars);
}

int status(double z[2*rows])
{
int running = 0; // false (optimal found, stop running)
for (int i=0;i<2*rows;++i)
 {
  if (z[i]>0.1) {running=1;return running;};
 }
return running;
}

int main()
{
 double   x1,x2,x3,x4,x5,x6;
 double   z[2*rows]             =  {0,0,50,80}; //zi-ci, initialize to zeros first 
 double   c_b[cols]        =  {0,0};
 double   c_n[cols]        =  {-50,-80};
 double   b[cols]          =  {120,90}; //result of Ax=b;
 //double*  b = bp;
 double   A[rows][10]      =  { {1,0,1,2},
                                {0,1,1,1},
                               };
 //double   (*Ap)[10]        =  A;
 double   (*B)[cols]       = malloc((rows*cols)*sizeof(double));
 double   (*N)[cols]       = malloc((rows*cols)*sizeof(double));

 double   Y[rows][cols];
 double   (*inv)[cols] = malloc((rows*cols)*sizeof(double));
 double   *xb   =  malloc(sizeof (double)*cols);
 double*  c_j   = (double*)calloc(cols,sizeof(double)); // initialize with zeros.
 
 printf("%s\n","Starting table"); 
 print_vars(vars);
 print_vector(z,2*rows);
 printf("%s\n"," - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ");
 print2_screen(A,rows,2*cols);

 initialize_matrix(A,B,N,vars);
 calculate_inverse(B,inv);
 mult(inv,N);
 copy_matrix(N,Y); // overwrites Y
 calc_xb(inv,b,xb);
 //
 calc_zi_ci(c_j,c_b,c_n,Y); // calculate zi-ci  stored in vector c_j. 
 double s = calc_cb_xb(c_b,xb);
 int xx,h;
 double pivot;
 double* exit = malloc(sizeof(double)*rows);
 int iter = 0;
 int update_cj[rows] = {0,0};
 int running=1; // run while 1
 while (running)
 {
  printf("%s\n"," ");
  printf("%s\t%i\n","Iteration",iter); 
  printf("%s\n"," ");
  print_vars(vars);
  print_vector(z,2*rows);
  printf("%s\n","- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ");
  print2_screen(A,rows,2*cols);
  printf("%s"," ");

  // index variable to enter the base. 
  xx = return_max(c_j,rows); // counts from 4...
  printf("%s\t%i\n","xx= ",xx);

  // exit criteria. take MIN of {} formed by:
  for (int i=0;i<rows;++i)
  {
   exit[i] = b[i]/N[i][xx]; // extract column i
  }
  h = return_min(exit,rows); // index variable to exit the base.
  printf("%s%d%s%d\n","The variable index to enter and exit from A are : ",xx+rows," ",h);
  swap_chars(vars,xx+rows,h); // vars, enter,exit.
  // Find the pivot.
  pivot = A[h][xx+rows];
  printf("%s%f\n","Pivot has the value: ",pivot);
  printf("%s\t%i\t%i\n","A index entry-exit are:",xx+cols,h);
  update_A(A,B,N,b,z,xx+cols,h,pivot); // enter,exit,pivot
  //

  // update c_j 
  int count=0;
  for (int i=2;i<4;++i)
  {
   c_j[count] = z[i];
   ++count;
  }
  // check values of z
  running = status(z);
  if (running==0) STOPSIMPLEX("Optimal solution found,STOP!");
  ++iter;
 }
 print_vars(vars);
 print_vector(b,2);
}



