#include <cstdlib>
#include <format>
#include <iostream>
#include <string>
#include <utility>
#include "thingThatLookLikeLib.hpp"
#include "credentials.cpp"

using namespace std;

int main(){
  int size;
  char opt;
  cout << "Enter size of an array: ";
  cin >> size;
  if(size >= 10) {
    cout << "For array that size it`ll be better to generate array\nShould we generate it? [y/n]: ";
    cin >> opt;
    if(opt == 'y' or opt == 'Y') ArrGen(size);
    else if(opt == 'n' or opt == 'N') HandTypeArr(size);
    else cout << "Wrong optin, bye!";
  }
  else if(size <= 10 and size > 0) {
    cout << "Should we enter array manually or generate it?\ng - generate\tm - enter it manually [g/m]: ";
    cin >> opt;
    if(opt == 'g' or opt == 'G') ArrGen(size);
    else if(opt == 'm' or opt == 'M') HandTypeArr(size);
    else cout << "Wrong optin, bye!";
  }


  ShowCreds();
  return 0;
}
