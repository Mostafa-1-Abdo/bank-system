#pragma once
#include <iostream>
#include "clLoginScreen.h"
#include "clMainMenuScreen.h"
using namespace std;

class clBankSystem
{
public:
	static void Bank()
	{
		
		while(true)
		{
			if (!clLoginScreen::ShowLoginScreen())
			{
				break;
			}
			clMainMenuScreen::ShowMainMenuScreen();
		}
	}
};