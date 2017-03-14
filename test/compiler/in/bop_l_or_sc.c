// Binary operator ||, false positive test. Trying to test short-circuit.

int f(){
  for (int i = 0 ; i < 5; i = i + 1){
    
  }
  
  return 13;
}

int main(){
  int a = 0x1;
  if (a||f()){
    return 53;
  };
  
  return 21;
}
