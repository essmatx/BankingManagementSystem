#pragma once
#include <iostream>
#include <iomanip>      
#include "clsScreen.h"  
#include "clsCurrency.h"
#include "clsInputValidDate.h"
#include <vector>
using namespace std;
class clsFindCurrency : protected clsScreen
{

	static short _ReadMainMenueOptions()
	{
		
		short Choose = clsInputValidDate<short>::ReadshorNumbertBetween(1, 2, "Enter a number between 1 - 2");

		return Choose;
	}

	static void _PrintCurrencyCrad(clsCurrency Currency)
	{
		cout << "\n\tCurrency's Card"; 
		cout << "\n_____________________________\n"; 
		cout << "\nCountry :" << Currency.Country(); 
		cout << "\nCode    :" << Currency.CurrencyCode(); 
		cout << "\nName    :" << Currency.CurrencyName(); 
		cout << "\nRate(1$=)   :" << Currency.getRate(); 
		cout << "\n_____________________________\n";
	}

	static void _ShowResults(clsCurrency Currency)
	{
		if (!Currency.IsEmpty())
		{
			cout << "Currency found :-)\n"; 
			_PrintCurrencyCrad(Currency); 
		}
		else
		{
			cout << "Currency was not found :-(\n"; 
		}
	}
	

public:
	
	static void ShowFindCurrencyScrren()
	{
		_DrawSecreenHeadr("Find Currency Scrren");

		short answer = 1; 
		cout << " Find by Code [1] or [2] Find by Country ?\n";
		cin >> answer; 

		if (answer == 1)
		{
			string CurrencyCode; 
			cout << "Please, enter currency code?\n"; 
			CurrencyCode = clsInputValidDate<string>::ReadString();
			clsCurrency Currency = clsCurrency::FindCourrencyByCode(CurrencyCode); 
			_ShowResults(Currency); 
		}
		else
		{
			string CurrencyCuntry;
			cout << "Please, enter currency Country?\n";

			CurrencyCuntry = clsInputValidDate<string>::ReadString();

			clsCurrency Currency = clsCurrency::FindCourrencyByCountry(CurrencyCuntry); 
			_ShowResults(Currency);

		}
	}
	
};

