#pragma once
#include <iostream>
#include<string>
#include <vector>

using namespace std; 

class clsString
{
    string _value;

public:
clsString()
    {
        _value = "";
    }

clsString(string value)
    {
        _value = value;
    }

void setValue(string value)
    {
        _value = value;
    };

string getValue()
    {
        return _value;
    }

__declspec(property(get = getvalue, put = steValue))string value;

static short CountWords(string str)
   {
        short count = 0;

        short pos = 0;

        string delim = " "; // Delimiter for splitting the string into words

        string word;

        while ((pos = str.find(delim)) != std::string::npos) // Find the position of the delimiter in the string
        {
            word = str.substr(0, pos); // Extract the word from the string
            if (word != "")
            {
                count++; // Increment the count if the word is not empty
            }
            str.erase(0, pos + delim.length()); // Remove the word from the string
        }

        return count;
   };

short CountWords()
    {
        return CountWords(_value);
    };

static void PrintEachWord(string str)
  {
        string delim = " "; // Delimiter for splitting the string into words

        cout << "Words in the string: " << endl;


        short pos = 0;


        string word;


        while ((pos = str.find(delim)) != std::string::npos) // Find the position of the delimiter in the string
        {
            word = str.substr(0, pos); // Extract the word from the string
            if (word != "")
            {
                cout << word << endl; // Print the word if it's not empty
            }

            str.erase(0, pos + delim.length()); // Remove the word from the string
        }
        if (str != "")
        {
            cout << str << endl; // Print the remaining part of the string if it's not empty
        }


  }

void PrintEachWord()
  {
      PrintEachWord(_value);
  }; 

static vector<string> SplitString(string str, string delim)
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
  };

vector<string> SplitString()
 {
     return SplitString(_value, " ");
 };

static void PrintFristlater(string str)
 {
     bool FristLater = true;

     cout << " The Frist late of Each word!\n";

     for (int i = 0; i < str.length(); i++)
     {
         if (str[i] != ' ' && FristLater)
         {
             cout << str[i] << endl;
         };

         FristLater = (str[i] == ' ' ? true : false);
     };
 };

 void PrintFristlater()
 {
     PrintFristlater(_value); 
 }

 static string UpperFristLaterOfEachWord(string str)
 {
     bool FristLater = true;

     for (int i = 0; i < str.length(); i++)
     {
         if (str[i] != ' ' && FristLater)
         {
             str[i] = toupper(str[i]); // Convert to uppercase and append to result
         };

         FristLater = (str[i] == ' ' ? true : false);
     };

     return str;
 };

 void UpperFristLaterOfEachWord()
 {
     _value = UpperFristLaterOfEachWord(_value);
 };

 static string LowerFristLaterOfEachWord(string str)
 {
     bool FristLater = true;
     for (int i = 0; i < str.length(); i++)
     {
         if (str[i] != ' ' && FristLater)
         {
             str[i] = tolower(str[i]); // Convert to lowercase and append to result
         }
         FristLater = (str[i] == ' ' ? true : false);
     }
     return str;
 }

 void  LowerFristLaterOfEachWord()
 {
     _value = LowerFristLaterOfEachWord(_value);
 };

static  string AllStringCapitalLater(string str)
 {
     for (int i = 0; i < str.length(); i++)
     {
         str[i] = toupper(str[i]); // Convert to uppercase and append to result
     }

     return str;
 }

void AllStringCapitalLater()
{
    _value = AllStringCapitalLater(_value);
};

static string AllStringLowerLater(string str)
{
    for (int i = 0; i < str.length(); i++)
    {
        str[i] = tolower(str[i]); // Convert to lowercase and append to result
    }

    return str;
}

void AllStringLowerLater()
{
    _value =  AllStringLowerLater(_value);
};

static string convertStringToUpperandLower(string str)
{
    for (int i = 0; i < str.length(); i++)
    {
        str[i] = isupper(str[i]) ? tolower(str[i]) : toupper(str[i]); // Convert to uppercase if it's lowercase, or to lowercase if it's uppercase
    }
    return str;
};

void convertStringToUpperandLower()
{
    _value = convertStringToUpperandLower(_value);
};

static short CountAllLCapitalLetters(string str)
{
    short count = 0;

    for (short i = 0; i < str.length(); i++)
    {
        if (isupper(str[i]))
        {
            count++;
        }
    }

    return count;
}

short CountAllLCapitalLetters()
{
    return CountAllLCapitalLetters(_value);
};

static short CountAllLowerLetters(string str)
{
    short count = 0;
    for (short i = 0; i < str.length(); i++)
    {
        if (islower(str[i]))
        {
            count++;
        }; 
    };
    return count;
};

short CountAllLowerLetters()
{
    return CountAllLowerLetters(_value);
}; 

 



static string TrimeLeft(string str)
{
    for (short i = 0; i < str.length(); i++)
    {
        if (str[i] != ' ') // Check for non-space charecter
        {
            return str.substr(i, str.length() - i);
        }
    }
}

void TrimeLeft()
{
    _value = TrimeLeft(_value);
};

static string TrimeRight(string str)
{
    for (short i = str.length() - 1; i >= 0; i--) // Start from the end of the string
    {
        if (str[i] != ' ') // Check for non-space character
        {
            return str.substr(0, i + 1); // Return the substring up to the last non-space character
        }
    }
}

void TrimeRight()
{
   _value =  TrimeRight(_value);
};

static string TrimeBothSides(string str)
{
    return(TrimeRight(TrimeLeft(str)));
}

