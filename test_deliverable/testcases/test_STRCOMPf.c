int strcmp ( const char * str1, const char * str2 );

int f(){
  char * c = "hi";
  char * d = "hi";
  if (strcmp(c,d)==0){
    return 0;
  }
  return 1;
}
