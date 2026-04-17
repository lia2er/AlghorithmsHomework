#include <iostream>
#include "sorting.hpp"
#include "utility.hpp"
#include "gui.hpp"
#include "lists.hpp"

using namespace std;


int main(){

  cout << "gui or cli: ";
  char option;
  cin >> option;
  if(tolower(option) == 'c') Exec();
  if(tolower(option) == 'g') GUI();
  cout << "\n|\tРоботу виконав студент групи КІ-22\n|\tМуравський Арсен\n\n";
  return 0;
}
