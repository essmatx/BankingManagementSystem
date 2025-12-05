#pragma once
#include <iostream>
#include "Global.h"
#include "clsDate.h"
using namespace std; 
class clsScreen
{
protected :


	

	static void _DrawSecreenHeadr(string Taitle, string subtitle = "")
	{
		cout << "\t\n                                   __________________________________________________\n"; 
		cout << "\t\t\n                                                    " <<    Taitle;
		if (subtitle != "")
		{
			cout << "\n" << subtitle;
			
		}

		cout << "\n                                  _______________________________________________________\n";


		cout << "\t\t\t\t\t\t\nUsername:" << CurrentUser.UserName; 
		
		cout << "\t\t\t\t\t\t\nDate:" << clsDate::DateToString(clsDate()) << endl; 
	}  
		

	static bool _CheckAccessRights(clsUser::enPermissions Permission)
	{
		if (!CurrentUser.CheckAccessPermissions(Permission))
		{
			cout << "\t\n                                   __________________________________________________\n";

			cout << "\t                                         Access Denied!, Contact your admin!";

			cout << "\n                                   _______________________________________________________\n";

			return false;
		}

		else
		{
			return true;
		}
	}
};

