#pragma once
#include <iostream>
#include "clScreen.h"
#include "clClient.h"
#include "clClientInfo.h"
#include "clInputValidation.h"
#include "clUtil.h"
using namespace std;

class clTransferScreen :protected clScreen
{
private:
	static void _Transfer()
	{
		string SenderAccountNumber = clInputValidation::ReadString("Enter the client's account number to transfer from : ");
		if (!clClient::IsExist(SenderAccountNumber))
		{
			cout << "\n\nThe client associated with account number (" << SenderAccountNumber << ") could not be found in the system.\n";
			return;
		}
		clClient SenderClient = clClient::Find(SenderAccountNumber);
		clClientInfo::PrintInfo(SenderClient);

		string ReceiverAccountNumber = clInputValidation::ReadString("\n\nEnter the client's account number to transfer to : ");
		if (!clClient::IsExist(ReceiverAccountNumber))
		{
			cout << "\n\nThe client associated with account number (" << ReceiverAccountNumber << ") could not be found in the system.\n";
			return;
		}
		clClient ReceiverClient = clClient::Find(ReceiverAccountNumber);
		clClientInfo::PrintInfo(ReceiverClient);

		float TransferAmount = clInputValidation::ReadNonNegativeNumber<float>("\n\nEnter transfer amount : ");

		if (clInputValidation::ReadOption("\n\nAre you sure you want to perform this transfer transaction? "))
		{
			if (SenderClient.Transfer(TransferAmount, ReceiverClient))
			{
				cout << "\n\nTransfer transaction completed successfully\n";
				clClientInfo::PrintInfo(SenderClient);
				cout << "\n";
				clClientInfo::PrintInfo(ReceiverClient);
			}
			else
				cout << "\n\nInsufficient balance. transfer transaction was cancelled.\n";
		}
	}

public:
	static void ShowTransferScreen()
	{
		DrawScreenHeader(clUtil::Spaces(12) + "Transfer Screen");

		_Transfer();
	}
};