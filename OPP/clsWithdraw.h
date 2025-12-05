#pragma once
#include <iostream>
#include "clsInputValidDate.h"
#include "clsBankClient.h"
#include "clsScreen.h"
class clsWithdraw :protected clsScreen
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

    static void WithdrawScreen()
    {
        string Accountnumber = "";

        Accountnumber = _ReadClientsAccountnumbr();

        while (!clsBankClient::IsClientExist(Accountnumber))
        {
            cout << "Clinet with account number " << Accountnumber << "is not exisit , please try again!\n";

            Accountnumber = _ReadClientsAccountnumbr();
        }

        clsBankClient client = clsBankClient::Find(Accountnumber);
        _PrintClient(client);

        double Amount = 0;

        double Totalblance = 0;


        cout << "please , enter Withdraw amount !\n";
        Amount = clsInputValidDate<double>::ReadDoublNumber();

        cout << " Are you sure that you wanna perform this operation ?\n";
        char answer = 'n';
        cin >> answer;

        if (answer == 'y'|| answer == 'Y')
        {
            if (client.Withdarw(Amount))
            {
                cout << "Amount was successfully withdarwed\n";

                cout << " your totalbalance is " << client.Accountbalance;
            }
            else
            {
                cout << "Cannot withdraw insuffecint balance\n";
                cout << "Amount to withdraw is" << Amount << endl;
                cout << " your totalbalance is " << client.Accountbalance;
            }
           
        }
        else
        {
            cout << "Operatin was cancled\n";
        }
       
    }
};

