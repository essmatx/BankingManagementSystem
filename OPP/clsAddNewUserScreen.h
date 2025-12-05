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
#include "clsManageUsers.h"
#include "clsUsersList.h"
#include "clsUser.h"
#include <string>
#include <vector>
using namespace std;
class clsAddNewUserScreen : clsScreen
{

	static void _ReadUserInfo(clsUser& User)
	{
		cout << "\nPlease enter,First name ?";
		User.FirstName = clsInputValidDate<string>::ReadString();

		cout << "\nPlease enter, Last name?";
		User.LastName = clsInputValidDate<string>::ReadString();

		cout << "\nPlease enter, Email addres?";
		User.Phone = clsInputValidDate<string>::ReadString();


		cout << "\nPlease enter, Phone number?";
		User.Email = clsInputValidDate<string>::ReadString();


		cout << "\nPlease enter, Passowrd?";
		User.Password = clsInputValidDate<string>::ReadString();

		cout << "\nPlease enter,Permissions?";
		User.Permissions = _ReadPermissions(); 
	}

	static  void _PrintUserCard(clsUser User)
	{
		cout << "\t\n User Card Info";
		cout << "\n_________________________________\n";
		cout << "First name	:" << User.FirstName << endl;
		cout << "Last name	:" << User.LastName << endl;
		cout << "Fullname	:" << User.FullName() << endl;
		cout << "Email		:" << User.Phone << endl;
		cout << "Phone		:" << User.Email << endl;
		cout << "Username   :" << User.UserName << endl; 
		cout << "Passowrd	:" << User.Password << endl;
		cout << "Permissions:" << User.Permissions << endl;
		cout << "\n_________________________________\n";
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

		cout << "Do you wnat to give access to\n"; 

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

		cout << "\nDelete Client ?Y/N"; 
		cin >> answer; 
		if (answer == 'y' || answer == 'Y')
		{
			permissions += clsUser::enPermissions::pDeleteCLient; 
		}

		cout << "Update Client\n"; 
		cin >> answer; 
		if (answer == 'y' || answer == 'Y')
		{
			permissions += clsUser::enPermissions::pUpdateClient; 
		}

		cout << "Find Client\n"; 
		cin >> answer; 
		if (answer == 'y' || answer == 'Y')
		{
			permissions += clsUser::enPermissions::pFindClient; 
		}

		cout << "Trancsactions\n"; 
		cin >> answer; 
		if (answer == 'y' || answer == 'Y')
		{
			permissions += clsUser::enPermissions::pTransaction; 
		}

		cout << "Manage Users\n"; 
		cin >> answer; 
		if (answer == 'y' || answer == 'Y')
		{
			permissions += clsUser::enPermissions::pManageUsers; 
		}

		cout << "Login Register\n";
		cin >> answer; 
		if (answer == 'y' || answer == 'Y')
		{
			permissions += clsUser::enPermissions::pLoginRegister;
		}

		return permissions; 
	};

	public:

		static void ShowAddNewUser()
		{
			_DrawSecreenHeadr("Add New User Screen");

			string Username = ""; 


			cout << "Please, Enter Username?\n"; 
			Username = clsInputValidDate<string>::ReadString();

			while(clsUser::IsUserExist(Username))
			{
				cout << "The Username that you have entred is already exists , Please try another one !";
				Username = clsInputValidDate<string>::ReadString();
			}

			clsUser Newuser = clsUser::GetAddnewUserObject(Username); 

			_ReadUserInfo(Newuser); 

			clsUser::enSaveResults SaveResullt;

			SaveResullt = Newuser.save(); 


			switch (SaveResullt)
			{
			case clsUser::enSaveResults::SaveSucceeded:
				cout << "User Added successfully :-)\n"; 
				_PrintUserCard(Newuser); 
				break;

			case clsUser::enSaveResults::SaveFailedEmptyObject:
				cout << "Error User was not saved because it's empty\n"; 
				break;

			case clsUser::enSaveResults::SaveFaileUserExixts:
				cout << "Error User was not saved because Username is used !\n";
				break;
			}
		}


		
}; 
