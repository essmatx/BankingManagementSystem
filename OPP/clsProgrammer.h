#pragma once
#include <iostream>
#include "clsEmployee.h"

using namespace std;


class clsProgrammer : public clsEmployee
{
    string _MainProgrammingLanguage;

public:

    clsProgrammer()
    {

    }
    clsProgrammer(int ID, string FirstName, string LastName, string Title, string Email, string Phone, double Salary, string Department, string MainProgrammingLanguage)
        : clsEmployee(ID, FirstName, LastName, Title, Email, Phone, Salary, Department)
    {
        _MainProgrammingLanguage = MainProgrammingLanguage;
    }

    void SetMainProgrammingLanguage(string MainProgrammingLanguage)
    {
        _MainProgrammingLanguage = MainProgrammingLanguage;
    }

    string GetMainProgrammingLanguage()
    {
        return _MainProgrammingLanguage;
    }

    void PrintInfo()
    {
        cout << "\tProgrammer Card Info";
        cout << "\n______________________________________________________\n";
        cout << "ID                     : " << GetId() << endl;
        cout << "FirstName              : " << GetFirstName() << endl;
        cout << "LastName               : " << GetLasstName() << endl;
        cout << "FullName               : " << FullName() << endl;
        cout << "Title                  : " << GetTitle() << endl;
        cout << "Email                  : " << GetEmail() << endl;
        cout << "Phone                  : " << GetPhone() << endl;
        cout << "Salary                 : " << GetSalary() << endl;
        cout << "Department             : " << GetDepartment() << endl;
        cout << "MainProgrammingLanguage: " << _MainProgrammingLanguage << endl;
        cout << "___________________________________________________________" << endl;

    }
};

