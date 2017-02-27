int main(){
        int i = 1;
        {
          int j = 2;
          int k = 2;
          int i = 2;
          i = i + 1;
        }
    i = i + 1;
    return i;
}
