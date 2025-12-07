/**************************************************************************
    Class:		CSCI 3333.01 Data Structures and Algorithms
                   	Spring 2025

    Project 1:	Have Fun with Lists, Vectors, Sets/Multisets, and Maps

    Name:		Julissa Gonzalez

    ID:            	20623146
    
    Description: Use respectively a list, a vector, a set / multiset,
        and a map to count word frequencies in two files and
        record the time needed.

    Input files: bible.txt, world192.txt
    Output files: list_counting.txt, vector_counting.txt,
                  set_counting.txt, map_counting.txt
    Example format of output file with a list:
        word frequencies in bible.txt
        word     frequency
        ......
        ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        time used to count word frequencies with a list is : xxx seconds

        word frequencies in world192.txt
        word     frequency
        ......
        ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        time used to count word frequencies with a list is : xxx seconds
**************************************************************************/
#include "def.cpp"
#include <iostream>
#include <fstream>
#include <list>
#include <set>
#include <vector>
#include <map>
#include <time.h>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std; 

/*Declaring functions*/
string CleanWord(const string& word);
string cleanFile(ifstream& file);
void printText(ofstream &out,const string &text);


int main()
{
    //derclare containers for counting
    list<string> mylist; 
    vector<string> myvector; 
    multiset<string> myset;
    map<string, int> mymap; 

    //file variables for input/output
    ifstream inFile1, inFile2; 
    ofstream outFile; 

    //time variables to record performance in seconds
    time_t start_time, end_time;

    //additional variables
    string word; 

    //cleaning bible and world192 
    inFile1.open("bible.txt");
    inFile2.open("world192.txt");

    string cleanedFile1 = cleanFile(inFile1);
    outFile.open("bible_cleaned.txt");
    outFile << cleanedFile1;
    outFile.close();

    outFile.open("world192_cleaned.txt");
    string cleanedFile2 = cleanFile(inFile2);
    outFile << cleanedFile2;
    outFile.close();

    /***********************************
    count word frequencies with a list
    ************************************/
    //start the time
    start_time = time(NULL);

    //count bible.txt
    inFile1.open("bible_cleaned.txt");
    inFile2.open("world192_cleaned.txt");
    outFile.open("list_counting.txt"); 

    //-------------Bible.txt with list-----------

    while (inFile1 >> word)
    {
        mylist.push_back(word);
    }
    inFile1.close();

    list<pair<string, int> > listcount;

    for (const string& w : mylist)
    {
        bool found = false;
        for (auto &p : listcount)     
        {
            if (p.first == w)
            {
                ++p.second;
                found = true;
                break;
            }
        }
        if (!found)
        {
            listcount.push_back(make_pair(w, 1));
        }
    }
    
    //Prints word and count for file
    printText(outFile,"bible.txt"); 

    for (const auto &p : listcount)
    {
        outFile << p.first << "     " << p.second << '\n';
    }

    // ---------- world192.txt with list ----------
    listcount.clear();
    mylist.clear();

    while (inFile2 >> word) 
    {
        mylist.push_back(word);
    }
    inFile2.close();

    for (const string& w : mylist)
    {
        bool found = false;
        for (auto &p : listcount)
        {
            if (p.first == w)
            {
                ++p.second;
                found = true;
                break;
            }
        }
        if (!found)
        {
            listcount.push_back(make_pair(w, 1));
        }
    }

    //Prints word and count for file
    printText(outFile, "World192.txt");

    for(auto& p : listcount)
    {
        outFile << p.first << " : " << p.second << endl;
    }

    //output the counting results
    //record the end time
    end_time = time(NULL);
    outFile << "++++++++++++++++++++++++++++++++++++++++++++++" << endl;
    outFile << "time used to count word frequencies with a list is: "
        << difftime(end_time, start_time) << " seconds" << endl << endl;
    //Counting is done. Close the files. 
    outFile.close();

    /***************
     Counting jobs with a vector 
    ****************/

   //-------------Bible.txt with Vector-----------
    start_time = time(NULL);
    inFile1.open("bible_cleaned.txt");
    inFile2.open("world192_cleaned.txt");
    outFile.open("vector_counting.txt");
    vector<string> onlyword;
    vector<int> count;

    while(inFile1 >> word)
    {
        myvector.push_back(word);
    }

    inFile1.close();

    for(const string &w: myvector)
    {
        bool found = false;
        for(size_t i = 0; i < onlyword.size(); i++)
        {
            if(onlyword[i] == w)
            {
                ++count[i];
                found = true;
                break;            
            }
        }
        if(!found)
        {
            onlyword.push_back(w);
            count.push_back(1);
        }

    }
    //Prints word and count for file
    printText(outFile, "bible_cleaned.txt");

    for(size_t i = 0; i < onlyword.size(); ++i)
    {
        outFile << onlyword[i] << "     " << count[i] << endl;
    }

    // ---------- world192.txt with Vector ----------
    myvector.clear();
    onlyword.clear();
    count.clear();

    while(inFile2 >> word)
    {
        myvector.push_back(word);
    }
    
    inFile2.close();

    for(const string &w: myvector)
    {
        bool found = false;
        for(size_t i = 0; i < onlyword.size(); i++)
        {
            if(onlyword[i] == w)
            {
                ++count[i];
                found = true;
                break;            
            }
        }
        if(!found)
        {
            onlyword.push_back(w);
            count.push_back(1);
        }

    }

    //Prints word and count for file
    printText(outFile, "World192_cleaned.txt");

    for(size_t i = 0; i < onlyword.size(); ++i)
    {
        outFile << onlyword[i] << ":     " << count[i] << endl;

    }
    //prints count
    //record the end time
    end_time = time(NULL);
    outFile << "++++++++++++++++++++++++++++++++++++++++++++++" << endl;
    outFile << "time used to count word frequencies with a vector is: "
        << difftime(end_time, start_time) << " seconds" << endl << endl;

    outFile.close();

    /***************
     Counting jobs with a multiset 
    ****************/

     //-------------Bible.txt with multisets-----------
    start_time = time(NULL);
    inFile1.open("bible_cleaned.txt");
    inFile2.open("world192_cleaned.txt");
    outFile.open("set_counting.txt");

    printText(outFile, "bible.txt");

    while(inFile1 >> word)
    {
        myset.insert(word);

    }

    for(auto it = myset.begin(); it != myset.end(); )
    {
        auto range = myset.equal_range(*it);
        int times = distance(range.first, range.second);
        outFile << *it << ":   " << times << endl;
        it = range.second;
    }
 
    inFile1.close();
    

    // ---------- world192.txt with mulitsets ----------
    myset.clear();

    printText(outFile, "world192.txt");

    while(inFile2 >> word)
    {
        myset.insert(word);

    }

    for(auto it = myset.begin(); it != myset.end(); )
    {
        auto range = myset.equal_range(*it);
        int times = distance(range.first, range.second);
        outFile << *it << ":   " << times << endl;
        it = range.second;
    }

    inFile2.close();
    
    //record the end time
    end_time = time(NULL);
    outFile << "++++++++++++++++++++++++++++++++++++++++++++++" << endl;
    outFile << "time used to count word frequencies with a vector is: "
        << difftime(end_time, start_time) << " seconds" << endl << endl;

    outFile.close();

    /***************
     Counting jobs with a map 
    ****************/
    start_time = time(NULL);
    inFile1.open("bible_cleaned.txt");
    inFile2.open("world192_cleaned.txt");
    outFile.open("map_counting.txt");

    //-------------Bible.txt with multisets-----------

    


    // ---------- world192.txt with mulitsets ----------


    //record the end time
    end_time = time(NULL);
    outFile << "++++++++++++++++++++++++++++++++++++++++++++++" << endl;
    outFile << "time used to count word frequencies with a vector is: "
        << difftime(end_time, start_time) << " seconds" << endl << endl;


    //the work is done
    return 0;
}