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
#include "clsMainScreen.h"
#include "clsDeposit.h"
#include "clsWithdraw.h"
#include "clsTotalblancesScreen.h"
#include "clsTransferLogScreen.h"
#include "clsTransfer.h"
#include <string>
#include <vector>
using namespace std;

class clsTransacion : protected clsScreen
{

	enum Transaction { Deposit = 1, Withdraw = 2, Totalbalances = 3,Transfer = 4 , TransferLog = 5,ShowMainMnu = 6};



	static short _ReadTransactionMenu()
	{
		cout << setw(35) << left << "" << "Please enter a number corresponding your desired action(1-6)";
		short choose = clsInputValidDate<short>::ReadshorNumbertBetween(1, 6, " wrong please enter a number between 1 - 6");
		return choose;
	}

	static void _GetBacktoTransactionMenu()
	{
		cout << setw(37) << left << "Please, press any kye to get back to the Transaction menu!\n";
		system("pause>0");

		TransactionMnuescreen();

	}

	static void _Deposit()
	{
		//cout << "Deposit screen will be soon here...\n";
		clsDeposit::DepositScreen();
	}

	static void _Withdarw()
	{
		//cout << "Withdraw screen will be soon here...\n";
		clsWithdraw::WithdrawScreen();
	}

	static void _Totalbalances()
	{
		//cout << " Total balances screen will be soon here...\n";
		clsTotalblancesScreen::ShowTotalBalances(); 
	}


	static void _Transfer()
	{
		//Transfer Screen will be soon here..//
		clsTransfer::performTransfer(); 
		
	}

	static void _TransferLog()
	{
		//TransferLog Screeen will be here....
		clsTransferLogScreen::ShowTransferList();

	}

	

	static void _PerformTransacionMnue(Transaction options)
	{
		switch (options)
		{
		case Transaction::Deposit:
			system("cls");
			_Deposit();
			_GetBacktoTransactionMenu();
			break;

		case Transaction::Withdraw:

			system("cls");
			_Withdarw();
			_GetBacktoTransactionMenu();
			break;

		case Transaction::Totalbalances:
			system("cls");
			_Totalbalances();
			_GetBacktoTransactionMenu();
			break;

		case Transaction::Transfer:
			system("cls");
			_Transfer();
			_GetBacktoTransactionMenu();
			break;

		case Transaction::TransferLog:
			system("cls");
			_TransferLog();
			_GetBacktoTransactionMenu();
			break;

		case Transaction::ShowMainMnu:
		{
			break; 
		}
	}
	};

public:

	static void TransactionMnuescreen()
	{
		if(!_CheckAccessRights(clsUser::enPermissions::pTransaction))
		 {
			return; 
		 }

		_DrawSecreenHeadr("Transaction Screen\n");


		cout << "\n                                  ======================================================\n";
		cout << "\t\t                                  Transaction Menu\n";
		cout << "\n                                  ======================================================\n";


		cout << "\t                                            [1] Deposit.\n";
		cout << "\t                                            [2] Withdraw.\n";
		cout << "\t                                            [3] Total Balances.\n";
		cout << "\t                                            [4] Transfer.\n";
		cout << "\t                                            [5] Transfer Log.\n";
		cout << "\t                                            [6] Main Menu.\n";

		cout << "\n                                   ======================================================\n";

		_PerformTransacionMnue((Transaction)_ReadTransactionMenu());

	};
};

