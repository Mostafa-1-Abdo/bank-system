#pragma once
#include <iostream>
#include "clCurrency.h"
#include "clScreen.h"
#include "clInputValidation.h"
#include "clUtil.h"
#include "clString.h"
#include "clCurrencyInfo.h"
using namespace std;

class clFindCurrencyScreen : protected clScreen
{
private:
	enum enFindCurrencyScreenoOption
	{
		Code = 1, Country
	};

	static void _FindByCode()
	{
		string Code = clInputValidation::ReadString("\n\nEnter the currency code : ");
		clCurrency Currency = clCurrency::FindByCode(Code);

		cout << "\n\n";
		if (Currency.IsEmpty())
		{
			cout << "The currency associated with code (" << Code << ") could not be found in the system.\n";
			return;
		}
		clCurrencyInfo::PrintInfo(Currency);
	}

	static void _FindByCountry()
	{
		string Country = clInputValidation::ReadString("\n\nEnter the country name for the currency : ");
		clCurrency Currency = clCurrency::FindByCountry(Country);

		cout << "\n\n";
		if (Currency.IsEmpty())
		{
			cout << "The currency associated with the country (" << Country << ") could not be found in the system.\n";
			return;
		}
		clCurrencyInfo::PrintInfo(Currency);
	}

	static void _Find()
	{
		enFindCurrencyScreenoOption Option = (enFindCurrencyScreenoOption)clInputValidation::ReadNumberBetween<short>(1,2,"Find By: [1] Code or [2] Country : ");
		
		switch (Option)
		{
		case enFindCurrencyScreenoOption::Code:
			_FindByCode();
			break;
		case enFindCurrencyScreenoOption::Country:
			_FindByCountry();
			break; 
		}
	}

public:
	static void ShowFindCurrencyScreen()
	{
		DrawScreenHeader(clUtil::Spaces(8) + "Find Currency Screen");

		_Find();
	}
};