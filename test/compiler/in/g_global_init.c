int de = 1;

int f(){
  de = 3;
  return 1;
}

int main(){
  de = 5;
  f();
  return de;
}
