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
#include <string>
#include <vector>
using namespace std;
class clsDeleteUserScreen : clsScreen
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


public: 

	static void ShowDeleteUser()
	{
		clsScreen::_DrawSecreenHeadr("Delete User Screen"); 

		string Username = ""; 

		cout << "\nPlease enter Username ?";
		Username = clsInputValidDate<string>::ReadString();

		while (!clsUser::IsUserExist(Username))
		{
			 
				Username = clsInputValidDate<string>::ReadString();
		}

		clsUser User = clsUser::Find(Username); 
		_PrintUserCardInfo(User); 

		char Answer = 'n'; 

		cout << "\nAre you sure you want to delete this User ?"; 
		cin >> Answer; 

		if (Answer == 'y' || Answer == 'Y')
		{
			if (User.Delete())
			{
				cout << "User was deleted successfully :-)\n";
				_PrintUserCardInfo(User); 
			}
			else
			{
				cout << "Error User was not deleted!"; 
			}
		}
	}



};

