/**
 * @file move.cpp
 * @author DECSAI
 * @note To be implemented by students
 */
#include <string>

#include "move.h"

using namespace std;

Move::Move(){
    
    row=0;
    column=0;
    ishorizontal=true;
    letters="";
    score=0;
}

void Move::set(int r, int c, char h, const std::string& l){
    
    row=r;
    column=c;
    
    if(h=='V' || h=='v'){
        
        ishorizontal=false;
    }
    else{
        
        ishorizontal=true;
    }
    
    letters=normalizeWord(l);
}

void Move::setRow(int r){
    
    row=r;
}

void Move::setCol(int c){
    
    column=c;
}

void Move::setHorizontal(char h){
    
    if(h=='V' || h=='v'){
        
        ishorizontal=false;
    }
    else{
        
        ishorizontal=true;
    }
}

void Move::setLetters(const string &l){
    letters = normalizeWord(l);
}

int Move::findScore(const Language& l) const{
    
    int puntos=0;
    
    if(l.query(letters)==false){
        
        puntos=-1;
    }
    else{
        
        for(int i = 0; i < letters.size(); i++){
            
            puntos = puntos + l.getScore(letters[i]);
        }
    }
    
    return puntos;
}

void Move::setScore(int s){
    
    score=s;
}

int Move::getScore() const{
    
    return score;
}

int Move::getRow() const{
    
    return row;
}

int Move::getCol() const{
    
    return column;
}

bool Move::isHorizontal() const{
    
    return ishorizontal;
}

std::string Move::getLetters() const{
    
    return letters;
}

void Move::print(std::ostream& os) const{
    
    if(ishorizontal){
        
        os << "H"<<" ";
    }
    else{
        
        os << "V"<<" ";
    }
    
    os << row <<" "<< column <<" "<< letters;
    
}

void Move::read(std::istream &is) {

  //@warging reading
  //@ set the others fields of move
    char horizontal;
    int fila,columna;
    string letras="";
    
    is>>horizontal;
    is>>fila;
    is>>columna;
    is>>letras;
    
    setHorizontal(horizontal);
    setRow(fila);
    setCol(columna);
    setLetters(letras);
    letters = normalizeWord(letters);
}
