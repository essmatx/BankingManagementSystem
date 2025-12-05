#pragma once
#include <iostream>
#include "clsPerson.h"
#include "clsString.h"
#include "clsDate.h" 
#include "clsBankClient.h"
#include "clsScreen.h"
#include <string>
#include <vector>
#include <fstream>
using namespace std;
class clsTransferLogScreen : clsScreen
{
    static void _PrintRecord(clsBankClient::stTransferLogReccord record)
    {
        cout << "|" << setw(15) << left << record.DataTime; 
        cout << "|" << setw(30) << left << record.SorceAccountNumber;
        cout << "|" << setw(12) << left << record.DistenationAccountNumber; 
        cout << "|" << setw(13) << left << record.Amount; 
        cout << "|" << setw(13) << left << record.SorceBalance;
        cout << "|" << setw(13) << left << record.DistenationBalance;
        cout << "|" << setw(13) << left << record.Username; 
    }

public:

    static  void ShowTransferList()
    {


        vector <clsBankClient::stTransferLogReccord> vrecord = clsBankClient::GetTransferLogListRecord(); 
        string title = " Transfer List Screen";
        string subtitle = "                                                     (" + to_string(vrecord.size()) + ") Records";

        _DrawSecreenHeadr(title, subtitle);
        cout << setw(50) << left << "_____________________________________________________"
            << "____________________________________________________________\n" << endl;
        cout << "|" << setw(15) << left << "DateTime"
            << "|" << setw(30) << left << "S.Acc"
            << "|" << setw(12) << left << "D.Acc"
            << "|" << setw(12) << right << "Amount"
            << "|" << setw(12) << right << "S.Balance"
            << "|" << setw(12) << right << "D.Balance"
            << "|" << setw(12) << right << "User"; 
        cout << setw(50) << left << "_____________________________________________________"
            << "______________________________________________________________\n" << endl;



        if (vrecord.size() == 0)
        {
            cout << " No Records availabal on the system!\n";
        }
        else
        {
            for (clsBankClient::stTransferLogReccord C : vrecord)
            {
                _PrintRecord(C);
                cout << endl;
            }

            cout << "_____________________________________________________"
                << "_________________________________________________________________\n";
        }

    }
};