void TrimeBothSides()
{
    _value = TrimeBothSides(_value);
};

static string JoinString(vector<string> words, string delim)
{
    string result = " ";

    for (string& word : words) // Iterate through each word in the vector
    {

        result = result + word + delim; // Append the word and delimiter to the result string
    }

    return result.substr(0, result.length() - delim.length()); // Return the result string without the trailing delimiter
}

static string JoinString(string Array[], int size, string delim)
{
    string result = " ";
    for (int i = 0; i < size; i++) // Iterate through each word in the array
    {
        result = result + Array[i] + delim; // Append the word and delimiter to the result string
    }
    return result.substr(0, result.length() - delim.length()); // Return the result string without the trailing delimiter
}

static string ReversWordsinString(string str)
{
    vector<string>words = SplitString(str, " "); // Split the string into words using space as a delimiter
    string result = " ";

    vector<string>::iterator iter = words.end(); // Initialize iterator to the end of the vector	

    while (iter != words.begin()) // Iterate through the vector in reverse order
    {
        --iter; // Move the iterator to the previous element
        result += *iter + " "; // Append the word and a space to the result string
    }


    result = result.substr(0, result.length() - 1); // Remove the trailing space from the result string

    return result; // Return the reversed string of words


}

void ReversWordsinString()
{
    _value = ReversWordsinString(_value);
};

static string Replacestrings(string str, string Oldword, string Newword)
{
    short pos = str.find(Oldword); // Find the position of the old word in the string

    while (pos != std::string::npos) // Continue until no more occurrences are found
    {
        str.replace(pos, Oldword.length(), Newword); // Replace the old word with the new word

        pos = str.find(Oldword.length()); // Find the next occurrence of the old word

    }

    return str; // Return the modified string
}

static string ReplaceStringUsingSpilt(string str, string Oldword, string Newword, bool CaseSenstive)
{
    vector<string> words = SplitString(str, " "); // Split the string into words using space as a delimiter

    if (CaseSenstive)
    {
        for (string& word : words) // Iterate through each word in the vector
        {
            if (word == Oldword) // Check for case-sensitive match
            {
                word = Newword; // Replace the old word with the new word		
            }
            else {
                if (AllStringLowerLater(word) == AllStringLowerLater(Oldword))
                {
                    word = Newword; // Replace the old word with the new word

                }
            }





        }
    }

    return  JoinString(words, " "); // Join the words back into a single string with space as a delimiter
}

static string RemovePunctuation(string str)
{
    string result = " ";

    for (short i = 0; i < str.length(); i++)
    {
        if (!ispunct(str[i])) // Check if the character is a punctuation mark
        {
            result += str[i]; // Append the punctuation mark to the result string
        }
    }

    return result; // Return the string containing only punctuation marks
}

void RemovePunctuation()
{
    _value = RemovePunctuation(_value);
};

static short Lingth(string str)
{
    return  string(str).length(); 
}

short Lingth()
{
    return Lingth(_value); 
}

char ReedCharter()
{
    char ch;
    cout << "Enter a character: ";
    cin >> ch; // Read a single character
    return ch;
}

char convertcharToUpperandLower(char ch)
{
    return isupper(ch) ? tolower(ch) : toupper(ch); // Convert to uppercase if it's lowercase, or to lowercase if it's uppercase
}

enum MenuOptions { SmallLetters = 0, CapitalLetters = 1, Stringth = 2 };

short DeterminStringType(string str, MenuOptions Type)
{
    if (Type == MenuOptions::Stringth)
    {
        return str.length(); // Return the length of the string if the type is Stringth
    }

    short count = 0;
    for (short i = 0; i < str.length(); i++)
    {


        if (Type == MenuOptions::CapitalLetters && isupper(str[i]))
        {
            count++;
        }

        if (Type == MenuOptions::SmallLetters && islower(str[i]))
        {
            count++;
        }
    }
    return count;

}

short CountallCharacters(string str, char ch)
{
    short count = 0;
    for (short i = 0; i < str.length(); i++)
    {
        if (str[i] == ch)
        {
            count++;

        }
    }

    return count;
}

short DeterminTypeOfCapitalChar(string str, char ch)
{
    short count = 0;


    for (short i = 0; i < str.length(); i++)
    {
        if (isupper(str[i] == ch))
        {
            count++;

            cout << "The character '" << ch << "' is a capital letter in the string." << endl;

        }
    }

    return count;
}

short CountLatters(string str, char ch, bool Machcase = true)
{
    short count = 0;


    for (short i = 0; i < str.length(); i++)
    {
        if (Machcase)
        {
            if (str[i] == ch)
            {
                count++;
            }
        }
        else  // If Machcase is false, check for case-insensitive match
        {
            if (tolower(str[i]) == tolower(ch))
            {
                count++;
            }
        }
    }

    return count;
}

bool isVowel(char ch)
{
    ch = tolower(ch); // Convert to lowercase for case-insensitive comparison

    return (ch == 'a' || ch == 'e' || ch == 'i' || ch == '0' || ch == 'u');	// Check if the character is a vowel

}

short CountVowels(string str)
{
    short count = 0;

    for (short i = 0; i < str.length(); i++)
    {
        if (isVowel(str[i]))
        {
            count++;
        }
    }

    return count; // Return the total count of vowels in the string
}

void PrintVowels(string str)
{
    cout << "Vowels in the string: ";
    for (short i = 0; i < str.length(); i++)
    {
        if (isVowel(str[i]))
        {
            cout << str[i] << " "; // Print each vowel found in the string
        }
    }
    cout << endl;
}

};

