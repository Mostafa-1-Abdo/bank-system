#pragma once
#include <iostream>
#include "clScreen.h"
#include "clUtil.h"
using namespace std;

class clAccessDeniedScreen : protected clScreen
{
public:
	static void ShowAccessDeniedScreen()
	{
		DrawScreenHeader(clUtil::Spaces(10) + "Access Denied Screen");
		cout << "You do not have permission for this action.\n";
	}
};