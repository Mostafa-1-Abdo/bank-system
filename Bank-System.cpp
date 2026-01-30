#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

enum enMainMenuOption
{
	ShowList = 1, AddClient, DeleteClient, UpdateClient, FindClient, Exit
};

struct stClient
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double Balance;
	bool DeleteBit = false;
};

//_________________________General_________________________
int ReadNumber(const string& Message = "Enter a number")
{
	int Number;
	cout << Message;
	cin >> Number;
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid number, enter a valid number\n";
		cin >> Number;
	}
	return Number;
}
bool ValidateNumberInRange(short Number, short From, short To)
{
	return Number >= From && Number <= To;
}
int ReadNumberInRange(const string& Message, const short& From, const short& To)
{
	int Number;

	do {
		Number = ReadNumber(Message);

	} while (!(ValidateNumberInRange(Number, From, To)));

	return Number;
}

double ReadNonNegativeNumber(const string& Message = "Enter a number")
{
	double Number;
	do {
		cout << Message;
		cin >> Number;
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid number, enter a valid number\n";
			cin >> Number;
		}
	} while (Number < 0);
	return Number;
}

string StringRead(const string& Message = "Enter a string")
{
	string String;
	cout << Message;
	getline(cin >> ws, String);
	return String;
}

enum enLetterCase
{
	Upper = 1, Lower
};
string StringChangeLettersCase(string String, const enLetterCase& CharCase)
{
	for (short i = 0; i < String.length(); i++)
	{
		if (CharCase == enLetterCase::Upper)
			String[i] = toupper(String[i]);

		else
			String[i] = tolower(String[i]);
	}

	return String;
}
bool StringReadChoice(const string& Message)
{
	string Choice;

	cout << Message;
	do {
		cin >> Choice;

		Choice = StringChangeLettersCase(Choice, enLetterCase::Lower);

	} while (Choice != "yes" && Choice != "no");

	return Choice == "yes";
}

vector <string> StringSplit(string String, const string& Delimiter = " ")
{
	string Word;
	short EndIndex;
	vector <string> veWords;

	while ((EndIndex = String.find(Delimiter)) != string::npos)
	{
		Word = String.substr(0, EndIndex);

		if (!Word.empty())
			veWords.push_back(Word);

		String.erase(0, EndIndex + Delimiter.length());
	}
	if (!String.empty())
		veWords.push_back(String);

	return veWords;
}

void FileAddNewLine(const string& FileName, const string& Line)
{
	ofstream File(FileName, ios::app);
	if (File.is_open())
	{
		File << Line << "\n";

		File.close();
	}
}

void PrintHeader(const string& Heading)
{
	cout << "------------------------------------\n";
	cout << "\t" << Heading << "\n";
	cout << "------------------------------------\n";
}
//_________________________________________________________

//_________________________BankGeneral_________________________
stClient ConvertRecordLineToRecord(const string& RecordLine, const string& Delimiter)
{
	vector <string> veFields = StringSplit(RecordLine, Delimiter);
	stClient Client;

	if (veFields.size() == 5)
	{
		Client.AccountNumber = veFields[0];
		Client.PinCode = veFields[1];
		Client.Name = veFields[2];
		Client.Phone = veFields[3];
		Client.Balance = stod(veFields[4]);
	}
	else
		cout << "Error : Invalid record line!";

	return Client;
}
vector <stClient> FileLoadClientsList(const string& FileName, const string& Delimiter)
{
	vector <stClient> veClients;

	ifstream File(FileName);
	if (File.is_open())
	{
		string Line;
		while (getline(File, Line))
		{
			veClients.push_back(ConvertRecordLineToRecord(Line, Delimiter));
		}
	}
	else
		cout << "Error : Cannot open file <" << FileName << ">";

	return veClients;
}

string ConvertRecordToRecordLine(const stClient& Client, const string& Delimiter)
{
	string RecordLine = "";

	RecordLine += Client.AccountNumber + Delimiter;
	RecordLine += Client.PinCode + Delimiter;
	RecordLine += Client.Name + Delimiter;
	RecordLine += Client.Phone + Delimiter;
	RecordLine += to_string(Client.Balance);

	return RecordLine;
}
void FileSaveRecordsLiensByVector(const string& FileName, const vector <stClient>& veClients, const string& Delimiter, const bool& DeleteOldData = false)
{
	ofstream File;

	if (DeleteOldData)
		File.open(FileName);
	else
		File.open(FileName, ios::app);
	if (File.is_open())
	{
		for (const stClient& Client : veClients)
		{
			if (Client.DeleteBit == false)
				File << ConvertRecordToRecordLine(Client, Delimiter) << "\n";
		}
		File.close();
	}
}

