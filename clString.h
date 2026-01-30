#pragma once
#include <iostream>
#include <vector>
using namespace std;

class clString
{
private :
	string _Value;

	enum enWhatToCount { UpperLetters, LowerLetters, VowelLetters };
	static bool LetterIsVowel(char Letter)
	{
		char arVowelLetters[5] = { 'a','e','i','o' ,'u' };
		Letter = tolower(Letter);

		for (char& Element : arVowelLetters)
		{
			if (Letter == Element)
				return true;
		}
		return false;
	}
	static short CountLetters(string String, const enWhatToCount LetterCase)
	{
		short coLetters = 0;

		for (short i = 0; i < String.length(); i++)
		{

			if (LetterCase == enWhatToCount::UpperLetters && isupper(String[i]))
				coLetters++;

			else if (LetterCase == enWhatToCount::LowerLetters && islower(String[i]))
				coLetters++;

			else if (LetterCase == enWhatToCount::VowelLetters && LetterIsVowel(String[i]))
				coLetters++;
		}

		return coLetters;
	}

	static char InvertLetterCase(const char Letter)
	{
		return isupper(Letter) ? tolower(Letter) : toupper(Letter);
	}

	enum enChangeLetterCase { Upper = 1, Lower };
	static string ChangeLettersCase(string String, const enChangeLetterCase CharCase)
	{
		for (short i = 0; i < String.length(); i++)
		{
			if (CharCase == enChangeLetterCase::Upper)
				String[i] = toupper(String[i]);

			else
				String[i] = tolower(String[i]);
		}

		return String;
	}
public :
	clString()
	{
		_Value = "";
	}
	clString(const string &Value)
	{
		_Value = Value;
	}

	void SetValue(const string& Value)
	{
		_Value = Value;
	}
	string GetValue()
	{
		return _Value;
	}
	__declspec(property(put = SetValue, get = GetValue))string Value;

	static short Length(const string &String)
	{
		return String.length();
	}
	short Length()
	{
		return _Value.length();
	}

	static short CountUpperLetters(const string& String)
	{
		return CountLetters(String, enWhatToCount::UpperLetters);
	}
	short CountUpperLetters()
	{
		return CountLetters(_Value, enWhatToCount::UpperLetters);
	}

	static short CountLowerLetters(const string& String)
	{
		return CountLetters(String, enWhatToCount::LowerLetters);
	}
	short CountLowerLetters()
	{
		return CountLetters(_Value, enWhatToCount::LowerLetters);
	}

	static short CountVowels(const string& String)
	{
		return CountLetters(String, enWhatToCount::VowelLetters);
	}
	short CountVowels()
	{
		return CountLetters(_Value, enWhatToCount::VowelLetters);
	}

	static short CountSpecificChar(string String, char Char, const bool MatchCase = true)
	{
		short coChar = 0;

		for (short i = 0; i < String.length(); i++)
		{
			if (!MatchCase)
			{
				Char = tolower(Char);
				String[i] = tolower(String[i]);
			}

			if (Char == String[i])
				coChar++;
		}

		return coChar;
	}
	short CountSpecificChar(const char  Char, const bool MatchCase = true)
	{
		return CountSpecificChar(_Value, Char, MatchCase);
	}

	static short CountWords(string String, const string& Delimiter = " ")
	{
		string Word;
		short EndIndex;
		short coWords = 0;

		while ((EndIndex = String.find(Delimiter)) != string::npos)
		{
			Word = String.substr(0, EndIndex);

			if (!Word.empty())
				coWords++;

			String.erase(0, EndIndex + Delimiter.length());
		}
		if (!String.empty())
			coWords++;

		return coWords;
	}
	short CountWords(const string& Delimiter = " ")
	{
		return CountWords(_Value,Delimiter);
	}

	static string GetFirstLetterOfEachWord(const string& String)
	{
		string FirstLetters = "";
		bool IsFirstLetter = true;

		for (short i = 0; i < String.length(); i++)
		{
			if (String[i] != ' ' && IsFirstLetter)
				FirstLetters += String[i];

			IsFirstLetter = String[i] == ' ';
		}

		return FirstLetters;
	}
	string GetFirstLetterOfEachWord()
	{
		return GetFirstLetterOfEachWord(_Value);
	}

	static string UpperFirstLetter(string& String)
	{
		return string(1,toupper(String[0])) + String.substr(1);
	}
	string UpperFirstLetter()
	{
		return UpperFirstLetter(_Value);
	}

	static string LowerFirstLetter(string& String)
	{
		return string(1, tolower(String[0])) + String.substr(1);
	}
	string LowerFirstLetter()
	{
		return LowerFirstLetter(_Value);
	}

