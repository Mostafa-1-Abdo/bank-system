#pragma once
#include <iostream>
#include "clScreen.h"
#include "clUtil.h"
#include "clInputValidation.h"
using namespace std;

class clCurrencyCalculatorScreen : protected clScreen
{
private:
	static void _Calculator()
	{
		string Code = clInputValidation::ReadString("Enter currency 1 code : ");
		clCurrency Currency1 = clCurrency::FindByCode(Code);
		if (Currency1.IsEmpty())
		{
			cout << "\n\nThe currency associated with code (" << Code << ") could not be found in the system.\n";
			return;
		}

		string Code2 = clInputValidation::ReadString("\n\nEnter currency 2 code : ");
		clCurrency Currency2 = clCurrency::FindByCode(Code2);
		if (Currency2.IsEmpty())
		{
			cout << "\n\nThe currency associated with code (" << Code2 << ") could not be found in the system.\n";
			return;
		}

		float Amount = clInputValidation::ReadNonNegativeNumber<float>("\n\nEnter amount to exchange : ");

		cout << "\n\n"<<Amount<<" " << Currency1.Code <<" = " << Currency1.ConvertToOtherCurrency(Amount, Currency2)<<" "<< Currency2.Code<< "\n";
	}


public:
	static void ShowCurrencyCalculatorScreen()
	{
		DrawScreenHeader(clUtil::Spaces(6) + "Currency Calculator Screen");

		_Calculator();
	}
};