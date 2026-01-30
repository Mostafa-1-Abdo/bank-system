#pragma once
#pragma warning(disable : 4996)
#include <iostream>
#include <ctime>
#include <string>
#include <iomanip>
#include "sstream"
#include "clString.h"
using namespace std;

class clDate
{
private:

	short _Day;
	short _Month;
	int _Year;

	static short _GetDayOrder(const clDate& Date)
	{
		short a, y, m;
		a = (14 - Date._Month) / 12;
		y = Date._Year - a;
		m = Date._Month + 12 * a - 2;

		return (Date._Day + y + (y / 4) - (y / 100) + (y / 400) + (31 * m / 12)) % 7;
	}

	static string _GetMonthShortName(const short Month)
	{
		string arNameOfMonths[12] = { "Jan" ,"Feb" ,"Mar","Apr","May","Jun", "Jul","Aug", "Sep","Oct","Nov","Dec" };
		return arNameOfMonths[Month - 1];
	}

	static void _IncreaseByOneDay(clDate& Date)
	{
		if (IsLastDayInMonth(Date))
		{
			Date._Day = 1;
			if (Date._Month == 12)
			{
				Date._Month = 1;
				Date._Year++;
				return;
			}
			Date._Month++;
		}
		else
		{
			Date._Day++;
		}
	}
	static void _IncreaseByOneWeek(clDate& Date)
	{
		IncreaseByDays(Date, 7);
	}
	static void _IncreaseByOneMonth(clDate& Date)
	{
		if (Date._Month == 12)
		{
			Date._Month = 1;
			Date._Year++;
		}
		else
			Date._Month++;

		short NumberOfDaysInCurrentMonth = GetNumberOfDaysInMonth(Date._Month, Date._Year);
		if (Date._Day > NumberOfDaysInCurrentMonth)
			Date._Day = NumberOfDaysInCurrentMonth;
	}
	

	static void _DecreaseByOneDay(clDate& Date)
	{
		if (Date._Day == 1)
		{
			if (Date._Month == 1)
			{
				Date._Month = 12;
				Date._Year--;
			}
			else
				Date._Month--;
			Date._Day = GetNumberOfDaysInMonth(Date._Month, Date._Year);
		}
		else
		{
			Date._Day--;
		}
	}
	static void _DecreaseByOneWeek(clDate& Date)
	{
		DecreaseByDays(Date, 7);
	}
	static void _DecreaseByOneMonth(clDate& Date)
	{
		if (Date._Month == 1)
		{
			Date._Month = 12;
			Date._Year--;
		}
		else
			Date._Month--;

		short NumberOfDaysInCurrentMonth = GetNumberOfDaysInMonth(Date._Month, Date._Year);
		if (Date._Day > NumberOfDaysInCurrentMonth)
			Date._Day = NumberOfDaysInCurrentMonth;
	}


	static bool _IsNumberInRange(const short Number, const short From, const short To)
	{
		return Number >= From && Number <= To;
	}

	static clDate _GetSystemDate()
	{
		time_t t = time(0);
		tm* now = localtime(&t);

		return clDate(now->tm_mday, now->tm_mon + 1, now->tm_year + 1900);
	}

public:
	clDate()
	{
		*this = _GetSystemDate();
	}
	clDate(const short Day, const short Month, const int Year)
	{
		_Day = Day;
		_Month = Month;
		_Year = Year;
	}
	clDate(const string& Date, const string& Delimiter = "/")
	{
		*this = ConvertStringToDate(Date, Delimiter);
	}
	clDate(const short DayOrderInYear, const int Year)
	{
		*this = GetDateFromDayOrderInYear(DayOrderInYear, Year);
	}

	void SetDay(const short Day)
	{
		_Day = Day;
	}
	short GetDay()
	{
		return _Day;
	}
	__declspec(property(put = SetDay, get = GetDay))short Day;

	void SetMonth(const short Month)
	{
		_Month = Month;
	}
	short GetMonth()
	{
		return _Month;
	}
	__declspec(property(put = SetMonth, get = GetMonth))short Month;

	void SetYear(const int Year)
	{
		_Year = Year;
	}
	int GetYear()
	{
		return _Year;
	}
	__declspec(property(put = SetYear, get = GetYear))int Year;

	static void Swap(clDate& Date1, clDate& Date2)
	{
		clDate Temp = Date1;
		Date1 = Date2;
		Date2 = Temp;
	}
	void Swap(clDate& Date2)
	{
		Swap(*this, Date2);
	}

