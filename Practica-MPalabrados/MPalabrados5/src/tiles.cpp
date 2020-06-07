#include <string>
#include "tiles.h"
#include <cassert>
#include <iostream>

using namespace std;
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
    
    if(cell != nullptr){
        
        deallocate();
    }
    
    allocate(r,c);
}

Tiles& Tiles::operator =(const Tiles& orig){
    
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
    assert ((r>0 and r<=getHeight()) and (c > 0 and c <= getWidth()));
    return cell[r-1][c-1];
    
    assert ((r>0 and r<=getHeight()) and (c > 0 and c <= getWidth()));
    
    return cell[r-1][c-1];
}

void Tiles::set(int r, int c, char l){
    assert ((r>0 and r<= getHeight()) and (c > 0 and c <= getWidth()));

    
    assert ((r>0 && r<= getHeight()) && (c > 0 && c <= getWidth()));
    
    cell[r-1][c-1] = l; 
}

void Tiles::add(const Move& m){
    
    string letters = m.getLetters();
    bool limite=false;
    
    if(m.getRow() <= rows && m.getCol()<= columns){
        
        for(int i = 0; i < letters.size() && limite==false; i++){
            
            if(m.isHorizontal()){
                
                set(m.getRow(), m.getCol()+i, letters[i]);
            
                if(m.getCol()+i == columns){
                
                    limite=true;
                }
            }
            else{
                
                set(m.getRow()+i, m.getCol(), letters[i]);
            
                if(m.getRow()+i == rows){
                
                    limite=true;
                }
            }
        }
    }
    
}

void Tiles::print(std::ostream& os) const{
    
    for(int i=0; i<rows; i++){
        
        for(int j=0; j<columns; j++){
            
            os<<cell[i][j]<<" ";
        }
        
        os<<endl;
    }
}

bool Tiles::read(std::istream& is){
   
   bool leer=true;
    
   for(int i=1; i<rows+1 && leer==true; i++){
       
       for(int j=1; j<columns+1 && leer==true; j++){
           
            char letra;
       
            is>>letra;
            set(i,j,letra);
            
            if(get(i,j) == letra){
                
                leer=true;
            }
            else{
                leer=false;
            }
       }
   }
   
   return leer;
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
