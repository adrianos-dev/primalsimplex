#include<stdlib.h>
#include<stdio.h>

// print to the screen.

void print_vars(char vars[6][2])
{
 for (int i=0;i<6;++i)
 {
  for (int j=0;j<2;++j)
  {
   printf("%c",vars[i][j]);
  }
   printf("%s\t\t","");
 }
 printf("%s\n","");
}


void print_vector(double* v,int size){for (int i=0;i<size;++i) { printf("%f\t",v[i]); } printf("%s\n",""); }

void print2_screen(double (*M)[10],int r,int c)
{
 for (int i =0;i<r;++i)
 {
  for (int j=0;j<c;++j) 
  {
   printf("%f\t",M[i][j]);
  }
  printf("%s\n","");
 } 
  printf("%s\n","");
}


void print_bases(double M[rows][cols])
{
 for (int i =0;i<rows;++i)
 {
  for (int j=0;j<cols;++j) 
  {
   printf("%f\t",M[i][j]);
  }
  printf("%s\n","");
 } 
  printf("%s\n","");
}


