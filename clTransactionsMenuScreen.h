#pragma once
#include <iostream>
#include "clScreen.h"
#include "clDepositScreen.h"
#include "clWithdrawScreen.h"
#include "clTotalBalancesScreen.h"
#include "clInputValidation.h"
#include "clTransferScreen.h"
#include "clTransferLogListScreen.h"
#include "clUtil.h"
using namespace std;

class clTransactionsMenuScreen : protected clScreen
{
private:
	enum class enTransactionsMenuOption
	{
		Deposit = 1, Withdrawal, TotalBalances,Transfer,TransferLog, MainMenu
	};

	static void _PrintTransactionsMenu()
	{
		DrawScreenHeader(clUtil::Spaces(9) + "Transactions Screen");
		cout << clUtil::Spaces(44) << "==============================================\n";
		cout << clUtil::Spaces(44) << clUtil::Spaces(15) << "Transactions Menu\n";
		cout << clUtil::Spaces(44) << "==============================================\n";
		cout << clUtil::Spaces(44) << "[1] Deposit.\n";
		cout << clUtil::Spaces(44) << "[2] Withdraw.\n";
		cout << clUtil::Spaces(44) << "[3] Total Balances.\n";
		cout << clUtil::Spaces(44) << "[4] Transfer.\n";
		cout << clUtil::Spaces(44) << "[5] Transfer Log.\n";
		cout << clUtil::Spaces(44) << "[6] Main Menu.\n";
		cout << clUtil::Spaces(44) << "==============================================\n";
	}

public:
	static void ShowTransactionsMenuScreen()
	{
		while (true)
		{
			_PrintTransactionsMenu();
			enTransactionsMenuOption Option = (enTransactionsMenuOption)clInputValidation::ReadNumberBetween<short>(1, 6, clUtil::Spaces(44)+"Choose what you would like to do : ");

			system("cls");

			switch (Option)
			{
			case enTransactionsMenuOption::Deposit:
				clDepositScreen::ShowDepositScreen();
				break;
			case enTransactionsMenuOption::Withdrawal:
				clWithdrawScreen::ShowWithdrawScreen();
				break;
			case enTransactionsMenuOption::TotalBalances:
				clTotalBalancesScreen::ShowTotalBalancesScreen();
				break;
			case enTransactionsMenuOption::Transfer:
				clTransferScreen::ShowTransferScreen();
				break;
			case enTransactionsMenuOption::TransferLog:
				clTransferLogScreen::ShowTransferLogListScreen();
				break;
			case enTransactionsMenuOption::MainMenu:
				return;
			}

			cout << endl << endl;
			WaitAndClear();
		}
	}
};