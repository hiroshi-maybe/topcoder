#include <iostream>
#include <sstream>
#include <cassert>
#include <vector>

using namespace std;

bool isLeap(int y) {
  bool A=(y%4==0)&&(y%100!=0);
  bool B=(y%400==0);
  return A||B;
}

int days[12]={31,28,31,30,31,30,31,31,30,31,30,31};
bool validateDay(int m, int d, bool isleap) {
  if(m!=2||!isleap) return 0<d&&d<=days[m-1];
  return 0<d&&d<=29;
}

bool validateDate(int y, int m, int d) {
  if(y<0) return false;
  if(m<1||m>12) return false;
  return validateDay(m,d,isLeap(y));
}

int main(int argc, char const *argv[]) {
  assert(validateDate(1900,1,1));
  assert(!validateDate(-1,1,1));
  assert(!validateDate(1900,1,32));
  assert(!validateDate(1900,4,31));
  assert(validateDate(400,2,29));
  assert(!validateDate(100,2,29));
  assert(validateDate(104,2,29));
}
