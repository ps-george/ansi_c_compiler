int strcmp ( const char * str1, const char * str2 );

int f(){
  char * c = "hi";
  char * d = "hello";
  if (strcmp(c,d)==0){
    return 1;
  }
  return 0;
}
