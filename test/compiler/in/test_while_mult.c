int mult(int a, int b){
  int c = 0;
  while (a!=0){
    c = c + b;
    a = a - 1;
  }
  return c;
}

int main(){
  int a = 5;
  int b = 7;
  return mult(a,b);
}