	void Print()
	{
		printf("%d/%d/%d\n", _Day, _Month, _Year);
	}

	static void PrintMonthCalendar(const short Month, const int Year)
	{
		clDate Date{ 1,Month,Year };

		short DayOrder = _GetDayOrder(Date);
		short NumberOfDays = GetNumberOfDaysInMonth(Month, Year);

		cout << "_______________" << _GetMonthShortName(Month) << "_______________\n";
		cout << "Sun  Mon  Tue  Wed  Thu  Fri  Sat\n";

		for (short i = 0; i < DayOrder; i++)
		{
			cout << "     ";
		}

		for (short i = 1; i <= NumberOfDays; i++)
		{
			cout << setw(3) << i << "  ";
			DayOrder++;

			if (DayOrder == 7)
			{
				cout << "\n";
				DayOrder = 0;
			}
		}
		cout << "\n_________________________________\n";
	}
	void PrintMonthCalendar()
	{
		PrintMonthCalendar(_Month, _Year);
	}

	static void PrintMonthDetails(const int Month, const int Year)
	{
		string MonthName = GetMonthName(Month);

		cout << "Number of days in " << MonthName << " in year [" << Year << "] is " << GetNumberOfDaysInMonth(Month, Year) << "\n";
		cout << "Number of hours in " << MonthName << " in year [" << Year << "] is " << GetNumberOfHoursInMonth(Month, Year) << "\n";
		cout << "Number of minutes in " << MonthName << " in year [" << Year << "] is " << GetNumberOfMinutesInMonth(Month, Year) << "\n";
		cout << "Number of seconds in " << MonthName << " in year [" << Year << "] is " << GetNumberOfSecondsInMonth(Month, Year);
	}
	void PrintMonthDetails()
	{
		PrintMonthDetails(_Month, _Year);
	}

	static void PrintYearCalendar(const int Year)
	{
		cout << "_________________________________\n\n";
		printf("         Calendar - %d          \n", Year);
		cout << "_________________________________";
		for (short i = 1; i <= 12; i++)
		{
			cout << "\n\n";
			PrintMonthCalendar(i, Year);
		}
	}
	void PrintYearCalendar()
	{
		PrintYearCalendar(_Year);
	}

	static void PrintYearDetails(const int Year)
	{
		cout << "Number of days in year [" << Year << "] is " << GetNumberOfDaysInYear(Year) << "\n";
		cout << "Number of hours in year [" << Year << "] is " << GetNumberOfHoursInYear(Year) << "\n";
		cout << "Number of minutes in year [" << Year << "] is " << GetNumberOfMinutesInYear(Year) << "\n";
		cout << "Number of seconds in year [" << Year << "] is " << GetNumberOfSecondsInYear(Year);
	}
	void PrintYearDetails()
	{
		PrintYearDetails(_Year);
	}


	static bool IsValid(const clDate& Date)
	{
		return (Date._Year > 0) && _IsNumberInRange(Date._Month, 1, 12) && _IsNumberInRange(Date._Day, 1, GetNumberOfDaysInMonth(Date._Month, Date._Year));
	}
	bool IsValid()
	{
		return IsValid(*this);
	}

	static bool IsLeapYear(const int Year)
	{
		return (Year % 400 == 0) || (Year % 4 == 0 && Year % 100 != 0);
	}
	bool IsLeapYear()
	{
		return  IsLeapYear(_Year);
	}

	static bool IsLastDayInMonth(const clDate& Date)
	{
		return Date._Day == GetNumberOfDaysInMonth(Date._Month, Date._Year);
	}
	bool IsLastDayInMonth()
	{
		return IsLastDayInMonth(*this);
	}

	static bool IsEndOfWeek(const clDate& Date)
	{
		return _GetDayOrder(Date) == 6;
	}
	bool IsEndOfWeek()
	{
		return IsEndOfWeek(*this);
	}

	static bool IsWeekend(const clDate& Date)
	{
		short DayOrder = _GetDayOrder(Date);

		return (DayOrder == 5 || DayOrder == 6);
	}
	bool IsWeekend()
	{
		return IsWeekend(*this);
	}

	static bool IsBusinessDay(const clDate& Date)
	{
		return !IsWeekend(Date);
	}
	bool IsBusinessDay()
	{
		return IsBusinessDay(*this);
	}

