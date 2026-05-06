#include <iostream>
#include "utility.hpp"
#include "gui.hpp"

using namespace std;


int main(){

  cout << "gui or cli: ";
  char option;
  cin >> option;
  if(tolower(option) == 'c') Exec();
  if(tolower(option) == 'g') GUI();
  return 0;
}
