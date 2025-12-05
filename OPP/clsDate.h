
#pragma once
#pragma warning (disable : 4996)
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include "clsString.h"
using namespace std;


class clsDate
{
    int _Day = 1; 
    int _Month = 1; 
    int _Year = 19000; 

public:

    clsDate()
    {
        time_t t = time(0); 
        tm* now = localtime(&t);
        _Day = now->tm_mday; 
        _Month = now->tm_mon + 1; 
        _Year = now->tm_year +1900; 
    }

    clsDate(string sDate)
    {
        vector <string>vDate; 

        vDate = clsString::SplitString(sDate, "/");

        _Day = stoi(vDate[0]); 
        _Month = stoi(vDate[1]);
        _Year = stoi(vDate[2]); 
    }

    clsDate(int Day, int Month, int Year)
    {
        _Day = Day; 
        _Month = Month; 
        _Year = Year; 
    }
    
    clsDate(int DateOrderInYear, int Year)
    {
        clsDate Date1 = GetDateFromDayOrderInYear(DateOrderInYear, Year);
        _Day = Date1.getDay();
        _Month = Date1.getMonth();
        _Year = Date1.getYear();
    }

    void setDay(int Day)
    {
        _Day = Day; 
    }
    int getDay()
    {
        return _Day; 
    }
    __declspec(property(get = getDay, put = setDay))int Day; 

    void setMonth(int Month)
    {
        _Month = Month; 
    }
    int getMonth()
    {
        return _Month; 
    }
    __declspec(property(get = getMonth, put = setMonth))int Month; 

    void setYear(int Year)
    {
        _Year = Year; 
    }
    int getYear()
    {
        return _Year; 
    }
    __declspec(property(get = getYear, put = setYear)) int Year; 

    void Print()
    {
      cout <<  DateToString(); 
    }

   static clsDate GetsystemDate()
    {
        time_t t = time(0);
        tm* now = localtime(&t);
        int Day, Month, Year; 
        Day = now->tm_mday;
        Month = now->tm_mon + 1;
        Year = now->tm_year + 1900;

        return clsDate(Day, Month, Year); 
    }

   static bool IsValidDate(clsDate Date)
   {
       if (Date.Day < 1 || Date.Day > 31)
       {
           return false;
       }

       if (Date.Month < 1 || Date.Month > 12)
       {
           return false;
       }

       if (Date.Month == 2)
       {
           if (IsLeapYear(Date.Year))
           {
               if (Date.Day > 29)
               {
                   return false;
               }
               else if (Date.Day > 28)
               {
                   return false;
               }
           }
       }

       int DaysinMonth = NumberOfDaysInAMonth(Date.Month, Date.Year);
       if (Date.Day > DaysinMonth)
       {
           return false;
       }

       return true;
   }

   bool IsValid()
   {
       return IsValidDate(*this);
   }

   static string DateToString(clsDate Date)
   {
       return to_string(Date.Day) + "/" + to_string(Date.Month) + "/" + to_string(Date.Year);
   }

   string DateToString()
   {
       return DateToString(*this);
   }


