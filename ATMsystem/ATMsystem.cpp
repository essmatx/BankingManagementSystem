#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;


struct sClient
{
    string Name; 
    string PinCode;
    string AccountNumber; 
    string Phone; 
    bool MarkForDelete = false;
    double AccountBalance; 
};

enum enMainMenueOp
{
    eQucikWithdraw = 1, eNormlaWithdrwa = 2, eDeposit = 3, eCheckBalance = 4, eExit = 5
};

const string Filename = "Clients.txt";

sClient CurrentClient; 

void Login(); 

void ShowDepositScreen(); 

void ShowCheckBalance(); 

void ShowNormalWithdrawScreen(); 

void ShowQuickWithdrawScreen(); 

void ShowMainMenueScree(); 


vector <string> SplitString(string str, string delim)
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

string ConvertRecordToLine(sClient Client, string Separator = "<<")
{
	string LineRecord;
	LineRecord += Client.AccountNumber + Separator;
	LineRecord += Client.PinCode + Separator;
	LineRecord += Client.Name + Separator;
	LineRecord += Client.Phone + Separator;
	LineRecord += to_string(Client.AccountBalance);
	return LineRecord;
}

sClient  ConvertLineToRecord(string LineRecord, string Separator = "<<")
{
	sClient Client;

	vector<string> vClient = SplitString(LineRecord, Separator);

	Client.AccountNumber = vClient[0];

	Client.PinCode = vClient[1];

	Client.Name = vClient[2];

	Client.Phone = vClient[3];

	Client.AccountBalance = stod(vClient[4]);

	return Client;
}

vector<sClient> LoadClientsDtatFromFile(string FileName)
{
	vector<sClient> vClients;
	fstream MyFile;
	MyFile.open(FileName, ios::in);

	if (MyFile.is_open())
	{
		string LineRecord;
		sClient Client;


		while (getline(MyFile, LineRecord))
		{
			Client = ConvertLineToRecord(LineRecord);

			vClients.push_back(Client);
		}

		MyFile.close();
	}


	return vClients;
}

bool FindClientByAccountNumberAndPincode(string AccountNumber, string Pincode, sClient& Clinet)
{
	vector <sClient> vClients = LoadClientsDtatFromFile(Filename); 

	for (sClient Client1 : vClients)
	{
		if (Client1.AccountNumber == AccountNumber && Client1.PinCode == Pincode)
		{
			Clinet = Client1;
			return true;
		}
	}


	return false;
}

vector <sClient> SaveClientsDataToFile(string FileName, vector <sClient> vClients)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out); // Open the file in overwrite mode

	string LineRecord;

	if (MyFile.is_open())
	{


		for (sClient Client : vClients)
		{
			if (Client.MarkForDelete == false)
			{
				LineRecord = ConvertRecordToLine(Client);
				MyFile << LineRecord << endl; // Write the data line to the file
			}
		}
		MyFile.close(); // Close the file
	}
	return vClients;
}

bool DepositBalanceToClientByAccountNumber(string AccountNumber, double Amount, vector <sClient> vClient)
{

	char Aprove;

	cout << " Are you sure you want to Aprove this transaction [Y/N] ? " << endl;
	cin >> Aprove;

	if (Aprove == 'Y' || Aprove == 'y')
	{
		for (sClient& Client : vClient)
		{
			if (Client.AccountNumber == AccountNumber)
			{
				Client.AccountBalance += Amount;
				SaveClientsDataToFile(Filename, vClient);

				cout << "The Amount Added Successfully New Balance is " << Client.AccountBalance;

				return true;
			}
		}

		return false;
	}


}

short ReadQuickWithdraw()
{
	short withdraw = 0; 

	cout << " Choose what do you want from 1 to 9 !"; 
	cin >> withdraw; 

	while (withdraw <= 0 || withdraw > 9)
	{
		 cout << " Choose what do you want from 1 to 9 !";
		 cin >> withdraw; 
	}

	return withdraw; 
}

