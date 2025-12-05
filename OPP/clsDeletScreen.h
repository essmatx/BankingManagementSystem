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
#include "clsMainScreen.h"
#include <string>
#include <vector>
using namespace std;
class clsDeletScreen : protected clsScreen
{

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

 static void DeletClient()
 {
     if (!_CheckAccessRights(clsUser::enPermissions::pDeleteCLient))
     {
         return; 
     }

        clsScreen::_DrawSecreenHeadr("Delet Client");
        string AccountNumber = "";

        cout << "Please enter your account number\n";
        AccountNumber = clsInputValidDate<string>::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << " The Account Number that you have entered is not exist , please try again\n";
            AccountNumber = clsInputValidDate<string>::ReadString();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClient(Client); 

        cout << " Are you sure you want to delet this Client ? Y/N\n";


        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            if (Client.Delet())
            {
                cout << "Client deleted successfully\n";
                _PrintClient(Client);
            }
            else
            {
                cout << "Error Client was not deleted\n";
            }
        }

 }

};

