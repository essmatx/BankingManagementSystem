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
#include "clsScreen.h"
#include "clsClientListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsUpdateClient.h"
#include "clsDeletScreen.h"
#include "clsFindClient.h"
#include "clsTransacion.h"
#include "clsManageUsers.h"
#include "clsLoginregister.h"
#include "clsShowCurrencyExchange.h"
#include "clsListCurrensecs.h"
#include "Global.h"
#include <string>
#include <vector>
using namespace std;

class clsTransacion;
class clsMainScreen : protected clsScreen 
{

	enum enMainMenueOptions {
		eListClients = 1, eAddNewClien = 2, eDeletClient = 3,
		eUpdateClient = 4, eFindClient = 5, eShowTransactionsMenue = 6,
		eManageUsers = 7, eLoginRegister = 8,eCurrencyExcgange = 9 ,eExit = 10
	};

	static short _ReadMainMenueOptions() 
	{
		cout << setw(35) << left << "" << "Please enter a number corresponding your desired action(1-10)"; 
		short Choose = clsInputValidDate<short>::ReadshorNumbertBetween(1, 10, "Enter a number between 1 - 10"); 

		return Choose; 
	}

	static void _GetbacktoMainMenue()
	{
		cout << setw(37) << left << "" << "\n\tPlease,press any kye to get back to the main menue! \n";
		system("pause>0"); 
		ShowMainMenu();
	}

	static void _ShowAllClientsScreen()
	{
		//cout << "\nClients List screen will be here...\n"; 
		 clsClientListScreen::ShowClientsList(); 
	}

	static void _ShowAddNewClientscren()
	{
		//AddNew Client screen will be here
		clsAddNewClientScreen::AddNewClient(); 
	}

	static void _ShowDeletClientScreen()
	{
		//cout << "\nDelet Client screen will be here...\n"; 
		clsDeletScreen::DeletClient(); 
	}

	static void _ShowUpdateClientscreen()
	{
		//cout << "\nUpdate Client screen will be here...\n"; 

		clsUpdateClient::UpateClient(); 
	}

	static void _ShowFindClientScreen()
	{
		//cout << "\n Find Client screen will be here...\n"; 
		clsFindClient::FindClient(); 
	}

	static void _ShowTransactionMenueScereen()
	{
		//cout << "\nTransaction Menue screen will be here..."; 


		clsTransacion::TransactionMnuescreen();
	}

	static void _ShowLoginRegister()
	{
		//Login register screen will be here...
		clsLoginregister::ShowLoginRegisterList(); 
	}

	static void _ShowManageUsersScreen()
	{
		//cout << "\nManage Users screen will be here...\n"; 
		clsManageUsers::ShoManageMnueScreen(); 
	}

	static void ShowCurrencyExchangeScreen()
	{
		//CurrencyExchangeSeccren Will be here...
		clsShowCurrencyExchange::ShowCurrencyExchangeMenue(); 
	}

	static void _Logout() 
	{
		//cout << "\nEnd Screen will be here...\n";

		CurrentUser = clsUser::Find("", ""); 
	}

	static void _PerformMenueOption(enMainMenueOptions options)
	{
		switch (options)
		{
		case enMainMenueOptions::eListClients:
			system("cls");
			_ShowAllClientsScreen();
			_GetbacktoMainMenue();
			break;

		case enMainMenueOptions::eAddNewClien:
			system("cls");
			_ShowAddNewClientscren();
			_GetbacktoMainMenue();
			break;

		case enMainMenueOptions::eDeletClient:
			system("cls");
			_ShowDeletClientScreen();
			_GetbacktoMainMenue();
			break;

		case enMainMenueOptions::eUpdateClient:
			system("cls");
			_ShowUpdateClientscreen();
			_GetbacktoMainMenue();
			break;

		case  enMainMenueOptions::eFindClient:
			system("cls");
			_ShowFindClientScreen();
			_GetbacktoMainMenue();
			break;

		case enMainMenueOptions::eShowTransactionsMenue:
			system("cls");
			_ShowTransactionMenueScereen();
				_GetbacktoMainMenue();
			break;

		case enMainMenueOptions::eManageUsers:
			system("cls");
			_ShowManageUsersScreen();
			_GetbacktoMainMenue();
			break;


		case enMainMenueOptions::eLoginRegister:
			system("cls");
			_ShowLoginRegister();
			_GetbacktoMainMenue();
			break;

		case enMainMenueOptions::eCurrencyExcgange:
			system("cls");
			ShowCurrencyExchangeScreen();
			_GetbacktoMainMenue();
			break;

		case enMainMenueOptions::eExit:
			system("cls");
			_Logout();
			break; 
		}; 
	}

	public: 

		static void ShowMainMenu()
		{
			system("cls");
			_DrawSecreenHeadr("Main Screen\n");


			cout  << "\n                                  ======================================================\n";
			cout  << "\t\t                                      Main Menu\n";
			cout  << "\n                                  ======================================================\n";


			cout  << "\t                                            [1] Show Client List.\n";
			cout  << "\t                                            [2] Add New Client.\n";
			cout  << "\t                                            [3] Delte Client.\n";
			cout  << "\t                                            [4] Update Client.\n";
			cout  << "\t                                            [5] Find a CLient.\n";
			cout  << "\t                                            [6] Transactions.\n";
			cout  << "\t                                            [7] Manage Users.\n";
			cout  << "\t                                            [8] Login register\n";
			cout  << "\t                                            [9] Currency Exchange.\n";
			cout  << "\t                                            [10] Logout.\n";

			cout  << "\n                                   ======================================================\n";


			_PerformMenueOption((enMainMenueOptions) _ReadMainMenueOptions());
		}; 


};