    string ConverNumberToText(int Number)
    {


        if (Number >= 1 && Number <= 19)
        {
            string arr[] = { "", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten",
                               "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen",
                               "Eighteen", "Nineteen" };

            return arr[Number] + " ";
        }

        if (Number >= 20 && Number <= 99)
        {
            string arr[] = { "","" ,"Twenty","Thirty","Forty","Fifty","Sixty","Seventy", "Eighty","Ninety" };

            return arr[Number / 10] + " " + ConverNumberToText(Number % 10);
        }

        if (Number >= 100 && Number <= 199)
        {
            return "One Hundred " + ConverNumberToText(Number % 100);
        }

        if (Number >= 200 && Number <= 1000)
        {
            return ConverNumberToText(Number / 100) + "Hundreds " + ConverNumberToText(Number % 100);
        }

        if (Number >= 1000 && Number <= 1999)
        {
            return "One Thousand " + ConverNumberToText(Number % 1000);
        }

        if (Number >= 2000 && Number <= 999999)
        {
            return ConverNumberToText(Number / 1000) + "Thousands " + ConverNumberToText(Number % 1000);
        }

        if (Number >= 1000000 && Number <= 1999999)
        {
            return " One Million " + ConverNumberToText(Number % 1000000);
        }

        if (Number >= 2000000 && Number <= 999999999)
        {
            return ConverNumberToText(Number / 1000000) + "Millions " + ConverNumberToText(Number % 1000000);
        }

        if (Number >= 1000000000 && Number <= 1999999999)
        {
            return "One Billion " + ConverNumberToText(Number % 1000000000);
        }

        return " ";
    }

    int ReadNumbers()
    {
        int Number = 0;

        cout << "please enter a year number ?" << endl;
        cin >> Number;

        return Number;
    }

    int ReadMonths()
    {
        int Number = 0;

        cout << "please enter a Month number ?" << endl;
        cin >> Number;

        return Number;
    }

