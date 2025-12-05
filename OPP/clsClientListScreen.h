#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include <vector>
using namespace std;
class clsClientListScreen : clsScreen
{
   static void PrintClientRecord(clsBankClient Client)
    {
        cout << "|"<< setw(15)  << left << Client.FullName();
        cout << "|"<< setw(30)  << left << Client.Phone;
        cout << "|"<< setw(12)  << left << Client.Email;
        cout << "|"<< setw(13)  << left << Client.getAccountNumber();
        cout << "|"<< setw(10)  << left << Client.PinCode;
        cout << "|"<< setw(12) << right << fixed << setprecision(2) << Client.Accountbalance << endl;

    }

public:

  static  void ShowClientsList()
    {

      if (!_CheckAccessRights(clsUser::enPermissions::pLisClient))
      {
          return; 
      }

        vector <clsBankClient> vClient = clsBankClient::GetClintsList();
        string title = " Client List Screen"; 
        string subtitle = "                                                                                         (" + to_string(vClient.size()) + ") Clients";

        _DrawSecreenHeadr(title, subtitle);
        cout << setw(50) << left << "_____________________________________________________"
            << "____________________________________________________________\n" << endl;
        cout <<"|" << setw(15) << left  << "FullName"
            << "|" << setw(30) << left  << "Email"
            << "|" << setw(12) << left  << "Phone"
            << "|" << setw(13) << left  << "AccountNumber"
            << "|" << setw(10) << left  << "PinCode"
            << "|" << setw(12) << right  << "Accountbalance" << " |" << endl;
         cout << setw (50) << left << "_____________________________________________________"
            << "______________________________________________________________\n" << endl;

       

        if (vClient.size() == 0)
        {
            cout << " No clients availabal on the system!\n";
        }
        else
        {
            for (clsBankClient C : vClient)
            {
                PrintClientRecord(C);
                cout << endl;
            }

            cout << "_____________________________________________________"
                << "_________________________________________________________________\n";
        }

    }

};

