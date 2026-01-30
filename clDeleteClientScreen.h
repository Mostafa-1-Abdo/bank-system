#pragma once
#include <iostream>
#include "clScreen.h"
#include "clClient.h"
#include "clClientInfo.h"
#include "clInputValidation.h"
#include "clUtil.h"
using namespace std;

class clDeleteClientScreen : protected clScreen
{
private:
	static void _Delete()
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

		if (clInputValidation::ReadOption("Are you certain you want to delete the client with account number (" + AccountNumber + ") from the system? "))
		{
			Client.Delete();
			cout << "\n\nClient deletion completed successfully.\n";
		}
	}

public:
	static void ShowDeleteClientScreen()
	{
		DrawScreenHeader(clUtil::Spaces(9) + "Delete Client Screen");

		_Delete();
	}
};