    static bool IsLeapYear(int year)
    {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);

    }

    bool IsLeapYear()
    {
        return IsLeapYear(_Year);
    }

  static int NumberofDayesInYear(int Year)
    {
        return  IsLeapYear(Year) ? 366 : 365;
    }
  
  int NumberofDayesInYear()
  {
      return NumberofDayesInYear(_Year); 
  }

   static int NumberOfHoursInYears(int Year)
    {
        return NumberofDayesInYear(Year) * 24;
    }

   int NumberOfHoursInYears()
   {
       return NumberOfHoursInYears(_Year); 
   }

  static int NumberOfMuintsinYear(int Year)
    {
        return NumberOfHoursInYears(Year) * 60;
    }

  int NumberOfMuintsinYear()
  {
      return NumberOfMuintsinYear(_Year); 
  }

   static int NumberOfSecondsinYear(int Year)
    {
        return  NumberOfMuintsinYear(Year) * 60;
    }
   
   int NumberOfSecondsinYear()
   {
       return NumberOfSecondsinYear(_Year); 
   }

    static int NumberOfDaysInAMonth(int Month, int Year)
    {
        if (Month < 1 || Month > 12)
        {
            return 0;
        }

        int ArrMonths[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

        return (Month == 2) ? (IsLeapYear(Year) ? 29 : 28) : ArrMonths[Month - 1];
    }

    int NumberOfDaysInAMonth()
    {
        return NumberOfDaysInAMonth(_Month, _Year); 
    }

    static int NumberHoursInMonth(int Month, int Year)
    {
        return NumberOfDaysInAMonth(Month, Year) * 24;
    }

    int NumberHoursInMonth()
    {
        return NumberHoursInMonth(_Year, _Month); 
    }

   static int NumberMuintsInMonth(int Year, int Month)
    {
        return NumberHoursInMonth(Year, Month) * 60;
    }

   int NumberMuintsInMonth()
   {
       return NumberMuintsInMonth(_Year, _Month); 
   }

    static int NumberSecondsInMonth(int Year, int Month)
    {
        return NumberMuintsInMonth(Year, Month) * 60;
    }

    int NumberSecondsInMonth()
    {
        return NumberSecondsInMonth(_Year, _Month); 
    }

   static int DayOfWeekOrder(int Day, int Month, int Year)
    {
        int a, y, m;

        a = (14 - Month) / 12;

        y = Year - a;

        m = Month + (12 * a) - 2;

        return (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
    }



    int ReadDay()
    {
        int Day = 0;
        cout << " Enter a Day" << endl;
        cin >> Day;

        return Day;
    }

    string MonthShortName(int Monthname)
    {
        string Months[12] = { "jan", "feb", "mar", "apr", "may", "jun",
        "jul", "aug", "sep", "oct", "nov", "dec" };

        return Months[Monthname - 1];
    }

    void PrintMonthCalendar(int Month, int Year)
    {
        int Daysinmonth;

        int Daysinweek = DayOfWeekOrder(1, Month, Year);

        Daysinmonth = NumberOfDaysInAMonth(Month, Year);

        printf("\n_____________________________(%s)_____________________________\n",
            MonthShortName(Month).c_str());


        printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

        int i;

        for (i = 0; i < Daysinweek; i++)
        {
            printf("     ");
        }

        for (int j = 1; j <= Daysinmonth; j++)
        {
            printf("%5d", j);

            if (++i == 7)
            {
                i = 0;

                printf("\n");
            }
        }

        printf("\n___________________________________________________________________\n");

    }

    void PrintYearCalendar(int Year)
    {
        printf("\n _______________________________________________________________\n\n");

        printf("                    Calendar-%d\n", Year);

        printf("__________________________________________________________________\n");

        for (int i = 1; i <= 12; i++)
        {
            PrintMonthCalendar(i, Year);
        }

    }

    

   

   static int DayOfWeekOrder(clsDate Date)
    {
        return DayOfWeekOrder(Date.Day, Date.Month, Date.Year);
    }

   int DayOfWeekOrder()
   {
       return DayOfWeekOrder(*this); 
   }

    string DayShortname(int DayOfWeekOrder)
    {
        string ArrDayName[] = { "Sun","Mon" ,"Tue" , "Wed", "Thu" , "Fri" , "Sat" };

        return ArrDayName[DayOfWeekOrder];
    }

     static clsDate GetDateFromDayOrderInYear(int DateOrderInYear, int Year)
    {
        clsDate Date;

        int RemaningDays = DateOrderInYear;

        int MonthDays = 0;

        Date.Year = Year;

        Date.Month = 1;



        while (true)
        {
            MonthDays = NumberOfDaysInAMonth(Date.Month, Year);

            if (RemaningDays > MonthDays)
            {
                RemaningDays -= MonthDays;

                Date.Month++;
            }
            else
            {
                Date.Day = RemaningDays;
                break;
            }
        }

        return Date;
    }

   static int NumberOfDaysFromTheBeginingTheYear(int Day, int Month, int Year)
    {
        int Totaldys = 0;

        for (int i = 1; i <= Month - 1; i++)
        {
            Totaldys += NumberOfDaysInAMonth(i, Year);
        }

        Totaldys += Day;

        return Totaldys;
    }

   int NumberOfDaysFromTheBeginingTheYear()
   {
       return NumberOfDaysFromTheBeginingTheYear(_Day, _Month, _Year); 
   }

    clsDate DateAddDays(int Days, clsDate Date)
    {
        int RemaningDays = Days + NumberOfDaysFromTheBeginingTheYear(Date.Day, Date.Month, Date.Year);

        int MonthDays = 0;

        Date.Month = 1;

        while (true)
        {
            MonthDays = NumberOfDaysInAMonth(Date.Month, Date.Year);

            if (RemaningDays > MonthDays)
            {
                RemaningDays -= MonthDays;
                Date.Month++;

                if (Date.Month > 12)
                {
                    Date.Month = 1;
                    Date.Year++;
                }
            }
            else
            {
                Date.Day = RemaningDays;
                break;
            }

        }

        return Date;
    }

    clsDate ReadFullDate()
    {
        clsDate Date;
        Date.Day = ReadDay();
        Date.Month = ReadMonths();
        Date.Year = ReadNumbers();

        return Date;
    }

    int DaysToAdd()
    {
        int Day = 0;

        cout << "Enter how many days to add !" << endl;
        cin >> Day;

        return Day;
    }

  static  bool IsDateOneBefreDateTwo(clsDate Date1, clsDate Date2)
    {
        if (Date1.Year < Date2.Year)
        {
            return true;
        }
        if (Date1.Year > Date2.Year)
        {
            return false;
        }


        if (Date1.Month < Date2.Month)
        {
            return true;
        }
        if (Date1.Month > Date2.Month)
        {
            return false;
        }

        return Date1.Day < Date2.Day;
    }

   static bool IsDate1EqualDate2(clsDate Date1, clsDate Date2)
    {
        return(Date1.Year == Date2.Year) ? ((Date1.Month == Date2.Month) ? ((Date1.Day == Date2.Day) ? true : false) : false) : false;
    }

   static bool IsLastDayinMonh(clsDate Date)
    {
        return (Date.Day == NumberOfDaysInAMonth(Date.Month, Date.Year));

    }

   bool IsLastDayinMonh()
   {
       return IsLastDayinMonh(*this); 
   }

   static bool IsLastMonthinYear(int Month)
    {
        return (Month == 12);
    }

   bool IsLastMonthinYear()
   {
       return IsLastMonthinYear(_Year); 
   }

   static clsDate IncreaseDateByOneDay(clsDate &Date)
    {
        if (IsLastDayinMonh(Date))
        {
            if (IsLastMonthinYear(Date.Month))
            {
                Date.Month = 1;

                Date.Day = 1;

                Date.Year++;
            }
            else
            {
                Date.Day = 1;
                Date.Month++;
            }
        }
        else
        {
            Date.Day++;
        }

        return Date;
    }

   void IncreaseDateByOneDay()
   {
       IncreaseDateByOneDay(*this); 
   }

  static  clsDate IncreaseDateByXDays(int Days, clsDate& Date)
    {
        for (int i = 1; i <= Days; i++)
        {
            Date = IncreaseDateByOneDay(Date);
        }

        return Date;
    }

  void IncreaseDateByXDays(int Days)
  {
      IncreaseDateByXDays(Days,*this); 
  }

  static  clsDate IncreaseDateByOneWeek(clsDate& Date)
    {
        for (int i = 1; i <= 7; i++)
        {
            Date = IncreaseDateByOneDay(Date);

        }

        return Date;
    }

  void IncreaseDateByOneWeek()
  {
      IncreaseDateByOneWeek(*this); 
  }

  static  clsDate IncreaseDateByXWeek(int Weeks, clsDate& Date)
    {
        for (int i = 1; i <= Weeks; i++)
        {
            Date = IncreaseDateByOneWeek(Date);
        }

        return Date;
    }

  void IncreaseDateByXWeek(int Weeks)
  {
      IncreaseDateByXWeek(Weeks, *this); 
  }

 static clsDate IncreaseDateByMonth(clsDate& Date)
    {
        if (Date.Month == 12)
        {
            Date.Month = 1;
            Date.Year++;
        }
        else
        {
            Date.Month++;
        }

        int MonthCheck = NumberOfDaysInAMonth(Date.Month, Date.Year);

        if (Date.Day > MonthCheck)
        {
            Date.Day = MonthCheck;
        }

        return Date;
    }

 void IncreaseDateByMonth()
 {
     IncreaseDateByMonth(*this); 
 }
 
 static clsDate IncreaseDateByXMonth(int Months, clsDate& Date)
    {
        for (int i = 1; i <= Months; i++)
        {
            Date = IncreaseDateByMonth(Date);
        }

        return Date;
    }

 void IncreaseDateByXMonth(int Months)
 {
     IncreaseDateByXMonth(Months, *this); 
 }
 
 static clsDate IncreaseDateByYear(clsDate &Date)
    {
        Date.Year++;

        return Date;
    }

 void IncreaseDateByYear()
 {
     IncreaseDateByYear(*this); 
 }
 
 static clsDate IncreaseDateByXYear(int Years, clsDate& Date)
    {
        for (int i = 1; i <= Years; i++)
        {
            Date = IncreaseDateByYear(Date);
        }

        return Date;
    }

 void IncreaseDateByXYear(int Years)
 {
     IncreaseDateByXYear(Years, *this); 
 }
 
 static clsDate IncreaseDateByOneDecate(clsDate& Date)
    {
        Date.Year += 10;

        return Date;
    }

 void IncreaseDateByOneDecate()
 {
     IncreaseDateByOneDecate(*this);
 }
 
 static clsDate IncreaseDateByXDecate(int Decats, clsDate& Date)
    {
        for (int i = 1; i <= Decats; i++)
        {
            Date = IncreaseDateByOneDecate(Date);
        }

        return Date;
    }

 void IncreaseDateByXDecate(int Decats)
 {
     IncreaseDateByXDecate(Decats, *this); 
 }
 
 static clsDate IncreaseDateByCentury(clsDate& Date)
    {
        Date.Year += 100;

        return Date;
    }

 void  IncreaseDateByCentury()
 {
     IncreaseDateByCentury(*this); 
 }
 
 static clsDate IncreaseDateBMilinume(clsDate& Date)
    {
        Date.Year += 1000;

        return Date;
    }

 void IncreaseDateBMilinume()
 {
     IncreaseDateBMilinume(*this); 
 }
 
 static clsDate DecreaseDateByOneDay(clsDate& Date)
    {
        if (Date.Day == 1)
        {
            if (Date.Month == 1)
            {
                Date.Month = 12;
                Date.Day = 31;
                Date.Year--;
            }
            else
            {
                Date.Month--;

                Date.Day = NumberOfDaysInAMonth(Date.Month, Date.Year);
            }
        }
        else
        {
            Date.Day--;
        }

        return Date;
    }

 void DecreaseDateByOneDay()
 {
     DecreaseDateByOneDay(*this); 
 }
 
 static clsDate DecreaseDateByXDays(int Days, clsDate& Date)
    {
        for (int i = 1; i <= Days; i++)
        {
            Date = DecreaseDateByOneDay(Date);
        }

        return Date;
    }

 void DecreaseDateByXDays(int Days)
 {
     DecreaseDateByXDays(Days, *this); 
 }
 
 static clsDate DecreaseDateByWeek(clsDate& Date)
    {
        for (int i = 1; i <= 7; i++)
        {
            Date = DecreaseDateByOneDay(Date);
        }

        return Date;
    }

 void DecreaseDateByWeek()
 {
     DecreaseDateByWeek(*this); 
 }
 
 static clsDate DecreaseDateByXWeeks(int Weeks, clsDate& Date)
    {
        for (int i = 1; i <= Weeks; i++)
        {
            Date = DecreaseDateByWeek(Date);
        }

        return Date;
    }
 
 void DecreaseDateByXWeeks(int Weeks)
 {
     DecreaseDateByXWeeks(Weeks,*this);
 }


 static clsDate DecreaseDateByMonth(clsDate& Date)
    {
        if (Date.Month == 1)
        {
            Date.Month = 12;
            Date.Year--;
        }
        else
        {
            Date.Month--;
        }

        int DaysinMonth = NumberOfDaysInAMonth(Date.Month, Date.Year);

        if (Date.Day > DaysinMonth)
        {
            Date.Day = DaysinMonth;
        }

        return Date;
    }
 
 void DecreaseDateByMonth()
 {
     DecreaseDateByMonth(*this);
 }

 static clsDate DecreaseDateByXMonths(int Months, clsDate& Date)
    {
        for (int i = 1; i <= Months; i++)
        {
            Date = DecreaseDateByMonth(Date);
        }

        return Date;
    }

 void  DecreaseDateByXMonths(int Months)
 {
     DecreaseDateByXMonths(Months, *this);
 }
 
 static clsDate DecreaseDateByYear(clsDate& Date)
    {
        Date.Year -= 1;

        return Date;
    }

 void DecreaseDateByYear()
 {
     DecreaseDateByYear(*this);
 }
 
 static clsDate DecreaseDateByxYears(int Years, clsDate& Date)
    {
        for (int i = 1; i <= Years; i++)
        {
            Date = DecreaseDateByYear(Date);
        }

        return Date;
    }

 void DecreaseDateByxYears(int Years)
 {
     DecreaseDateByxYears(Years, *this); 
 }
 
 static clsDate DecreaseDateByDecate(clsDate& Date)
    {
        Date.Year -= 10;

        return Date;
    }

 void DecreaseDateByDecate()
 {
     DecreaseDateByDecate(*this);
 }
 
 static void SwapDate(clsDate& Date1, clsDate& Date2)
    {
        clsDate TempDate;

        TempDate.Year = Date1.Year;
        TempDate.Month = Date1.Month;
        TempDate.Day = Date1.Day;

        Date1.Year = Date2.Year;
        Date1.Month = Date2.Month;
        Date1.Day = Date2.Day;

        Date2.Year = TempDate.Year;
        Date2.Month = TempDate.Month;
        Date2.Day = TempDate.Day;


    }


 static int GetDifferenceInDays(clsDate Date1, clsDate Date2, bool IncludeEndDay = false)
    {

        int Days = 0;
        int Swap = 1;

        if (!IsDateOneBefreDateTwo(Date1, Date2))
        {
            SwapDate(Date1, Date2);

            Swap = -1;

        }

        while (IsDateOneBefreDateTwo(Date1, Date2))
        {
            Days++;
            Date1 = IncreaseDateByOneDay(Date1);


        }

        return IncludeEndDay ? ++Days * Swap : Days * Swap;
    }
 
 static string DayShortName(int DayOfWeekOrder)
    {
        string NameDay[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };

        return NameDay[DayOfWeekOrder];
    }

   static bool IsWeekEnd(clsDate Date)
    {
        int DayIndx = DayOfWeekOrder(Date);

        return (DayIndx == 5 || DayIndx == 6);

    }

   bool IsWeekEnd()
   {
       return IsWeekEnd(*this); 
   }

   static bool IsBusinessDay(clsDate Date)
    {
        return !IsWeekEnd(Date);
    }

   bool IsBusinessDay()
   {
       return IsBusinessDay(*this); 
   }

   static int IsEndOfWeek(clsDate Date)
    {
        return  DayOfWeekOrder(Date) == 6;
    }

   int IsEndOfWeek()
   {
       return IsEndOfWeek(*this);
   }

   static int DayUntilTheEndofWeek(clsDate Date)
    {
        return 6 - DayOfWeekOrder(Date);
    }

   int DayUntilTheEndofWeek()
   {
       return DayUntilTheEndofWeek(*this); 
   }

  static int DaysUntilEndofMonth(clsDate Date)
    {
        clsDate EndofMonth;

        EndofMonth.Day = NumberOfDaysInAMonth(Date.Month, Date.Year);

        EndofMonth.Month = Date.Month;
        EndofMonth.Year = Date.Year;

        return GetDifferenceInDays(Date, EndofMonth, true);
    }

  int DaysUntilEndofMonth()
  {
      return DaysUntilEndofMonth(*this); 
  }

   static int DaysUntilEndofYear(clsDate Date)
    {
        clsDate EndofYear;

        EndofYear.Day = 31;
        EndofYear.Month = 12;
        EndofYear.Year = Date.Year;

        return GetDifferenceInDays(Date, EndofYear, true);
    }

   int DaysUntilEndofYear()
   {
       return DaysUntilEndofYear(*this); 
   }

   

   static int CalculateVacationDays(clsDate From, clsDate To)
    {
        int VacDays = 0;
        while (IsDateOneBefreDateTwo(From, To))
        {
            if (IsBusinessDay(From))
            {
                VacDays++;
            }

            From = IncreaseDateByOneDay(From);
        }

        return VacDays;
    }

  static  clsDate CalculateVacationDaysinreturn(clsDate From, int Vacationdays)
    {
        int WeekEndDays = 0;

        while (IsWeekEnd(From))
        {
            From = IncreaseDateByOneDay(From);
        }

        for (int i = 1; i <= Vacationdays + WeekEndDays - 1; i++)
        {
            if (IsWeekEnd(From))
                WeekEndDays++;


            From = IncreaseDateByOneDay(From);


        }

        while (IsWeekEnd(From))
        {
            From = IncreaseDateByOneDay(From);
        }

        return From;
    }

  static  int ReedVacationDays()
    {
        int Vacationdays = 0;

        cout << " Please Enter The Vacation days ? " << endl;
        cin >> Vacationdays;

        return Vacationdays;
    }

  static  bool IsDate1AfterDate2(clsDate Date1, clsDate Date2)
    {
        return (!IsDateOneBefreDateTwo(Date1, Date2) && !IsDate1EqualDate2(Date1, Date2));
    }

   static enum enCompareDate { Before = -1, Equal = 0, After = 1 };

    static enCompareDate CompareDate(clsDate Date1, clsDate Date2)
    {
        if (IsDateOneBefreDateTwo(Date1, Date2))
        {
            return enCompareDate::Before;
        }
        else if (IsDate1EqualDate2(Date1, Date2))
        {
            return enCompareDate::Equal;
        }
        else
            return enCompareDate::After;
    }

   

    vector<string> SplitString(string str, string delim)
    {
        short pos = 0;

        string word; // Variable to hold each word

        vector<string> result; // Vector to store the split words

        while ((pos = str.find(delim)) != std::string::npos) //Find the position of the delimiter in the string
        {
            word = str.substr(0, pos); // Extract the word from the string

            if (word != "")
            {
                result.push_back(word); // Add the word to the result vector if it's not empty
            }

            str.erase(0, pos + delim.length()); // Remove the word from the string
        }

        if (str != "")
        {
            result.push_back(str); // Add the remaining part of the string to the result vector if it's not empty
        }

        return result; // Return the vector containing the split words
    }

    string ReadDateinString(string message)
    {
        string Dateinstring;

        cout << message << endl;
        getline(cin >> ws, Dateinstring);

        return Dateinstring;
    }

  
    clsDate StringToDate(string DateString)
    {
        clsDate Date;
        vector<string> vDate;

        vDate = SplitString(DateString, "/");
        Date.Day = stoi(vDate[0]);
        Date.Month = stoi(vDate[1]);
        Date.Year = stoi(vDate[2]);

        return Date;

    }

    string Replacestrings(string str, string Oldword, string Newword)
    {
        short pos = str.find(Oldword); // Find the position of the old word in the string

        while (pos != std::string::npos) // Continue until no more occurrences are found
        {
            str.replace(pos, Oldword.length(), Newword); // Replace the old word with the new word

            pos = str.find(Oldword); // Find the next occurrence of the old word

        }

        return str; // Return the modified string
    }

    string FormatDate(clsDate Date, string String = "DD/MM/YYY")
    {

        String = Replacestrings(String, "DD", to_string(Date.Day));
        String = Replacestrings(String, "MM", to_string(Date.Month));
        String = Replacestrings(String, "YYY", to_string(Date.Year));

        return String;
    }

  static string SystemDateTimeString()
    {
        time_t t = time(0); 

        tm* now = localtime(&t); 


        short year, month, day,hour, minute, second; 

        year = now->tm_year + 1900; 

        month = now->tm_mon + 1; 

        day = now->tm_mday;

        minute = now->tm_min; 

        hour = now->tm_hour; 

        second = now->tm_sec; 


        return(to_string(day) + "/" + to_string(month) + "/"
            + to_string(year) + "-" + to_string(hour) + ":" 
            + to_string(minute) + ":" + to_string(second)); 

        
    }

};