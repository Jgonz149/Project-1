
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <iostream>

using namespace std;

string CleanWord(const string& word)
{
        string cleared;
        cleared.reserve(word.size());

        for (char c : word)
        {
            if(isalpha(static_cast<unsigned char>(c)))
            {
                cleared += static_cast<char>(tolower(static_cast<unsigned char>(c)));
            }
        }

        return cleared;
}


string cleanFile(ifstream& file)
{
    stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    string word;
    string clearedtxt;

    while(buffer >> word)
    {
        string cleanwrd = CleanWord(word);

        if (!cleanwrd.empty())
        {
            clearedtxt += cleanwrd + " ";

        }
    }

    return clearedtxt;
}

void printText(ofstream &out,const string &text)
{
    out << "Word frequencies in "<< text << endl;
    out << "word     frequency\n";
    out << "++++++++++++++++++++++++++++++++++++++++++++++" << endl;
}
