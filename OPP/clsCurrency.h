#pragma once
#include <iostream>
#include "clsString.h"
#include <string>
#include <vector>
#include <fstream>
using namespace std;

const string CurrencyFile = "CurrencyFile.txt"; 

class clsCurrency
{
	enum Mode {EmptyMode = 0 , UpdateMode = 1};

	Mode _Mode; 
	
	string _Country; 

	string _CurrencyCode; 

	string _CurrencyName; 

	float _Rate; 

	static clsCurrency _ConvertLineToCurrencyObject(string line, string seperator = "<<")
	{
		vector <string>  vDataline;

		vDataline = clsString::SplitString(line, seperator); 

		return clsCurrency(Mode::UpdateMode, vDataline[0], vDataline[1], vDataline[2], stod(vDataline[3])); 
	}

	//we will need to modify this function after builing the cunstrutor
	static string _ConverCurrencyObjectToLine(clsCurrency Currency, string seperator = "<<")
	{
		string Data = ""; 

		Data += Currency._Country + seperator; 

		Data += Currency._CurrencyCode + seperator; 

		Data += Currency._CurrencyName + seperator; 

		Data += to_string(Currency._Rate); 

		return Data; 
	}

	static vector<clsCurrency> _LoadCurrencyDataFromFile()
	{
		vector<clsCurrency> vData; 

		fstream Myfile; 

		Myfile.open(CurrencyFile, ios::in); 

		if (Myfile.is_open())
		{
			string line = ""; 
			

			while (getline(Myfile, line))
			{
				clsCurrency currency = _ConvertLineToCurrencyObject(line);

				vData.push_back(currency); 
			}

			Myfile.close(); 
		}
		
		return vData; 
	}

	static void _SaveCurrencyDataToFile(vector<clsCurrency> vcurrency)
	{
		fstream Myfile; 

		string line; 

		Myfile.open(CurrencyFile,ios::out);

		if (Myfile.is_open())
		{
			for (clsCurrency C : vcurrency)
			{
				line = _ConverCurrencyObjectToLine(C); 

				Myfile << line << endl; 
			}

			Myfile.close(); 
		}
	}

	//we should file this function after builing the cunstrutor
	void _Update()
	{
		vector <clsCurrency> vCurrency; 

		vCurrency = _LoadCurrencyDataFromFile(); 

		for (clsCurrency& C : vCurrency)
		{
			if (C.CurrencyCode() == CurrencyCode())
			{
				C = *this;
				break;
			}
		}
	}

	static clsCurrency _GetEmptyCurrencyObject()
	{
		return clsCurrency(Mode::EmptyMode, "", "", "", 0); 
	}

public :

	clsCurrency(Mode Mode, string Country, string CurrencyCode, string CurrencyName, float Rate)
	{
		_Mode = Mode; 

		_Country = Country; 

		_CurrencyCode = CurrencyCode; 

		_CurrencyName = CurrencyName; 

		_Rate = Rate; 
	}

	static vector <clsCurrency> GetAllCurrecyes()
	{
		return _LoadCurrencyDataFromFile(); 
	}

	bool IsEmpty()
	{
		return (_Mode == Mode::EmptyMode); 
	}

	string Country()
	{
		return _Country;
	}

	 string CurrencyCode()
	{
		return _CurrencyCode; 
	}

	string CurrencyName()
	{
		return _CurrencyName; 
	}

	// we need to put Update function here
	void UpdateRate(float NewRate)
	{
		_Rate = NewRate; 
		_Update();
	}

	float getRate()
	{
		return _Rate; 
	}

	static clsCurrency FindCourrencyByCode(string CurrencyCode)
	{
		fstream Myfile; 

		Myfile.open(CurrencyFile, ios::in); 

		if (Myfile.is_open())
		{
			string line; 

			while (getline(Myfile, line))
			{
				clsCurrency Data = _ConvertLineToCurrencyObject(line); 

				if (clsString::AllStringCapitalLater(Data.CurrencyCode()) == clsString::AllStringCapitalLater (CurrencyCode))
				{
					Myfile.close(); 

					return Data; 
				}
			}

			Myfile.close(); 
		}

		return _GetEmptyCurrencyObject();
	}

	static clsCurrency FindCourrencyByCountry(string CountryCurency)
	{
		fstream Myfile; 

		Myfile.open(CurrencyFile, ios::in); 

		if (Myfile.is_open())
		{
			string line; 

			while (getline(Myfile, line))
			{
				clsCurrency Data = _ConvertLineToCurrencyObject(line); 

				if (clsString::AllStringCapitalLater(Data.Country()) == clsString::AllStringCapitalLater(CountryCurency))
				{
					Myfile.close(); 

					return Data; 
				}
			}

			Myfile.close(); 
		}

		return _GetEmptyCurrencyObject(); 
	}

	static bool IsCurrencyExsistCode(string Currency)
	{
		clsCurrency C = clsCurrency::FindCourrencyByCode(Currency);

		return (!C.IsEmpty()); 
	}

	static bool IsCurrencyExsistCounrty(string Currency)
	{
		clsCurrency C = clsCurrency::FindCourrencyByCountry(Currency);

		return (!C.IsEmpty());
	}

	static vector<clsCurrency> GetcurrencyList()
	{
		return clsCurrency::_LoadCurrencyDataFromFile(); 
	}

	 float ChangeCurrencyToUSD(float Amount)
	 {
		return (float)(Amount / getRate());
	 }

	 float ChangeToOtherCurrency(float Amount, clsCurrency Currency)
	 {
		 float AmountInUSD = 0; 

		 AmountInUSD = ChangeCurrencyToUSD(Amount); 

		 if (Currency.CurrencyCode() == "USD")
		 {
			 return AmountInUSD;

		 }
		 return (float)(AmountInUSD * Currency.getRate()); 
	 }
};

