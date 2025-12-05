#pragma once
#include <iostream>
#include <iomanip>      
#include "clsScreen.h"  
#include "clsCurrency.h"
#include <vector>
using namespace std;
class clsListCurrencies : clsScreen
{ 
	static void _PrintCurrencyRecord(clsCurrency Currency)
	{
		cout << "| " << setw(25) << left << Currency.Country(); 
		cout << "| " << setw(10) << left << Currency.CurrencyCode(); 
		cout << "| " << setw(25) << left << Currency.CurrencyName();
		cout << "| " << setw(12) << left << Currency.getRate() 
			 << "|" << endl;
	}

public:

	static void ShowCurrencesList()
	{

		vector<clsCurrency> vcurrency = clsCurrency::GetcurrencyList();

		string Title = "Currence List";

		string subTitle = "           (                                      " + to_string(vcurrency.size()) + ") (Currency)";

		clsScreen::_DrawSecreenHeadr(Title, subTitle); 

		cout << "_____________________________________________________"
			<< "____________________________________________________________\n" << endl;
		cout<< "|" << setw(25) << left << "Country"
			<< "|" << setw(10) << left << "Code"
			<< "|" << setw(25) << left << "Name"
			<< "|" << setw(12) << left << "Rate" 
			<< "|" << endl;
		cout  << "_____________________________________________________"
			<< "______________________________________________________________\n" << endl;

		if (vcurrency.size() == 0)
		{
			cout << "There is no availbale currences in the list";
		}
		else
		{
			for (clsCurrency C : vcurrency)
			{
				_PrintCurrencyRecord(C);
				cout << endl; 

				cout << "_____________________________________________________"
					<< "_________________________________________________________________\n";
			}
		}

		
	}
}; 