	static bool IsDate1BeforeDate2(const clDate& Date1, const clDate& Date2)
	{
		return (Date1._Year < Date2._Year) ? true : (Date1._Year != Date2._Year) ? false : (Date1._Month < Date2._Month) ? true : (Date1._Month != Date2._Month) ? false : (Date1._Day < Date2._Day) ? true : false;
	}
	bool IsBefore(const clDate& Date)
	{
		return IsDate1BeforeDate2(*this, Date);
	}

	static bool IsDate1EqualDate2(const clDate& Date1, const clDate& Date2)
	{
		return ((Date1._Year == Date2._Year) ? ((Date1._Month == Date2._Month) ? (Date1._Day == Date2._Day) : false) : false);
	}
	bool IsEqual(const clDate& Date)
	{
		return IsDate1EqualDate2(*this, Date);
	}

	static bool IsDate1AfterDate2(const clDate& Date1, const clDate& Date2)
	{
		return !IsDate1BeforeDate2(Date1, Date2) && !IsDate1EqualDate2(Date1, Date2);
	}
	bool IsAfter(const clDate& Date2)
	{
		return IsDate1AfterDate2(*this, Date2);
	}

	static bool IsDateBetween(const clDate& Date, clDate Date1, clDate Date2)
	{
		if (IsDate1AfterDate2(Date1, Date2))
			Swap(Date1, Date2);

		return !(IsDate1AfterDate2(Date1, Date) || IsDate1BeforeDate2(Date2, Date));
	}
	bool IsBetween(const clDate& Date1, const  clDate& Date2)
	{
		return IsDateBetween(*this, Date1, Date2);
	}



	static clDate IncreaseByDays(clDate Date, const int Days)
	{
		for (short i = 0; i < Days; i++)
			_IncreaseByOneDay(Date);

		return Date;
	}
	void IncreaseByDays(const int Days)
	{
		for (short i = 0; i < Days; i++)
			_IncreaseByOneDay(*this);
	}

	static clDate IncreaseByWeeks( clDate Date, const int Weeks)
	{
		for (short i = 0; i < Weeks; i++)
			_IncreaseByOneWeek(Date);

		return Date;
	}
	void IncreaseByWeeks(const int Weeks)
	{
		for (short i = 0; i < Weeks; i++)
			_IncreaseByOneWeek(*this);
	}

	static clDate IncreaseByMonths(clDate Date, const int Months)
	{
		for (short i = 0; i < Months; i++)
			_IncreaseByOneMonth(Date);

		return Date;
	}
	void IncreaseByMonths(const int Months)
	{
		for (short i = 0; i < Months; i++)
			_IncreaseByOneMonth(*this);
	}

	static clDate IncreaseByYears( clDate Date, const int Years)
	{
		Date._Year += Years;

		return Date;
	}
	void IncreaseByYears(const int Years)
	{
		_Year += Years;
	}

	static clDate IncreaseByDecades(clDate Date, const int Decades)
	{
		Date._Year += Decades * 10;

		return Date;
	}
	void IncreaseByDecades(const int Decades)
	{
		_Year += Decades * 10;
	}

	static clDate IncreaseByCentury(clDate Date, const int Centuries)
	{
		Date._Year += Centuries * 100;

		return Date;
	}
	void IncreaseByCentury(const int Centuries)
	{
		_Year += Centuries * 100;
	}

	static clDate IncreaseByMillennium( clDate Date, const int Millenniums)
	{
		Date._Year += Millenniums * 1000;

		return Date;
	}
	void IncreaseByMillennium(const int Millenniums)
	{
		_Year += Millenniums * 1000;
	}


	static clDate DecreaseByDays(clDate Date,const int Days)
	{
		for (short i = 0; i < Days; i++)
			_DecreaseByOneDay(Date);

		return Date;
	}
	void DecreaseByDays(const int Days)
	{
		for (short i = 0; i < Days; i++)
			_DecreaseByOneDay(*this);
	}

	static clDate DecreaseByWeeks(clDate Date, const int Weeks)
	{
		for (short i = 0; i < Weeks; i++)
			_DecreaseByOneWeek(Date);

		return Date;
	}
	void DecreaseByWeeks(const int Weeks)
	{
		for (short i = 0; i < Weeks; i++)
			_DecreaseByOneWeek(*this);
	}

	static clDate DecreaseByMonths(clDate Date, const int Months)
	{
		for (short i = 0; i < Months; i++)
			_DecreaseByOneMonth(Date);

		return Date;
	}
	void DecreaseByMonths(const int Months)
	{
		for (short i = 0; i < Months; i++)
			_DecreaseByOneMonth(*this);
	}

