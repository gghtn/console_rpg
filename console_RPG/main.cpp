#include <iostream>
#include <string>
#include "game.h"
#include "user.h"
#include "console.h"
using namespace std;

int main() {
	setConsoleSize(30, 20);
	CursorView();

	//char name[10];
	//cin >> name;

	CUser hero("Dsf");

	CGame _new(hero);

	_new.gameStart();

	//_new.battleStart();

	//hero.printUser();



	return 0;
}