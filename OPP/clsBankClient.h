#pragma once
#include <iostream>
#include "clsPerson.h"
#include "clsString.h"
#include "clsDate.h" 
#include <string>
#include <vector>
#include <fstream>
using namespace std;

const string ClienttsFile = "Client.txt"; 

const string TransFileRecord= "TransFile";

class clsBankClient :public clsPerson
{
	 struct stTransferLogReccord; 


	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNew = 2 };
	enMode _Mode;

	string _AccountNumber;
	string _PinCode;
	float _Accountbalance;
	bool _MarkforDelet = false;

	static string _ConvertClientObjectToLine(clsBankClient Client, string Seperator = "<<")
	{
		string Line = "";

		Line += Client.FirstName + Seperator;
		Line += Client.LastName + Seperator;
		Line += Client.Phone + Seperator;
		Line += Client.Email + Seperator;
		Line += Client.getAccountNumber() + Seperator;
		Line += Client.PinCode + Seperator;
		Line += to_string(Client.getAccountbalance());
		return Line;

	}


	static clsBankClient _ConvertLinetoClientObject(string Line, string Seperator = "<<")
	{
		vector < string > vClient;

		vClient = clsString::SplitString(Line, Seperator);

		return clsBankClient(enMode::UpdateMode, vClient[0], vClient[1], vClient[2], vClient[3], vClient[4], vClient[5], stod(vClient[6]));


	}

	static vector <clsBankClient> _LoadClientDataFromFile()
	{
		vector <clsBankClient> vClient;

		fstream Myfile;

		Myfile.open(ClienttsFile, ios::in);

		if (Myfile.is_open())
		{
			string Line;

			while (getline(Myfile, Line))
			{
				clsBankClient Client = _ConvertLinetoClientObject(Line);

				vClient.push_back(Client);

			}

			Myfile.close();
		}

		return vClient;
	}

	static void _SaveClientDatatoFile(vector <clsBankClient> vClient)
	{
		string Line;

		fstream Myfile;
		Myfile.open(ClienttsFile, ios::out);

		if (Myfile.is_open())
		{
			for (clsBankClient& C : vClient)
			{
				if (C.getMarkeforDelet() == false)
				{
					Line = _ConvertClientObjectToLine(C);

					Myfile << Line << endl;
				}

			}

			Myfile.close();
		}
	}

	void _Update()
	{
		vector <clsBankClient> vClient;

		vClient = _LoadClientDataFromFile();

		for (clsBankClient& C : vClient)
		{
			if (C.getAccountNumber() == getAccountNumber())
			{
				C = *this;
				break;
			}
		}

		_SaveClientDatatoFile(vClient);
	}

	void _AddNewClient()
	{
		_AddDataLinetoFile(_ConvertClientObjectToLine(*this));
	}

	void _AddDataLinetoFile(string Line)
	{
		fstream Myfile;

		Myfile.open(ClienttsFile, ios::out | ios::app);

		if (Myfile.is_open())
		{
			Myfile << Line << endl;

			Myfile.close();
		}
	}

	static clsBankClient _GetEmptyClient()
	{
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	string _PrepareTransferRecord(float Amount, clsBankClient DistantCLient, string Username, string seperator = "<<")
	{
		string recordline = ""; 

		

		recordline += clsDate::SystemDateTimeString() + seperator;

		recordline += getAccountNumber() + seperator;

		recordline += DistantCLient.getAccountNumber() + seperator;

		recordline += to_string(Amount) + seperator; 

		recordline += to_string(Accountbalance) + seperator; 

		recordline += to_string(DistantCLient.Accountbalance) + seperator;

		recordline += Username; 

		return recordline; 

	}

	void _TransLogRecord(float Amount, clsBankClient DistantCLient, string Username)
	{

		string Dataline = _PrepareTransferRecord(Amount, DistantCLient, Username);

		fstream Myfile;

		Myfile.open(TransFileRecord, ios::out | ios::app);

		if (Myfile.is_open())
		{
			Myfile << Dataline << endl;

			Myfile.close();
		}
	}

	static stTransferLogReccord _ConverTransferLogLineToRecord(string line, string Seperater = "<<")
	{
		

		stTransferLogReccord Dataline; 
		vector <string> vDataline = clsString::SplitString(line, Seperater);
		Dataline.DataTime = vDataline[0]; 
		Dataline.SorceAccountNumber = vDataline[1];
		Dataline.DistenationAccountNumber = vDataline[2];
		Dataline.Amount = stod(vDataline[3]); 
		Dataline.SorceBalance = stod(vDataline[4]);
		Dataline.DistenationBalance = stod(vDataline[5]);
		Dataline.Username = vDataline[6]; 

		if (vDataline.size() < 7)
		{
			cout << "Record format error -> line: " << line << endl;
			throw exception("Invalid record format.");
		}


		return Dataline; 
	}


public:

	clsBankClient(enMode Mode, string FirstName,
		string LastName, string Email, string Phone, string AccountNumber, string PinCode, float Accountbalance) :
		clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;

		_AccountNumber = AccountNumber;

		_PinCode = PinCode;

		_Accountbalance = Accountbalance;

	}
  
	struct stTransferLogReccord
	{
		string DataTime; 
		string SorceAccountNumber; 
		string DistenationAccountNumber; 
		float Amount; 
		float SorceBalance;
		float DistenationBalance; 
		string Username; 
	};

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	bool getMarkeforDelet()
	{
		return _MarkforDelet;
	}

	string getAccountNumber()
	{
		return _AccountNumber;
	}

	__declspec(property(get = getAccountNumber)) string AccountNumber;

	void setPinCode(string PinCode)
	{
		_PinCode = PinCode;
	}

	string getPinCode()
	{
		return _PinCode;
	}
	__declspec(property(get = getPinCode, put = setPinCode)) string PinCode;

	void setAccountbalance(float Accountbalance)
	{
		_Accountbalance = Accountbalance;
	}

	 float getAccountbalance()
	{
		return _Accountbalance;
	}
	__declspec(property(get = getAccountbalance, put = setAccountbalance)) float Accountbalance;



	bool Delet()
	{
		vector<clsBankClient> vClient;

		vClient = _LoadClientDataFromFile();

		for (clsBankClient& C : vClient)
		{
			if (C.getAccountNumber() == _AccountNumber)
			{
				C._MarkforDelet = true;
				break;
			};



		};

		_SaveClientDatatoFile(vClient);

		this->_MarkforDelet = true;

		*this = _GetEmptyClient();



		return true;
	}

	void Print()
	{
		cout << "\nClient Card:";
		cout << "\n_______________________________________\n";
		cout << "FirstName      :" << FirstName << endl;
		cout << "LastName       :" << LastName << endl;
		cout << "FullName       :" << FullName() << endl;
		cout << "Email          :" << Phone << endl;
		cout << "Phone          :" << Email << endl;
		cout << "Account Number :" << _AccountNumber << endl;
		cout << "PinCode        :" << _PinCode << endl;
		cout << "Account Balance:" << _Accountbalance << endl;
		cout << "\n_______________________________________\n";
	}

	static clsBankClient Find(string AccountNumber)
	{
		vector <clsBankClient>  vClient;

		fstream Myfile;
		Myfile.open(ClienttsFile, ios::in);

		if (Myfile.is_open())
		{
			string Line = "";
			while (getline(Myfile, Line))
			{
				clsBankClient Client = _ConvertLinetoClientObject(Line);

				if (Client.getAccountNumber() == AccountNumber)
				{
					Myfile.close();

					return Client;
				}
				vClient.push_back(Client);
			}

			Myfile.close();

		}

		return _GetEmptyClient();
	}

	static clsBankClient Find(string AccountNumber, string PinCode)
	{
		vector<clsBankClient> vClient;
		fstream Myfile;

		Myfile.open(ClienttsFile, ios::in);

		if (Myfile.is_open())
		{
			string Line;

			while (getline(Myfile, Line))
			{
				clsBankClient Client = _ConvertLinetoClientObject(Line);

				if (Client.getAccountNumber() == AccountNumber && Client.getPinCode() == PinCode)
				{
					Myfile.close();
					return Client;
				}

				vClient.push_back(Client);
			}

			Myfile.close();
		}

		return  _GetEmptyClient();
	}

	enum enSaveResults { SaveFileEmptyObject = 0, SaveSucceded = 1, SavefaildClientexsied };

	enSaveResults save()
	{
		switch (_Mode)
		{
		case enMode::EmptyMode:
			return enSaveResults::SaveFileEmptyObject;

		case enMode::UpdateMode:

			_Update();
			return enSaveResults::SaveSucceded;
			break;

		case enMode::AddNew:
			if (clsBankClient::IsClientExist(_AccountNumber))
			{
				return enSaveResults::SavefaildClientexsied;

			}
			else
			{
				_AddNewClient();
				_Mode = enMode::UpdateMode;
				return enSaveResults::SaveSucceded;
			}
		}
	}

	static bool IsClientExist(string AccountNumber)
	{
		clsBankClient Client = clsBankClient::Find(AccountNumber);

		return(!Client.IsEmpty());
	}

	static clsBankClient GetAddNewClientObject(string AccountNumber)
	{
		return clsBankClient(enMode::AddNew, "", "", "", "", AccountNumber, "", 0);
	}

	static	vector < clsBankClient> GetClintsList()
	{
		return _LoadClientDataFromFile();
	}

	static float GetToatalBalances()
	{
		vector<clsBankClient> vClient = clsBankClient::GetClintsList();

		double ToatalBalances = 0;

		for (clsBankClient C : vClient)
		{
			ToatalBalances += C.Accountbalance;
		}

		return ToatalBalances;
	}

	void Deposit(double Amount)
	{
		_Accountbalance += Amount;

		save();
	}

	bool Withdarw(double Amount)
	{
		if (Amount > _Accountbalance)
		{
			return false;
		}

		_Accountbalance -= Amount;

		save();
	}

	static double ShowTotalBalances()
	{
		vector<clsBankClient> vclient = clsBankClient::GetClintsList();

		double TotalBalances = 0; 

		for (clsBankClient client : vclient)
		{
			TotalBalances += client.Accountbalance;
		}

		return TotalBalances;
	}

	bool Transfer(float Amount, clsBankClient& DistnationClient,string Username)
	{
		if (Amount > Accountbalance)
		{
			return false; 
		}

		Withdarw(Amount); 

		DistnationClient.Deposit(Amount); 
		_TransLogRecord(Amount, DistnationClient, Username); 
		return true; 
	}

	static vector< stTransferLogReccord> GetTransferLogListRecord()
	{
		vector< stTransferLogReccord> vDataline; 


		fstream Myfile; 

		Myfile.open(TransFileRecord, ios::in); 

		if (Myfile.is_open())
		{
			string line = "";

			stTransferLogReccord Dataline;

			while (getline(Myfile, line))
			{
				 Dataline = _ConverTransferLogLineToRecord(line); 

				vDataline.push_back(Dataline); 
			}

			Myfile.close(); 
		}

		return vDataline; 
	}

	
};