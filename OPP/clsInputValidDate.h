#pragma once
#include "clsDate.h"
#include "clsString.h"
#include "clsUtil.h"
#include "clsPeriod.h"
#include <string>
using namespace std; 

template <class T>
class clsInputValidDate
{
public:

   
    static T IsNumberBetween(T Number, T from, T to)
    {
        if (Number >= from && Number <= to)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

   
    static T IsDateBetween(T Number, T From, T To)
    {
        if (Number >= From && Number <= To)
        {
            return true;
        }
        else
        {
            return false;
        }
    };

    
    static T ReadIntNumber(string Message = "Invalid number , Please enter the number aagin\n")
    {
        T Number;

        while (!(cin >> Number))
        {
            cin.clear();

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << Message;
        }
        return Number; 
    }

    
    static T ReadShortNumber(string Message = "Invalid number , Please enter the number aagin\n")
    {
        T Number;

        while (!(cin >> Number))
        {
            cin.clear();

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << Message;
        }
        return Number;
    }

   
    static T ReadIntBetween(T From,T To, string Message = "Number is not within range, Enter again: \n")
    {
        T Number = ReadIntNumber(); 

        while (!IsNumberBetween(Number, From, To))
        {
            cout << Message; 

            Number = ReadIntNumber(); 
        }

        return Number; 
    }

    
    static T ReadshorNumbertBetween(T From,T To, string Message = "Number is not within range, Enter again: \n")
    {
        short Number = ReadIntNumber();

        while (!IsNumberBetween(Number, From, To))
        {
            cout << Message;

            Number = ReadShortNumber();
        }

        return Number;
    }

   
    static T ReadDoublNumber(string message = "Invalid number , Please enter the number aagin\n")
    {
        double number; 

        while (!(cin >> number))
        {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

            cout << message; 
        }

        return number; 
    }

    
    static T ReadDoublNumberBteween(T from, T to, string message = "Invalid number , Please enter the number aagin\n")
    {
        T number = ReadDoublNumber(); 

        while (!IsNumberBetween(number, from, to))
        {
            cout << message; 

            number = ReadDoublNumber();
        }

        return number; 
    }

    
    static T ReadfloatNumber(string Message = "Invalid number , Please enter the number aagin\n")
    {
        T Number;

        while (!(cin >> Number))
        {
            cin.clear();

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << Message;
        }
        return Number;
    }


    static T Validate(T Date)
    {
        return clsDate::IsValidDate(Date); 
    }


    static T ReadString()
    {
        T str =  "";

        getline(cin >> ws, str);

        return str; 
    }
};


