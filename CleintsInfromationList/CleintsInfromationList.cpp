
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

const string Filename= "Clients.txt";

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


struct sClient
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
	bool MarkForDelete = false;
};


sClient ReadNewClient()
{
	sClient Client;

	cout << "Please Enter Account Number" << endl;
	getline(cin >> ws, Client.AccountNumber);

	cout << "Enter Pin Code: ";
	getline(cin, Client.PinCode);

	cout << "Enter Name: ";
	getline(cin, Client.Name);

	cout << "Enter Phone: ";
	getline(cin, Client.Phone);

	cout << "Enter Account Balance: ";
	cin >> Client.AccountBalance;

	return Client;
}

bool ClientExistbyAccountNumber(string Filename, string AccountNumber)
{
	vector <sClient> vClients;
	ifstream MyFile;
	MyFile.open(Filename, ios::in);
	if (MyFile.is_open())
	{
		sClient Client;
		string Line;
		while (getline(MyFile, Line))
		{
			Client = ConvertLineRecordToClient(Line);

			if (Client.AccountNumber == AccountNumber)
			{
				MyFile.close();
				return true;
			}

			vClients.push_back(Client);
		}

		MyFile.close();

	}


	return false;
}

string ConvertClientToLineRecord(sClient Client, string Separator = "<<")
{
	string LineRecord;
	LineRecord += Client.AccountNumber + Separator;
	LineRecord += Client.PinCode + Separator;
	LineRecord += Client.Name + Separator;
	LineRecord += Client.Phone + Separator;
	LineRecord += to_string(Client.AccountBalance);
	return LineRecord;
}

sClient ConvertLineRecordToClient(string LineRecord, string Separator = "<<")
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

void PrintClient(sClient Client)
{
		cout << "The following is the extracted Client record \n"
		cout << "\n Account Number  :" << Client.AccountNumber;
		cout << "\n PinCode         :" << Client.PinCode;
		cout << "\n Name            :" << Client.Name;
		cout << "\n Phone Number    :" << Client.Phone;
		cout << "\n Account Balance :" << Client.AccountBalance;
}

void ClientsDataToFileName(string FileName, string Dtaline)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out | ios::app); // Open the file in append mode

	if(MyFile.is_open())
	{
		MyFile << Dtaline << endl; // Write the data line to the file
		MyFile.close(); // Close the file
	}
}

void AddClient()
{
	sClient Client = ReadNewClient();
	string LineRecord = ConvertClientToLineRecord(Client);
	ClientsDataToFileName(Filename, LineRecord);
	cout << "\nClient Added Successfully\n";
}

void AddNewClients()
{
	char AddMore = 'Y';
	do
	{
		cout << "\n\n";
		AddClient();
		cout << "\n\nDo you want to add more clients? Y/N? ";
		cin >> AddMore;
	} while (toupper(AddMore) == 'Y');
}

sClient ReadNewClient()
{
	sClient Client; 

	cout << "Please Enter Account Number" << endl;
	getline(cin >> ws, Client.AccountNumber);

	while (ClientExistbyAccountNumber(Client.AccountNumber, Filename))
	{
		cout << "Client with Account Number [" << (Client.AccountNumber) 
			<< " ]Already Exixt, Enter Another account number" << endl;
		getline(cin >> ws , Client.AccountNumber);
	}

	ReadClientInformation();

	return Client; 

}

vector<sClient> LoadClientsFromFile(string FileName)
{
	vector<sClient> vClients; 
	fstream MyFile;
	MyFile.open(FileName, ios::in);

	if (MyFile.is_open())
	{
		string LineRecord;
		sClient Client;

;
		while (getline(MyFile, LineRecord))
		{
			 Client = ConvertLineRecordToClient(LineRecord);

			vClients.push_back(Client);
		}
		MyFile.close();
	}
	return vClients;
}

void PrintAllClients()
{
	vector<sClient> vClients = LoadClientsFromFile(Filename);

	cout << "\n\t\t\t\t\t\tClient List (" << vClients.size() << ")\n";
	cout << "=====================================================================================================\n";
	cout << "| " << left << setw(15) << "Account Number";
	cout << "| " << left << setw(10) << "Pin Code";
	cout << "| " << left << setw(25) << "Name";
	cout << "| " << left << setw(15) << "Phone";
	cout << "| " << left << setw(15) << "Account Balance";
	cout << "\n=====================================================================================================\n";



	if (vClients.size() == 0)
	{
		cout << "\t\t\t No Clients Avialable in the system!";
	}
	else
	{
		for (sClient Client : vClients)
		{
			PrintClient(Client);
			cout << endl;
		}
	}

	cout << "=====================================================================================================\n";
}


bool FindClientbyAccountNumber(string AccountNumber, vector <sClient> vClients,sClient& Clinet)
{
	 vClients = LoadClientsFromFile(Filename);

	for (sClient Client1 : vClients)
	{
		if(Client1.AccountNumber == AccountNumber)
		{
			Clinet = Client1;
			return true;
		}
	}


	return false;
}