	static clDate DecreaseByYears(clDate Date, const int Years)
	{
		Date._Year -= Years;

		return Date;
	}
	void DecreaseByYears(const int Years)
	{
		_Year -= Years;
	}

	static clDate DecreaseByDecades(clDate Date, const int Decades)
	{
		Date._Year -= Decades * 10;

		return Date;
	}
	void DecreaseByDecades(const int Decades)
	{
		_Year -= Decades * 10;
	}

	static clDate DecreaseByCenturies(clDate Date, const int Centuries)
	{
		Date._Year -= 100 * Centuries;

		return Date;
	}
	void DecreaseByCenturies(const int Centuries)
	{
		_Year -= 100 * Centuries;
	}

	static clDate DecreaseByMillenniums(clDate Date, const int Millenniums)
	{
		Date._Year -= 1000 * Millenniums;

		return Date;
	}
	void DecreaseByMillenniums(const int Millenniums)
	{
		_Year -= 1000 * Millenniums;
	}


	static short GetNumberOfDaysInYear(const int Year)
	{
		return (IsLeapYear(Year) ? 366 : 365);
	}
	short NumberOfDaysInYear()
	{
		return GetNumberOfDaysInYear(_Year);
	}

	static short GetNumberOfHoursInYear(const int Year)
	{
		return GetNumberOfDaysInYear(Year) * 24;
	}
	short NumberOfHoursInYear()
	{
		return  GetNumberOfHoursInYear(_Year);
	}

	static int GetNumberOfMinutesInYear(const int Year)
	{
		return GetNumberOfHoursInYear(Year) * 60;
	}
	short NumberOfMinutesInYear()
	{
		return  GetNumberOfMinutesInYear(_Year);
	}

	static int GetNumberOfSecondsInYear(const int Year)
	{
		return GetNumberOfMinutesInYear(Year) * 60;
	}
	short NumberOfSecondsInYear()
	{
		return  GetNumberOfSecondsInYear(_Year);
	}


