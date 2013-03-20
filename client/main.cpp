/* Project: 2DEV 
 * File: main.cpp
 * Last modif.: 15/03/2012 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
//Les 2 includes suivants ne doivent pas être rouge !!
#include <irrlicht.h>
#include <irrKlang.h>
#include "game.h"

using namespace std;


int main(int argc, char **argv)
{
	game g;

	g.play("mountain");	

	system("PAUSE");

	return 0;
}

