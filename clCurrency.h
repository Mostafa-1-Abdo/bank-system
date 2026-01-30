#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "clString.h"
using namespace std;

string CurrenciesFileName = "Currencies.txt";
string CurrenciesDelimiter = "#//#";

class clCurrency
{
private:
	enum enMode
	{
		EmptyMode,UpdateMode
	};


	string _Country, _Code, _Name;
	float _Rate;
	enMode _Mode;

	static clCurrency _EmptyCurrencyObject()
	{
		return  clCurrency(enMode::EmptyMode,"", "", "", 0);
	}

	static clCurrency _ConvertLineToCurrencyObject(const string &Line)
	{
		vector <string> veCurrencyData = clString::Split(Line, CurrenciesDelimiter);
		return clCurrency(enMode::UpdateMode,veCurrencyData[0], veCurrencyData[1], veCurrencyData[2], stof(veCurrencyData[3]));
	}
	static vector <clCurrency> _LoadCurrenciesDataFromFile()
	{
		vector <clCurrency> veCurrencies;
		ifstream File(CurrenciesFileName);

		if (File.is_open())
		{
			string Line;
			while (getline(File, Line))
			{
				veCurrencies.push_back(_ConvertLineToCurrencyObject(Line));
			}
			File.close();
		}

		return veCurrencies;
	}
	static string _ConvertCurrencyObjectToLine(const clCurrency& Currency)
	{
		return Currency._Country + CurrenciesDelimiter + Currency._Code + CurrenciesDelimiter + Currency._Name + CurrenciesDelimiter + to_string(Currency._Rate);
	}
	void _SaveCurrenciesDataInFile(const vector <clCurrency> &veCurrencies)
	{
		ofstream File(CurrenciesFileName);

		if (File.is_open())
		{
			for (const clCurrency& Currency : veCurrencies)
			{
				File << _ConvertCurrencyObjectToLine(Currency) << "\n";
			}
			File.close();
		}
	}

	void _Update()
	{
		vector <clCurrency> veCurrencies = _LoadCurrenciesDataFromFile();

		for (clCurrency& Currency : veCurrencies)
		{
			if (Currency._Code == _Code)
			{
				Currency = *this;
				break;
			}
		}

		_SaveCurrenciesDataInFile(veCurrencies);
	}

	float _ConvertToUSD(const float Amount)
	{
		return Amount / _Rate;
	}

public:
	clCurrency(const enMode Mode,const string &Country,const string &Code,const string &Name,const float Rate )
	{
		_Mode = Mode;
		_Country = Country;
		_Code = Code;
		_Name = Name;
		_Rate = Rate;
	}

	string GetCountry()const
	{
		return _Country;
	}
	__declspec(property(get = GetCountry))string Country;

	string GetCode()const
	{
		return _Code;
	}
	__declspec(property(get = GetCode))string Code;

	string GetName()const
	{
		return _Name;
	}
	__declspec(property(get = GetName))string Name;
	
	float GetRate()const
	{
		return _Rate;
	}
	__declspec(property( get = GetRate))float Rate;

	bool IsEmpty()
	{
		return _Mode == enMode::EmptyMode;
	}

	static clCurrency FindByCountry(const string& Country)
	{
		string CountryInUpperCase = clString::UpperAllString(Country);
		ifstream File(CurrenciesFileName);

		if (File.is_open())
		{
			string Line;
			while (getline(File, Line))
			{
				clCurrency Currency = _ConvertLineToCurrencyObject(Line);
				if (clString::UpperAllString(Currency._Country) == CountryInUpperCase)
				{
					File.close();
					return Currency;
				}
			}
			File.close();
		}
		return _EmptyCurrencyObject();
	}
	static clCurrency FindByCode(const string& Code)
	{
		string CodeInUpperCase = clString::UpperAllString(Code);
		ifstream File(CurrenciesFileName);

		if (File.is_open())
		{
			string Line;
			while (getline(File, Line))
			{
				clCurrency Currency = _ConvertLineToCurrencyObject(Line);
				if (Currency._Code == CodeInUpperCase)
				{
					File.close();
					return Currency;
				}
			}
			File.close();
		}
		return _EmptyCurrencyObject();
	}
	static bool IsExistByCountry(const string& Country)
	{
		return !FindByCountry(Country).IsEmpty();
	}
	static bool IsExistByCode(const string& Code)
	{
		return !FindByCode(Code).IsEmpty();
	}

	static vector <clCurrency> GetCurrenciesList()
	{
		return _LoadCurrenciesDataFromFile();
	}

	void UpdateRate(const float Rate)
	{
		_Rate = Rate;
		_Update();
	}

	float ConvertToOtherCurrency(const float Amount,const clCurrency &Currency2)
	{
		return _ConvertToUSD(Amount)* Currency2._Rate;
	}
};