void PrintClientRecord(const stClient& Client)
{
	cout << "The following are the client details: \n";
	cout << "------------------------------------\n";
	cout << "Account number : " << Client.AccountNumber << "\n";
	cout << "Pin code       : " << Client.PinCode << "\n";
	cout << "Name           : " << Client.Name << "\n";
	cout << "Phone          : " << Client.Phone << "\n";
	cout << "Balance        : " << Client.Balance << "\n";
	cout << "------------------------------------\n";
}

bool IsClientExistByAccountNumber(const vector <stClient>& veClients, const string& AccountNumber, stClient& ClientRecord)
{
	for (const stClient& Client : veClients)
	{
		if (Client.AccountNumber == AccountNumber)
		{
			ClientRecord = Client;
			return true;
		}
	}

	return false;
}

//_________________________________________________________

void ShowMainMenuScreen()
{
	cout << "=============================================\n";
	cout << "\t\t Main Menu Screen\n";
	cout << "=============================================\n";
	cout << "\t[1] Show Client List.\n";
	cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Delete Client.\n";
	cout << "\t[4] Update Client.\n";
	cout << "\t[5] Find Client.\n";
	cout << "\t[6] EXit.\n";
	cout << "=============================================\n";
}

void PrintListHeader(const short& NumberOfClients)
{
	cout << "\t\t\t\tClients List (" << NumberOfClients << ")" << " Client(s)\n";
	cout << "____________________________________________________________________________________________________\n\n";
	cout << left;
	cout << "| " << setw(15) << "Account Number";
	cout << "| " << setw(10) << "Pin Code";
	cout << "| " << setw(40) << "Client Name";
	cout << "| " << setw(12) << "Phone";
	cout << "| " << setw(12) << "Balance" << "|\n";
	cout << "____________________________________________________________________________________________________\n";
}
void PrintClient(const stClient& Client)
{
	cout << "| " << setw(15) << Client.AccountNumber;
	cout << "| " << setw(10) << Client.PinCode;
	cout << "| " << setw(40) << Client.Name;
	cout << "| " << setw(12) << Client.Phone;
	cout << "| " << setw(12) << Client.Balance << "|\n";
}
void ShowClientListScreen(const string& FileName, const string& Delimiter)
{
	vector <stClient> veClients = FileLoadClientsList(FileName, Delimiter);
	PrintListHeader(veClients.size());

	for (const stClient& Client : veClients)
	{
		PrintClient(Client);
	}

	cout << "____________________________________________________________________________________________________\n\n";
}

stClient ReadNewClientRecord(vector <stClient> veClients)
{
	stClient Client;

	Client.AccountNumber = StringRead("Enter account number : ");
	while (IsClientExistByAccountNumber(veClients, Client.AccountNumber, Client))
	{
		Client.AccountNumber = StringRead("Client with [" + Client.AccountNumber + "] already exists, enter another account number : ");
	}
	Client.PinCode = StringRead("Enter pin code : ");
	Client.Name = StringRead("Enter name : ");
	Client.Phone = StringRead("Enter phone : ");
	Client.Balance = ReadNonNegativeNumber("Enter balance : ");

	return Client;
}
void AddNewClient(const string& FileName, const string& Delimiter)
{
	vector <stClient> veClients = FileLoadClientsList(FileName, Delimiter);
	short static NumberOfClientsAdd = 1;

	cout << "Add client " << NumberOfClientsAdd << "\n";
	stClient Client = ReadNewClientRecord(veClients);
	cout << "\n\n";

	PrintClientRecord(Client);

	bool AddClient = StringReadChoice("Are you sure you want add new client with account number (" + Client.AccountNumber + ") : ");
	if (AddClient)
	{
		FileAddNewLine(FileName, ConvertRecordToRecordLine(Client, Delimiter));
		cout << "\n\n";
		cout << "Client add successfully";
		NumberOfClientsAdd++;
	}
}
void ShowAddClientsScreen(const string& FileName, const string& Delimiter)
{
	PrintHeader("Add New Clients Screen");

	do {
		AddNewClient(FileName, Delimiter);
		cout << "\n\n";

	} while (StringReadChoice("Do you want to add more Clients ? "));

}

