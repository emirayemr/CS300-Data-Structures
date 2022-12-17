/* Emir Ay ( CS 300 - Homework2 )
   I used mostly xCode for this homework
 */
#include <iostream>
#include <fstream>
#include <string>
#include "emiray_Ay_Emir_hw2_AVLSearchTree.h"
using namespace std;

int main()
{
    int file_number;
    cout << "Enter number of input files: ";
    cin >> file_number;
    
    AVLSearchTree<string, WordItem> myTree("");
    
    string fileNames[10];
    for (int i=0; i < file_number; i++)
    {
        ifstream input;
        string name;
        do
        {
            cout << "Enter " << i+1 << ". file name: ";
            cin >> name;
            input.open(name.c_str());
            
        } while(input.fail());
        
        fileNames[i] = name;
        string w;
        while (input >> w)
        {
            myTree.insert(w, name, file_number, i);
        }
    }
        
    string words;
    cout << "Enter queried words in one line: ";
    cin.ignore();
    getline(cin, words);

    bool isWordThere = true;
    
    for (int i=0; i < file_number; i++)
    {
        string temp = words;
        while (temp != " ")
        {
            string word = temp.substr(0, temp.find(' '));
            deleteNonAlpha<string, WordItem>(word);
            if (temp.length() != word.length())
                temp = temp.substr(temp.find(' ')+1);
            else
                temp = " ";
            
            myTree.find(word, i, isWordThere);
        }
    }
    
    if (isWordThere == true)
    {
        for (int i=0; i < file_number; i++)
        {
            cout << "in Document " << fileNames[i] << ", ";
            string temp = words;
            while (temp != " ")
            {
                string word = temp.substr(0, temp.find(' '));
                deleteNonAlpha<string, WordItem>(word);
                if (temp.length() != word.length())
                    temp = temp.substr(temp.find(' ')+1);
                else
                    temp = " ";
                
                myTree.findAndPrint(word, i);
                if (temp == " ")
                    cout << ".";
                else
                    cout << ", ";
            }
            cout << endl;
        }
    }
    else
        cout << "No document contains the given query\n";
    
    
    return 0;
}

