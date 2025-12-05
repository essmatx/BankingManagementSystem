#pragma once
#include <iostream>
#include "clsPerson.h"
#include "clsString.h"
#include "clsDate.h" 
#include "clsUtil.h"
#include <string>
#include <vector>
#include <fstream>
using namespace std;
const string RecordLogin = "Logfile"; 
const string UsersFile = "UsersInfo.txt";


class clsUser : public clsPerson
{
	

	enum enMode{EmptyMode = 0 , UpdateMode = 2 , AddNewMode = 3 };

	struct stLoginRegisterRecord;

	enMode _Mode; 
	string _UserName;
	string _Password;
	int _Permissions; 
	bool _MarkforDelete = false; 

	static clsUser _ConvertLinetoUserobject(string Line, string Seperater = "<<")
	{
		vector<string>vUser; 

		vUser = clsString::SplitString(Line, Seperater);

		return clsUser(enMode::UpdateMode, vUser[0], vUser[1], vUser[2], vUser[3], vUser[4],vUser[5], stoi(vUser[6]));
		

	}

	
	static string _ConvertUserobjecttoLine(clsUser User, string Seperater = "<<")
	{
		string UserRecord = "";

		UserRecord += User.FirstName + Seperater;
		UserRecord += User.LastName + Seperater;
		UserRecord += User.Phone + Seperater;
		UserRecord += User.Email + Seperater;
		UserRecord += User.UserName + Seperater;
		UserRecord += clsUtil::EncrypText(User.Password) + Seperater;
		UserRecord += to_string(User.Permissions); 

		return UserRecord; 

	}
	
	static vector <clsUser> _LoadUsersDatafromFile()
	{
		vector <clsUser> vUser; 

		fstream Myfile; 

		Myfile.open(UsersFile, ios::in);

		if (Myfile.is_open())
		{
			string Line; 

			while (getline(Myfile, Line))
			{
				clsUser User = _ConvertLinetoUserobject(Line); 

				vUser.push_back(User);
			}

			Myfile.close(); 
		}

		return vUser; 
	}

	
	static void _SaveUsersDatatoFile(vector<clsUser> vUser)
	{

		fstream Myfile; 

		Myfile.open(UsersFile, ios::out);

		string Data; 

		if (Myfile.is_open())
		{
			for (clsUser U : vUser)
			{
				if (U.Markedfordelete() == false)
				{
					Data = _ConvertUserobjecttoLine(U);

					Myfile << Data << endl; 
				}
			}
			Myfile.close();
		}
		
	}


	 void _Update()
	 {
		 vector <clsUser> vUser; 

		 vUser = _LoadUsersDatafromFile();

		 for (clsUser& U : vUser)
		 {
			 if (U.UserName == UserName)
			 {
				 U = *this; 
				 break;
			 }
		 }

		 _SaveUsersDatatoFile(vUser); 
	 }

	 void _AddDataLinetoFile(string stData)
	 {
		 fstream Myfile;

		 Myfile.open(UsersFile, ios::out | ios::app);

		 if (Myfile.is_open())
		 {
			 Myfile << stData << endl; 

			 Myfile.close();
		 }

		 

	 }

	 void _AddNew()
	 {
		 _AddDataLinetoFile(_ConvertUserobjecttoLine(*this)); 
	 }

	 static clsUser _GetEmptyUser0bject()
	 {
		 return clsUser(enMode::EmptyMode, "", "", "", "", "","", 0);
	 }

	 static string EncryptedPassword(string Password)
	 {
		 return clsUtil::EncrypText(Password); 
	 }

	 string _PrepareLoginRecord(string seperator = "<<")
	 {
		 string recordline = ""; 

		 recordline +=  clsDate::SystemDateTimeString() + seperator; 

		 recordline += UserName + seperator; 

		 recordline += clsUtil::EncrypText(Password) + seperator;

		 recordline += to_string(Permissions); 

		 return recordline; 
	 }

	 

	 static stLoginRegisterRecord _ConvertLoginRegisterLineToRecord(string line, string Seperater = "<<")
	 {
		 stLoginRegisterRecord record; 

		 vector <string> vData = clsString::SplitString(line, Seperater);

		 record.DateTime = vData[0]; 

		 record.Username = vData[1];

		 record.Password = clsUtil::DecryptedText(vData[2]);

		 record.Permissions = stoi(vData[3]);

		 return record; 
	 }

	
 public:

	 enum enPermissions {eAll = -1 , pLisClient =1 , pAddNewClient = 2 ,  pDeleteCLient = 4,pUpdateClient = 8 ,
	 pFindClient = 16 ,  pTransaction = 32 , pManageUsers = 64 , pLoginRegister = 128};

		clsUser(enMode Mode, string FirstName, string LastName, string Phone,
			string Email, string UserName, string Password, int Permissions)  :
			clsPerson(FirstName, LastName, Email, Phone)
		{
			_Mode = Mode; 
			_UserName = UserName;
			_Password = Password;
			_Permissions = Permissions; 
		
		}

