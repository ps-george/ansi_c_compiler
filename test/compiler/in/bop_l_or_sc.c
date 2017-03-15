// Binary operator ||, false positive test. Trying to test short-circuit.

int main(){
  int a = 0x1;
  int b = 0;
  if (a||b++){
    
  };
  
  return b;
}
