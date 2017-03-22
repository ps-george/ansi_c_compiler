// DEEFor loop with break

int main(){
  int j = 0;
  for (int i = 0;i<10;i++) {
    if (i==5){
      continue;
    }
    j += i;
  }
  return j;
}
