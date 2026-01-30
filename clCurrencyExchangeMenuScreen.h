#pragma once
#include <iostream>
#include "clScreen.h"
#include "clCurrenciesListScreen.h"
#include "clFindCurrencyScreen.h"
#include "clUpdateRateScreen.h"
#include "clCurrencyCalculatorScreen.h"
#include "clInputValidation.h"
#include "clUtil.h"
using namespace std;

class clCurrencyExchangeMenuScreen : protected clScreen
{
private:
	enum enCurrencyExchangeMenuOption
	{
		ListCurrencies = 1, FindCurrency, UpdateRate, CurrencyCalculator, MainMenu
	};

	static void _PrintCurrencyExchangeMenu()
	{
		DrawScreenHeader(clUtil::Spaces(14) + "Currency Exchange Screen");
		cout << clUtil::Spaces(44) << "==============================================\n";
		cout << clUtil::Spaces(44) << clUtil::Spaces(15) << "Currency Exchange Menu\n";
		cout << clUtil::Spaces(44) << "==============================================\n";
		cout << clUtil::Spaces(44) << "[1] List Currencies.\n";
		cout << clUtil::Spaces(44) << "[2] Find Currency.\n";
		cout << clUtil::Spaces(44) << "[3] Update Rate.\n";
		cout << clUtil::Spaces(44) << "[4] Currency Calculator.\n";
		cout << clUtil::Spaces(44) << "[5] Main Menu.\n";
		cout << clUtil::Spaces(44) << "==============================================\n";
	}

public:
	static void ShowCurrencyExchangeMenuScreen()
	{
		while (true)
		{
			_PrintCurrencyExchangeMenu();
			enCurrencyExchangeMenuOption Option = (enCurrencyExchangeMenuOption)clInputValidation::ReadNumberBetween<short>(1, 5, clUtil::Spaces(44) + "Choose what you would like to do : ");

			system("cls");

			switch (Option)
			{
			case enCurrencyExchangeMenuOption::ListCurrencies:
				clCurrenciesListScreen::ShowCurrenciesListScreen();
				break;
			case enCurrencyExchangeMenuOption::FindCurrency:
				clFindCurrencyScreen::ShowFindCurrencyScreen();
				break;
			case enCurrencyExchangeMenuOption::UpdateRate:
				clUpdateRateScreen::ShowUpdateRateScreen();
				break;
			case enCurrencyExchangeMenuOption::CurrencyCalculator:
				clCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();
				break;
			case enCurrencyExchangeMenuOption::MainMenu:
				return;
			}

			cout << endl << endl;
			WaitAndClear();
		}
	}
};