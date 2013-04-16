//============================================================================
// Name        : main.cpp
// Author      : rainloader
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "LsParser.h"
using namespace std;

int main()
{
	LsParser lsParser;

	lsParser.openFiles("vobos_all_20130410.txt", "output.txt");

	lsParser.parse();

	lsParser.closeFiles();

	return 0;
}
