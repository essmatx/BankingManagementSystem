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
#include "clsScreen.h"
#include <string>
#include <vector>
using namespace std;
class clsLoginregister : clsScreen
{
    static void PrintRecord(clsUser::stLoginRegisterRecord record)
    {
        cout << "|" << setw(15) << left << record.DateTime;
        cout << "|" << setw(30) << left << record.Username; 
        cout << "|" << setw(12) << left << record.Password;
        cout << "|" << setw(13) << left << record.Permissions;
    }


public:

    static  void ShowLoginRegisterList()
    {
        if (!_CheckAccessRights(clsUser::enPermissions::pLoginRegister))
        {
            return;
        }


        vector <clsUser::stLoginRegisterRecord> vrecord = clsUser::GetLoginRegisterList(); 
        string title = " Login Resgister List Screen";
        string subtitle = "                                                     (" + to_string(vrecord.size()) + ") Records";

        _DrawSecreenHeadr(title, subtitle);
        cout << setw(50) << left << "_____________________________________________________"
            << "____________________________________________________________\n" << endl;
        cout << "|" << setw(15) << left << "DateTime"
            << "|" << setw(30) << left << "Username"
            << "|" << setw(12) << left << "Password"
            << "|" << setw(12) << right << "Permissions" << " |" << endl;
        cout << setw(50) << left << "_____________________________________________________"
            << "______________________________________________________________\n" << endl;



        if (vrecord.size() == 0)
        {
            cout << " No Records availabal on the system!\n";
        }
        else
        {
            for (clsUser::stLoginRegisterRecord C : vrecord)
            {
                PrintRecord(C);
                cout << endl;
            }

            cout << "_____________________________________________________"
                << "_________________________________________________________________\n";
        }

    }
};

