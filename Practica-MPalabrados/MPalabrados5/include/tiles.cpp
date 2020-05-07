/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   tiles.cpp
 * Author: reko98
 * 
 * Created on 7 de mayo de 2020, 14:12
 */
#include<string>
#include "tiles.h"


//Métodos Públicos

Tiles::Tiles(){
    columns = 0;
    rows = 0;
    cell = nullptr;
    
}

Tiles::Tiles(int r, int c){
    setSize(r,c);
    
    
}

Tiles::Tiles(const Tiles& orig){
    copy(orig);
    
    
}

Tiles::~Tiles(){
    deallocate();
    
}

void Tiles::setSize(int r, int c){
    allocate(r,c);
    
}

Tiles& Tiles::operator =(Tiles& orig){
    if(this!= &orig){
        deallocate();
        copy(orig);
    }
    
    return *this;
    
}

int Tiles::getWidth() const{
    return columns;
    
}

int Tiles::getHeight() const{
    return rows;
    
    
}

char Tiles::get(int r, int c) const{
    assert ((r>=0 and r<getHeight()) and (c >= 0 and c < getWidth()));
    return cell[r][c];
    
}

void Tiles::set(int r, int c, char l){
    assert ((r>=0 and r< getHeight()) and (c >= 0 and c < getWidth()));
    cell[r][c] = l; 
}

void Tiles::add(const Move& m){
    string letters = m.getLetters();
    
   
        for(int i = 0; i < letters.size(); i++){
            if(m.isHorizontal())
                set(m.getRow(), m.getCol()+i, letters[i]);
            
            else{
                set(m.getRow()+i, m.getCol(), letters[i]);
            }
        }
    
}

void Tiles::print(std::ostream& os) const{
    
    
}

bool Tiles::read(std::istream& is){
   int nColumns;
   int nRows;
   
    
}

void Tiles::allocate(int r, int c){
    if((r > 0 ) and (c > 0)){
      
        this->rows = r;
        this->columns= c;
        cell = new char *[r];
        
        for(int i = 0; i < r; i++)
            cell[i] = new char[c];
    }
    
}

void Tiles::deallocate(){
    
    for(int i = 0; i < getHeight(); i++)
        delete [] cell[i];
        
    delete [] cell;
    this->rows = 0;
    this->columns = 0;
}

void Tiles::copy(const Tiles &t) {
    allocate(t.getHeight(), t.getWidth());
    
    for(int i = 0; i < getHeight(); i++){
        for(int j = 0; j < getWidth(); j++)
            set(i,j, t.get(i,j));
    }
}
