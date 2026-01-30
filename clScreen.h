#pragma once
#include <iostream>
#include "clUtil.h"
#include "CurrentUser.h"
#include "clDate.h"
using namespace std;

class clScreen
{
public:
    static void DrawScreenHeader(const string &Title, const string& SubTitle = "")
    {
        cout <<clUtil::Spaces(48) <<"______________________________________\n\n";
        cout << clUtil::Spaces(48) << Title;
        if (SubTitle != "")
        {
            cout << "\n"<< clUtil::Spaces(48) << SubTitle;
        }
        cout << "\n" << clUtil::Spaces(48) << "______________________________________\n\n";
        cout << clUtil::Spaces(48) << "User : " << CurrentUser.Username << "\n";
        cout << clUtil::Spaces(48) << "Date : " << clDate::ConvertToString(clDate::GetToday()) << "\n";
        cout << clUtil::Spaces(48) << "______________________________________\n\n";
    }

    static void WaitAndClear()
    {
        cout << "Press any key to go back to main menu...";
        system("pause>0");
        system("cls");
    }
};