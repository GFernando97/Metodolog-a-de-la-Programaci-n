/**
 * @file bag.cpp
 * @author DECSAI
 * @note To be implemented by students except function shuffle()
 */
#include <cassert>
#include <random>
#include <algorithm>
#include "bag.h"
#include <cstring>
#include <string>
#include <iostream>
#include "mi_random.h"
///@warning Fill missing #include

using namespace std;

/**
 * @brief USING mi_random class. Randomly reorders a vector of char
 * @param s Vector of char
 * @param n Number of char in the vector
 * @param id Seed for the random sorting
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


// Main methods
char Bag::get(int p) const{
    
    char getletra;
    
    getletra=letters[p];
    
    return getletra;
}

void Bag::set(int p, char c){
    
    letters[p]=c;
}

Bag::Bag() {
    nletters = 0;
    id = time(NULL);
}

void Bag::setRandom(int newid){
    
    id=newid;
}

void Bag::define(const Language& l){
    
    int i=0,n=0;
    string letras=l.getLetterSet();
    
    while(letras[i]!='\0'){
        
        for(int j=n;j<n+l.getFrequency(letras[i]);j++){
            
            letters[j]=letras[i];
        }
        
        n=n+l.getFrequency(letras[i]);
        nletters=n;
        i++;
    }
    
    shuffleVector(letters, nletters, id);
}

int Bag::size() const{
    
    return nletters;
}

std::string Bag::to_string() const{
    
    string cadenastring="";
    
    for(int i=0;i<nletters;i++){
        
        cadenastring=cadenastring+letters[i];
    }
    
    return cadenastring;
}

void Bag::set(std::string &s){
    
    char cadena[200];
    int i=0,numero=0;
    
    while(s[i]!='\0'){
        
        numero++;
        i++;
    }
    
    if(numero >0 && numero <= 200){
        
        strcpy(cadena,s.c_str());
        nletters=strlen(cadena);
    
        for(int i=0;i<nletters;i++){
        
            letters[i]=cadena[i];
        }
    }
    else{
        
        nletters = 0;
        id = time(NULL);
    }
}

std::string Bag::extract(int n){
    
    string cadenastring="";
    
    if(n<=nletters && n>0){
       
        for(int i=0;i<n;i++){
        
            cadenastring=cadenastring+letters[i];
        }

        for(int i=0;i<n;i++){
            
            removeVector(letters,nletters,0); 
        }
    }
    else if(n>nletters){
        
        int p=nletters;
        
        for(int i=0;i<nletters;i++){
            
            cadenastring=cadenastring+letters[i];
        }

        for(int i=0;i<p;i++){
            
            removeVector(letters,nletters,0);
        }
    }
    else if(n<=0){
        
        cadenastring=cadenastring;
    }
    
    return cadenastring;
}
///@warning Implement all the methods

// Auxiliary functions 

void shuffleVector(char *s, int n, int id) {
    //std::shuffle(aux.begin(), aux.end(), std::default_random_engine(id));
    mi_shuffle(s, s+n, mi_random(id));

}

void removeVector(char *s, int &n, int p){
    
    for(int i=p;i<n-1;i++){
        
        s[i]=s[i+1];
    }
    
    n=n-1;
}
