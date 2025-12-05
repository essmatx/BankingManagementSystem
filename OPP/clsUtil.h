#pragma once
#include <iostream>
#include "clsPerson.h"
#include "clsCalculater.h"

#include "clsAddress.h"
#include "clsString.h"
#include "clsDate.h"
#include <string>
#include <vector>
using namespace std; 

class clsUtil
{
public:

	enum enCharTyp { Small = 1, Capital = 2, Specialcharcter = 3, Digit = 4 ,MixChars = 5};

	static void Srand()
	{
		srand((unsigned)time(NULL)); 
	}

	static int RandomNumber(int From, int To)
	{
		int Random = rand() % (To - From + 1) + From;

		return Random;
	}

	static char GetRandomCharacter(enCharTyp CharType)
	{
		if (CharType == MixChars)
		{
			CharType = (enCharTyp)RandomNumber(1, 3);
		}

		switch (CharType)
		{
		case enCharTyp::Small:
			return char(RandomNumber(97, 122));  // 'a'–'z'

		case enCharTyp::Capital:
			return char(RandomNumber(65, 90));   // 'A'–'Z'

		case enCharTyp::Digit:
			return char(RandomNumber(48, 57));   // '0'–'9'

		case enCharTyp::Specialcharcter:
			return char(RandomNumber(33, 47));   // punctuation

		default:
			return char(RandomNumber(65, 90));   // fallback (capital)
		}
	}

	static string Generatewords(enCharTyp CharType, short Length)
	{
		string word;

		for (int i = 1; i <= Length; i++)
		{
			word = word + GetRandomCharacter(enCharTyp(CharType));
		}

		return word;
	}

	static string GenerateKye(enCharTyp CharType)
	{
		string K = "";
		K = (Generatewords(CharType, 4)) + "-";
		K = K + (Generatewords(CharType, 4)) + "-";
		K = K + (Generatewords(CharType, 4)) + "-";
		K = K + (Generatewords(CharType, 4));

		return K;

	}

	static void GenerateKyes(short Length, enCharTyp CharType)
	{
		for (int i = 1; i <= Length; i++)
		{
			cout << " Key [ " << i << " ] ";
			cout << GenerateKye(CharType) << endl;
		}
	}

	static void FillArryWithRandomNum(int Arr[100], int& Length,int from , int to)
	{
		cout << " Please Enter the Number of Elemntes " << endl;
		cin >> Length;

		for (int i = 0; i < Length; i++)
		{
			Arr[i] = RandomNumber(from, to);
		}
	}

	static void FillArryWithRandomWords(string Arr[100], int Lingth, enCharTyp CharType, int WordLingth)
	{
		for (int i = 0; i < Lingth; i++)
		{
			Arr[i] = Generatewords(CharType, WordLingth);
		}
	}

	static void FillArryWithRandomKyes(string Arr[100], int Lingth, enCharTyp CharType)
	{
		for (int i = 0; i < Lingth; i++)
		{
			Arr[i] = GenerateKye(CharType); 
		}
	}

	static void Swap(int& A, int& B)
	{

		int Temp;
		Temp = A;
		A = B;
		B = Temp;


	}

	static void Swap(double& A, double& B)
	{

		int Temp;
		Temp = A;
		A = B;
		B = Temp;


	}

	static void Swap(bool& A, bool &B)
	{

		int Temp;
		Temp = A;
		A = B;
		B = Temp;


	}

	static void Swap(char& A, char& B)
	{

		int Temp;
		Temp = A;
		A = B;
		B = Temp;


	}

	static void Swap(string& A, string& B)
	{

		string Temp;
		Temp = A;
		A = B;
		B = Temp;


	}

	static void Swap(clsDate& A, clsDate& B)
	{
		clsDate::SwapDate(A, B); 
	}

	static void ShufleArr(int Arr[100], int Length)
	{
		for (int i = 0; i < Length; i++)
		{
			int Index1 = RandomNumber(1, Length) - 1;
			int Index2 = RandomNumber(1, Length) - 1;

			Swap(Arr[Index1], Arr[Index2]);
		}
	}

	static void ShufleArr(string Arr[100], int Length)
	{
		for (int i = 0; i < Length; i++)
		{
			int Index1 = RandomNumber(1, Length) - 1;
			int Index2 = RandomNumber(1, Length) - 1;

			Swap(Arr[Index1], Arr[Index2]);
		}
	}

	static string Tabs(int NumberOfTabs)
	{
		string t = ""; 

		for (int i = 0; i < NumberOfTabs; i++)
		{
			t = t + "\t";
			cout << t; 
		}

		return t; 
	}

	static string EncrypText( string Text, short Encryption = 2)
	{
		
		for (int i = 0; i < Text.length(); i++)
		{
			Text[i] = char((int)Text[i] + Encryption);
		}

		return Text;
	}

	static string DecryptedText(string Text, short Decryption = 2)
	{
		
		for (int i = 0; i < Text.length(); i++)
		{
			Text[i] = char((int)Text[i] - Decryption);
		}

		return Text;
	}

	static string NumberToText(int Number)

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

        return arr[Number / 10] + " " + NumberToText(Number % 10);
    }

    if (Number >= 100 && Number <= 199)
    {
        return "One Hundred " + NumberToText(Number % 100);
    }
    
    if (Number >= 200 && Number <= 1000)
    {
        return NumberToText(Number / 100) + "Hundreds " + NumberToText(Number % 100);
    }

    if (Number >= 1000 && Number <= 1999)
    {
        return "One Thousand " + NumberToText(Number % 1000);
    }
    
    if (Number >= 2000 && Number <= 999999)
    {
        return NumberToText(Number / 1000) + "Thousands " + NumberToText(Number % 1000);
    }

    if (Number >= 1000000 && Number <= 1999999)
    {
        return " One Million " + NumberToText(Number % 1000000); 
    }

    if (Number >= 2000000 && Number <= 999999999)
    {
        return NumberToText(Number / 1000000) + "Millions " + NumberToText(Number % 1000000);
    }
    
    if (Number >= 1000000000 && Number <= 1999999999)
    {
        return "One Billion " + NumberToText(Number % 1000000000);
    }

    return " ";
	}
};

