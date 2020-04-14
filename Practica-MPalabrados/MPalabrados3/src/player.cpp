/**
 * @file player.cpp
 * @author DECSAI
 * @note To be implemented by students
 */

#include <cstring>
#include "player.h"
#include <iostream>
///@warning complete missing #includes
/// See http://www.cplusplus.com/reference/cstring/ for details about cstrings
using namespace std;

void removeCString(char *cstr, int pos);

void sortCString(char *cstr);

Player::Player(){
    
    letters[0]='\0';
}

int Player::size() const{
    
    return strlen(letters);
}

std::string Player::to_string() const{
    
    string s(letters);
    return s;
}

void Player::clear(){
    
    letters[0]='\0';
}

bool Player::isValid(const std::string &s) const{
    
    char stringordenada[s.size()];
    
    strcpy(stringordenada,s.c_str());
    sortCString(stringordenada);
    
    bool valido=true;
    int n=0;
    
    for(int i=0; i<s.size() && valido==true; i++){
        
        bool encontrado=false;
        
        for(int j=n; j<size() && encontrado==false; j++){
            
            if(stringordenada[i] == letters[j]){
                
                encontrado=true;
                n++;
            }
            else{
                
                encontrado=false;
                n++;
            }
        }
        
        if(encontrado==false){
            
            valido=false;
        }
        else{
            
            valido=true;
        }
    }
    
    return valido;
}

bool Player::extract(const std::string &s){
    
    bool found;
    
    if(isValid(s)==true){
        
        for(int i = 0; i < s.size(); i++){
            
            found = false;
            
            for(int j = 0; j < size() && !found; j++){
                
                if(s[i] == letters[j]){
                    
                    removeCString(letters, j);
                    found = true;
                }
            }
        }
        return true;
    }
    else{
        
        return false;
    }
}

void Player::add(const std::string &frombag){
    
    if( (strlen(letters)+frombag.size()) <= 7 ){
        
        char cadena[frombag.size()];
        
        strcpy(cadena, frombag.c_str());
        
        strcat(letters, cadena);
        
        sortCString(letters);
    }
}

/**
 * @brief Removes a position from a cstring
 * @param cstr The cstring
 * @param pos The position
 * @return The cstring is modified
 * @warning To be fully implemented
 */
void removeCString(char *cstr, int pos){
    
    for(int i=pos;i<strlen(cstr);i++){
        
        cstr[i]=cstr[i+1];
    }
}

/**
 * @brief Sort a cstring from A to Z
 * @param cstr The cstring
 * @return The cstring is modified
 * @warning To be fully implemented
 */
void sortCString(char *cstr){
    
    char menor,letra,aux;
    
    for(int i=0; i < strlen(cstr);i++){
        
        int posicion=i;
        menor=cstr[i];
            
        for(int j=i; j < strlen(cstr); j++){
                
            letra=cstr[j];
                
            if(letra < menor){
                    
                menor=letra;
                posicion=j;
            }
            else{
                 menor=menor;
                 posicion=posicion;
            }
        }
        aux=cstr[i];
        cstr[i]=menor;
        cstr[posicion]=aux;
    }
}

