#include <iostream>
#include "sorting.hpp"
#include "utility.hpp"
#include "gui.hpp"

using namespace std;


int main(){
  cout << "gui or cli: ";
  char option;
  cin >> option;
  if(option == 'c') Exec();
  if(option == 'g') GUI();
  cout << "\n|\tРоботу виконав студент групи КІ-22\n|\tМуравський Арсен\n\n";
  return 0;
}