	static string UpperFirstLetterOfEachWord(string& String)
	{
		bool IsFirstLetter = true;

		for (short i = 0; i < String.length(); i++)
		{
			if (IsFirstLetter && String[i] != ' ')
				String[i] = toupper(String[i]);

			IsFirstLetter = String[i] == ' ';
		}

		return String;
	}
	void UpperFirstLetterOfEachWord()
	{
		_Value = UpperFirstLetterOfEachWord(_Value);
	}

	static string LowerFirstLetterOfEachWord(string String)
	{
		bool IsFirstLetter = true;

		for (short i = 0; i < String.length(); i++)
		{
			if (IsFirstLetter && String[i] != ' ')
				String[i] = tolower(String[i]);

			IsFirstLetter = String[i] == ' ';
		}

		return String;
	}
	void LowerFirstLetterOfEachWord()
	{
		_Value = LowerFirstLetterOfEachWord(_Value);
	}

	static string UpperAllString(const string& String)
	{
		return ChangeLettersCase(String, enChangeLetterCase::Upper);
	}
	void UpperAllString()
	{
		_Value = ChangeLettersCase(_Value, enChangeLetterCase::Upper);
	}

	static string LowerAllString(const string& String)
	{
		return ChangeLettersCase(String, enChangeLetterCase::Lower);
	}
	void LowerAllString()
	{
		_Value = ChangeLettersCase(_Value, enChangeLetterCase::Lower);
	}
	
	static string InvertAllLettersCase(string String)
	{
		for (short i = 0; i < String.length(); i++)
		{
			String[i] = InvertLetterCase(String[i]);
		}

		return String;
	}
	void InvertAllLettersCase()
	{
		_Value = InvertAllLettersCase(_Value);
	}

	static string RemovePunctuations(const string& String)
	{
		string Result = "";

		for (short i = 0; i < String.length(); i++)
		{
			if (!ispunct(String[i]))
			{
				Result += String[i];
			}
		}

		return Result;
	}
	void RemovePunctuations()
	{
		_Value = RemovePunctuations(_Value);
	}

	static string Reverse(const string& String, const string& Delimiter = " ")
	{
		vector <string> veWords = Split(String, Delimiter);
		string ReverseString = "";

		for (short i = veWords.size() - 1; i >= 0; i--)
		{
			ReverseString += veWords[i];
			ReverseString += Delimiter;
		}

		return ReverseString.substr(0, ReverseString.length() - Delimiter.length());
	}
	void Reverse(const string& Delimiter = " ")
	{
		_Value = Reverse(_Value, Delimiter);
	}

	static string ReplaceWord(string String, const string& OldWord, const string& NewWord)
	{
		short StartIndex = 0;

		while ((StartIndex = String.find(OldWord, StartIndex)) != string::npos)
		{
			String.replace(StartIndex, OldWord.length(), NewWord);

			StartIndex += NewWord.length();
		}

		return String;
	}
	void ReplaceWord(const string& OldWord, const string& NewWord)
	{
		_Value = ReplaceWord(_Value, OldWord, NewWord);
	}

	static string TrimLeft(const string &String)
	{
		for (short i = 0; i < String.length(); i++)
		{
			if (String[i] != ' ')
				return String.substr(i);
		}
		return "";
	}
	void TrimLeft()
	{
		_Value = TrimLeft(_Value);
	}

	static string TrimRight(const string& String)
	{
		for (short i = String.length() - 1; i > 0; i--)
			if (String[i] != ' ')
				return String.substr(0, i + 1);
		return "";
	}
	void TrimRight()
	{
		_Value = TrimRight(_Value);
	}

	static string Trim(const string& String)
	{
		return TrimRight(TrimLeft(String));
	}
	void Trim()
	{
		_Value = Trim(_Value);
	}
	
	static vector <string> Split(string String, const string& Delimiter = " ")
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
	vector <string> Split(const string Delimiter = " ")
	{
		return Split(_Value, Delimiter);
	}

	static string JoinString(vector <string>& veWords, string Delimiter = " ")
	{
		string String = "";

		for (string& Word : veWords)
		{
			if (!Word.empty())
			{
				String += Word;
				String += Delimiter;
			}
		}
		return String.substr(0, String.length() - Delimiter.length());
	}
	static string JoinString(string arWords[], short ArrayLength, string Delimiter = " ")
	{
		string String = "";

		for (short i = 0; i < ArrayLength; i++)
		{
			if (!arWords[i].empty())
			{
				String += arWords[i];
				String += Delimiter;
			}
		}
		return String.substr(0, String.length() - Delimiter.length());
	}
};