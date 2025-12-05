#pragma once
#include <iostream>
#include <iomanip>           
#include "clsScreen.h"       
#include "clsInputValidDate.h"  
#include "clsListCurrensecs.h" 
#include "clsFindCurrency.h"
#include "clsUpdateCurrencyRate.h"
#include "clsCurrencyCalculater.h"
using namespace std;



class clsShowCurrencyExchange :  protected clsScreen
{
	

	static short _ReadMainMenueOptions()
	{
		cout << setw(35) << left << "" << "Please enter a number corresponding your desired action(1-5)";
		short Choose = clsInputValidDate<short>::ReadshorNumbertBetween(1, 5, "Enter a number between 1 - 5");

		return Choose;
	}

	static void _ListCurrences()
	{
		//cout << "ListCurrences will be here...";
		clsListCurrencies::ShowCurrencesList();
	};

	static void _FindCurrences()
	{
		//cout << "FindCurrences will be here...";
		clsFindCurrency::ShowFindCurrencyScrren();
	}

	static void _UpdateRate()
	{
		//cout << "UpdateRate will be here...";
		clsUpdateCurrencyRate::ShowUpdateCurrencyRate(); 
	}

	static void _CurrencyCalculater()
	{
		//cout << "CurrencyCalculater will be here...";
		clsCurrencyCalculater::ShowCurrencyCalculator(); 
	}

	static void _GetBackToCurrensyMenueScreen()
	{
		
		cout << setw(37) << left << "" << "\n\tPlease,press any kye to get back to the main menue! \n";
		system("pause>0"); 
	
		ShowCurrencyExchangeMenue();

		
	}

	enum enCurrencyMenue { eListCurrencs = 1, eFindCurrency = 2, eUpdateRate = 3, 
		eCurrencyCalculater = 4, eMainMnue = 5
	};

	static void _PerformCurrencyExchangeMenue(enCurrencyMenue Currency)
	{
		switch (Currency)
		{
		case enCurrencyMenue::eListCurrencs:
			system("cls");
			_ListCurrences();
			_GetBackToCurrensyMenueScreen();
			break;

		case enCurrencyMenue::eFindCurrency:
			system("cls");
			_FindCurrences();
			_GetBackToCurrensyMenueScreen();
			break;

		case enCurrencyMenue::eUpdateRate:
			system("cls");
			_UpdateRate();
			_GetBackToCurrensyMenueScreen();
			break;

		case enCurrencyMenue::eCurrencyCalculater:
			system("cls");
			_CurrencyCalculater();
			_GetBackToCurrensyMenueScreen();
			break;

		case enCurrencyMenue::eMainMnue:
		default:
			break; 
		};
	};



public:

	

	

	static void ShowCurrencyExchangeMenue()
	{
		clsScreen::_DrawSecreenHeadr("Currency Exchange Main Screen"); 

			cout  << "\n                                  ======================================================\n";
			cout  << "\t\t                                    Currency Exchang Menu\n";
			cout  << "\n                                  ======================================================\n";


			cout  << "\t                                            [1] Show List Currences.\n";
			cout  << "\t                                            [2] Find Currence.\n";
			cout  << "\t                                            [3] Update Rate.\n";
			cout  << "\t                                            [4] Currency Calculater.\n";
			cout  << "\t                                            [5] Main Menue.\n";

			cout  << "\n                                   ======================================================\n";


			_PerformCurrencyExchangeMenue((enCurrencyMenue)_ReadMainMenueOptions());
	}
};

