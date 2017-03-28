// Pointer arithmetic

int main(){
  int a[3];
  int *b = &a[0];
  a[0] = 5;
  a[1] = 3;
  a[2] = 7;
  b++;
  return *(++b);
}
