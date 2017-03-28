// Sizeof operator for int, char, double, not for pointers

int main(){
  int f = 3;
  int * i = &f;
  char c;
  double d;
  f = sizeof(i);
  f = sizeof(int) + sizeof(d) + sizeof(c) + sizeof(char) + sizeof(int);
  
  return f;
}
