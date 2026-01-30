#pragma once
#include <iostream>
#include "clScreen.h"
#include "clClient.h"
#include "clClientInfo.h"
#include "clInputValidation.h"
#include "clUtil.h"
using namespace std;

class clFindClientScreen : protected clScreen
{
private:
	static void _Find()
	{
		string AccountNumber = clInputValidation::ReadString("Enter the client's account number : ");
		clClient Client = clClient::Find(AccountNumber);
		cout << "\n\n";
		if (Client.IsEmpty())
		{
			cout << "The client associated with account number (" << AccountNumber << ") could not be found in the system.\n";
			return;
		}
		clClientInfo::PrintInfo(Client);
	}

public:
	static void ShowFindClientScreen()
	{
		DrawScreenHeader(clUtil::Spaces(10)+"Find Client Screen");

		_Find();
	}
};