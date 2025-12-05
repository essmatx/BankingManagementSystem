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
#include "clsUser.h"
#include <string>
#include <vector>
using namespace std;
class clsUsersList : clsScreen 
{
	static void _PrintUserRecrdLine(clsUser user)
	{
		cout << "        | " << setw(20) << left << user.FullName();
		cout << "| " << setw(25) << left << user.Email;
		cout << "| " << setw(15) << left << user.Phone;
		cout << "| " << setw(15) << left << user.UserName; 
		cout << "| " << setw(15) << left << user.Password;
		cout << "| " << setw(5) << left << user.Permissions;
		cout << "|\n" << endl; 
	}

public:

	static void ShowUsersList()
	{
		vector <clsUser> vuser = clsUser::GetUsersList(); 

		string Title = "\tUser Lisr Screen "; 
		string subtitle = "\t                                                 (" + to_string(vuser.size()) + ") User(s)"; 

		_DrawSecreenHeadr(Title, subtitle); 

		cout << setw(8) << left << "" << "\n\t__________________________________________________________________________________________________________                  \n";

		cout << "        | " << left << setw(20) << "Full Name";
		cout << "| " << left << setw(25) << "Email";
		cout << "| " << left << setw(15) << "Phone";
		cout << "| " << left << setw(15)  << "Username"; 
		cout << "| " << left << setw(15) << " Password"; 
		cout << "| " << left << setw(2) << "Perm";
		cout << "|\n" << endl;
		cout << setw(8) << left << "" << "\n\t___________________________________________________________________________________________________________\n";
		 

		if (vuser.size() == 0)
		{
			cout << "\n No users available in the system!"; 
		}
		else
		{
			for (clsUser user : vuser)
			{
				_PrintUserRecrdLine(user); 

				cout << endl; 
			}
		}

		cout << setw(8) << left << "" << "\n\t___________________________________________________________________________________________________________\n";
	}
};

