#pragma once
#include <iostream>
#include <iomanip>
#include "clsMainScreen.h"
#include "clsScreen.h"
#include "clsUser.h"
#include "Global.h"

using namespace std;
class clsLoginScreen : protected clsScreen
{

	static bool _LoginScreen()
	{
		bool faild = false; 
		short loginfailed = 0; 
		string username, password;

		do
		{
			 
			if (faild)
			{
				loginfailed++;

				cout << "Invalid Username or Password\n"; 
				cout << "you have " << 3 - loginfailed; 
				cout << "traile(s) "; 
			}
			if (loginfailed == 3)
			{
				cout << "you are locked!" <<endl;
				return false;
			}

			
			cout << "Please,Enter Username ?\n"; 
			cin >> username; 

			cout << "Please,Enter Passowrd ?\n";
			cin >> password; 

			CurrentUser = clsUser::Find(password , username);
		//cout << "\n=== DEBUG LOGIN ===" << endl;
		//cout << "After Find - IsEmpty: " << CurrentUser.IsEmpty() << endl;
		//cout << "After Find - Username: '" << CurrentUser.UserName << "'" << endl;
		//cout << "After Find - Password: '" << CurrentUser.Password << "'" << endl;
			faild = CurrentUser.IsEmpty(); 

		} while (faild);

		CurrentUser.RegisterLogin(); 
		 clsMainScreen::ShowMainMenu();

		 return true; 
		
	}

public:

	static bool ShowLigenScreen()
	{

		system("cls"); 

		_DrawSecreenHeadr("Login Screen"); 

		return _LoginScreen(); 


	}

};

