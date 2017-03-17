// Break out of while statement, nested

int main(){
  int i = 9;
  int j = 45;
  while (i!=0){
    
    while (i>5){
      break;
      j--;
    }
    j++;
    i--;
  }
  return j;
}
