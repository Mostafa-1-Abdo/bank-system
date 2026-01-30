#pragma once
#include <iostream>
#include "clCurrency.h"
using namespace std;

class clCurrencyInfo
{
public:
	static void PrintInfo(const clCurrency& Currency)
	{
		cout << "Currency Card:\n";
		cout << "__________________________________\n";
		cout << "Country  : " << Currency.Country << "\n";
		cout << "Code     : " << Currency.Code << "\n";
		cout << "Name     : " << Currency.Name << "\n";
		cout << "Rate(1$) : " << Currency.Rate << "\n";
		cout << "__________________________________\n";
	}
};