#pragma once
#include <iostream>
#include <iomanip>      
#include "clsScreen.h"  
#include "clsCurrency.h"
#include "clsInputValidDate.h"
#include <vector>
using namespace std;
class clsUpdateCurrencyRate : protected clsScreen
{
	static float _NewRate()
	{
		cout << "Please,Enter new rate of currency ?\n"; 
		float NewRate = 0;
		NewRate = clsInputValidDate<float>::ReadfloatNumber();

		return NewRate; 
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

public:

	static void ShowUpdateCurrencyRate()
	{
		string CurrencyCode;

		cout << "Please, Enter The Currency Code to update ?\n"; 
		CurrencyCode = clsInputValidDate<string>::ReadString();

		while (!clsCurrency::IsCurrencyExsistCode(CurrencyCode))
		{
			cout << "Currency code that you have entred was not found :-( , Please try agin !\n"; 
			CurrencyCode = clsInputValidDate<string>::ReadString();
		}

		clsCurrency Currency = clsCurrency::FindCourrencyByCode(CurrencyCode); 
		_PrintCurrencyCrad(Currency); 

		char answer = 'n'; 

		cout << "Are you sure you wanna update this currency's rate ?\n"; 
		cin >> answer; 

		if (answer == 'y' || answer == 'Y')
		{
			cout << "\nUpdate Currency Rate\n";
			cout << "\n_____________________________\n"; 

			Currency.UpdateRate(_NewRate());

			cout << "Currency Rate Updated Succefully :-)\n"; 
			_PrintCurrencyCrad(Currency); 
		}
	}
};

