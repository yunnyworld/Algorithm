#include <iostream>
using namespace std;
const int MAX=30;
int c[MAX+1][MAX+1];
int Combination(int n, int r)
{
  for(int i=0;i<=MAX;i++) c[i][0]=c[i][i]=1;
  for(int i=1;i<=MAX;i++) for(int j=1;j<=i;j++) c[i][j]=c[i-1][j-1]+c[i-1][j];
  return c[n][r];
}
//nCr, iCj, n>=r, O(n^2)
