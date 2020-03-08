/**
 * @file bag.cpp
 * @author DECSAI
 * @note To be implemented by students except function shuffle()
 */

#include "bag.h"

// Auxiliary functions 
/**
 * @brief Randomly reorders a vector of char
 * @param s Vector of char
 * @param n Number of char in the vector
 * @author DECSAI
 */
void shuffleVector(char *s, int n, int id);

/**
 * @brief Removes a position from a vector and compacts the remaining positions, 
 * thus reducing its size
 * @param s Vector of char
 * @param n Number of chars
 * @param p Position to remove
 * @warning TO BE FULLY IMPLEMENTED. 
 * @warning Check parameters const/&/* and their types
 */
void removeVector(char *s, int &n, int p);

// End of Auxiliaty functions



Bag::Bag(){
    nletters = 0;
    id = time(NULL);
}

void Bag::define(const Language &l){
    int i = 0;
    string aux = l.getLetterSet();
    string bagValue;
    
    
    while(aux[i] != '\0' ){        
        for(int j = 0; j < l.getFrequency(aux[i]); j++){
            bagValue.push_back(aux[i]);
        }
        i++;
    }
    
    Bag::set(bagValue);
}

void Bag::set(std::string &s){
    
    for(int i = 0; i < s.size(); i++){
        Bag::set(i, s[i]);
        nletters++;
    }
    shuffleVector(letters, nletters, id);
}




void shuffleVector(char *s, int n, int id) {
    vector <char> aux(s, s+n);
    unsigned seed = id;
    std::shuffle(aux.begin(), aux.end(), std::default_random_engine(seed));
    for (int i=0; i<n; i++)
        s[i] = aux[i];    
}

void removeVector(char *s, int &n, int p){
    for (int i = p+n; i < strlen(s); i++){
            s[i-n]= s[i];
    }
    //DDBC694C20B
    
}
