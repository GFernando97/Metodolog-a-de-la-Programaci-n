/**
 * @file language.cpp
 * @author DECSAI
 * @brief Fully functional static library to handle languages, which are
 * represented as a full list of allowed words, stored as a tree to make 
 * search efficient O(n) being n the number of letters in the word to 
 * be loocked up
 * @note Fully implemented. No further implementation required.
 */
#include <string>
#include <cassert>
#include <fstream>
#include <iostream>
#include "language.h"
using namespace std;

Language::Language()  {
   language =""; 
}

Language::Language(string l)  {
    language="";
    setLanguage(l);
}

void Language::setLanguage(string l)  {
    bool res, exit=false;
    ifstream fi;
    string letters;
    int number, scs, frecs;
    
    for (auto & c: l) c = toupper(c);
    language = l;
    letterset = "";
    res = wordlist.load("./languages/"+language+".tree");
    assert(res);
    cout << "Opening ./languages/"+language+".scrabble" << endl;
    fi.open("./languages/"+language+".scrabble");
    assert(fi);
    while (!exit)  {
        fi >> scs;
        fi >> number;
        while (number >= 0){
            frecs = number;
            fi >> letters;
            letterset+=letters;
            for (int i=0; i<letters.size(); i++) {
                frequencies.push_back(frecs);
                scores.push_back(scs);
            }
            fi >> number;
        } 
        if (number == -2)
            exit = true;
    }
    cout << "OK "<<letterset.size()<< " Scrabble's letter read " << endl;
//    cerr << "["<<toUTF(letterset)<<"]"<<endl;
    fi.close();
}

bool Language::query(string word) const {
    return wordlist.searchWord(normalizeWord(word));
}

string Language::getLanguage() const {
    return language;
}

int Language::getFrequency(char letter) const {
    int pos = letterset.find(letter);
    if ( pos != string::npos) {
        return frequencies[pos];
    }
    else return 0;
}
int Language::getScore(char letter)  const {
    int pos = letterset.find(letter);
    if ( pos != string::npos) {
        return scores[pos];
    }
    else return 0;
}

string Language::getLetterSet() const {
    return letterset;
}

