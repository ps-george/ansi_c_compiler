// Recursive Fibonacci program with a silly amount of arguments

int Fibonacci(int n, int a, int b, int c, int d, int e, int f, int g, int h, int i, int j, int k, int l) {
  int i;
  if (n==0)
    {i = 0;}
  else if (n==1)
    {i = 1;}
  else
    {i = Fibonacci(n-1,a,b,c,d,e,f,g,h,i,j,k,l) + Fibonacci(n-2,a,b,c,d,e,f,g,h,i,j,k,l);}
  return i;
}

int main(){
  int f = 0;
  
  f = Fibonacci(6,3,4,5,6,2,3,1,5,3,2,1,2);
  return f;
}
