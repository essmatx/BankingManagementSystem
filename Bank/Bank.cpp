#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

const string Filename = "Clients.txt";
const string UserFilename = "Users.txt";


struct sClient
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
	bool MarkForDelete = false;
};

struct stUsers
{
	string Username;
	string Password;
	int Permission;
	bool Markfordelet;

};


enum eMainMenueOptions
{
	eListClients = 1, eAddNewClients = 2,
	eDeletClient = 3, eUpdateClient = 4,
	eFindClient = 5, eTransactions = 6,
	ManageUsers= 7 , Logout = 8
};

enum enTransactionMeneOption
{
	Deposit = 1, Withdraw = 2, Totalblance = 3, ReturnToMainmenue = 4
};

enum enManageUsersMenueOptions
{ 
	ListUsers = 1, Addusers = 2, DelteUsers = 3, Upbdateusers = 4, Findusers = 5, ToMainmenue = 6
};

enum  enMainMenuePermission 
{ 
	All = -1, PListClients = 1, pAddClinet = 2, pDeleteClient = 4, pUpbdateClient = 8, pFindClient = 16, pTransactions = 32, pManageUsers = 64
};





void ShowTransactionsMenu();
short ReadTransactionMainMenu();
void PerformTransactionsMainMenueOption(enTransactionMeneOption Options);
void ShowDepositScreen();
void ShowWithdrawScreen();
void ShowTotalBalances();
void GoBeckToTranscationMenu();
void ShowMainMenu();
void GoBackToMainMenue();
short ReadMainMenu();
void PerformMainMenueOption(eMainMenueOptions MenueOptions);
void ShowAllusersScreen();
void ShowListUserScreen();
void ShowAddNewUserScreen();
void ShowDeleteUserScreen();
void ShowUpbdateUserScreen();
void ShowFindUserScreen();



stUsers CurrentUser;
void ShowMainMenu(); 
void ShowTransactionsMenu();
void ShowManageMenue(); 
bool CheckAccessPermission(enMainMenuePermission Permission); 
bool FindUserbyUsernameandPassword(string Username, string Password, stUsers& user);
void Login(); 



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

sClient ConvertLineToRecord(string LineRecord, string Separator = "<<")
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

