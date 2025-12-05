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
class clsFindClient : protected clsScreen
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

    static void FindClient()
    {
        if (!_CheckAccessRights(clsUser::enPermissions::pFindClient))
        {
            return;
        }

        clsScreen::_DrawSecreenHeadr("Find Client");
        string Accountnumber = "";
        cout << "Please enter you account number ?\n";
        Accountnumber = clsInputValidDate<string>::ReadString();

       
       
        while(!clsBankClient::IsClientExist(Accountnumber))
        {
            cout << "The account number that you have enterd dosen't exist , please try again!\n";
            Accountnumber = clsInputValidDate<string>::ReadString();
            
        }

       
        clsBankClient Client = clsBankClient::Find(Accountnumber);

        if (!Client.IsEmpty())
        {
            cout << " Client was found :-)\n";
        }
        else
        {
            cout << "Client was not found :-(\n"; 
        }

        _PrintClient(Client); 
    };

};

