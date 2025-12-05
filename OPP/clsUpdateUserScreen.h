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
class clsUpdateUserScreen : clsScreen
{

	static void _ReadUsersInfo(clsUser &User)
	{
		
		cout << "Please, Enter  First name?\n"; 
		User.FirstName = clsInputValidDate<string>::ReadString();

		cout << "Please, Enter  Last name ?\n"; 
		User.LastName  = clsInputValidDate<string>::ReadString();

		cout << "Please, Enter  Email ?\n"; 
		User.Email = clsInputValidDate<string>::ReadString();

		cout << "Please, Enter  Phone number ?\n";
		User.Phone = clsInputValidDate<string>::ReadString();

		cout << "Please, Enter Password ?\n"; 
		User.Password = clsInputValidDate<string>::ReadString();

		cout << "Please,Enter  Permissions ?\n"; 
		User.Permissions = _ReadPermissions();
	}

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

	static int _ReadPermissions()
	{
		int permissions = 0;

		char answer = 'n';

		cout << "\nDo you want to give full access Y/N ?";
		cin >> answer;

		if (answer == 'y' || answer == 'Y')
		{
			return -1;
		}

		cout << "Do you wnat to give access to\n ";

		cout << "Show Client List Y/N?\n";
		cin >> answer;

		if (answer == 'y' || answer == 'Y')
		{
			permissions += clsUser::enPermissions::pLisClient;
		}


		cout << "Add New Client?Y/N\n";
		cin >> answer;
		if (answer == 'y' || answer == 'Y')
		{
			permissions += clsUser::enPermissions::pAddNewClient;
		}

		cout << "Delete Client\n ";
		cin >> answer;
		if (answer == 'y' || answer == 'Y')
		{
			permissions += clsUser::enPermissions::pDeleteCLient;
		}

		cout << "Update Client\n ";
		cin >> answer;
		if (answer == 'y' || answer == 'Y')
		{
			permissions += clsUser::enPermissions::pUpdateClient;
		}

		cout << "Find Client\n ";
		cin >> answer;
		if (answer == 'y' || answer == 'Y')
		{
			permissions += clsUser::enPermissions::pFindClient;
		}

		cout << "Trancsactions\n ";
		cin >> answer;
		if (answer == 'y' || answer == 'Y')
		{
			permissions += clsUser::enPermissions::pTransaction;
		}

		cout << "Manage Users\n ";
		cin >> answer;
		if (answer == 'y' || answer == 'Y')
		{
			permissions += clsUser::enPermissions::pManageUsers;
		}

		return permissions;
	};

	public : 

		static void ShowUpateUserScreen()
		{

			clsScreen::_DrawSecreenHeadr("Update User Screen");
			string Username = ""; 

			cout << "Please,Enter your Username ?\n"; 
			Username = clsInputValidDate<string>::ReadString();

			while (!clsUser::IsUserExist(Username))
			{
				cout << "Username that you have entred is not exisit please try another one!\n";
				Username = clsInputValidDate<string>::ReadString();
			}

			clsUser User = clsUser::Find(Username); 
			 _PrintUserCardInfo(User); 

			  

			 cout << "Are you suer you want to update this User ?\n"; 
			 char Answer = 'n';
			 cin >> Answer; 

			 if (Answer == 'y' || Answer == 'Y')
			 {
				 
				 cout << "\tUpdate User Info"; 
				 cout << "\n___________________\n";
				 _ReadUsersInfo(User);

				 clsUser::enSaveResults SaveResullts;
				 SaveResullts = User.save(); 

				 switch (SaveResullts)
				 {

				 case clsUser::enSaveResults::SaveSucceeded:
					 cout << "User updated successfully :-)\n";
					 _PrintUserCardInfo(User); 
					 break; 

				 case clsUser::enSaveResults::SaveFailedEmptyObject:
					 cout << "Error was not saved !"; 
					 break; 
				 }
			 }
		}
};