void MarkClientToDeleteByAccountNumber(vector <stClient>& veClients, const string& AccountNumber)
{
	for (stClient& Client : veClients)
	{
		if (Client.AccountNumber == AccountNumber)
		{
			Client.DeleteBit = true;
			break;
		}
	}
}
void ShowDeleteClientScreen(const string& FileName, const string& Delimiter)
{
	PrintHeader("Delete Client Screen");

	vector <stClient> veClients = FileLoadClientsList(FileName, Delimiter);

	string AccountNumber = StringRead("Enter account number : ");
	stClient ClientRecord;

	if (IsClientExistByAccountNumber(veClients, AccountNumber, ClientRecord))
	{
		cout << "\n\n";
		PrintClientRecord(ClientRecord);

		bool DeleteAccount = StringReadChoice("Are you sure you want to delete the client with account number (" + ClientRecord.AccountNumber + ") : ");

		if (DeleteAccount)
		{
			MarkClientToDeleteByAccountNumber(veClients, ClientRecord.AccountNumber);

			FileSaveRecordsLiensByVector(FileName, veClients, Delimiter, true);

			veClients = FileLoadClientsList(FileName, Delimiter);

			cout << "\n\nClient deleted successfully";
		}
	}
	else
		cout << "\n\nClient with account number (" << AccountNumber << ") not found!";
}

void UpdateClientByAccountNumber(vector <stClient>& veClients, const string& AccountNumber)
{
	for (stClient& Client : veClients)
	{
		if (Client.AccountNumber == AccountNumber)
		{
			Client.PinCode = StringRead("Enter pin code : ");
			Client.Name = StringRead("Enter name : ");
			Client.Phone = StringRead("Enter phone : ");
			Client.Balance = ReadNonNegativeNumber("Enter balance : ");
			break;
		}
	}
}
void ShowUpdateClientScreen(const string& FileName, const string& Delimiter)
{
	PrintHeader("Update Client Info Screen");

	vector <stClient> veClients = FileLoadClientsList(FileName, Delimiter);

	string AccountNumber = StringRead("Enter account number : ");
	stClient ClientRecord;

	if (IsClientExistByAccountNumber(veClients, AccountNumber, ClientRecord))
	{
		cout << "\n\n";
		PrintClientRecord(ClientRecord);

		bool UpdateAccount = StringReadChoice("Are you sure you want to update the client with account number (" + ClientRecord.AccountNumber + ") : ");

		if (UpdateAccount)
		{
			cout << "\n\n";
			UpdateClientByAccountNumber(veClients, ClientRecord.AccountNumber);

			FileSaveRecordsLiensByVector(FileName, veClients, Delimiter, true);

			veClients = FileLoadClientsList(FileName, Delimiter);

			cout << "\n\nClient update successfully";
		}
	}
	else
		cout << "\n\nClient with account number (" << AccountNumber << ") not found!";
}

void ShowFindClientScreen(const string& FileName, const string& Delimiter)
{
	PrintHeader("Update Client Info Screen");

	vector <stClient> veClients = FileLoadClientsList(FileName, Delimiter);

	string AccountNumber = StringRead("Enter account number : ");
	stClient ClientRecord;

	if (IsClientExistByAccountNumber(veClients, AccountNumber, ClientRecord))
	{
		cout << "\n\n";
		PrintClientRecord(ClientRecord);
	}
	else
		cout << "\n\nClient with account number (" << AccountNumber << ") not found!";
}

void Bank(const string& FileName, const string& Delimiter)
{
	while (true)
	{
		ShowMainMenuScreen();

		enMainMenuOption Option = (enMainMenuOption)ReadNumberInRange("Choose what do you want to do ? 1:6 ? ", 1, 6);

		system("cls");

		switch (Option)
		{
		case enMainMenuOption::ShowList:
			ShowClientListScreen(FileName, Delimiter);
			break;
		case enMainMenuOption::AddClient:
			ShowAddClientsScreen(FileName, Delimiter);
			break;
		case enMainMenuOption::DeleteClient:
			ShowDeleteClientScreen(FileName, Delimiter);
			break;
		case enMainMenuOption::UpdateClient:
			ShowUpdateClientScreen(FileName, Delimiter);
			break;
		case enMainMenuOption::FindClient:
			ShowFindClientScreen(FileName, Delimiter);
			break;
		case enMainMenuOption::Exit:
			PrintHeader("Program Ends");
			return;
		}

		cout << endl << endl;
		cout << "Press any key to go back to main menu...";
		system("pause>0");
		system("cls");
	}
}

int main()
{
	string FileName = "Clients.txt";
	string Delimiter = "#";
	Bank(FileName, Delimiter);
}