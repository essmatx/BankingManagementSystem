#pragma once
#include <iostream>
#include "clsPerson.h"
#include "clsCalculater.h"
#include "clsAddress.h"
#include "clsString.h"
#include "clsDate.h"
#include "clsUtil.h"
#include "clsInputValidDate.h"
#include "clsBankClient.h"
#include "clsMainScreen.h"
#include "clsAddNewUserScreen.h"
#include <string>
#include <vector>
using namespace std;
class clsFindUserScreen : clsScreen
{
	static void _PrintUserCardInfo(clsUser user)
	{
		cout << "\tUser Card ";
		cout << "\n__________________________________\n";
		cout << "\nFirst name :" << user.FirstName;
		cout << "\nLast name  :" << user.LastName;
		cout << "\nFullname   :" << user.FullName();
		cout << "\nEmail      :" << user.Email;
		cout << "\nPhone      :" << user.Phone;
		cout << "\nUser name  :" << user.UserName;
		cout << "\nPermissions:" << user.Permissions;
		cout << "\nPassowrd   :" << user.Password;
		cout << "\n__________________________________\n";
	}

public :
	static void ShowFindUserScreen()
	{
		clsScreen::_DrawSecreenHeadr("Find User Screen"); 

		string user = ""; 

		cout << "Please, Enter Username ?\n"; 
		user = clsInputValidDate<string>::ReadString();

		while (!clsUser::IsUserExist(user))
		{
			cout << "Username that you have entred is not exisit please try another one!\n";
			user = clsInputValidDate<string>::ReadString();
		}

		clsUser Username = clsUser::Find(user); 

		if (!Username.IsEmpty())
		{
			cout << "User was found :-)\n"; 
			
		}
		else
		{
			cout << "User was not found :-(\n"; 
		}

		_PrintUserCardInfo(Username);

	}
};

