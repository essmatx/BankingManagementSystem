#pragma once
#include "clsPerson.h"
#include "clsCalculater.h"
#include "clsAddress.h"
#include "clsString.h"
#include "clsDate.h"
#include "clsUtil.h"
#include "clsInputValidDate.h"
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsMainScreen.h"
#include "clsDeposit.h"
#include "clsWithdraw.h"
#include <string>
#include <vector>
using namespace std;
class clsTotalblancesScreen : protected clsScreen
{
	static void _PrintClientRecordBalanceLine(clsBankClient client)
	{
		cout << setw(15) << left << "" << "|" << left << client.AccountNumber;
		cout << "                        |" << setw(20) << left << client.FullName(); 
		cout << "|" << setw(15) << left << client.Accountbalance;
	}

public: 

	static void ShowTotalBalances()
	{
		vector<clsBankClient> vclient = clsBankClient::GetClintsList(); 

		string Title = "\tBalances List screen";

		string subtitle = "\n                                                      (" + to_string(vclient.size()) + ")  Client(s).";
		clsScreen::_DrawSecreenHeadr(Title, subtitle); 

		cout << setw(40) << left << "" << "\n            _________________________________________________________________________________"
			<< "_____________\n";
		cout << setw(15) << left << "" << "|" << left << "Account Number"; 
		cout << "              |" << setw(20) << left << "Fullname";
		cout << "|" << setw(15) << left << "Balance"; 
		cout << setw(40) << left << "" << "\n              _______________________________________________________________________________"
			<< "_____________\n";


		double Totalbalance = clsBankClient::GetToatalBalances(); 
		if (vclient.size() == 0)
		{
			cout << "\t\t\tno clients available in the system";

		}
		else
		{
			for (clsBankClient client : vclient)
			{
				_PrintClientRecordBalanceLine(client);
				cout << endl; 
			}
		}

		cout << setw(15) << left << "" << "\n            _________________________________________________________________________________"
			<< "_____________\n"  ;

		cout << setw(8) << left << "" << "\t\t\t\t\t\t\t\t\Total balances = " << Totalbalance; 
		cout << setw(8) << left << "" << "\t\t\t\             (" << clsUtil::NumberToText(Totalbalance) << ")\n"; 

	}
	
};

