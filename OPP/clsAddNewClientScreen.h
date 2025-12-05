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
#include "clsClientListScreen.h"
#include <string>
#include <vector>
using namespace std;

class clsAddNewClientScreen : protected clsScreen
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

  static  void AddNewClient()
  {
      if (!_CheckAccessRights(clsUser::enPermissions::pAddNewClient))
      {
          return;
      }

      clsScreen::_DrawSecreenHeadr("Add New Client");


        string AccountNumber = "";

        cout << "Please enter your account number ?\n";
        AccountNumber = clsInputValidDate<string>::ReadString();

        while (clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "The account number the you have entered is already exist ,Please enter differet account number!\n";
            AccountNumber = clsInputValidDate<string>::ReadString();
        }

        cout << "\t\nAdd New Client";
        cout << "\n_______________________\n";
        clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);
        _ReadClientInfo(NewClient);

        clsBankClient::enSaveResults SaverClient;

        SaverClient = NewClient.save();

        switch (SaverClient)
        {
        case clsBankClient::enSaveResults::SaveSucceded:
            cout << "Client Added successfully :-)\n";
            _PrintClient(NewClient); 
            break;

        case clsBankClient::enSaveResults::SaveFileEmptyObject:
            cout << "Error Account was not saved because its empty :-(\n";
            break;

        case clsBankClient::enSaveResults::SavefaildClientexsied:
            cout << "Error Account is already exist please enter new account :-(\n";
            break;
        }
  }

};

