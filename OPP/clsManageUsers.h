#pragma once
#include <iostream>
#include "clsInputValidDate.h"
#include "clsScreen.h"
#include "clsUsersList.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"

using namespace std; 
class clsManageUsers : clsScreen
{
	enum eUsersMenu { eListUsers = 1, eAddNewUser = 2, eDeleteUser = 3, eUpdateUser = 4, eFindUser = 5, eMainMenu = 6 };

	static short _ReadUsersMenu()
	{
		cout << setw(35) << left << " Please,enter a number corresponding your desired action (1 - 7)!\n"; 
		short number = clsInputValidDate<short>::ReadshorNumbertBetween(1, 7); 

		return number; 
	}

	static void _GetbackToMangeUsersMenu()
	{
		cout << setw(37) << left << "Please, press any kye to get back to the Manage Users menu!" << endl;
		system("pause>0");

		ShoManageMnueScreen(); 
	}

	static void _ListUsersScreen()
	{
		//cout << " Users List screen will be here...."; 
		clsUsersList::ShowUsersList(); 
	}

	static void _AddNewUserScreen()
	{
		//cout << "Add New User Screen will be here..."; 
		clsAddNewUserScreen::ShowAddNewUser(); 
	}

	static void _DeleteUsersScreen() 
	{
		//cout << "Delete Users screen will be here..."; 
		clsDeleteUserScreen::ShowDeleteUser(); 
	}

	static void _UpdateUssersScreen()
	{
		//cout << "Update Users Screen will be here...";
		clsUpdateUserScreen::ShowUpateUserScreen(); 
	}

	static void _FindUsersScreen()
	{
		//cout << "Find Users Screen will be here...";

		clsFindUserScreen::ShowFindUserScreen(); 
	}

	static  void _PerformManageUsersMenu(eUsersMenu options)
	{
		switch (options)
		{
		case eUsersMenu::eListUsers:
			system("cls");
			_ListUsersScreen();
			_GetbackToMangeUsersMenu();
			break;

		case eUsersMenu::eAddNewUser:
			system("cls");
			_AddNewUserScreen();
			_GetbackToMangeUsersMenu();
			break;

		case eUsersMenu::eDeleteUser:
			system("cls");
			_DeleteUsersScreen();
			_GetbackToMangeUsersMenu();
			break;

		case eUsersMenu::eUpdateUser:
			system("cls");
			_UpdateUssersScreen();
			_GetbackToMangeUsersMenu();
			break;

		case eUsersMenu::eFindUser:
			system("cls");
			_FindUsersScreen();
			_GetbackToMangeUsersMenu();
			break;

		case eUsersMenu::eMainMenu:
		{

		}
		}
	}

public:

	static void ShoManageMnueScreen()
	{
		system("cls");
		if (!_CheckAccessRights(clsUser::enPermissions::pManageUsers))
		{
			return;
		}
		_DrawSecreenHeadr("Manage Users Screen\n");


		cout << "\n                                  ======================================================\n";
		cout << "\t\t                                 Manage Users Menu\n";
		cout << "\n                                  ======================================================\n";


		cout << "\t                                            [1] List Users.\n";
		cout << "\t                                            [2] Add New User.\n";
		cout << "\t                                            [3] Delete User.\n";
		cout << "\t                                            [4] Update User.\n";
		cout << "\t                                            [5] Find User.\n";
		cout << "\t                                            [6] Main Menu.\n";


		cout << "\n                                   ======================================================\n";

		_PerformManageUsersMenu((eUsersMenu)_ReadUsersMenu());

	}
};

