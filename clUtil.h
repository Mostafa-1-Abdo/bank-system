#pragma once
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class clUtil
{
public:
    static void Srand()
    {
        srand((unsigned)time(NULL));
    }
    template <typename T>
    static T GetNumberInRange(const T From, const T To)
    {
        return rand() % (To - From + 1) + From;
    }
 
    enum enCharType {
        UpperLetter = 1, LowerLetter, Digit, RandomChar, SpecialChar
    };
    static char GetRandomChar(enCharType CharType)
    {
        if (CharType == RandomChar)
        {
            CharType = (enCharType)GetNumberInRange<short>(1, 3);
        }

        switch (CharType)
        {
        case enCharType::LowerLetter:
            return char(GetNumberInRange<short>(97, 122));
        case enCharType::UpperLetter:
            return char(GetNumberInRange<short>(65, 90));
        case enCharType::SpecialChar:
            return char(GetNumberInRange<short>(33, 47));
        case enCharType::Digit:
            return char(GetNumberInRange<short>(48, 57));
        }
    }
    static string GetRandomWord(const short Length,const enCharType CharType)
    {
        string Word;

        for (short i = 1; i <= Length; i++)
            Word = Word + GetRandomChar(CharType);

        return Word;
    }
    static string GetRandomKey(enCharType CharType = UpperLetter)
    {
        string Key;

        Key = GetRandomWord(4, CharType) + "-";
        Key += GetRandomWord(4, CharType) + "-";
        Key += GetRandomWord(4, CharType) + "-";
        Key += GetRandomWord(4, CharType);

        return Key;
    }

    template <typename T>
    void Swap(T& Variable1, T& Variable2)
    {
        T Temp = Variable1;
        Variable1 = Variable2;
        Variable2 = Temp;
    }

    static bool IsPrime(const int Number)
    {
        if (Number <= 1)
            return false;

        int SqrtOfNumber = sqrt(Number);
        for (int i = 2; i <= SqrtOfNumber; i++)
        {
            if (Number % i == 0)
                return false;
        }
        return true;
    }

    static bool IsPalindrome(const int Number)
    {
        return Number == GetReversedNumber(Number);
    }

    static string EncryptText(const string &Text, const short EncryptionKey)
    {
        string EncryptedText = "";

        short TextLength = Text.length();
        for (short i = 0; i < TextLength; i++)
            EncryptedText += char((short)Text[i] + EncryptionKey);

        return EncryptedText;
    }
    static string DecryptText(const string& Text, const short EncryptionKey)
    {
        string DecryptedText = "";

        short TextLength = Text.length();
        for (short i = 0; i < TextLength; i++)
            DecryptedText += char((int)Text[i] - EncryptionKey);

        return DecryptedText;
    }

    static int GetReversedNumber(int Number)
    {
        int ReversedNumber = 0;
        int Remainder;

        while (Number > 0)
        {
            Remainder = Number % 10;
            ReversedNumber = ReversedNumber * 10 + Remainder;
            Number /= 10;

        }

        return ReversedNumber;
    } 

    static string Convert1NumberToNumberText(const short Number)
    {
        string arNumberText[] = { "","One","Two","Three","Four","Five","Six","Seven","Eight","Nine" };
        return arNumberText[Number];
    }
    static string Convert2NumbersToNumberText(const short Number)
    {
        short Tens = Number / 10;
        short Ones = Number % 10;

        if (Tens == 0)
            return  Convert1NumberToNumberText(Ones);

        if (Number < 20)
        {
            string arNumberText[] = { "Ten","Eleven","Twelve","Thirteen","Fourteen","Fifteen","Sixteen","Seventeen","Eighteen","Nineteen" };
            return arNumberText[Ones];
        }

        string arTensText[] = { "Twenty","Thirty","Forty","Fifty","Sixty","Seventy","Eighty","Ninety" };
        string OnesText = Convert1NumberToNumberText(Ones);
        return arTensText[Tens - 2] + (OnesText.empty() ? "" : " " + OnesText);
    }
    static string Convert3NumbersToNumberText(const short Number)
    {
        if (Number == 0)
            return "";

        if (Number < 100)
            return Convert2NumbersToNumberText(Number);

        return  Convert1NumberToNumberText(Number / 100) + " Hundred " + Convert2NumbersToNumberText(Number % 100);
    }
    static string ConvertNumberToText(long long Number, short Scale = 0)
    {
        const string arScales[] = { "","Thousand","Million","Billion" };

        if (Number == 0)
        {
            if (Scale == 0)
                return "Zero";

            return "";
        }

        string Text = Convert3NumbersToNumberText(Number % 1000);
        if (!Text.empty())
            Text += " " + arScales[Scale] + " ";

        Scale++;
        return  ConvertNumberToText(Number / 1000, Scale) + Text;
    }

    static string Tabs(const short Count)
    {
        return string(Count, '\t');
    }
    static string Spaces(const int Width)
    {
        return string(Width, ' ');
    }
};