string ReadAccountNumber()
{
	string AccountNumber;
	cout << "Enter Account Number: ";
	getline(cin >> ws, AccountNumber);
	return AccountNumber;
}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector <sClient> &vClients)
{
	vClients = LoadClientsFromFile(Filename);

	for (sClient& Client1 : vClients)
	{
		if (Client1.AccountNumber == AccountNumber)
		{
			Client1.MarkForDelete = true;
			return true;
		}
	}
	return false;
}

vector <sClient> SaveClientsDataToFile(string FileName, vector <sClient> &vClients)
{
	ofstream MyFile;
	MyFile.open(FileName, ios::out); // Open the file in overwrite mode
	
	string LineRecord;
	
	if (MyFile.is_open())
	{
		

		for (sClient Client : vClients)
		{
			if (Client.MarkForDelete == false)
			{
				 LineRecord = ConvertClientToLineRecord(Client);
				MyFile << LineRecord << endl; // Write the data line to the file
			}
		}
		MyFile.close(); // Close the file
	}
	else
	{
		cout << "Error opening file!" << endl;
	}
	return vClients;
}

bool DeleteClientByAccountNumber(string AccountNumber, vector <sClient> vClients)
{
	sClient Client1;

	char Confirm = 'N';

	if (FindClientbyAccountNumber(AccountNumber, vClients, Client1))
	{
		PrintClient(Client1);
		cout << "\nAre you sure you want to delete this client? Y/N? ";
		cin >> Confirm;
		if (Confirm == 'Y' || Confirm == 'y')
		{
			MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
			SaveClientsDataToFile(Filename, vClients);

			//Reload the clients from the file

			vClients = LoadClientsFromFile(Filename);

			cout << "\nClient Deleted Successfully\n";

			return true;
		}
	}
	else
	{

		cout << "Client with Account Number (" << AccountNumber << ") Not Found!\n";
		return false;
	}
}

sClient ChangeClientRecord(string AccountNumber)
{
	sClient Client; 

	Client.AccountNumber = AccountNumber; 

	cout << "Enter Pin Code: ";
	getline(cin >> ws, Client.PinCode);

	cout << "Enter Name: ";
	getline(cin, Client.Name);

	cout << "Enter Phone: ";
	getline(cin, Client.Phone);

	cout << "Enter Account Balance: ";
	cin >> Client.AccountBalance;

	return Client;
}

bool UpdateClientData(string AccountNumber, vector <sClient> vClients)
{
	sClient Client; 

	char Answer = 'n';

	if (FindClientbyAccountNumber(AccountNumber, vClients, Client))
	{
		PrintClient(Client);

		cout << "Do you ure you want to update this Client Data (Y/N) ?" << endl;
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y')
		{
			for (sClient &Client1 : vClients)
			{
				if (Client1.AccountNumber == AccountNumber)
				{
					Client1 = ChangeClientRecord(AccountNumber); 
					break; 
				}
			}

			SaveClientsDataToFile(Filename, vClients);
			cout << "\nClient Updated Successfully\n";

			return true;
		}



	}
	else
	{

		cout << "Client with Account Number (" << AccountNumber << ") Not Found!\n";
		return false;
	}


}

void ShowAddClients()
{
	cout << "\n------------------------------\n";
	cout << "\tUpdate Client Info Screen\n";
	cout << "------------------------------\n";

	AddNewClients();
}

void ClientList()
{
	// Load all clients from the file
	vector<sClient> vClients = LoadClientsFromFile(Filename);

	// Print the header and table title
	cout << "\n\t\t\t\t\t\tClient List (" << vClients.size() << ") Client(s)\n";
	cout << "=====================================================================================================\n";
	cout << "| " << left << setw(15) << "Account Number";
	cout << "| " << left << setw(10) << "Pin Code";
	cout << "| " << left << setw(25) << "Name";
	cout << "| " << left << setw(15) << "Phone";
	cout << "| " << left << setw(15) << "Account Balance";
	cout << "\n=====================================================================================================\n";

	// Check if there are any clients
	if (vClients.size() == 0)
	{
		// Display message if no clients found
		cout << "\t\t\t\tNo Clients Available In the System!\n";
	}
	else
	{
		// Loop through each client and print their information
		for (sClient Client : vClients)
		{
			// Print one client record in table row format
			cout << "| " << left << setw(15) << Client.AccountNumber;
			cout << "| " << left << setw(10) << Client.PinCode;
			cout << "| " << left << setw(25) << Client.Name;
			cout << "| " << left << setw(15) << Client.Phone;
			cout << "| " << left << setw(15) << fixed << setprecision(2) << Client.AccountBalance;
			cout << endl;
		}
	}

	// Print the table footer
	cout << "=====================================================================================================\n";
}







int main()
{


	if (ClientExistbyAccountNumber("clients.txt", "12345"))
		cout << "Client found!" << endl;
	else
		cout << "Client not found!" << endl;
	



	return 0;
} 