short GetQuickWithdrawAmount(short WithdrawAmount)
{
	switch (WithdrawAmount)
	{
	case 1:
		return 20; 
		
	case 2:
		return 50;

	case 3 :
		return 100; 

	case 4 : 
		return 200; 

	case 5 : 
		return 400; 

	case 6 :
		return 600; 

	case 7: 
		return 800; 

	case 8:
		return 1000; 

	default:
		return 0; 
	}
}

void PerfromQuickWithdrawOp(short WithdrawOp)
{
	if (WithdrawOp == 9)
	{
		return; 
	}

	short WithdrawBalance = 0; 

	WithdrawBalance = GetQuickWithdrawAmount(WithdrawOp); 

	if (WithdrawBalance > CurrentClient.AccountBalance)
	{
		cout << " The amount exceeds your balance please make another choice\n "; 

		cout << " press any key to continue...."; 
		system("cls"); 
		ShowQuickWithdrawScreen(); 
		return; 
	}

	vector <sClient> vClient = LoadClientsDtatFromFile(Filename); 

	DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber, WithdrawBalance * -1, vClient);

	CurrentClient.AccountBalance -= WithdrawBalance; 

}

double ReadDepositAmount()
{
	double Amount = 0; 

	cout << " Please enter deposit amount "; 
	cin >> Amount; 

	while (Amount <= 0)
	{
		cout << " Please enter positive number !"; 
	}

	return Amount; 
}

void PerformDepositOp()
{
	double Depositamount = ReadDepositAmount(); 

	vector <sClient> vClient = LoadClientsDtatFromFile(Filename); 

	DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber, Depositamount, vClient); 

	CurrentClient.AccountBalance += Depositamount; 
	
}

void ShowDepositScreen()
{
	cout << "========================================\n";
	cout << "\t\tDepsoit Screen\n"; 
	cout << "=========================================\n";

	PerformDepositOp(); 

}

void ShowCheckBalance()
{
	cout << "=======================================\n";
	cout << "\t\tCheck Balance Screen\n"; 
	cout << "========================================\n"; 
	cout << " Your balance is :" << CurrentClient.AccountBalance << endl; 
}

int ReadWithdrawAmount()
{
	int Amount = 0; 

	cout << "Please enter an amount multiple 5's ? "; 
	cin >> Amount; 

	while (Amount % 5 != 0)
	{
		cout << "Please enter an amount multiple 5's ? ";
		cin >> Amount;
	}

	return Amount; 
}

void PerformNormalWithdrawOp()
{
	int Withdraw = ReadWithdrawAmount(); 

	if (Withdraw > CurrentClient.AccountBalance)
	{
		cout << " The amount  exceds your balance ! , Please try again \n"; 

		cout << "press any key to go back..."; 
		system("pause>0"); 

		ShowNormalWithdrawScreen();
	}

	vector <sClient> vCLient = LoadClientsDtatFromFile(Filename);

	DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber, Withdraw * -1, vCLient); 

	CurrentClient.AccountBalance -= Withdraw; 
}

void ShowNormalWithdrawScreen()
{
	system("cls"); 

	cout << "======================================\n";
	cout << "\t\t Normal Withdraw Screen\n"; 
	cout << "======================================\n"; 

	PerformNormalWithdrawOp(); 

}

void ShowQuickWithdrawScreen()
{
	system("cls"); 
	cout << "===================================\n";
	cout << "\t\tQuick Withdraw Screen\n"; 
	cout << "===================================\n"; 
	cout << "\t[1] 20\t\t[2] 50\n"; 
	cout << "\t[3] 100\t\t[4] 200\n"; 
	cout << "\t[5] 400\t\t[6] 600\n"; 
	cout << "\t[7] 800\t\t[8] 1000\n"; 
	cout << "\t[9] Exit\n"; 
	cout << " Your Balance is:" << CurrentClient.AccountBalance << endl; 
	PerfromQuickWithdrawOp(ReadQuickWithdraw()); 
}