stUsers ConvertUsersLineToRecord(string Line, string Saperator = "<<")
{
	stUsers Users;
	vector <string> vUsers;

	vUsers = SplitString(Line, Saperator);

	Users.Username = vUsers[0];

	Users.Password = vUsers[1];

	Users.Permission = stoi(vUsers[2]);

	return Users;
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

string ConvertUsersRecordToLine(stUsers Users, string Saperator = "<<")
{
	string UsersRecord = "";

	UsersRecord += Users.Username + Saperator;

	UsersRecord += Users.Password + Saperator;

	UsersRecord += to_string(Users.Permission);

	return UsersRecord;

}

int ReadPermissions()
{
	int Permissions = 0;

	char Answer = 'n';

	cout << " Do you want to give full Access  Y/N ? ";
	cin >> Answer;

	if (Answer == 'Y' || Answer == 'y')
	{
		return -1;
	}

	cout << "Do you want to give access to : \n ";
	cout << "\n Show Client List Y/N ? ";
	cin >> Answer;
	if (Answer == 'Y' || Answer == 'y')
	{
		 Permissions += enMainMenuePermission::PListClients;
	}

	cout << "\nAdd New Client Y/N ?";
	cin >> Answer;

	if (Answer == 'Y' || Answer == 'y')
	{
		Permissions += enMainMenuePermission::pAddClinet;
	}

	cout << "\nDelete Clinet Y/N ? ";
	cin >> Answer;
	if (Answer == 'Y' || Answer == 'y')
	{
		Permissions += enMainMenuePermission::pDeleteClient;
	}

	cout << "\nUpbdate Clinet Y/N ? ";
	cin >> Answer;
	if (Answer == 'Y' || Answer == 'y')
	{
		 Permissions += enMainMenuePermission::pUpbdateClient;
	}

	cout << "\nFind Client Y/N ?";
	cin >> Answer;
	if (Answer == 'Y' || Answer == 'y')
	{
		 Permissions += enMainMenuePermission::pFindClient;
	}

	cout << "\nShow Transactions Y/N ?";
	cin >> Answer;
	if (Answer == 'Y' || Answer == 'y')
	{
		 Permissions += enMainMenuePermission::pTransactions;
	}

	cout << "\nManage Users Y/N ?";
	cin >> Answer;
	if (Answer == 'Y' || Answer == 'y')
	{
		 Permissions += enMainMenuePermission::pManageUsers;
	}


	return Permissions;
}

bool CheckAccessPermission(enMainMenuePermission Permission)
{
	if (CurrentUser.Permission == enMainMenuePermission::All)
	{
		return true;
	}

	if ((Permission & CurrentUser.Permission) == Permission)
	{
		return true;
	}

	else
		return false; 
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

vector <stUsers> LoadUaersDataFromFile(string FileName)
{
	vector <stUsers> vUsers;
	fstream Myfile;
	Myfile.open(FileName, ios::in);

	if (Myfile.is_open())
	{
		string Line;
		stUsers user;

		while (getline(Myfile, Line))
		{
			user = ConvertUsersLineToRecord(Line);

			vUsers.push_back(user);
		}

		Myfile.close();
	}

	return vUsers;
}

bool LoadUserInfo(string Username, string Password)
{
	if (FindUserbyUsernameandPassword(Username, Password, CurrentUser))
	{
		return true;
	}
	else
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

vector <stUsers> SaveUserDatatoFile(string Filename, vector <stUsers> vuser)
{
	fstream Myfile;
	Myfile.open(Filename, ios::out);

	string Dataline;

	if (Myfile.is_open())
	{

		for (stUsers& user : vuser)
		{
			if (user.Markfordelet == false)
			{
				Dataline = ConvertUsersRecordToLine(user);
				Myfile << Dataline << endl;
			}
		}

		Myfile.close();
	}

	return vuser;
}

void AddDataLineToFile(string FileName, string Dtaline)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out | ios::app); // Open the file in append mode

	if (MyFile.is_open())
	{
		MyFile << Dtaline << endl; // Write the data line to the file
		MyFile.close(); // Close the file
	}
}



bool ClientExistbyAccountNumber(string Filename, string AccountNumber)
{
	vector <sClient> vClients;
	fstream MyFile;
	MyFile.open(Filename, ios::in);


	if (MyFile.is_open())
	{
		string Line;
		sClient Client;
		
		while (getline(MyFile, Line))
		{
			Client = ConvertLineToRecord(Line);
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

bool UserExsistByUsserName(string Username, string Filename)
{
	fstream Myfile;
	Myfile.open(Filename, ios::in);
	if (Myfile.is_open())
	{
		string line;
		stUsers user;

		while (getline(Myfile, line))
		{
			user = ConvertUsersLineToRecord(line);
			if (user.Username == Username)
			{
				Myfile.close();
				return true;
			}
		}

		Myfile.close();
	}

	return false;
}

bool FindClientByAccountNumber(string AccountNumber, vector <sClient> vClient, sClient& Clinet)
{
	vector <sClient> vClients = LoadClientsDtatFromFile(Filename);

	for (sClient Client1 : vClients)
	{
		if (Client1.AccountNumber == AccountNumber)
		{
			Clinet = Client1;
			return true;
		}
	}


	return false;
}

bool FindUserByUsername(string Username, vector<stUsers> vUser, stUsers& user)
{
	for (stUsers U : vUser)
	{
		if (U.Username == Username)
		{
			user = U;

			return true;
		}
	}

	return false;
}

bool FindUserbyUsernameandPassword(string Username, string Password, stUsers& user)
{
	vector <stUsers> vuser = LoadUaersDataFromFile(UserFilename);

	for (stUsers U : vuser)
	{
		if (U.Username == Username && U.Password == Password)
		{
			user = U;
			return true;
		}
	}

	return false;
}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{
	vClients = LoadClientsDtatFromFile(Filename);

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

bool MarkUserforDeleteBUsername(string Username, vector <stUsers>& vuser)
{
	for (stUsers& user : vuser)
	{
		if (user.Username == Username)
		{
			user.Markfordelet = true;

			return true;
		}
	}
	return false;
}


string ReadClientAccountNumber()
{
	string AccountNumber = " ";

	cout << "Enter Account Number: ";
	cin >> AccountNumber;


	return AccountNumber;
}

sClient ReadNewClient()
	{
		sClient Client;

		// Get Account Number with validation
		cout << "Please Enter Account Number: ";


		getline(cin >> ws, Client.AccountNumber);

		if (ClientExistbyAccountNumber(Filename,Client.AccountNumber)) // Fixed function name
		{
			cout << "Client with Account Number [" << Client.AccountNumber<< "] Already Exists, Enter Another Account Number: ";
			getline(cin >> ws, Client.AccountNumber);
		}

		// Get other client information
		cout << "Enter Pin Code: ";
		getline(cin >> ws, Client.PinCode);

		cout << "Enter Name: ";
		getline(cin, Client.Name);

		cout << "Enter Phone: ";
		getline(cin, Client.Phone);

		cout << "Enter Account Balance: ";
		cin >> Client.AccountBalance;
		cin.ignore(); // ? FIX: Clear the input buffer after cin

		return Client;
	}

stUsers ReadNewUser()
{
	stUsers user;

	cout << " Enter user name ? ";
	getline(cin >> ws, user.Username);

	while (UserExsistByUsserName(user.Username, UserFilename))
	{
		cout << "User with [" << user.Username << "] already exists  enter another username ? ";
		getline(cin >> ws, user.Username);
	}

	cout << "Enter passweord";
	getline(cin, user.Password);

	user.Permission = ReadPermissions();

	return user;
}

string ReadUsername()
{
	string Username = "";
	cout << "\nPlease enter Username !";
	cin >> Username;
	return Username;
}

sClient ChangeClientRecord(string AccountNumber)
{
	sClient Client;

	Client.AccountNumber = AccountNumber;

	cout << " Enter Pin Code ?";
	getline(cin >> ws, Client.PinCode);

	cout << " Enter Name ?";
	getline(cin, Client.Name);

	cout << " Enter Phone Number ?";
	getline(cin, Client.Phone);

	cout << " Enter Account Balance";
	cin >> Client.AccountBalance;

	return Client;
}

stUsers ChangUserRecord(string Username)
{
	stUsers user;

	user.Username = Username;

	cout << "\n\nEnter Password?:";
	getline(cin >> ws, user.Password);

	user.Permission = ReadPermissions();

	return user;
}



void PrintClientRecord(sClient Client)
{
	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(10) << left << Client.PinCode;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.Phone;
	cout << "| " << setw(12) << left << Client.AccountBalance;
}

void PrintUserRecordLine(stUsers user)
{
	cout << "| " << setw(40) << left << user.Username;
	cout << "| " << setw(15) << left << user.Password;
	cout << "| " << setw(17) << left << user.Permission;
}

void PrintClientCard(sClient Client)
{
	cout << "The following are the Client details \n";
	cout << "\n Account Number  :" << Client.AccountNumber;
	cout << "\n PinCode         :" << Client.PinCode;
	cout << "\n Name            :" << Client.Name;
	cout << "\n Phone Number    :" << Client.Phone;
	cout << "\n Account Balance :" << Client.AccountBalance;
}

void PrintUsersCard(stUsers user)
{
	cout << "\nthe folowing are the user detailes:\n";
	cout << "________________________________________";
	cout << "\nUsername     :" << user.Username;
	cout << "\nPassword		:" << user.Password;
	cout << "\nPermissions  :" << user.Permission;
	cout << "\n-------------------------------------\n";
}



void AddNewClient()
{
	sClient Client;

	Client = ReadNewClient();

	AddDataLineToFile(Filename, ConvertRecordToLine(Client));

}

void AddNewUser()
{
	stUsers user;

	user = ReadNewUser();

	AddDataLineToFile(UserFilename, ConvertUsersRecordToLine(user));

}

void AddNewClients()
{

	char AddMore = 'Y';
	do
	{
		system("cls"); 
		cout << "Adding New Client:\n\n ";

		AddNewClient();
		cout << "\nClient Added Successfully, do you want to addmore clients ? Y / N ? ";
		cin >> AddMore;

	} while (toupper(AddMore) == 'Y');
}

void AddNewUsers()
{
	char AddMore = 'Y';
	do
	{
		cout << "\nAdding a new user: \n\n";
		AddNewUser();

		cout << "\nUser added successfully, do you want to add more users again Y/N ?:";
		cin >> AddMore;
	} while (toupper(AddMore) == 'Y');
}


bool DeleteClientByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{
	sClient Client1;

	char Confirm = 'N';

	if (FindClientByAccountNumber(AccountNumber, vClients, Client1))
	{
		PrintClientCard(Client1);
		cout << "\nAre you sure you want to delete this client? Y/N? ";
		cin >> Confirm;
		if (Confirm == 'Y' || Confirm == 'y')
		{
			MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
			SaveClientsDataToFile(Filename, vClients);

			//Reload the clients from the file

			vClients = LoadClientsDtatFromFile(Filename);

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

bool DeleteUserbyUsername(string Username, vector <stUsers>& vusers)
{
	if (Username == "Admin")
	{
		cout << "\nyou cannot delete this user ";
		return false;
	}

	char Answer = 'n';
	stUsers user;

	if (FindUserByUsername(Username, vusers, user))
	{
		PrintUsersCard(user);

		cout << "\n\nAre you sure you wanna delete this user Y/N";
		cin >> Answer;

		if (Answer == 'Y' || Answer == 'y')
		{
			MarkUserforDeleteBUsername(Username, vusers);

			SaveUserDatatoFile(UserFilename, vusers);

			vusers = LoadUaersDataFromFile(UserFilename);

			cout << "\n\nUser has been deleted successfully ";
			return true;
		}
	}
	else
	{
		cout << "\nUser with username[" << Username << "] is not found!";
		return false;
	}
}

bool UpdateClientByAccountNumber(string AccountNumber, vector <sClient> & vClients)
{
	sClient Client;

	char Answer = 'n';

	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		PrintClientCard(Client);

		cout << "Do you ure you want to update this Client Data (Y/N) ?" << endl;
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y')
		{
			for (sClient& Client1 : vClients)
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

bool UpdateUserbyUsername(string Username, vector <stUsers>& vusers)
{
	char Answer = 'n';
	stUsers user;

	if (FindUserByUsername(Username, vusers, user))
	{
		PrintUsersCard(user);
		cout << "\n\n Are you sure you wanna upbdate this user Y/N ?";
		cin >> Answer;



		if (Answer == 'Y' || Answer == 'y')
		{
			for (stUsers& U : vusers)
			{
				if (U.Username == Username)
				{
					U = ChangUserRecord(Username);
					break;
				}
			}

			SaveUserDatatoFile(UserFilename, vusers);

			cout << "\n The User has been Upbdated successfully ";
			return true;
		}
	}
	else
	{
		cout << "\nUser with Account Number [" << Username << "] is not found ";
		return false;
	}
}

void AccessDeniedMessage()
{
	cout << "\n---------------------------------------------------------------------------------\n";
	cout << "Access Denied , you doin't have Permission to do this, please contact your admin ";
	cout << "\n----------------------------------------------------------------------------------\n";
}



void ShowAllClientsScreen()
{
	vector<sClient> vClient = LoadClientsDtatFromFile(Filename);
	// Print the header and table title
	cout << "\n\t\t\t\t\t\tClient List (" << vClient.size() << ") Client(s)\n";
	cout << "=====================================================================================================\n";
	cout << "| " << left << setw(15) << "Account Number";
	cout << "| " << left << setw(10) << "Pin Code";
	cout << "| " << left << setw(40) << "Name";
	cout << "| " << left << setw(12) << "Phone";
	cout << "| " << left << setw(12) << "Account Balance";
	cout << "\n=====================================================================================================\n";


	for (sClient Client : vClient)
	{
		PrintClientRecord(Client);
		cout << endl;
	}

	cout <<
		"\n=====================================================================================================\n";
}

void ShowAddScerrn()
{
	cout << "\n----------------------------------------------\n";

	cout << "\t Add    Clients   Screen";

	cout << "\n----------------------------------------------\n";

	AddNewClients();
}

void ShowDeletCLientScreen()
{
	cout << "\n----------------------------------------------\n";

	cout << "\t Delet    Clients   Screen";

	cout << "\n----------------------------------------------\n";

	vector <sClient> Client = LoadClientsDtatFromFile(Filename);

	string AccountNumber = ReadClientAccountNumber();

	DeleteClientByAccountNumber(AccountNumber, Client);
}

void ShowUpdateClientScreen()
{
	cout << "\n----------------------------------------------\n";

	cout << "\t Update    Clients   Screen";

	cout << "\n----------------------------------------------\n";

	vector <sClient> vClient = LoadClientsDtatFromFile(Filename);

	string AccountNumber = ReadClientAccountNumber();

	UpdateClientByAccountNumber(AccountNumber, vClient);

}

void ShowFindClientScreen()
{
	cout << "\n----------------------------------------------\n";

	cout << "\t Find    Clients   Screen";

	cout << "\n----------------------------------------------\n";

	vector <sClient> vClient = LoadClientsDtatFromFile(Filename);

	string AccountNumber = ReadClientAccountNumber();

	sClient Client;

	if (FindClientByAccountNumber(AccountNumber, vClient, Client))
	{
		PrintClientCard(Client);
	}
	else
	{
		cout << "Client With Account Number [" << AccountNumber << "] is not found! ";
	}
}

void ShowEndScreen()
{
	cout << "\n----------------------------------------------\n";

	cout << "\t Program    Ends   :-)";

	cout << "\n----------------------------------------------\n";

}

void ShowAllusersScreen()
{
	vector <stUsers> vuser = LoadUaersDataFromFile(UserFilename);

	cout << "\t\t\t\t\tUsers List (" << vuser.size() << ") User(s)";


	cout << "\n==============================================================\n\n";
	cout << "| " << left << setw(40) << "Username";
	cout << "| " << left << setw(15) << "Password";
	cout << "| " << left << setw(17) << "Permission";
	cout << "\n========================================================================\n";

	if (vuser.size() == 0)
	{
		cout << "\t\t\tNo users availabal in the system ";
	}
	else
	{
		for (stUsers user : vuser)
		{
			PrintUserRecordLine(user);
			cout << endl;
		}
	}

	cout << "\n===========================================================================\n";

}

void ShowListUserScreen()
{
	ShowAllusersScreen();
}

void ShowAddNewUserScreen()
{
	cout << "\n--------------------------------------------\n";
	cout << "\tAdd New User Screen";
	cout << "\n-------------------------------------------=\n";

	AddNewUsers();
}

void ShowDeleteUserScreen()
{
	cout << "\n--------------------------------------------\n";
	cout << "\tDelete User Screen";
	cout << "\n-------------------------------------------=\n";

	vector <stUsers> Vusers = LoadUaersDataFromFile(UserFilename);

	string Username = ReadUsername();

	DeleteUserbyUsername(Username, Vusers);
}

void ShowUpbdateUserScreen()
{
	cout << "\n--------------------------------------------\n";
	cout << "\tUpdate User Screen";
	cout << "\n--------------------------------------------\n";


	vector <stUsers> vUser = LoadUaersDataFromFile(UserFilename);
	string Username = ReadUsername();

	UpdateUserbyUsername(Username, vUser);

}

void ShowFindUserScreen() 
{
	cout << "\n--------------------------------------------\n";
	cout << "\tFind User Screen";
	cout << "\n--------------------------------------------\n";

	vector <stUsers> vuser = LoadUaersDataFromFile(UserFilename);

	string Username = ReadUsername();

	stUsers user;

	if (FindUserByUsername(Username, vuser, user))
	{
		PrintUsersCard(user);
	}
	else
	{
		cout << "User With username [" << Username << "] is not found! ";
	}
}

short ReadManageUsersMenueOp()
{
	short Choice = 0;

	cout << "\n chose what do you want from 1 to 6 !";
	cin >> Choice;

	return Choice;
}






short ReadMainMenu()
{


	cout << "Chooce what do you wnat to do [1 to 8] ? " << endl;
	short Choice = 0;
	cin >> Choice;

	return Choice;
}

void PerformMainMenueOption(eMainMenueOptions MenueOptions)
{
	switch (MenueOptions)
	{
	case eMainMenueOptions::eListClients:

		system("cls");
		ShowAllClientsScreen();
		GoBackToMainMenue();
		break;
	case eMainMenueOptions::eAddNewClients:
		system("cls");
		ShowAddScerrn();
		GoBackToMainMenue();
		break;
	case eMainMenueOptions::eDeletClient:
		system("cls");
		ShowDeletCLientScreen();
		GoBackToMainMenue();;
		break;

	case eMainMenueOptions::eUpdateClient:
		system("cls");
		ShowUpdateClientScreen();
		GoBackToMainMenue();;
		break;

	case eMainMenueOptions::eFindClient:
		system("cls");
		ShowFindClientScreen();
		GoBackToMainMenue();;
		break;

	case eMainMenueOptions ::eTransactions:
		system("cls");
		ShowTransactionsMenu();
		break;

	case eMainMenueOptions::ManageUsers:
		system("cls"); 
		ShowManageMenue();
		break;

	case eMainMenueOptions ::Logout:
		system("cls");
		ShowEndScreen();
		return; 
	}
}

void GoBackToMainMenue()
{
	cout << "press any key to main menue ";
	system("pause>0");
	ShowMainMenu();
}

void GobacktoManageUsersMenue()
{
	cout << "\n\n Press any key to go back to transaction menue..."; 
	system("pause>0");
	ShowManageMenue();
	 
}

void ShowMainMenu()
{
	system("cls"); // Use "clear" for Linux/macOS

	cout << "============================================\n";
	cout << "\t\tMain Menu Screen\n";
	cout << "============================================\n";
	cout << "\t[1] Show Client List.\n";
	cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Delete Client.\n";
	cout << "\t[4] Update Client Info.\n";
	cout << "\t[5] Find Client.\n";
	cout << "\t[6] Transactions.\n";
	cout << "\t[7] Manage Users\n";
	cout << "\t[8] Logout\n";
	cout << "============================================\n";

	PerformMainMenueOption((eMainMenueOptions)ReadMainMenu());
}




void ShowTransactionsMenu()
{
	system("cls"); // Use "clear" for Linux/macOS

	cout << "============================================\n";
	cout << "\t\tTransactions Menu Screen\n";
	cout << "============================================\n";
	cout << "\t[1] Deposit.\n";
	cout << "\t[2] Withdraw.\n";
	cout << "\t[3] Total Balances.\n";
	cout << "\t[4] Main Menu.\n";
	cout << "============================================\n";

	PerformTransactionsMainMenueOption((enTransactionMeneOption)ReadTransactionMainMenu());
}

bool DepositBalanceToClientByAccountNumber(string AccountNumber, double Amount, vector <sClient> vClient)
{

	char Aprove; 

	cout << " Are you sure you want to Aprove this transaction [Y/N] ? " << endl;
	cin >> Aprove;

	if (Aprove == 'Y' || Aprove == 'y')
	{
		for (sClient &Client : vClient)
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

void ShowDepositScreen()
{
	cout << "\n----------------------------------------------\n";

	cout << "\t Deposit  Screen";

	cout << "\n----------------------------------------------\n";

	vector <sClient> vClient = LoadClientsDtatFromFile(Filename);

	string AccountNumber = ReadClientAccountNumber();

	sClient Client;

	while (!FindClientByAccountNumber(AccountNumber, vClient, Client))
	{
		cout << "Client With Account Number [" << AccountNumber << "] is not found! ";
		AccountNumber = ReadClientAccountNumber();
	}

	
	PrintClientCard(Client);


	double Amount = 0; 
	cout << "Please enter deposit amount !" << endl; 
	cin >> Amount;

	DepositBalanceToClientByAccountNumber(AccountNumber, Amount, vClient);
}

void ShowWithdrawScreen()
{

	cout << "\n----------------------------------------------\n";

	cout << "\t Withdraw  Screen";

	cout << "\n----------------------------------------------\n";

	vector <sClient> vClient = LoadClientsDtatFromFile(Filename);

	string AccountNumber = ReadClientAccountNumber();

	sClient Client;

	if (FindClientByAccountNumber(AccountNumber, vClient, Client))
	{
		PrintClientCard(Client);
	}
	else
	{
		cout << "Client With Account Number [" << AccountNumber << "] is not found! ";
		AccountNumber = ReadClientAccountNumber();
	}

	PrintClientCard(Client);

	double Amount = 0;
	cout << "Please enter withdraw  amount !" << endl;
	cin >> Amount;

	while (Amount > Client.AccountBalance)
	{
		cout << "Amount Exceeds the balance ,you can withdraw up to" << Client.AccountBalance << endl;

		cout << " Please enter another amount";
		cin >> Amount; 
	}

	DepositBalanceToClientByAccountNumber(AccountNumber, Amount * -1, vClient);
}

void ShowTotalBalances()
{
	
	vector<sClient> vClient = LoadClientsDtatFromFile(Filename);

	cout << "\n\t\t\t\t\tBalances List (" << vClient.size() << ") Client(s)\n";
	cout << "=======================================================================\n";
	cout << "| " << left << setw(15) << "Account Number";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << right << setw(12) << "Balance";
	cout << "\n=======================================================================\n";

	double TotalBalance = 0;

	if (vClient.size() == 0)
	{
		cout << "\t\t\tNo Clients Available in the system\n";
	}
	else
	{
		for (sClient Client : vClient)
		{
			cout << "| " << left << setw(15) << Client.AccountNumber;
			cout << "| " << left << setw(40) << Client.Name;
			cout << "| " << right << setw(12) << fixed << setprecision(2) << Client.AccountBalance << endl;
			TotalBalance += Client.AccountBalance;
		}
	}

	cout << "=======================================================================\n";
	cout << "\t\t\tTotal Balances = " << fixed << setprecision(2) << TotalBalance << endl;
}

void GoBeckToTranscationMenu()
{
	cout << "press any key to main menue ";
	system("pause>0");
	ShowTransactionsMenu();
}

short ReadTransactionMainMenu()
{
	cout << "Chooce what do you wnat to do [1 to 4] ? " << endl;
	short Choice = 0;
	cin >> Choice;

	return Choice;
}

void PerformTransactionsMainMenueOption(enTransactionMeneOption Options)
{
	switch (Options)
	{
	case enTransactionMeneOption::Deposit:

		system("cls");
		ShowDepositScreen();
		GoBeckToTranscationMenu();
		break;

	case enTransactionMeneOption::Withdraw:
		system("cls");
		ShowWithdrawScreen();
		GoBeckToTranscationMenu();
		break;

	case enTransactionMeneOption::Totalblance:
		system("cls");
		ShowTotalBalances();
		GoBeckToTranscationMenu();
		break;

	case enTransactionMeneOption::ReturnToMainmenue:
		system("cls");
		ShowMainMenu();
		return;
	}


	
}

void PerformManageUsersMenueOp(enManageUsersMenueOptions ManageUsers)
{
	switch (ManageUsers)
	{
	case enManageUsersMenueOptions::ListUsers:
	{
		system("cls"); 
		ShowListUserScreen(); 
		GobacktoManageUsersMenue();
		break; 

	}
	case enManageUsersMenueOptions::Addusers:
	{
		system("cls"); 
		ShowAddNewUserScreen();
		GobacktoManageUsersMenue();
		break;
	}
	case enManageUsersMenueOptions::DelteUsers:
	{
		system("cls"); 
		ShowDeleteUserScreen(); 
		GobacktoManageUsersMenue();
		break; 
	}
	case enManageUsersMenueOptions::Upbdateusers: 
	{
		system("cls"); 
		ShowUpbdateUserScreen(); 
		GobacktoManageUsersMenue();
		break; 
	}
	case enManageUsersMenueOptions::Findusers:
	{
		system("cls"); 
		ShowFindUserScreen(); 
		GobacktoManageUsersMenue();
		break; 
	}
	case enManageUsersMenueOptions::ToMainmenue :
	{
	
		ShowMainMenu(); 
	}

	}
}

void ShowManageMenue()
{
	if (!CheckAccessPermission(enMainMenuePermission::pManageUsers))
	{
		AccessDeniedMessage();
		GoBackToMainMenue();
		return;
	}

	system("cls");
	cout << "===========================================================\n";
	cout << "\t\tManage Users Menue Screen\n ";
	cout << "===========================================================\n";
	cout << "\t[1] List Users.:\n";
	cout << "\t[2] Add New User.:\n";
	cout << "\t[3] Delete User.:\n";
	cout << "\t[4] Update User.:\n";
	cout << "\t[5] Find User.:\n";
	cout << "\t[6] Main Menue.:\n";
	cout << "===========================================================\n";

	PerformManageUsersMenueOp(
		(enManageUsersMenueOptions)ReadManageUsersMenueOp()); 
}

void Login()
{
	bool Loginfaild = false; 
	string username, password; 

	do
	{
		system("cls"); 
		cout << "\n------------------------------------------\n"; 
		cout << "\t Login Screen"; 
		cout << "\n------------------------------------------\n";

		if (Loginfaild)
		{
			cout << "Invalaid Username/Password:\n"; 
		}

		cout << "Enter Username ? "; 
		cin >> username; 

		cout << "Enter Passoword ? "; 
		cin >> password; 

		Loginfaild = !LoadUserInfo(username, password); 
	} while (Loginfaild); 

	ShowMainMenu(); 
}









int main()
{
	Login(); 
	//vector<stUsers>vuser; 
	 //SaveUserDatatoFile("Users.txt", vuser); 
	//AddDataLineToFile("Users.txt", "Admin<<1234<<-1"); 
	system("pause>0");

    return 0;
}

