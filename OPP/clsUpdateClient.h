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

class clsUpdateClient : clsScreen
{
    static void _ReadClientInfo(clsBankClient& Client)
    {
        cout << "Enter First Name\n";
        Client.FirstName = clsInputValidDate<string>::ReadString();

        cout << "Enter Last  Name\n";
        Client.LastName = clsInputValidDate<string>::ReadString();

        cout << "Enter Email\n";
        Client.Phone = clsInputValidDate<string>::ReadString();

        cout << "Enter Phone Number\n";
        Client.Email = clsInputValidDate<string>::ReadString();

        cout << " Enter PinCode\n";
        Client.PinCode = clsInputValidDate<string>::ReadString();

        cout << "Enter Account Balance\n";
        Client.Accountbalance = clsInputValidDate<float>::ReadfloatNumber();
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

public :

   static void UpateClient()
   {
       if (!_CheckAccessRights(clsUser::enPermissions::pUpdateClient))
       {
           return;
       }
        clsScreen::_DrawSecreenHeadr("Updtate Client");

        string AccountNumber = "";

        cout << " Please Enter Account Number ?";
        AccountNumber = clsInputValidDate<string>::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "The Account Number was not found Please try again";
            AccountNumber = clsInputValidDate<string>::ReadString();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);
        Client.Print();


        cout << "\n\tUpdate Client\n";
        cout << "\n____________________________\n";
        _ReadClientInfo(Client);

        clsBankClient::enSaveResults saveResults;

        saveResults = Client.save();

        switch (saveResults)
        {
        case clsBankClient::enSaveResults::SaveSucceded:
            cout << "Account Updated Succesfully :-)\n";
            _PrintClient(Client);
            break;

        case clsBankClient::enSaveResults::SaveFileEmptyObject:
            cout << "Error Account was not saved because its empty :-(\n";
            break;
        }



   }
};

