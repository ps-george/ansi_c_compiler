// Adding the return values of two one input function calls

int Basic(int n) {
  return n;
}

int main(){
  int f = 0;
  
  f = Basic(5) + Basic(15);
  
  return f;
}