		struct stLoginRegisterRecord
		{
			string DateTime;
			string Username;
			string Password;
			int Permissions;
		};

		bool IsEmpty()
		{
			return (_Mode == enMode::EmptyMode); 
		}

		bool Markedfordelete()
		{
			return _MarkforDelete;
		}

		void setUserName(string UserName)
		{
			_UserName = UserName; 
		}

		string getUserName()
		{
			return _UserName; 
		}
		__declspec(property(get = getUserName, put = setUserName)) string UserName; 

		void setPassword(string Password)
		{
			_Password = Password;
		}

		string getPassword()
		{
			return _Password; 
		}

		__declspec(property(get = getPassword, put = setPassword)) string Password;

		void setPermissions(int Permissions)
		{
			_Permissions = Permissions; 
		}

		int getPermissions()
		{
			return _Permissions; 
		}

		__declspec(property(get = getPermissions, put = setPermissions))int Permissions; 

		static clsUser Find(string Username)
		{
			fstream Myfile; 

			Myfile.open(UsersFile, ios::in);

			if (Myfile.is_open())
			{
				string Line = ""; 

				while (getline(Myfile, Line))
				{
					clsUser User = _ConvertLinetoUserobject(Line); 

					if (User.UserName == Username)
					{
						Myfile.close(); 

						return User; 
					}

				}

				Myfile.close(); 
			}

			return _GetEmptyUser0bject(); 
		}

		static clsUser Find(string Password, string UserName)
		{
			fstream Myfile; 

			string Encrpttxt = clsUtil::EncrypText(Password); 

			Myfile.open(UsersFile, ios::in);

			

			if (Myfile.is_open())
			{
				string Line = "";

				while (getline(Myfile, Line))
				{
					clsUser User = _ConvertLinetoUserobject(Line); 


					if (User.UserName == UserName && User.Password == Encrpttxt)
					{
						Myfile.close(); 
						return User; 
					}
				}

				Myfile.close(); 
			}

			return _GetEmptyUser0bject();
		}

		enum enSaveResults{SaveFailedEmptyObject = 0 , SaveSucceeded = 1, SaveFaileUserExixts  = 2};

		enSaveResults save()
		{
			switch (_Mode)
			{
			case enMode::EmptyMode:
				if (IsEmpty())
				{
					return enSaveResults::SaveFailedEmptyObject;

				}

			case enMode::UpdateMode:

				_Update();
				return enSaveResults::SaveSucceeded;

			case enMode::AddNewMode:

				if (clsUser::IsUserExist(_UserName))
				{
					return enSaveResults::SaveFaileUserExixts;
				}
				else
				{
					_AddNew();
					_Mode = enMode::UpdateMode;
					return enSaveResults::SaveSucceeded;
				}

				break;
			}

		}

		static bool IsUserExist(string UserName)
		{
			clsUser User = clsUser::Find(UserName);

			return (!User.IsEmpty());
		}

		bool Delete()
		{
			vector <clsUser> vUser = _LoadUsersDatafromFile(); 

			for (clsUser& U : vUser)
			{
				if (U.UserName == _UserName)
				{
					U._MarkforDelete = true;
					break; 
				}
			}

			_SaveUsersDatatoFile(vUser);

			*this = _GetEmptyUser0bject();

			return true; 
		}

		static clsUser GetAddnewUserObject(string UserName)
		{
			return clsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0); 
		}

		static vector<clsUser> GetUsersList()
		{
			return _LoadUsersDatafromFile(); 
		} 

		bool CheckAccessPermissions(enPermissions Permission)
		{
			if (this->Permissions == enPermissions::eAll)
			{
				return true; 
			}

			if ((Permission & this->Permissions) == Permission)
			{
				return true;
			}
			
			else
			{
				return false;
			}
			
				
			
			
			
		}

		static vector<stLoginRegisterRecord> GetLoginRegisterList()
		{
			vector <stLoginRegisterRecord> vrecord;

			fstream Myfile; 

			Myfile.open(RecordLogin, ios::in); 

			if (Myfile.is_open())
			{
				string line = ""; 

				stLoginRegisterRecord record;

				while (getline(Myfile, line))
				{
					record = _ConvertLoginRegisterLineToRecord(line); 

					vrecord.push_back(record);
				}

				Myfile.close(); 
				
			}

			return vrecord;
		}
	
		void RegisterLogin()
		{
			string Dataline = _PrepareLoginRecord();

			fstream Myfile; 
			Myfile.open(RecordLogin, ios::out | ios::app);

			if (Myfile.is_open())
			{
				Myfile << Dataline << endl;

				Myfile.close();
			}
		}

		static void EncryptAllpasswordsInFile()
		{
			vector <clsUser> vUser = _LoadUsersDatafromFile();

			fstream Myfile;

			Myfile.open(UsersFile, ios::out);

			if (Myfile.is_open())
			{
				for (clsUser& User : vUser)
				{
					User.Password = clsUtil::EncrypText(User.Password);

					string Dataline = _ConvertUserobjecttoLine(User);

					Myfile << Dataline << endl;
				}

				Myfile.close();
			}
		};
 

};


