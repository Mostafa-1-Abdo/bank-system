#pragma once
#include <iostream>
#include "clScreen.h"
#include "clClient.h"
#include "clClientInfo.h"
#include "clInputValidation.h"
#include "clUtil.h"
using namespace std;

class clAddNewClientScreen : protected clScreen
{
private:
	static void _AddNew()
	{
		clClient Client = clClient::GetNewClientObject();
		cout  << "Add new client:\n";
		clClientInfo::ReadInfo(Client);

		if (clInputValidation::ReadOption( "Are you certain you want to register this client in the system? "))
		{
			Client.Save();

			cout << "\n\n";
			clClientInfo::PrintInfo(Client);
			cout << "Client registration completed successfully.\n";
		}
	}

public:
	static void ShowAddNewClientScreen()
	{
		DrawScreenHeader(clUtil::Spaces(9) + "Add New Client Screen");

		_AddNew();
	}
};