void GobacktoMainMenue()
{
	cout << " Please press any key to get back to the main menue... !"; 
	system("pause>0"); 
	ShowMainMenueScree(); 
}

short ReadMainMenue()
{
	short choice = 0;

	cout << " Choose what do you wnat to do from 1 to 5";
	cin >> choice; 

	return choice; 
}

void PerformMainMenueOp(enMainMenueOp Mainmenueop)
{
	switch (Mainmenueop)
	{
	case enMainMenueOp::eQucikWithdraw:
		system("cls"); 
		ShowQuickWithdrawScreen(); 
		GobacktoMainMenue(); 
		break; 

	case enMainMenueOp::eNormlaWithdrwa:
		system("cls"); 
		ShowNormalWithdrawScreen();
		GobacktoMainMenue();
		break;

	case enMainMenueOp::eDeposit:
		system("cls"); 
		ShowDepositScreen(); 
		GobacktoMainMenue();
		break; 

	case enMainMenueOp::eCheckBalance :
		system("cls"); 
		ShowCheckBalance(); 
		GobacktoMainMenue();

	case enMainMenueOp::eExit :
		system("cls"); 
		Login();

		break; 

	}
}

void ShowMainMenueScree()
{
	cout << "========================================\n";
	cout << "\t\tATM Maine Menue\n";
	cout << "========================================\n";
	cout << "\t[1] QuicK WithDraw.\n";
	cout << "\t[2] Normal Withdraw.\n";
	cout << "\t[3] Deposit.\n";
	cout << "\t[4] Check Balance.\n";
	cout << "\t[5] Logout.\n";
	cout << "===========================================\n";

	PerformMainMenueOp((enMainMenueOp)ReadMainMenue());
}

bool LoadClientInfo(string AccountNumber, string Pincode)
{
	if (FindClientByAccountNumberAndPincode(AccountNumber, Pincode, CurrentClient))
	{
		return true;
	}
	else
		return false; 
}

void Login()
{
	bool Loginfaild = false; 
	
	string AccountNumber, Pincode; 

	do
	{
		cout << "================================\n"; 
		cout << "\t\tLogin Screen\n"; 
		cout << "================================\n"; 

		if (Loginfaild)
		{
			cout << "Invalaid Account Number/Pincode, Please try again\n"; 
		}
		cout << " Enter account number please ?"; 
		cin >> AccountNumber; 

		cout << " Please enter Pincode ";
		cin >> Pincode;

		Loginfaild = !LoadClientInfo(AccountNumber, Pincode); 

	} while (Loginfaild); 

		ShowMainMenueScree(); 
}

void InitClientsFile()
{
	fstream MyFile("Clients.txt", ios::out); // open for writing (will overwrite if exists)
	if (!MyFile)
	{
		cout << "Cannot create file!" << endl;
		return;
	}

	// Sample clients (AccountNumber<<PinCode<<Name<<Phone<<Balance)
	MyFile << "A600<<87496<<Mohammed<<25522555<<75000.000000\n";
	MyFile << "A200<<3456<<Amy Adam<<555-1002<<28500.000000\n";
	MyFile << "A180<<9012<<Alex Johnson<<555-1003<<1000.000000\n";
	MyFile << "A250<<5678<<Alice Brown<<555-1005<<2000.000000\n";
	MyFile << "A130<<74125<<Ahmad<<542255855<<65000.000000\n";
	MyFile << "A100<<1234<<Ali Ahmed<<01001234567<<5000.00\n";

	MyFile.close();
	cout << "Clients.txt initialized successfully!" << endl;
}

int main()
{
	InitClientsFile(); 

	//vector <sClient> vClient = LoadClientsDtatFromFile(Filename); 

	//for (sClient Client : vClient)
	//{
		//cout << Client.AccountNumber << " " << Client.PinCode << " " << Client.Name << " " 
			//<< Client.Phone << " " << Client.AccountBalance << endl; 
	//}

	Login();

	return 0; 
}
