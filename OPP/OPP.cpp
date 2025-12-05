

#include <iostream>
#include "clsLoginScreen.h"
#include <string>
#include <vector>
#include "Global.h"

clsUser CurrentUser = clsUser::Find("", "");
using namespace std; 
class Phone
{
public:

    virtual void CallPhone(string PhoneNumber) = 0; 
    virtual void SendSMS(string Message, string PhoneNumber) = 0; 
    virtual void TakePhoto() = 0; 
};

class MobileApp : public Phone
{
public:

    void CallPhone(string PhoneNumber)
    {

    };

    void SendSMS(string Message, string PhoneNumber)
    {

    }; 

    void TakePhoto()
    {

    };
};

class clsCar
{
    string _brand;
    string _Model;
    string _Year;
    double _Price; 

public:
    clsCar() {};
    clsCar(string brand, string Model, string Year ,double Price)
    {
        _brand = brand;
        _Model = Model;
        _Year = Year;
        _Price = Price;
    }

    void  print()
    {

        cout << "Car brand           : " << _brand << endl;
        cout << "Car Model           : " << _Model << endl;
        cout << "Car production year : " << _Year << endl;
        cout << "Car Price           : " << _Price << endl; 
    };

};

class clsBook
{
    string _Title; 
    string _author; 
    string _Year; 

public:
    
    clsBook(string Title, string author, string Year)
    {
        _Title = Title;
        _author = author;
        _Year = Year;
    };

    void Print()
    {
        cout << "Book Title      :" << _Title << endl;
        cout << "Book author     :" << _author << endl;
        cout << "Publication Year:" << _Year << endl;
    };
};

class clsStudent
{
    int _ID; 
    string _Name; 
    char _Grade; 

public: 
    clsStudent() {}; 

    clsStudent(int ID , string Name, char Grade)
    {
        _ID = ID; 
        _Name = Name;
        _Grade = Grade; 
    }

    void PrintStudentinfo()
    {
            cout << "Student ID: " << _ID << endl;
            cout << "Student Name: " << _Name << endl;
            cout << "Student Grade: " << _Grade << endl;
            cout << "------------------------" << endl;
    }
};

class clsProduct
{
    int _ID; 
    string _Name; 
    double _Price; 
    int _Quantity; 
public: 

    clsProduct()
    {

    };

    clsProduct(int ID, string Name, double Price, int Quantity)
    {
        _ID = ID;
        _Name = Name;
        _Price = Price;
        _Quantity = Quantity;
    };

    double CalculateValue()
    {
        return _Price * _Quantity; 
    }

    void PrintProductInfo()
    {
        cout << "\tProduct info \n";
        cout << "Product ID      : " << _ID << endl;
        cout << "Product Name    : " << _Name << endl;
        cout << "Product Price   : " << _Price << endl;
        cout << "Product Quantity: " << _Quantity << endl;
    };
};

void ReadClientInfo(clsBankClient& Client)
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

void sUpateClient()
{
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
    ReadClientInfo(Client); 

    clsBankClient::enSaveResults saveResults; 

    saveResults = Client.save(); 

    switch (saveResults)
    {
    case clsBankClient::enSaveResults::SaveSucceded:
        cout << "Account Updated Succesfully :-)\n"; 
        Client.Print(); 
        break;

    case clsBankClient::enSaveResults::SaveFileEmptyObject:
        cout << "Error Account was not saved because its empty :-(\n";
        break;
    }

    
    
}

void static AddNewClient()
{
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
    ReadClientInfo(NewClient); 

    clsBankClient::enSaveResults SaverClient; 

    SaverClient = NewClient.save(); 

    switch (SaverClient)
    {
    case clsBankClient::enSaveResults::SaveSucceded:
        cout << "Client Added successfully :-)\n"; 
         NewClient.Print();
         break;

    case clsBankClient::enSaveResults::SaveFileEmptyObject:
        cout << "Error Account was not saved because its empty :-(\n";
        break;

    case clsBankClient::enSaveResults::SavefaildClientexsied:
         cout << "Error Account is already exist please enter new account :-(\n";
        break;
    }
}

void static DeletClient()
{
    string AccountNumber = "";

    cout << "Please enter your account number\n";
    AccountNumber = clsInputValidDate<string>::ReadString();

    while (!clsBankClient::IsClientExist(AccountNumber))
    {
        cout << " The Account Number that you have entered is not exist , please try again\n";
        AccountNumber = clsInputValidDate<string>::ReadString();
    }

     clsBankClient Client = clsBankClient::Find(AccountNumber);
    Client.Print(); 

    cout << " Are you sure you want to delet this Client ? Y/N\n"; 
  

    char Answer = 'n';
    cin >> Answer; 

    if (Answer == 'y' || Answer == 'Y')
    {
        if (Client.Delet())
        {
            cout << "Client deleted successfully\n";
            Client.Print(); 
        }
        else
        {
            cout << "Error Client was not deleted\n"; 
        }
    }

}

