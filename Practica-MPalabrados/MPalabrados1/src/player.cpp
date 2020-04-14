/**
 * @file player.cpp
 * @author DECSAI
 * @note To be implemented by students
 */

#include <cstring>
#include "player.h"
///@warning complete missing #includes
/// See http://www.cplusplus.com/reference/cstring/ for details about cstrings
using namespace std;

/**
 * @brief Removes a position from a cstring
 * @param cstr The cstring
 * @param pos The position
 * @return The cstring is modified
 * @warning To be fully implemented
 */
void removeCString(char *cstr, int pos);

/**
 * @brief Sort a cstring from A to Z
 * @param cstr The cstring
 * @return The cstring is modified
 * @warning To be fully implemented
 */
void sortCString(char *cstr);



Player::Player(){
    letters[0]='\0';
}


int Player::size()const{
	return strlen(letters);
}

string Player::to_string()const{
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

bool Player::extract(const std::string s){
    bool found;
    if(isValid(s)){
        for(int i = 0; i < s.size(); i++){
            found = false;
            for(int j = 0; j < strlen(letters) and !found; j++){
                if(s[i] == letters[j]){
                    removeCString(letters, j);
                    found = true;
                }
            }
        }
        return true;
    }
    
    else return false;
}

void Player::add(std::string frombag){
    if( (strlen(letters)+frombag.size()-1) < MAXPLAYER ){
        strcat(letters, frombag.c_str());
    }    
}

//Auxiliary functions

void removeCString(char *cstr, int pos){
    for(int i = pos; i< strlen(cstr); i++)
        cstr[i]=cstr[i+1];
}

void sortCString(char *cstr){
    for (int i = 0; i < strlen(cstr)-1; i++){
        for(int j = 0; j < strlen(cstr)-i-1; j++){
            if(cstr[j] > cstr[j+1]){
                char aux = cstr[j];
                cstr[j] = cstr[j+1];
                cstr[j+1] = aux;
            }
        }
        
    }
    
}
