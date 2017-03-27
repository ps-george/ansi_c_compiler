// Recursive Fibonacci program with a silly amount of arguments

int Fibonacci(int n, int a, int b, int c, int d) {
  int i;
  if (n==0)
    {i = 0;}
  else if (n==1)
    {i = 1;}
  else
    {i = Fibonacci(n-1,a,b,c,d) + Fibonacci(n-2,a,b,c,d);}
  return i;
}

int main(){
  int f = 0;
  
  f = Fibonacci(8,10,5,5,6);
  return f;
}
