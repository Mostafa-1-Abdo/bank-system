#pragma once
#include <iostream>
#include "clScreen.h"
#include "clCurrency.h"
#include "clUtil.h"
using namespace std;

class clCurrenciesListScreen : protected clScreen
{
private:
	static void _PrintCurrenciesListHeader()
	{
		cout << clUtil::Tabs(2) << "_______________________________________________________________________________________________________\n\n";
		cout << left;
		cout << clUtil::Tabs(2) << "| " << setw(40) << "Country";
		cout << "| " << setw(4) << "Code";
		cout << "| " << setw(40) << "Name";
		cout << "| " << setw(10) << "Rate(1$)" << "|\n";
		cout << clUtil::Tabs(2) << "_______________________________________________________________________________________________________\n\n";
	}
	static void _PrintCurrencyRecordLine(const clCurrency& Currency)
	{
		cout << clUtil::Tabs(2) << "| " << setw(40) << Currency.Country;
		cout << "| " << setw(4) << Currency.Code;
		cout << "| " << setw(40) << Currency.Name;
		cout << "| " << setw(10) << Currency.Rate << "|\n";
	}
	static void _PrintCurrenciesList(const vector <clCurrency>& veCurrencies)
	{
		for (const clCurrency& Currency : veCurrencies)
		{
			_PrintCurrencyRecordLine(Currency);
		}
		cout << clUtil::Tabs(2) << "_______________________________________________________________________________________________________\n\n";
	}

public:
	static void ShowCurrenciesListScreen()
	{
		vector <clCurrency> veCurrencies = clCurrency::GetCurrenciesList();
		DrawScreenHeader(clUtil::Spaces(8) + "Currencies List Screen", clUtil::Spaces(13) + to_string(veCurrencies.size()) + " Currencies");

		_PrintCurrenciesListHeader();
		_PrintCurrenciesList(veCurrencies);
	}
};


