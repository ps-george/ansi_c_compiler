int f(int a){
  if (a==0){
    return 2;
  }
  else if (a==1){
    return 1;
  }
  return f(a-1) + f(a-2);
}
