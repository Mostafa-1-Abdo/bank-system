#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
using namespace std;

enum enMainMenuOption
{
	ShowList = 1, AddClient, DeleteClient, UpdateClient, FindClient, Transactions, ManageUsers, Logout
};
enum enMainMenuPermissions
{
	PShowList = 1, PAddClient = 2, PDeleteClient = 4, PUpdateClient = 8, PFindClient = 16, PTransactions = 32, PManageUsers = 64
};

enum class enTransactionsOption
{
	Deposit = 1, Withdrawal, TotalBalances, MainMenu
};

enum class enMangaeUsersOption
{
	ListUsers = 1, AddNewUser, DeleteUser, UpdateUser, FindUser, MainMenue
};

struct stClient
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double Balance = 0;
	bool Delete = false;
};

struct stUser
{
	string Username;
	string Password;
	short Permissions = 0;
	bool Delete = false;
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
int ReadNumberInRange(const string& Message, const short From, const short To)
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
bool StringReadOption(const string& Message)
{
	string Option;

	cout << Message;
	do {
		cin >> Option;

		Option = StringChangeLettersCase(Option, enLetterCase::Lower);

	} while (Option != "yes" && Option != "no");

	return Option == "yes";
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

void WaitAndClear()
{
	cout << "Press any key to go back to main menu...";
	system("pause>0");
	system("cls");
}
//_________________________________________________________

//_________________________BankGeneral_________________________
stClient ConvertClientRecordLineToRecord(const string& RecordLine, const string& Delimiter)
{
	vector <string> veFields = StringSplit(RecordLine, Delimiter);

	return { veFields[0] ,veFields[1] ,veFields[2] ,veFields[3] ,stod(veFields[4]) };
}
vector <stClient> FileLoadClientsListInVector(const string& ClientsFileName, const string& Delimiter)
{
	vector <stClient> veClients;

	ifstream File(ClientsFileName);
	if (File.is_open())
	{
		string Line;
		while (getline(File, Line))
		{
			veClients.push_back(ConvertClientRecordLineToRecord(Line, Delimiter));
		}

		File.close();
	}
	else
		cout << "Error : Cannot open file (" << ClientsFileName << ")";

	return veClients;
}

string ConvertClientRecordToRecordLine(const stClient& Client, const string& Delimiter)
{
	return	Client.AccountNumber + Delimiter + Client.PinCode + Delimiter + Client.Name + Delimiter + Client.Phone + Delimiter + to_string(Client.Balance);
}
void FileSaveClientsRecordsLiensByVector(const string& ClientsFileName, const string& Delimiter, const vector <stClient>& veClients)
{
	ofstream File(ClientsFileName);
	if (File.is_open())
	{
		for (const stClient& Client : veClients)
		{
			if (Client.Delete == false)
				File << ConvertClientRecordToRecordLine(Client, Delimiter) << "\n";
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

bool IsClientExistUsingAccountNumber(const vector <stClient>& veClients, const string& AccountNumber, stClient& ClientRecord)
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

void UpdateBalanceUsingClientAccountNumber(vector <stClient>& veClients, const string& AccountNumber, const double Amount)
{
	for (stClient& Client : veClients)
	{
		if (Client.AccountNumber == AccountNumber)
		{
			Client.Balance += Amount;
			break;
		}
	}
}
//--
stUser ConvertUserRecordLineToRecord(const string& RecordLine, const string& Delimiter)
{
	vector <string> veFields = StringSplit(RecordLine, Delimiter);

	return { veFields[0],veFields[1],(short)stoi(veFields[2]) };
}
vector <stUser> FileLoadUsersListInVector(const string& UsersFileName, const string& Delimiter)
{
	vector <stUser> veUsers;

	ifstream File(UsersFileName);
	if (File.is_open())
	{
		string Line;
		while (getline(File, Line))
		{
			veUsers.push_back(ConvertUserRecordLineToRecord(Line, Delimiter));
		}

		File.close();
	}
	else
		cout << "Error : Cannot open file <" << UsersFileName << ">";

	return veUsers;
}

string ConvertUserRecordToRecordLine(const stUser& User, const string& Delimiter)
{
	return User.Username + Delimiter + User.Password + Delimiter + to_string(User.Permissions);
}
void FileSaveUsersRecordsLinesByVector(const string& UserFileName, const string& Delimiter, const vector <stUser>& veUsers, const bool DeleteOldDate = false)
{
	ofstream File;

	if (DeleteOldDate)
		File.open(UserFileName);
	else
		File.open(UserFileName, ios::app);
	if (File.is_open())
	{
		for (const stUser& User : veUsers)
		{
			if (User.Delete == false)
				File << ConvertUserRecordToRecordLine(User, Delimiter) << "\n";
		}
		File.close();
	}
}

void PrintUserRecord(const stUser& User)
{
	cout << "The following are the user details: \n";
	cout << "------------------------------------\n";
	cout << "Username    : " << User.Username << "\n";
	cout << "Password    : " << User.Password << "\n";
	cout << "Permissions : " << User.Permissions << "\n";
	cout << "------------------------------------\n";
}

bool IsUserExist(const vector <stUser>& veUsers, const string& Username, stUser& UserRecord)
{
	for (const stUser& User : veUsers)
	{
		if (User.Username == Username)
		{
			UserRecord = User;
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
	cout << "\t[6] Transactions.\n";
	cout << "\t[7] Manage Users.\n";
	cout << "\t[8] Logout.\n";
	cout << "=============================================\n";
}

void PrintClientsListHeader(const short NumberOfClients)
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
void ShowClientListScreen(const string& ClientsFileName, const string& ClientsDelimiter)
{
	vector <stClient> veClients = FileLoadClientsListInVector(ClientsFileName, ClientsDelimiter);

	PrintClientsListHeader(veClients.size());

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
	while (IsClientExistUsingAccountNumber(veClients, Client.AccountNumber, Client))
	{
		Client.AccountNumber = StringRead("Client with [" + Client.AccountNumber + "] already exists, enter another account number : ");
	}
	Client.PinCode = StringRead("Enter pin code : ");
	Client.Name = StringRead("Enter name : ");
	Client.Phone = StringRead("Enter phone : ");
	Client.Balance = ReadNonNegativeNumber("Enter balance : ");

	return Client;
}
void AddNewClient(const string& ClientsFileName, const string& ClientsDelimiter)
{
	vector <stClient> veClients = FileLoadClientsListInVector(ClientsFileName, ClientsDelimiter);
	short static NumberOfClientsAdding = 1;

	printf("Adding New Client (%d):\n", NumberOfClientsAdding);
	stClient Client = ReadNewClientRecord(veClients);
	cout << "\n\n";

	PrintClientRecord(Client);

	if (StringReadOption("Are you sure you want to add new client with account number (" + Client.AccountNumber + ") : "))
	{
		FileAddNewLine(ClientsFileName, ConvertClientRecordToRecordLine(Client, ClientsDelimiter));
		cout << "\n\nClient add successfully";
		NumberOfClientsAdding++;
	}
}
void ShowAddClientsScreen(const string& ClientsFileName, const string& ClientsDelimiter)
{
	PrintHeader("Add New Clients Screen");

	do {
		AddNewClient(ClientsFileName, ClientsDelimiter);
		cout << "\n\n";

	} while (StringReadOption("Do you want to add more Clients ? "));

}

void MarkClientForDeleteUsingAccountNumber(vector <stClient>& veClients, const string& AccountNumber)
{
	for (stClient& Client : veClients)
	{
		if (Client.AccountNumber == AccountNumber)
		{
			Client.Delete = true;
			break;
		}
	}
}
void ShowDeleteClientScreen(const string& ClientsFileName, const string& ClientsDelimiter)
{
	PrintHeader("Delete Client Screen");

	vector <stClient> veClients = FileLoadClientsListInVector(ClientsFileName, ClientsDelimiter);

	string AccountNumber = StringRead("Enter account number : ");
	stClient ClientRecord;

	if (IsClientExistUsingAccountNumber(veClients, AccountNumber, ClientRecord))
	{
		cout << "\n\n";
		PrintClientRecord(ClientRecord);
		cout << "\n\n";

		if (StringReadOption("Are you sure you want to delete the client with account number (" + ClientRecord.AccountNumber + ") : "))
		{
			MarkClientForDeleteUsingAccountNumber(veClients, ClientRecord.AccountNumber);

			FileSaveClientsRecordsLiensByVector(ClientsFileName, ClientsDelimiter, veClients);

			cout << "\n\nClient deleted successfully";
		}
	}
	else
		cout << "\n\nClient with account number (" << AccountNumber << ") was not found!";
}

void UpdateClientUsingAccountNumber(vector <stClient>& veClients, const string& AccountNumber)
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
void ShowUpdateClientScreen(const string& ClientsFileName, const string& ClientsDelimiter)
{
	PrintHeader("Update Client Info Screen");

	vector <stClient> veClients = FileLoadClientsListInVector(ClientsFileName, ClientsDelimiter);

	string AccountNumber = StringRead("Enter account number : ");
	stClient ClientRecord;

	if (IsClientExistUsingAccountNumber(veClients, AccountNumber, ClientRecord))
	{
		cout << "\n\n";
		PrintClientRecord(ClientRecord);
		cout << "\n\n";

		if (StringReadOption("Are you sure you want to update the client with account number (" + ClientRecord.AccountNumber + ") : "))
		{
			cout << "\n\n";
			UpdateClientUsingAccountNumber(veClients, ClientRecord.AccountNumber);

			FileSaveClientsRecordsLiensByVector(ClientsFileName, ClientsDelimiter, veClients);

			cout << "\n\nClient update successfully";
		}
	}
	else
		cout << "\n\nClient with account number (" << AccountNumber << ") was not found!";
}

void ShowFindClientScreen(const string& ClientsFileName, const string& DelimiterClients)
{
	PrintHeader("Update Client Info Screen");

	vector <stClient> veClients = FileLoadClientsListInVector(ClientsFileName, DelimiterClients);

	string AccountNumber = StringRead("Enter account number : ");
	stClient ClientRecord;

	if (IsClientExistUsingAccountNumber(veClients, AccountNumber, ClientRecord))
	{
		cout << "\n\n";
		PrintClientRecord(ClientRecord);
	}
	else
		cout << "\n\nClient with account number (" << AccountNumber << ") was not found!";
}

enum class enTransactionType
{
	Deposit = 1, Withdrawal
};
string TransactionTypeToString(const enTransactionType TransactionType)
{
	switch (TransactionType)
	{
	case enTransactionType::Deposit:
		return "Deposit";
	case enTransactionType::Withdrawal:
		return "Withdrawal";
	}
}
short TransactionTypeToSign(const enTransactionType TransactionType)
{
	switch (TransactionType)
	{
	case enTransactionType::Deposit:
		return 1;
	case  enTransactionType::Withdrawal:
		return -1;
	}
}
void ShowTransactionScreen(const string& ClientsFileName, const string& ClientsDelimiter, const enTransactionType TransactionType)
{
	string TransactionName = TransactionTypeToString(TransactionType);
	string TransactionNameWithLowerCase = StringChangeLettersCase(TransactionName, enLetterCase::Lower);
	short Sign = TransactionTypeToSign(TransactionType);

	PrintHeader(TransactionName + " Screen");

	vector <stClient> veClients = FileLoadClientsListInVector(ClientsFileName, ClientsDelimiter);

	string AccountNumber;
	stClient ClientRecord;

	while (true)
	{
		AccountNumber = StringRead("Enter account number : ");

		if (IsClientExistUsingAccountNumber(veClients, AccountNumber, ClientRecord))
		{

			cout << "\n\n";
			PrintClientRecord(ClientRecord);
			cout << "\n\n";

			double TransactionAmount = ReadNonNegativeNumber("Enter " + TransactionNameWithLowerCase + " amount : ") * Sign;

			cout << "\n\n";
			bool PerformTransaction = StringReadOption("Are you sure you want to perform this transaction for the client with account number (" + ClientRecord.AccountNumber + ") : ");

			if (Sign == -1 && ClientRecord.Balance < abs(TransactionAmount))
			{
				cout << "\n\nInsufficient balance, " << TransactionNameWithLowerCase << " was cancelled!";
				return;
			}

			if (PerformTransaction)
			{
				UpdateBalanceUsingClientAccountNumber(veClients, ClientRecord.AccountNumber, TransactionAmount);
				ClientRecord.Balance += TransactionAmount;

				FileSaveClientsRecordsLiensByVector(ClientsFileName, ClientsDelimiter, veClients);

				cout << "\n\n" << TransactionName << " was successfully\n";
				cout << "New balance = " << ClientRecord.Balance;
			}
			return;
		}
		else
			cout << "\n\nClient with account number (" << AccountNumber << ") was not found!\n";
	}
}

void PrintTotalBalancesHeader(const int NumberOfClients)
{
	cout << "\t\t\t\tClients List (" << NumberOfClients << ")" << " Client(s)\n";
	cout << "____________________________________________________________________________________________________\n\n";
	cout << left;
	cout << "| " << setw(15) << "Account Number";
	cout << "| " << setw(48) << "Client Name";
	cout << "| " << setw(30) << "Balance" << "|\n";
	cout << "____________________________________________________________________________________________________\n";
}
void PrintClientBalance(const stClient& Client)
{
	cout << "| " << setw(15) << Client.AccountNumber;
	cout << "| " << setw(48) << Client.Name;
	cout << "| " << setw(30) << Client.Balance << "|\n";
}
void ShowTotalBalancesScreen(const string& ClientsFileName, const string& DelimiterClients)
{
	vector <stClient> veClients = FileLoadClientsListInVector(ClientsFileName, DelimiterClients);

	PrintTotalBalancesHeader(veClients.size());

	double TotalBalances = 0;

	for (const stClient& Client : veClients)
	{
		PrintClientBalance(Client);
		TotalBalances += Client.Balance;
	}
	cout << "____________________________________________________________________________________________________\n\n";


	cout << "\t\t\t\t\tTotal balances = " << TotalBalances;
	cout << "\n\n";
}

void PrintTransactionsScreen()
{
	cout << "=============================================\n";
	cout << "\t\t Transactions Menu Screen\n";
	cout << "=============================================\n";
	cout << "\t[1] Deposit.\n";
	cout << "\t[2] Withdraw.\n";
	cout << "\t[3] Total Balances.\n";
	cout << "\t[4] Main Menu.\n";
	cout << "=============================================\n";
}
void ShowTransactionsMainMenuScreen(const string& ClientsFileName, const string& ClientsDelimiter)
{
	while (true)
	{
		PrintTransactionsScreen();

		enTransactionsOption Option = (enTransactionsOption)ReadNumberInRange("Choose what do you want to do ? 1:4 ? ", 1, 4);

		system("cls");

		switch (Option)
		{
		case enTransactionsOption::Deposit:
			ShowTransactionScreen(ClientsFileName, ClientsDelimiter, enTransactionType::Deposit);
			break;
		case enTransactionsOption::Withdrawal:
			ShowTransactionScreen(ClientsFileName, ClientsDelimiter, enTransactionType::Withdrawal);
			break;
		case enTransactionsOption::TotalBalances:
			ShowTotalBalancesScreen(ClientsFileName, ClientsDelimiter);
			break;
		case enTransactionsOption::MainMenu:
			return;
		}

		cout << endl << endl;
		WaitAndClear();
	}
}
//--
bool IsLoginValid(const vector <stUser>& veUsers, const string& Username, const string Password, stUser& UserRecord)
{
	return  IsUserExist(veUsers, Username, UserRecord) && Password == UserRecord.Password;
}
stUser ShowLoginScreen(const string& UsersFileName, const string& UsersDelimiter)
{
	vector <stUser> veUsers = FileLoadUsersListInVector(UsersFileName, UsersDelimiter);
	stUser User;
	bool LoginValid = true;
	do
	{
		PrintHeader("    Login Screen");

		if (!LoginValid)
			cout << "Invalid Username or Password!\n";

		User.Username = StringRead("Enter Username : ");
		User.Password = StringRead("Enter Password : ");

		LoginValid = IsLoginValid(veUsers, User.Username, User.Password, User);

		system("cls");

	} while (!LoginValid);

	return User;
}

void PrintUsersListHeader(const short NumberOfUsers)
{
	cout << "\t\t\t\tUsers List (" << NumberOfUsers << ")" << " User(s)\n";
	cout << "____________________________________________________________________________________________________\n\n";
	cout << left;
	cout << "| " << setw(15) << "User Name";
	cout << "| " << setw(48) << "Password";
	cout << "| " << setw(30) << "Permissions" << "|\n";
	cout << "____________________________________________________________________________________________________\n";
}
void PrintUser(const stUser& User)
{
	cout << "| " << setw(15) << User.Username;
	cout << "| " << setw(48) << User.Password;
	cout << "| " << setw(30) << User.Permissions << "|\n";
}
void ShowUsersListScreen(const string& UsersFileName, const string& UsersDelimiter)
{
	vector <stUser> veUsers = FileLoadUsersListInVector(UsersFileName, UsersDelimiter);

	PrintUsersListHeader(veUsers.size());

	for (const stUser& User : veUsers)
	{
		PrintUser(User);
	}

	cout << "____________________________________________________________________________________________________";
}

short ReadUserPermissions()
{
	short Permissions = 0;

	if (StringReadOption("Do you want to give him full access? "))
		Permissions = 127;
	else
	{
		cout << "\nDo you want to give him access to:\n";

		if (StringReadOption("Show client list : "))
			Permissions += enMainMenuPermissions::PShowList;
		if (StringReadOption("Add new client : "))
			Permissions += enMainMenuPermissions::PAddClient;
		if (StringReadOption("Delete client : "))
			Permissions += enMainMenuPermissions::PDeleteClient;
		if (StringReadOption("Update client : "))
			Permissions += enMainMenuPermissions::PUpdateClient;
		if (StringReadOption("Find client : "))
			Permissions += enMainMenuPermissions::PFindClient;
		if (StringReadOption("Transactions : "))
			Permissions += enMainMenuPermissions::PTransactions;
		if (StringReadOption("Manage users : "))
			Permissions += enMainMenuPermissions::PManageUsers;
	}

	return Permissions;
}
stUser ReadNewUser(vector <stUser>& veUsers)
{
	stUser User;

	User.Username = StringRead("Enter username : ");
	while (IsUserExist(veUsers, User.Username, User))
	{
		User.Username = StringRead("User with [" + User.Username + "] already exists, enter another username : ");
	}

	User.Password = StringRead("Enter password : ");

	User.Permissions = ReadUserPermissions();

	return User;
}
void AddNewUser(const string& UsersFileName, const string& UsersDelimiter)
{
	vector <stUser> veUsers = FileLoadUsersListInVector(UsersFileName, UsersDelimiter);
	static short NumberOfUsersAdding = 1;

	printf("Adding New User (%d):\n", NumberOfUsersAdding);
	stUser User = ReadNewUser(veUsers);

	if (StringReadOption("\n\nAre you sure you want to add new user with username (" + User.Username + ") ? "))
	{
		FileAddNewLine(UsersFileName, ConvertUserRecordToRecordLine(User, UsersDelimiter));
		cout << "\n\nUser add successfully";
		NumberOfUsersAdding++;
	}
}
void ShowAddNewUserScreen(const string& UsersFileName, const string& UsersDelimiter)
{
	PrintHeader("Add New User Screen");

	do {

		AddNewUser(UsersFileName, UsersDelimiter);
		cout << "\n\n";

	} while (StringReadOption("Do you want to add more users? "));
}

void MarkUserForDeleteByUsername(vector <stUser>& veUsers, const string& Username)
{
	for (stUser& User : veUsers)
	{
		if (User.Username == Username)
			User.Delete = true;
	}
}
void ShowDeleteUserScreen(const string& UsersFileName, const string& UsersDelimiter)
{
	PrintHeader("Delete Users Screen");

	vector <stUser> veUsers = FileLoadUsersListInVector(UsersFileName, UsersDelimiter);
	string Username = StringRead("Enter username : ");
	stUser UserRecord;

	if (Username != "Admin")
	{
		if (IsUserExist(veUsers, Username, UserRecord))
		{
			cout << "\n\n";
			PrintUserRecord(UserRecord);
			cout << "\n\n";

			if (StringReadOption("Are you sure you want to delete the user with username (" + UserRecord.Username + ") : "))
			{
				MarkUserForDeleteByUsername(veUsers, Username);

				FileSaveUsersRecordsLinesByVector(UsersFileName, UsersDelimiter, veUsers, true);

				cout << "\n\nUser deleted successfully";
			}
		}
		else
			cout << "\n\nUser with username (" << Username << ") was not found!";
	}
	else
		cout << "\n\nYou cannot delete this user";
}

void UpdateUser(vector <stUser>& veUsers, const string& Username)
{
	for (stUser& User : veUsers)
	{
		if (User.Username == Username)
		{
			User.Password = StringRead("Enter password : ");
			User.Permissions = ReadUserPermissions();
			return;
		}
	}
}
void ShowUpdateUsersScreen(const string& UsersFileName, const string& UsersDelimiter)
{
	PrintHeader("Update Users Screen");

	vector <stUser> veUsers = FileLoadUsersListInVector(UsersFileName, UsersDelimiter);
	string Username = StringRead("Enter username : ");
	stUser UserRecord;

	if (IsUserExist(veUsers, Username, UserRecord))
	{
		cout << "\n\n";
		PrintUserRecord(UserRecord);
		cout << "\n\n";

		if (StringReadOption("Are you sure you want to update the user with username (" + UserRecord.Username + ") : "))
		{
			UpdateUser(veUsers, Username);

			FileSaveUsersRecordsLinesByVector(UsersFileName, UsersDelimiter, veUsers, true);

			cout << "\n\nUser update successfully";
		}
	}
	else
		cout << "\n\nUser with username (" << Username << ") was not found!";
}

void ShowFindUserScreen(const string& UsersFileName, const string& UsersDelimiter)
{
	PrintHeader("Find User Screen");

	vector <stUser> veUsers = FileLoadUsersListInVector(UsersFileName, UsersDelimiter);
	string Username = StringRead("Enter username : ");
	stUser UserRecord;

	if (IsUserExist(veUsers, Username, UserRecord))
	{
		cout << "\n\n";
		PrintUserRecord(UserRecord);
	}
	else
		cout << "\n\nUser with username (" << Username << ") was not found!";
}

void PrintManageUsersScreen()
{
	cout << "=============================================\n";
	cout << "\t\t Manage Users Menu Screen\n";
	cout << "=============================================\n";
	cout << "\t[1] List Users.\n";
	cout << "\t[2] Add New User.\n";
	cout << "\t[3] Delete User.\n";
	cout << "\t[4] Update User.\n";
	cout << "\t[5] Find User.\n";
	cout << "\t[6] Main Menu.\n";
	cout << "=============================================\n";
}
void ShowManageUsersMainMenuScreen(const string& UsersFileName, const string& UsersDelimiter)
{
	while (true)
	{
		PrintManageUsersScreen();

		enMangaeUsersOption Option = (enMangaeUsersOption)ReadNumberInRange("Choose what do you want to do ? 1:6 ? ", 1, 6);

		system("cls");

		switch (Option)
		{
		case enMangaeUsersOption::ListUsers:
			ShowUsersListScreen(UsersFileName, UsersDelimiter);
			break;
		case enMangaeUsersOption::AddNewUser:
			ShowAddNewUserScreen(UsersFileName, UsersDelimiter);
			break;
		case enMangaeUsersOption::DeleteUser:
			ShowDeleteUserScreen(UsersFileName, UsersDelimiter);
			break;
		case enMangaeUsersOption::UpdateUser:
			ShowUpdateUsersScreen(UsersFileName, UsersDelimiter);
			break;
		case enMangaeUsersOption::FindUser:
			ShowFindUserScreen(UsersFileName, UsersDelimiter);
			break;
		case enMangaeUsersOption::MainMenue:
			return;
		}

		cout << endl << endl;
		WaitAndClear();
	}
}

enMainMenuPermissions ConvertOptionToPermission(const enMainMenuOption Option)
{
	short arPermissions[] = { 1,2,4,8,16,32,64 };
	return (enMainMenuPermissions)arPermissions[Option - 1];
}
bool DoesUserHavePermission(const stUser& User, const enMainMenuOption Option)
{
	if (Option == enMainMenuOption::Logout)
		return true;

	enMainMenuPermissions Permission = ConvertOptionToPermission(Option);

	return (User.Permissions & Permission) == Permission;
}
void ShowNotPermissionScreen()
{
	cout << "------------------------------------\n";
	cout << "Access denied\n";
	cout << "You don't have permission to do this\n";
	cout << "------------------------------------\n";
}

void Bank(const string& ClientsFileName, const string& ClientsDelimiter, const string& UsersFileName, const string& UsersDelimiter)
{
	stUser User = ShowLoginScreen(UsersFileName, UsersDelimiter);

	while (true)
	{
		ShowMainMenuScreen();
		enMainMenuOption Option = (enMainMenuOption)ReadNumberInRange("Choose what do you want to do ? 1:8 ? ", 1, 8);

		system("cls");
		if (DoesUserHavePermission(User, Option))
		{
			switch (Option)
			{
			case enMainMenuOption::ShowList:
				ShowClientListScreen(ClientsFileName, ClientsDelimiter);
				break;
			case enMainMenuOption::AddClient:
				ShowAddClientsScreen(ClientsFileName, ClientsDelimiter);
				break;
			case enMainMenuOption::DeleteClient:
				ShowDeleteClientScreen(ClientsFileName, ClientsDelimiter);
				break;
			case enMainMenuOption::UpdateClient:
				ShowUpdateClientScreen(ClientsFileName, ClientsDelimiter);
				break;
			case enMainMenuOption::FindClient:
				ShowFindClientScreen(ClientsFileName, ClientsDelimiter);
				break;
			case  enMainMenuOption::Transactions:
				ShowTransactionsMainMenuScreen(ClientsFileName, ClientsDelimiter);
				continue;
			case enMainMenuOption::ManageUsers:
				ShowManageUsersMainMenuScreen(UsersFileName, UsersDelimiter);
				continue;
			case enMainMenuOption::Logout:
				return;
			}
		}
		else
			ShowNotPermissionScreen();

		cout << endl << endl;
		WaitAndClear();
	}
}

int main()
{
	string ClientsFileName = "Clients.txt";
	string ClientsDelimiter = "#";

	string UsersFileName = "Users.txt";
	string UsersDelimiter = "#";

	Bank(ClientsFileName, ClientsDelimiter, UsersFileName, UsersDelimiter);
}