int Fibonacci(int n) {
  int i;
  if (n==0)
    i = 0;
  else if (n==1)
    i = 1;
  else
    i = Fibonacci(n-1) + Fibonacci(n-2);
    i;
  return i;
}

int main(){
  int f = 0;
  
  f = Fibonacci(4);
  return f;
}
