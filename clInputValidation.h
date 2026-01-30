#pragma once
#include <iostream>
#include <conio.h>
#include "clString.h"
#include "clDate.h"
using namespace std;

class clInputValidation
{
public:
	template <typename T>
	static T ReadNumber(const string& Message = "Enter a number : ")
	{
		T Number;

		cout << Message;
		cin >> Number;

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid number, enter again : ";
			cin >> Number;
		}

		return Number;
	}

	template <typename T>
	static T ReadNonNegativeNumber(const string& Message = "Enter a non negative number : ")
	{
		T Number;
		bool InvalidNumber = false;

		cout << Message;
		do {
			if (InvalidNumber)
			{
				cout << "Number is not non negative number, enter again : ";
			}
			cin >> Number;

			while (cin.fail())
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');

				cout << "Invalid number, enter a valid number : ";
				cin >> Number;
			}

			InvalidNumber = true;
		} while (Number < 0);

		return Number;
	}

	template <typename T>
	static T ReadNumberBetween(const T From, const T To, const string& Message = "Enter a number : ")
	{
		T Number;
		bool InvalidNumber = false;

		cout << Message;
		do {
			if (InvalidNumber)
			{
				cout << "Number is not within range, enter again : ";
			}
			cin >> Number;

			while (cin.fail())
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');

				cout << "Invalid number, enter again : ";
				cin >> Number;
			}

			InvalidNumber = true;
		} while (!(IsNumberBetween<T>(Number, From, To)));

		return Number;
	}

	static short ReadHiddenNumber(const string& Message)
	{
		char Number;
		cout << Message ;
		Number = _getch();
		return Number - '0';
	}

	template <typename T>
	static bool IsNumberBetween(const T Number, const T From, const T To)
	{
		return Number >= From && Number <= To;
	}

	static string ReadString(const string& Message = "Enter a string : ")
	{
		string String;

		cout << Message;
		getline(cin >> ws, String);

		return String;
	}
	static bool ReadOption(const string& Message)
	{
		string Option;
		bool InvalidOption = false;

		cout << Message ;
		do {
			if (InvalidOption)
			{
				cout <<"Invalid option, enter again : ";
			}
			cin >> Option;
			Option = clString::LowerAllString(Option);

			InvalidOption = true;

		} while (Option != "yes" && Option != "no");

		return Option == "yes";
	}

	static clDate ReadDate(const string Message = "Enter a date:\n")
	{
		clDate Date;

		cout << Message;
		Date.Year = ReadNonNegativeNumber<int>("Enter a year");
		Date.Month = ReadNumberBetween<short>(1, 12, "Enter a month");
		Date.Day = ReadNumberBetween<short>(1, clDate::GetNumberOfDaysInMonth(Date.Month, Date.Year), "Enter a day");

		return Date;
	}
};