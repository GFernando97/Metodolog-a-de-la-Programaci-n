/**
 * @file main.cpp
 * @author DECSAI
 * @note To be implemented by students either completely or by giving them
 * key functions prototipes to guide the implementation
 */

#include <string>
#include <cstring>
#include <iostream>
#include "language.h"
#include "bag.h"
#include "player.h"
///@warning complete missing #includes

using namespace std;
/**
 * @brief Shows final data
 * @param l Language
 * @param random Random seed
 * @param b Final bag
 * @param p Final player
 * @param nwords Number of words found
 * @param score Number of letters found
 * @param result Aggregation of all valid words found
 */
void HallOfFame(const Language &l, int random, const Bag &b, const Player &p, 
        int nwords, int score, const string &result);

/**
 * @brief Main function. 
 * @return 
 */
int main() {
    int Id;             /// To be used in bag.setRandom())
    Bag bag;            /// Bag of letters
    Player player;      /// Player set of letters
    Language language;  /// Language to be loaded from disk
    string result="",lang,word="AB";      /// String that contains all the words found
    int nletters=0,          /// Number of letters found
        nwords=0;          /// Number of words found
    
    cout << "TYPE LANGUAGE: ";
    cin >> lang;
    language.setLanguage(lang);
    cout << "ALLOWED LETTERS: " << toUTF(language.getLetterSet()) <<endl;
    cout << "TYPE SEED (<0 RANDOM): ";
    cin >> Id;
    if (Id >= 0)
        bag.setRandom(Id);
    
    bag.define(language);
    cout<<"BAG"<<" ("<<Id<<"-"<<bag.size()<<") :"<<bag.to_string()<<endl<<endl;
    
    
    while(bag.size() > 0 && word.size() >= 2){
        
        string extraer=bag.extract(7-player.size());
        
        player.add(extraer);
        
        do{
            cout<<"PLAYER: "<<player.to_string()<<" BAG"<<"("<<bag.size()<<")"<<endl;
            
            cout<<"INPUT A WORD:"; 
            cin>>word;
            
            cout<<endl;
            
            if(word.size() >= 2){
            
                if(player.isValid(word)==false){
                
                    cout<<word<<" INVALID!"<<endl<<endl;;
                }
                else{
                
                    if(language.query(word)==true){
                    
                        cout<<word<<" FOUND!"<<endl<<endl;                    
                        nwords++;
                        nletters = nletters + word.size();
                        result = result + word + " - ";
                    }
                    else{
                    
                        cout<<word<<" NOT REGISTERED!"<<endl<<endl;
                    }
                
                    player.extract(word);
                }
            }
            
        }while(player.isValid(word)==true && word.size() >= 2);
    }
    
    /// @warning; complete code
    HallOfFame(language,Id,bag,player, nwords, nletters, result);
    return 0;
}

string bestAdvice(const string & s, const Language &l)  {
    
}

void HallOfFame(const Language &l, int random, const Bag &b, const Player &p, 
        int nwords, int score, const string &result) {
    cout << endl << "LANGUAGE: "<<l.getLanguage()<< " ID: " << random << endl;
    cout << "BAG ("<<b.size()<<"): " << toUTF(b.to_string()) << endl;
    cout << "PLAYER (" <<p.size() << "): " << toUTF(p.to_string())<<endl;
    cout << nwords << " words and " << score << " letters "<<endl << 
            toUTF(result) << endl;    
}

