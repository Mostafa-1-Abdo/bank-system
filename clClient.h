#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "clPerson.h"
#include "clString.h"
#include "clFile.h"
#include "CurrentUser.h"
using namespace std;


string ClientsFileName = "Clients.txt";
string ClientsDelimiter = "#//#";

string TransferLogFileName = "Trasnfer Log.txt";
string TransferLogDelimiter = "#//#";


class clClient : public clPerson
{
private:
	enum enMode
	{
		EmptyMode , UpdateMode,AddNewMode,DeleteMode
	};
	struct stTransferLog;

	string _AccountNumber, _PinCode;
	float _Balance;
	enMode _Mode;

	static clClient _EmptyClientObject()
	{
		return clClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static string _NextAccountNumber;
	static void _IncreaseAccountNumber(string &AccountNumber)
	{
		char LetterPart = AccountNumber[0];
		short IntPart = stoi(AccountNumber.substr(1));

		IntPart++;
		if (IntPart > 999999)
		{
			IntPart = 0;
			LetterPart++;
		}

		string IntPartAsString = to_string(IntPart);
		while (IntPartAsString.length() < 6)
		{
			IntPartAsString = "0" + IntPartAsString;
		}

		AccountNumber = string(1, LetterPart) + IntPartAsString;
	}
	static string _GetCurrentAccountNumber()
	{
		ifstream File("Last Account Number.txt");

		if (File.is_open())
		{
			getline(File, _NextAccountNumber);

			File.close();

			return _NextAccountNumber;
		}
		return "A000000";
	}
	static void _SaveNextAccountNumber(string& NextAccountNumber)
	{
		_IncreaseAccountNumber(NextAccountNumber);

		ofstream File("Last Account Number.txt");

		if(File.is_open())
		{
			File << NextAccountNumber;
			File.close();
		}
	}

	static clClient _ConvertLineToClientObject(const string &Line)
	{
		vector <string> veClientData = clString::Split(Line, ClientsDelimiter);
		return clClient(enMode::UpdateMode,veClientData[0], veClientData[1], veClientData[2], veClientData[3], veClientData[4], veClientData[5], stof(veClientData[6]));
	}
	static vector <clClient> _LoadClientsDataFromFile()
	{
		vector <clClient> veClients;
		ifstream File(ClientsFileName);
		
		if (File.is_open())
		{
			string Line;
			while (getline(File, Line))
			{
				veClients.push_back(_ConvertLineToClientObject(Line));
			}
			File.close();
		}

		return veClients;
	}

	static string _ConvertClientObjectToLine(const clClient &Client)
	{
		return Client._FirstName + ClientsDelimiter + Client._LastName + ClientsDelimiter + Client._Email + ClientsDelimiter + Client._Phone + ClientsDelimiter + Client._AccountNumber + ClientsDelimiter + Client._PinCode + ClientsDelimiter + to_string(Client._Balance);
	}
	static void _SaveClientsDataInFile(const vector <clClient> &veClients)
	{
		ofstream File(ClientsFileName);

		if (File.is_open())
		{
			for (const clClient& Client : veClients)
			{
				if (Client._Mode == DeleteMode)
					continue;

				File << _ConvertClientObjectToLine(Client) << "\n";
			}
			File.close();
		}
	}

	static stTransferLog _ConvertLineToUserTransferLogObject(const string& Line)
	{
		vector <string> veTransfer = clString::Split(Line, TransferLogDelimiter);
		return stTransferLog{ veTransfer[0], veTransfer[1], veTransfer[2], stof(veTransfer[3]),stof(veTransfer[4]),stof(veTransfer[5]),veTransfer[6]};
	}
	static vector <stTransferLog> _LoadTransfersLogFromFile()
	{
		vector <stTransferLog> veRecords;
		ifstream File(TransferLogFileName);

		if (File.is_open())
		{
			string Line;
			while (getline(File, Line))
			{
				veRecords.push_back(_ConvertLineToUserTransferLogObject(Line));
			}
			File.close();
		}

		return veRecords;
	}

	void _Update()
	{
		vector <clClient> veClients = _LoadClientsDataFromFile();

		for (clClient& Client : veClients)
		{
			if (Client._AccountNumber == _AccountNumber)
			{
				Client = *this;
				break;
			}
		}

		_SaveClientsDataInFile(veClients);
	}

	void _AddNew()
	{
		clFile::SaveNewLineInFile( ClientsFileName, _ConvertClientObjectToLine(*this));
	}

	string _PrepareTransferLogLine(const float Amount,const clClient& ReceiverClient)
	{
		return  clDate::ConvertToString(clDate::GetToday()) + " - " + clDate::GetTimeAsString() + TransferLogDelimiter + _AccountNumber + TransferLogDelimiter + ReceiverClient._AccountNumber + TransferLogDelimiter + to_string(Amount) + TransferLogDelimiter + to_string(_Balance) + TransferLogDelimiter + to_string(ReceiverClient._Balance) + TransferLogDelimiter + CurrentUser.Username;
	}
public:
	clClient(const enMode Mode,const string& FirstName, const string& LastName, const string& Email, const  string& Phone, const string& AccountNumber, const string& PinCode, const float Balance)
		:clPerson(FirstName, LastName, Email,Phone)
	{
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PinCode = PinCode;
		_Balance = Balance;
	}

	string GetAccountNumber()const
	{
		return _AccountNumber;
	}
	__declspec(property(get = GetAccountNumber))string AccountNumber;

	void SetPinCode(const string &PinCode)
	{
		_PinCode = PinCode;
	}
	string GetPinCode()const
	{
		return _PinCode;
	}
	__declspec(property(put = SetPinCode, get = GetPinCode))string PinCode;

	void SetBalance(const float Balance)
	{
		_Balance = Balance;
	}
	float GetBalance()const
	{
		return _Balance;
	}
	__declspec(property(put = SetBalance, get = GetBalance))float Balance;

	bool IsEmpty()
	{
		return _Mode == enMode::EmptyMode;
	}

	static clClient Find(const string& AccountNumber)
	{
		ifstream File(ClientsFileName);

		if (File.is_open())
		{
			string Line;
			while (getline(File, Line))
			{
				clClient Client = _ConvertLineToClientObject(Line);
				if (Client._AccountNumber == AccountNumber)
				{
					File.close();
					return Client;
				}
			}
			File.close();
			return _EmptyClientObject();
		}
	}
	static bool IsExist(const string& AccountNumber)
	{
		return !Find(AccountNumber).IsEmpty();
	}

    static clClient GetNewClientObject()
	{
		return clClient(enMode::AddNewMode, "", "", "", "", _GetCurrentAccountNumber(), "", 0);
	}

	enum enSaveResult
	{
		EmptyFalid,AccountNumberExistFalid,Succeeded
	};
	enSaveResult Save()
	{
		switch (_Mode)
		{
		case enMode::EmptyMode:
		{
			return EmptyFalid;
		}
		case enMode::UpdateMode:
		{
			_Update();
			return Succeeded;
		}
		case enMode::AddNewMode:
		{
			if (IsExist(_AccountNumber))
			{
				return AccountNumberExistFalid;
			}

			_AddNew();
			_Mode = UpdateMode;
			_SaveNextAccountNumber(_NextAccountNumber);
			return Succeeded;
		}
		}
	}
	struct stTransferLog
	{
		string Date;
		string SenderClientAccountNumber;
		string RecevierClientAccountNumber;
		float Amount;
		float SenderClientNewBalance;
		float RecevierClientNewBalance;
		string Username;
	};
	static vector <stTransferLog> GetTransferLogList()
	{
		return _LoadTransfersLogFromFile();
	}

	void Delete()
	{
		vector <clClient> veClients = _LoadClientsDataFromFile();

		for (clClient& Client : veClients)
		{
			if (Client._AccountNumber == _AccountNumber)
			{
				Client._Mode = DeleteMode;
			}
		}

		_SaveClientsDataInFile(veClients);

		*this = _EmptyClientObject();
	}

	static vector <clClient> GetClientsList()
	{
		return _LoadClientsDataFromFile();
	}

	static float GetTotalBalances()
	{
		float TotalBalance = 0;
		vector <clClient> veClients = _LoadClientsDataFromFile();

		for (clClient& Client : veClients)
		{
			TotalBalance += Client.Balance;
		}

		return TotalBalance;
	}

	void Deposit(const float Amount)
	{
		_Balance += Amount;
		Save();
	}
	bool Withdraw(const float Amount)
	{
		if (Amount > _Balance)
			return false;

		_Balance -= Amount;
		Save();
		return true;
	}
	bool Transfer(const float Amount, clClient& ReceiverClient)
	{
		if (!Withdraw(Amount))
			return false;

		ReceiverClient.Deposit(Amount);
		clFile::SaveNewLineInFile(TransferLogFileName, _PrepareTransferLogLine(Amount, ReceiverClient));
		return true;
	}
};
string clClient::_NextAccountNumber ;