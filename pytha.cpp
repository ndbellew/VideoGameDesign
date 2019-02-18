#include <iostream>
#include <cmath>

using namespace std;

float usefulFunction(float a,float b) {
  return sqrt(a*a+b*b);
}

int main(int argc,char **argv) {
  float x;
  x=usefulFunction(10,30);
  cout << x << endl;
  return 0;
}


