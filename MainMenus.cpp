#include "MenuMain.h"
#include <iostream>
using namespace std;

int main()
{
	cout << "prueba";
	initscr();
	cbreak();
    noecho();
    curs_set(0);
	MenuMain* a = new MenuMain();
	return 1;
}