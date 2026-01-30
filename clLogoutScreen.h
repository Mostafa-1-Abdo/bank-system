#pragma once
#include <iostream>
#include <chrono>
#include <thread>
#include "clScreen.h"
#include "clUser.h"
#include "CurrentUser.h"
#include "clUtil.h"
using namespace std;

class clLogoutScreen : protected clScreen
{
public:
	static void ShowLogoutScreen()
	{
		DrawScreenHeader(clUtil::Spaces(13) + "Logout Screen");
		cout << "Logging out...\n";

		CurrentUser = clUser::Find("");

		this_thread::sleep_for(chrono::seconds(5));
	}
};