#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include "clsDate.h"
using namespace std; 

class clsPeriod
{
public:
	clsDate Startdate;
	clsDate EndDate; 


	clsPeriod(clsDate Startdate, clsDate EndDate)
	{
		this -> Startdate  = Startdate; 
		this -> EndDate =  EndDate; 
	}


	static bool IsOverLap(clsPeriod Period1, clsPeriod Period2)
	{
		
		if (
			clsDate::CompareDate(Period1.Startdate, Period2.EndDate) == clsDate::enCompareDate::Before 
			|| clsDate::CompareDate(Period1.Startdate, Period2.EndDate) == clsDate::enCompareDate::After)
			return false;
		else
			return true;

	}

	bool IsOverLapWith(clsPeriod Period)
	{
		return IsOverLap(*this, Period);
	}

	void Print()
	{
		cout << "Start Date " << endl; 
		Startdate.Print(); 

		cout << "End Date " << endl;
		EndDate.Print(); 
	}


};

