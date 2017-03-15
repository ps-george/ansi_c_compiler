// Binary operator &&, false positive test. Trying to test short-circuit.

int main(){
  int a = 0x0;
  int b = 0;
  if(a&&b++){
    
  }
  return b;
}
