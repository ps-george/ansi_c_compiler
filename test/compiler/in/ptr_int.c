int main(){
  int b = 0;
  int * a = &b;
  *a = 5;
  return *a;
}
