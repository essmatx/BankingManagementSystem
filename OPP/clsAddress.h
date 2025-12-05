#pragma once
#include <iostream>

using namespace std; 
class clsAddress
{
    string _AddressLine1;
    string _AddressLine2;
    string _POBOX;
    string _ZipCode;

public:

    clsAddress(string AddressLine1, string AddressLine2, string POBOX, string ZipCode)
    {
        _AddressLine1 = AddressLine1;
        _AddressLine2 = AddressLine2;
        _POBOX = POBOX;
        _ZipCode = ZipCode;
    }

    void SetAddressLine1(string AddressLine1)
    {
        _AddressLine1 = AddressLine1;
    }

    string GetAddressLine1()
    {
        return _AddressLine1;
    }

    void  SetAddressLine2(string AddressLine2)
    {
        _AddressLine2 = AddressLine2;
    }

    string GetAddressLine2()
    {
        return _AddressLine2;
    }

    void SetPOBOX(string POBOX)
    {
        _POBOX = POBOX;
    }

    string GetPOBOX()
    {
        return  _POBOX;
    }

    void SetZipCode(string ZipCode)
    {
        _ZipCode = ZipCode;
    }

    string GetZipCode()
    {
        return  _ZipCode;
    }

    void PrintAddress()
    {
        cout << "\tAdress Info";
        cout << "\n-----------------------------------\n";
        cout << "AdressLine1: " << _AddressLine1 << endl;
        cout << "AdressLine2: " << _AddressLine2 << endl;
        cout << "POBOX      : " << _POBOX << endl;
        cout << "ZipCode    : " << _ZipCode << endl;
    }

    ~clsAddress()
    {
        cout << "Operation has ben destructed !" << endl;
    }

};

