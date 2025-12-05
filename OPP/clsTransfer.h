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
#include <string>
#include <vector>
using namespace std;

class clsTransfer :  protected clsScreen
{
    static string _ReadClientsAccountnumbr()
    {
        string AccountNumber = "";
        cout << "Please, enter your account number that you want transfer from ?\n";
        AccountNumber = clsInputValidDate<string>::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "Client withe account numberr" << AccountNumber << "doesn't exisit , please try again!\n";
            AccountNumber = clsInputValidDate<string>::ReadString();
        }
        return AccountNumber; 
    }

    static string _ReadClientsAccountnumbrTo()
    {
        string accountNumber = "";
        cout << "Please, enter  account number that you want transfer to ?\n";
        accountNumber = clsInputValidDate<string>::ReadString();

        while (!clsBankClient::IsClientExist(accountNumber))
        {
            cout << "Client withe account numberr" << accountNumber << "doesn't exisit , please try again!\n";
            accountNumber = clsInputValidDate<string>::ReadString();
        }
        return accountNumber;
    }


    static float _ReadAmount(clsBankClient SorceClient)
    {
        float Amount = 0;
        cout << "\nPlease, Enter transfer amount number ?";
        Amount = clsInputValidDate<float>::ReadfloatNumber();

        while (Amount > SorceClient.Accountbalance)
        {
            cout << "\nAmount Exceeds the available balance , Please enter another anount !"; 
            Amount = clsInputValidDate<double>::ReadDoublNumber(); 
        }

        return Amount; 
    }

    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n__________________________________________\n";
        cout << "\nFull Name     :" << Client.FullName();
        cout << "\nAccount Number:" << Client.getAccountNumber();
        cout << "\nBalance       :" << Client.Accountbalance;
        cout << "\n__________________________________________\n";
    }


public :


    static void performTransfer()
    {
        _DrawSecreenHeadr("Transfer Screen"); 

        clsBankClient SorcClient = clsBankClient::Find(_ReadClientsAccountnumbr()); 
        _PrintClient(SorcClient); 

        clsBankClient DistnationClient = clsBankClient::Find(_ReadClientsAccountnumbrTo());
        _PrintClient(DistnationClient);

        float Amount = _ReadAmount(SorcClient); 

        cout << "Are you sure you wanr to implement this operation ? Y/N\n"; 
        char Answer = 'n'; 
        cin >> Answer; 

        if (Answer == 'y' || Answer == 'Y')
        {
            if (SorcClient.Transfer(Amount, DistnationClient,CurrentUser.UserName))
            {
                cout << "Transfer done successfully :-)\n"; 
            }
            else
            {
                cout << "Transfer faild :-(\n"; 
            }
        }

        _PrintClient(SorcClient);
        _PrintClient(DistnationClient);
    }
};

