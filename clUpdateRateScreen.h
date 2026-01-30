#pragma once
#include <iostream>
#include "clScreen.h"
#include "clUtil.h"
using namespace std;

class clUpdateRateScreen :protected clScreen
{
private:
	static void _Update()
	{
		string Code = clInputValidation::ReadString("Enter the currency code : ");
		clCurrency Currency = clCurrency::FindByCode(Code);

		cout << "\n\n";
		if (Currency.IsEmpty())
		{
			cout << "The currency associated with code (" << Code << ") could not be found in the system.\n";
			return;
		}
		clCurrencyInfo::PrintInfo(Currency);
;
		float NewRate = clInputValidation::ReadNonNegativeNumber<float>("\n\nEnter new rate : ");

		if (clInputValidation::ReadOption("\n\nAre you certain you want to update the currency rate for ("+Currency.Name+")?"))
		{
			Currency.UpdateRate(NewRate);

			cout << "\n\n";
			clCurrencyInfo::PrintInfo(Currency);
			cout << "Currency update completed successfully.\n";
		}
	}

public:
	static void ShowUpdateRateScreen()
	{
		DrawScreenHeader(clUtil::Spaces(10) + "Update Rate Screen");

		_Update();
	}
};