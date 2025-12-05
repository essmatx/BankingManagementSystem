#pragma once
#include <iostream>
#include <iomanip>      
#include "clsScreen.h"  
#include "clsCurrency.h"
#include "clsInputValidDate.h"
#include <vector>
using namespace std;

class clsCurrencyCalculater : protected clsScreen
{
	static float _ReadAmount()
	{
		cout << "Please , Enter amount to exchange ?\n";
		float amount = 0; 

		amount = clsInputValidDate<float>::ReadfloatNumber(); 

		return amount; 
	}

	static clsCurrency _GetCurrency(string message)
	{
		string CurrencyCode; 

		cout << message << endl; 
		CurrencyCode = clsInputValidDate<string>::ReadString();

		while (!clsCurrency::IsCurrencyExsistCode(CurrencyCode))
		{
			cout << "Currecny code that you have entren is not found , please try again!\n";
			CurrencyCode = clsInputValidDate<string>::ReadString();
		}

		clsCurrency Currency = clsCurrency::FindCourrencyByCode(CurrencyCode);

		return Currency; 
	}

	static void _PrintCurrencyCrad(clsCurrency Currency, string title = "Currency Card")
	{
		cout << "\n" << title << "\n"; 
		cout << "\n_____________________________\n";
		cout << "\nCountry      :" << Currency.Country();
		cout << "\nCode         :" << Currency.CurrencyCode();
		cout << "\nName         :" << Currency.CurrencyName();
		cout << "\nRate(1$ ) =  :" << Currency.getRate();
		cout << "\n_____________________________\n";
	}

	static void _PrintCalculationResults(float amount, clsCurrency Currency1, clsCurrency Currency2)
	{
		_PrintCurrencyCrad(Currency1, "Convert from");

		float AmountInUSD = Currency1.ChangeCurrencyToUSD(amount);

		cout << amount << " " << Currency1.CurrencyCode() <<
			" = " << AmountInUSD << " USD\n "; 

		if (Currency2.CurrencyCode() == "USD")
		{
			return; 
		}

		cout << "Converting From USD\n"; 

		_PrintCurrencyCrad(Currency2, "Convert To");

		AmountInUSD = Currency1.ChangeToOtherCurrency(amount, Currency2); 

		cout << amount << " " << Currency1.CurrencyCode() <<
			" = " << AmountInUSD << " " << Currency2.CurrencyCode();

	}

public:

	static void ShowCurrencyCalculator()
	{

		char Continue = 'y'; 
		while(Continue == 'y'|| Continue == 'Y')
		{
			system("cls"); 
			_DrawSecreenHeadr("Currency Calculator Screen");

			clsCurrency Currency1 = _GetCurrency("\nPlease enter Currency1 Code"); 
			clsCurrency Currency2 = _GetCurrency("\nPlease enter Currency2 Code");

			float amount = _ReadAmount(); 

			_PrintCalculationResults(amount, Currency1, Currency2); 

			cout << "\nDo you want to perform another calculation Y/N ?";
			cin >> Continue; 
		}
		

	}
};