	static short GetNumberOfDaysInMonth(const int Month, const int Year)
	{
		short arNumberOfDaysInMonths[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
		return (Month == 2) ? (IsLeapYear(Year) ? 29 : 28) : arNumberOfDaysInMonths[Month - 1];
	}
	short NumberOfDaysInMonth()
	{
		return  GetNumberOfDaysInMonth(_Month, _Year);
	}

	static short GetNumberOfHoursInMonth(const int Month, const int Year)
	{
		return GetNumberOfDaysInMonth(Month, Year) * 24;
	}
	short NumberOfHoursInMonth()
	{
		return  GetNumberOfHoursInMonth(_Month, _Year);
	}

	static int GetNumberOfMinutesInMonth(const int Month, const int Year)
	{
		return GetNumberOfHoursInMonth(Month, Year) * 60;
	}
	short NumberOfMinutesInMonth()
	{
		return  GetNumberOfMinutesInMonth(_Month, _Year);
	}

	static int GetNumberOfSecondsInMonth(const int Month, const int Year)
	{
		return GetNumberOfMinutesInMonth(Month, Year) * 60;
	}
	short NumberOfSecondsInMonth()
	{
		return  GetNumberOfSecondsInMonth(_Month, _Year);
	}

	static string GetMonthName(const short Month)
	{
		string arNameOfMonths[12] = { "January" ,"February" ,"March","April","May","June", "July","August", "September","October","November","December" };
		return arNameOfMonths[Month - 1];
	}
	string MonthName()
	{
		return GetMonthName(_Month);
	}

	static string GetDayName(const clDate& Date)
	{
		string arNameOfDays[7] = { "Sunday" ,"Monday" ,"Tuesday","Wednesday","Thursday","Friday", "Saturday" };
		return arNameOfDays[_GetDayOrder(Date)];
	}
	string DayName()
	{
		return GetDayName(*this);
	}


	static short DaysUntilEndOfWeek(const clDate& Date)
	{
		return 6 - _GetDayOrder(Date);
	}
	short DaysUntilEndOfWeek()
	{
		return DaysUntilEndOfWeek(*this);
	}

	static short GetDaysUntilEndOfMonth(const clDate& Date)
	{
		return (GetNumberOfDaysInMonth(Date._Month, Date._Year) - Date._Day) + 1;
	}
	short DaysUntilEndOfMonth()
	{
		return GetDaysUntilEndOfMonth(*this);
	}

	static short GetDaysUntilEndOfYear(clDate Date)
	{
		return (short)GetDifferenceInDays(Date, { 31,12,Date._Year }, true);
	}
	short DaysUntilEndOfYear()
	{
		return GetDaysUntilEndOfYear(*this);
	}

	static short GetTotalDaysFromBeginningOfYear(const clDate& Date)
	{
		short TotalDays = 0;

		for (short i = 1; i < Date._Month; i++)
		{
			TotalDays += GetNumberOfDaysInMonth(i, Date._Year);
		}
		TotalDays += Date._Day;

		return TotalDays;
	}
	short TotalDaysFromBeginningOfYear()
	{
		return GetTotalDaysFromBeginningOfYear(*this);
	}

	static int GetDaysUntilNow(const clDate& Date)
	{
		return GetDifferenceInDays(Date, _GetSystemDate(), true);
	}
	int DaysUntilNow()
	{
		return GetDaysUntilNow(*this);
	}

	static int GetDifferenceInDays(clDate Date1, clDate Date2, bool IncludeEndDay = false)
	{
		int coDays = 0;
		short SwapFlag = 1;

		if (IsDate1AfterDate2(Date1, Date2))
		{
			Swap(Date1, Date2);
			SwapFlag = -1;
		}

		while (IsDate1BeforeDate2(Date1, Date2))
		{
			coDays++;
			_IncreaseByOneDay(Date1);
		}

		return  (IncludeEndDay ? ++coDays : coDays) * SwapFlag;
	}
	int DifferenceInDays(clDate Date2, bool IncludeEndDay = false)
	{
		return GetDifferenceInDays(*this, Date2, IncludeEndDay);
	}


	static string Format(const clDate& Date, const string& Format = "dd/mm/yy")
	{
		string FormattedDateString;

		FormattedDateString = clString::ReplaceWord(Format, "dd", to_string(Date._Day));
		FormattedDateString = clString::ReplaceWord(FormattedDateString, "mm", to_string(Date._Month));
		FormattedDateString = clString::ReplaceWord(FormattedDateString, "yy", to_string(Date._Year));

		return FormattedDateString;
	}
	string Format(const string& Formatting = "dd/mm/yy")
	{
		return Format(*this, Formatting);
	}

	static string ConvertToString(const clDate& Date, const string& Delimiter = "/")
	{
		return to_string(Date._Day) + Delimiter + to_string(Date._Month) + Delimiter + to_string(Date._Year);
	}
	string ConvertToString(const string& Delimiter = "/")
	{
		return ConvertToString(*this, Delimiter);
	}

	static clDate GetToday()
	{
		return _GetSystemDate();
	}
	static string GetTimeAsString()
	{
		time_t t = time(0);
		tm* now = localtime(&t);

		ostringstream Time;
		short Hour, Minute, Second;

		Hour = now->tm_hour;
		Minute = now->tm_min;
		Second = now->tm_sec;

		Time << setfill('0') << setw(2) << Hour << ":" << setw(2) << Minute << ":" << setw(2) << Hour;

		return Time.str();
	}
	static clDate GetDateFromDayOrderInYear(short DayOrder, const int Year)
	{
		clDate Date{ 0,1,Year };
		short MonthDays = GetNumberOfDaysInMonth(Date._Month, Year);

		while (DayOrder > MonthDays)
		{
			DayOrder -= MonthDays;
			Date._Month++;
			MonthDays = GetNumberOfDaysInMonth(Date._Month, Year);
		}
		Date._Day = DayOrder;

		return Date;
	}
	static clDate ConvertStringToDate(const string& StringDate, const string& Delimiter)
	{
		vector <string> veDate = clString::Split(StringDate, Delimiter);

		return { (short)stoi(veDate[0]),(short)stoi(veDate[1]),stoi(veDate[2]) };
	}

	static short GetBusinessDays(const clDate Date1, const clDate& Date2)
	{
		return GetVacationDays(Date1, Date2);
	}

	static short GetVacationDays(clDate Date1, const clDate& Date2)
	{
		short coDays = 0;

		while (!IsDate1EqualDate2(Date1, Date2))
		{
			if (IsBusinessDay(Date1))
				coDays++;

			_IncreaseByOneDay(Date1);
		}

		return coDays;
	}
	static clDate GetVacationEndingDate(clDate StartingDate, short VacationDays)
	{
		while (VacationDays != 0)
		{
			if (IsBusinessDay(StartingDate))
				VacationDays--;

			_IncreaseByOneDay(StartingDate);
		}

		return StartingDate;
	}

	friend class clPeriod;
};
