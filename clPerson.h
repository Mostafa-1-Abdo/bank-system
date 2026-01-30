#pragma once
#include <iostream>
using namespace std;

class clPerson  
{
protected:
	string  _FirstName, _LastName, _Email, _Phone;

public:
	clPerson( const string& FirstName, const string& LastName, const string& Email, const  string& Phone)
	{
		_FirstName = FirstName;
		_LastName = LastName;
		_Email = Email;
		_Phone = Phone;
	}

	void SetFirstName(const string& FirstName)
	{
		_FirstName = FirstName;
	}
	string GetFirstName()const
	{
		return _FirstName;
	}
	__declspec(property(put = SetFirstName, get = GetFirstName))string FirstName;

	void SetLastName(const string& LastName)
	{
		_LastName = LastName;
	}
	string GetLastName()const
	{
		return _LastName;
	}
	__declspec(property(put = SetLastName, get = GetLastName))string LastName;

	void SetEmail(const string& Email)
	{
		_Email = Email;
	}
	string GetEmail()const
	{
		return _Email;
	}
	__declspec(property(put = SetEmail, get = GetEmail))string Email;

	void SetPhone(const string& Phone)
	{
		_Phone = Phone;
	}
	string GetPhone()const
	{
		return _Phone;
	}
	__declspec(property(put = SetPhone, get = GetPhone))string Phone;

	string GetFullName()const
	{
		return _FirstName + " " + _LastName;
	}
	__declspec(property(get = GetFullName))string FullName;
};