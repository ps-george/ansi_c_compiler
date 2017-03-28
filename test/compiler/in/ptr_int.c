// Get address using &, dereference pointer but no offset thingy (*a +4 or a[]+4)

int main(){
  int b = 1;
  int *a = &b;
  return *a;
}
