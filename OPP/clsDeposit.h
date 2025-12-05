#pragma once
#include <iostream>
#include "clsInputValidDate.h"
#include "clsBankClient.h"
#include "clsScreen.h"
using namespace std;
class clsDeposit : protected clsScreen
{
    static string _ReadClientsAccountnumbr()
    {
        string AccountNumber = ""; 
        cout << "Please, enter your account number ?\n";
        cin >> AccountNumber;
        return AccountNumber; 
    }

    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n__________________________________________\n";
        cout << "\nFirst Name    :" << Client.FirstName;
        cout << "\nLast Name     :" << Client.LastName;
        cout << "\nFull Name     :" << Client.FullName();
        cout << "\nEmail         :" << Client.Phone;
        cout << "\nPhone         :" << Client.Email;
        cout << "\nAccount Number:" << Client.getAccountNumber();
        cout << "\nPassowrd      :" << Client.PinCode;
        cout << "\nBalance       :" << Client.Accountbalance;
        cout << "\n__________________________________________\n";
    }

public: 

    static void DepositScreen()
    {
      _DrawSecreenHeadr("Deposit Screen\n"); 

        string Accountnumber = _ReadClientsAccountnumbr(); 

        while (!clsBankClient::IsClientExist(Accountnumber))
        {
            cout << "Client withe account numberr" << Accountnumber << "doesn't exisit , please try again!\n"; 
            Accountnumber = _ReadClientsAccountnumbr();
        }

        clsBankClient client = clsBankClient::Find(Accountnumber); 
        _PrintClient(client);

        double Amount = 0; 

        cout << "Please enter deposit amount ?\n"; 
        Amount = clsInputValidDate<double>::ReadDoublNumber(); 

        cout << "Are you sure that you want to perform this transaction?\n"; 
        char answer ='n';
        cin >> answer; 

        if (answer == 'Y' || answer == 'y')
        {
            client.Deposit(Amount);

            cout << "Amount deposited successfully\n"; 

            cout << "Toatal balance is " << client.Accountbalance << endl; 
        }
    }
};

