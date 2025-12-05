#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

struct stUsers
{
	string Username; 
	string Password; 
	int Permission; 
	bool Markfordelet; 

};
 
enum enTransactionMeneOption {Deposit = 1, Withdraw = 2 , Totalblance = 3 , Mainmenue = 4};

enum enManageUsersMenueOptions { ListUsers = 1 , Addusers = 2 , DelteUsers = 3 , Upbdateusers = 4 , Findusers = 5 , Mainmenue = 6 };

enum  enMainMnueOptions {ShowClientlist = 1 , AddNewClient = 2, DeleteClient = 3, UpbdateClient = 4 , FindClient = 5 , Transactions = 6, Manageusers = 6 , Logout = 7};

enum  enMainMenuePermission {All = - 1 , PListClients = 1 , pAddClinet = 2 , pDeleteClient = 4 , pUpbdateClient = 8 , pFindClient = 16 , pTransactions = 32 , pManageUsers = 64 };

const string UserFilename = "Users.txt"; 

stUsers CurrentUser;

 
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

string ConvertUsersRecordToLine(stUsers Users, string Saperator = "<<")
{
	string UsersRecord = " ";

	UsersRecord += Users.Username + Saperator;

	UsersRecord += Users.Password + Saperator; 

	UsersRecord += to_string(Users.Permission); 

	return UsersRecord; 

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
	if (Answer == 'Y' || 'y')
	{
		return Permissions += enMainMenuePermission::PListClients; 
	}

	cout << "\nAdd New Client Y/N ?";
	cin >> Answer;

	if (Answer == 'Y' || Answer == 'y')
	{
		return Permissions += enMainMenuePermission::pAddClinet; 
	}

	cout << "\nDelete Clinet Y/N ? ";
	cin >> Answer; 
	if (Answer == 'Y' || Answer == 'y')
	{
		return Permissions += enMainMenuePermission::pDeleteClient; 
	}

	cout << "\nUpbdate Clinet Y/N ? "; 
	cin >> Answer; 
	if (Answer == 'Y' || Answer == 'y')
	{
		return Permissions += enMainMenuePermission::pUpbdateClient; 
	}

	cout << "\nFind Client Y/N ?"; 
	cin >> Answer; 
	if (Answer == 'Y' || Answer == 'y')
	{
		return Permissions += enMainMenuePermission::pFindClient; 
	}

	cout << "\nShow Transactions Y/N ?"; 
	cin >> Answer; 
	if (Answer == 'Y' || Answer == 'y')
	{
		return Permissions += enMainMenuePermission::pTransactions; 
	}

	cout << "\nManage Users Y/N ?";
	cin >> Answer; 
	if (Answer == 'Y' || Answer == 'y')
	{
		return Permissions += enMainMenuePermission::pManageUsers; 
	}
	

	return Permissions; 
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

void PrintUserRecordLine(stUsers user)
{
	cout << "|" << setw(15) << left << user.Username; 
	cout << "|" << setw(10) << left << user.Password;
	cout << "|" << setw(40) << left << user.Permission;
}

void AccessDeniedMessage()
{
	cout << "\n---------------------------------------------------------------------------------\n";
	cout << "Access Denied , you doin't have Permission to do this, please contact your admin ";
	cout << "\n----------------------------------------------------------------------------------\n";
}

void ShowAllusersScreen()
{
	vector <stUsers> vuser = LoadUaersDataFromFile(UserFilename);

	cout << "\n\t\t\t\t\tUsers List (" << vuser.size() << ") User(s)"; 

	cout << "\n------------------------------------------------------------------------";
	cout << "__________________________________________________________\n" << endl;

	cout << "|" << left << setw(15)  << "Username";
	cout << "|" << left << setw(10) << "Password";
	cout << "|" << left << setw(40)  << "Permission";

	cout << "\n------------------------------------------------------------------------";
	cout <<"________________________________________________________\n" << endl;

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

	cout << "\n------------------------------------------------------------------------";
	cout << "________________________________________________________\n" << endl;

}

void PrintUsersCard(stUsers user)
{
	cout << "\nthe folowing are the user detailes:\n";
	cout << "________________________________________"; 
	cout << "\nUsername     :" << user.Username ; 
	cout << "\nPassword		:" << user.Password ; 
	cout << "\nPermissions  :" << user.Permission; 
	cout << "\n-------------------------------------\n"; 
}

bool FindUserByUsername(string Username, vector<stUsers> vUser,stUsers &user)
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

stUsers ChangUserRecord(string Username)
{
	stUsers user; 

	user.Username = Username; 

	cout << "\n\nEnter Password?:";
	getline(cin >> ws, user.Password); 

	user.Permission = ReadPermissions(); 

	return user; 
}

bool MarkUserforDeleteBUsername(string Username, vector <stUsers>& vuser)
{
	for (stUsers &user : vuser)
	{
		if (user.Username == Username)
		{
			user.Markfordelet = true;

			return true;
		}
	}
	return false; 
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

void AddNewUser()
{
	stUsers user; 

	user = ReadNewUser();

	AddDataLineToFile(UserFilename, ConvertUsersRecordToLine(user));

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
		false; 
}

string ReadUsername()
{
	string Username = "";
	cout << "\nPlease enter Username !";
	cin >> Username; 
	return Username; 
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





int main()
{
   
}