void static PrintClientRecord(clsBankClient Client)
{
    cout << "|" << left << setw(15) << Client.FullName();
    cout << "|" << left << setw(30) << Client.Phone ;
    cout << "|" << left << setw(12) << Client.Email ;
    cout << "|" << left << setw(13) << Client.getAccountNumber();
    cout << "|" << left << setw(10) << Client.PinCode ; 
    cout << "|" << right << setw(12) << fixed << setprecision(2) << Client.Accountbalance << endl;
  
}

void static PrinClientsList()
{
    vector <clsBankClient> vClient = clsBankClient::GetClintsList(); 

    cout << "\n\t\t\t\t\t\tClient List (" << vClient.size() << ") Clients";
    cout << "_____________________________________________________"
    << "_________________________________________\n";
    cout<< "|" <<left << setw(15) << "FullName"
        << "|" << left << setw(30) << "Email"
        << "|" << left << setw(12) << "Phone"
        << "|" << left << setw(13) << "AccountNumber"
        << "|" << left << setw(10) << "PinCode"
        << "|" << right << setw(12) << "Accountbalance" << " |" << endl;
    cout << "_____________________________________________________"
     << "_________________________________________\n";


    if(vClient.size() == 0)
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
            << "_________________________________________\n";
    }

}

void static PrintClientRecordTotalBalances(clsBankClient C)
{
    cout << "|" << setw(13) << left << C.getAccountNumber();
    cout << "|" << setw(15) << left << C.FullName();
    cout << "|" << right << setw(12) << fixed << setprecision(2) << C.Accountbalance << endl;
}

void static PrinClientsListTotalBalances()
{
    vector <clsBankClient> vClient = clsBankClient::GetClintsList(); 

    cout << "\n\t\t\t\tBalances List(" << vClient.size() << ") Client(s)\n"; 
    cout << "\n_______________________________________________________________"
        << "__________________________________________\n";
    cout <<"|" << left << setw(13) << "Account Number"
        << "|" << left << setw(15) << "FullName"
        << "|" << right << setw(12) << "Total Balance" << endl; 
    cout << "\n_______________________________________________________________"
        << "__________________________________________\n"; 

    double TotalBalances = clsBankClient::GetToatalBalances(); 

        if (vClient.size() == 0)
        {
            cout << " No clients availabal on the system!\n";
        }
        else
        {
            for (clsBankClient C : vClient)
            {
                PrintClientRecordTotalBalances(C);
                cout << endl; 
            }
        }

        cout << "\n_______________________________________________________________"
            << "__________________________________________\n";
        cout << "\n\t\t\t\t Total Balances =  (" << TotalBalances << ") Client(s)\n"; 

        cout << "\n\t\t\t\t (" << clsUtil::NumberToText(TotalBalances) << ") \n"; 
}

void PrintCurrency(clsCurrency Currency)
{
    cout << "\n\tCurrency Card"; 
    cout << "\n_________________________\n"; 
    cout << "\nCountry:" << Currency.Country();
    cout << "\nCode   :" << Currency.CurrencyCode(); 
    cout << "\nName   :" << Currency.CurrencyName(); 
    cout << "\nRate($):" << Currency.getRate(); 
    cout << "\n_________________________\n";
}

template <typename T>

T Max(T Number1, T Number2)
{
    return (Number1 > Number2) ? Number1 : Number2;
}

template <class T> 
class Calculator
{
    T Number1, Number2; 

public:
    Calculator(T n1, T n2)
    {
        Number1 = n1; 
        Number2 = n2; 
    }

    void Print()
    {
        cout << " Numbers " << Number1 << " and " << Number2 << "."; 
        cout << Number1 << " + " << Number2 << " = " << Add() << endl;
        cout << Number1 << " - " << Number2 << " = " << Subtract() << endl; 
        cout << Number1 << " / " << Number2 << " = " << Divide() << endl; 
        cout << Number1 << " * " << Number2 << " = " << MultyPly() << endl; 
    }

    T Add()
    {
        return Number1 + Number2; 
    }

    T Subtract()
    {
       return Number1 - Number2; 
    }

    T Divide()
    {
        return Number1 / Number2; 
    }

    T MultyPly()
    {
      return  Number1* Number2;
    }
};

int main()
{
    /*clsBankClient Client = clsBankClient::Find("A100");
   Client.Print();
    cout << Client.IsClientExist("A100");*/

    // UpateClient();
    //AddNewClient();
    // DeletClient(); 
    // PrinClientsList(); 
     //PrinClientsListTotalBalances();
         //clsMainScreen::ShowMainMenu(); 


    while (true)
    {
        if (!clsLoginScreen::ShowLigenScreen())
        {
            break;
        }

    }

    // clsUser::EncryptAllpasswordsInFile(); 


// clsCurrency currency = clsCurrency::FindCourrencyByCode("EGP");

 //PrintCurrency(currency); 


// Calculator <int> intgercallculater(10, 100); 
 //intgercallculater.Print(); 
 //Calculator <float> floatcallculater(14.5, 57.4); 
 //floatcallculater.Print(); 

    return 0;

}

   
   

