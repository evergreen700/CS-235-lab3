#include <ctime>
#include <list>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <map>

using namespace std;

int main(int argc, char *argv[] ){
    if(argc < 3){
        cout << "Invalid input. Arguments required: text <filename> <number of words> <key length>" << endl;
        return -1;
    }

    string inFile = argv[1];
    int n = stoi(argv[2]);
    int M = stoi(argv[3]);
    if(n < M){
        cout << "Number of words cannot be longer than key length" << endl;
        return -1;
    }
    ifstream readfile;
    readfile.open(inFile);

    vector<string> wordVector;
    set<string> wordSet;
    string newWord;
    string tempWord;
    map<list<string>, vector<string> > wordmap;
    list<string> newKey;
    for (int i = 0; i < M; i++) {
        newKey.push_back("");
    }
    
    while(!readfile.eof()){
        readfile >> tempWord;
        newWord = "";
        //remove spaces and punctuation
        for(string::iterator i = tempWord.begin(); i != tempWord.end(); i++){
            if(isalpha(*i)||(*i == '-')){
                newWord.push_back(*i);
            }
        }
        if(newWord == ""){
            continue;
        }
        //Adds the new word to the list corresponding to the previous phrase
        wordmap[newKey].push_back(newWord);
        //adds the new word to the vector and set respectively
        wordVector.push_back(newWord);
        wordSet.insert(newWord);

        //Updates the phrase by removing first element and adding new word to the back
        newKey.pop_front();
        newKey.push_back(newWord);
    }
    readfile.close();
    /*for(map<string, vector<string>>::iterator i = words.begin(); i != words.end(); i++){
            cout << i->first << " ";
            for(vector<string>::iterator j = i->second.begin(); j != i->second.end(); j++){
                cout << *j << " ";
            }
            cout << endl;
    }*/

    ofstream writeFile;
    writeFile.open("newtext.txt");
    writeFile << "File: " << inFile << " n: " << n << " l: " << M << endl;

    srand(time(NULL));
    newKey.clear();
    for (int i = 0; i < M; i++){
        newKey.push_back("");
    }
    for (int i = 0; i < n; i++) {
        int ind = rand() % wordmap[newKey].size();
        newWord = wordmap[newKey][ind];
        writeFile << newWord << " ";
        newKey.pop_front();
        newKey.push_back(newWord);
    }
    writeFile << endl;
    writeFile.close();

    writeFile.open("vector.txt");
    for(vector<string>::iterator i = wordVector.begin(); i != wordVector.end(); i++){
        writeFile << *i << endl;
    }
    writeFile.close();
    
    writeFile.open("set.txt");
    for(set<string>::iterator i = wordSet.begin(); i != wordSet.end(); i++){
        writeFile << *i << endl;
    }
    writeFile.close();
    return 0;
}