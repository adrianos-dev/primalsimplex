#include<stdlib.h>
#include<stdio.h>
const int rows = 2;
const int cols = 2;

int return_max(double* v,int lines)
{
 int i=0;
 double m = v[0];
 while (i<lines)
 {
  m = (m>v[i]) ? m : v[i];
  ++i;
 } 
 int index;
 for (int j=0;j<lines;++j)
 {
  if (v[j] == m) {index=j;break;}
 }
return index;
}

//  return index where the min of {} positive values.
int return_min(double* v,int rows)
{
 double val = v[0];
 int index;
 for (int i=0;i<rows;++i)
 {
  if (v[i]<0 && val<0) val = v[i];
  if (v[i]>=0 && val<0) 
  {
  val = v[i];
  }   
  if (v[i]>=0 && val>=0)
  val = (val >= v[i]) ? v[i] : val;
 }
 for (int i=0;i<rows;++i) { if (v[i]==val) index=i;}
 return index;
}

double sum_vector(double v[cols])
{
double sum=0;
 for (int i =0;i<cols;++i)
 {
   sum = v[i] + sum;
 }
return sum; 
}

void calc_xb(double m[rows][cols],double b[cols],double xb[cols])
{
 for (int j=0;j<rows;++j)
 {
  for (int i =0;i<cols;++i)
  {
    xb[i] = m[j][i]*b[i];
  }
 }
}
