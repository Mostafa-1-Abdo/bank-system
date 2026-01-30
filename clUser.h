#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "clPerson.h"
#include "clString.h"
#include "clFile.h"
#include "clDate.h"
using namespace std;

string UsersFileName = "Users.txt";
string UsersDelimiter = "#//#";

string AdminsLoginLogFileName = "Login Log.txt";
string AdminsLoginLogDelimiter = "#//#";

const short Key = 5;


class clUser : public clPerson
{
private:
	struct stLoginLog;
	enum enMode
	{
		EmptyMode,UpdateMode,AddNewMode,DeleteMode
	};

	string _Username, _Password;
	short _Permissions ;
	enMode _Mode;

	static clUser _EmptyUserObject()
	{
		return clUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static clUser _ConvertLineToUserObject(const string& Line)
	{
		vector <string> veUserData = clString::Split(Line, UsersDelimiter);
		return clUser(enMode::UpdateMode, veUserData[0], veUserData[1], veUserData[2], veUserData[3], veUserData[4], clUtil::DecryptText(veUserData[5], Key), stoi(veUserData[6]));
	}
	static vector <clUser> _LoadUsersDataFromFile()
	{
		vector <clUser> veUsers;
		ifstream File(UsersFileName);

		if (File.is_open())
		{
			string Line;
			while (getline(File, Line))
			{
				veUsers.push_back(_ConvertLineToUserObject(Line));
			}
			File.close();
		}

		return veUsers;
	}
	static string _ConvertUserObjectToLine(const clUser& User)
	{
		return User._FirstName + UsersDelimiter + User._LastName + UsersDelimiter + User._Email + UsersDelimiter + User._Phone + UsersDelimiter + User._Username + UsersDelimiter + clUtil::EncryptText(User._Password, Key) + UsersDelimiter + to_string(User._Permissions);
	}
	static void _SaveUsersDataInFile(const vector <clUser>& veUsers)
	{
		ofstream File(UsersFileName);

		if (File.is_open())
		{
			for (const clUser& User : veUsers)
			{
				if (User._Mode == DeleteMode)
					continue;

				File << _ConvertUserObjectToLine(User) << "\n";
			}
			File.close();
		}
	}
	
	static stLoginLog _ConvertLineToUserLoginLogObject(const string& Line)
	{
		vector <string> veUserData = clString::Split(Line, AdminsLoginLogDelimiter);
		return stLoginLog{ veUserData[0], veUserData[1], clUtil::DecryptText(veUserData[2],Key), (short)stoi(veUserData[3]) };
	}
	static vector <stLoginLog> _LoadUsersLoginLogFromFile()
	{
		vector <stLoginLog> veUsers;
		ifstream File(AdminsLoginLogFileName);

		if (File.is_open())
		{
			string Line;
			while (getline(File, Line))
			{
				veUsers.push_back(_ConvertLineToUserLoginLogObject(Line));
			}
			File.close();
		}

		return veUsers;
	}
	string _PrepareLoginLogLine()
	{
		return  clDate::ConvertToString(clDate::GetToday()) + " - " + clDate::GetTimeAsString() + AdminsLoginLogDelimiter + _Username + AdminsLoginLogDelimiter + clUtil::EncryptText(_Password, Key) + AdminsLoginLogDelimiter + to_string(_Permissions);
	}

	void _Update(const string &OldUsername)
	{
		vector <clUser> veUsers = _LoadUsersDataFromFile();

		for (clUser& User : veUsers)
		{
			if (User._Username == OldUsername)
			{
				User = *this;
				break;
			}
		}

		_SaveUsersDataInFile(veUsers);
	}

	void _AddNew()
	{
		clFile::SaveNewLineInFile( UsersFileName, _ConvertUserObjectToLine(*this));
	}

public:
	clUser(const enMode Mode,const string& FirstName,const string& LastName,const string& Email,const string& Phone,const string& Username,const string &Password,const short Permissions)
		:clPerson(FirstName,LastName,Email,Phone)
	{
		_Mode = Mode;
		_Username = Username;
		_Password = Password;
		_Permissions = Permissions;
	}

	void SetUsername(const string &Username)
	{
		_Username = Username;
	}
	string GetUsername()const
	{
		return _Username;
	}
	__declspec(property(put = SetUsername, get = GetUsername))string Username;

	void SetPassword(const string& Password)
	{
		_Password = Password;
	}
	string GetPassword()const
	{
		return _Password;
	}
	__declspec(property(put = SetPassword, get = GetPassword))string Password;

	void SetPermissions(const short& Permissions)
	{
		_Permissions = Permissions;
	}
	short GetPermissions()const
	{
		return _Permissions;
	}
	__declspec(property(put = SetPermissions, get = GetPermissions))short Permissions;

	bool IsEmpty()
	{
		return _Mode == enMode::EmptyMode;
	}

	static clUser Find(const string& Username)
	{
		ifstream File(UsersFileName);

		if (File.is_open())
		{
			string Line;
			while (getline(File, Line))
			{
				clUser User = _ConvertLineToUserObject(Line);
				if (User._Username == Username )
				{
					File.close();
					return User;
				}
			}
			File.close();
			return _EmptyUserObject();
		}
	}
	static clUser Find(const string& Username, const string& Password)
	{
		ifstream File(UsersFileName);

		if (File.is_open())
		{
			string Line;
			while (getline(File, Line))
			{
				clUser User = _ConvertLineToUserObject(Line);
				if (User._Username == Username && User._Password == Password)
				{
					File.close();
					return User;
				}
			}
			File.close();
			return _EmptyUserObject();
		}
	}
	static bool IsExist(const string& Username)
	{
		return !Find(Username).IsEmpty();
	}
	static bool IsExist(const string& Username, const string& Password)
	{
		return !Find(Username,Password).IsEmpty();
	}

	static clUser GetNewUserObject()
	{
		return clUser(enMode::AddNewMode, "", "", "", "", "", "", 0);
	}

	enum enSaveResult
	{
		EmptyFalid, AccountNumberExistFalid, Succeeded
	};
	enSaveResult Save(const string &OldUsername ="")
	{
		switch (_Mode)
		{
		case enMode::EmptyMode:
		{
			return EmptyFalid;
		}
		case enMode::UpdateMode:
		{
			_Update(OldUsername);
			return Succeeded;
		}
		case enMode::AddNewMode:
		{
			if (IsExist(_Username))
			{
				return AccountNumberExistFalid;
			}

			_AddNew();
			_Mode = UpdateMode;
			return Succeeded;
		}
		}
	}
	void SaveLoginInLogFile()
	{
		clFile::SaveNewLineInFile(AdminsLoginLogFileName, _PrepareLoginLogLine());
	}

	void Delete()
	{
		vector <clUser> veUsers = _LoadUsersDataFromFile();

		for (clUser& User : veUsers)
		{
			if (User._Username == _Username )
			{
				User._Mode = DeleteMode;
			}
		}

		_SaveUsersDataInFile(veUsers);

		*this = _EmptyUserObject();
	}

	static vector <clUser> GetUsersList()
	{
		return _LoadUsersDataFromFile();
	}
	struct stLoginLog
	{
		string Date;
		string Username;
		string Password;
		short Permissions;
	};
	static vector <stLoginLog> GetLoginLogList()
	{
		return _LoadUsersLoginLogFromFile();
	}

	enum enPermissions
	{
		Logout = 0,ShowList = 1, AddClient = 2, DeleteClient = 4, UpdateClient = 8, FindClient = 16, Transactions = 32, ManageUsers = 64,LoginLog = 128,CurrencyExchange = 256
	};
	bool DoHavePermissions(const enPermissions Permission)const
	{
		return (_Permissions & Permission) == Permission;
	}
};
