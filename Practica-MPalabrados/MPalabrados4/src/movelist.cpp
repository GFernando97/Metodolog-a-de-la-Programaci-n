/**
 * @file movelist.cpp
 * @author DECSAI
 * @note To be implemented by students
 * @warning Complete the code
 *  */
#include <iostream>

#include "movelist.h"

using namespace std;


void Movelist::allocate(int n){
    if (n!= nMove){
        Move* nPuntero = new Move [n];
     
        delete []moves;
        moves = nPuntero;
        nMove = n;       
    }  
}

void Movelist::deallocate(){
    if(nMove!=0){
        delete [] moves;
        nMove = 0;
    }
}

void Movelist::copy(const Movelist& ml){

    this->nMove = ml.size();

    for(int i = 0; i < nMove; i++)
        this->moves[i] = ml.moves[i];
   

}

Movelist::Movelist(){
    moves = nullptr;
    nMove = 0;
}

Movelist::Movelist(int nmov){
    
    allocate(nmov);
}

Movelist::Movelist(const Movelist &orig){
    copy(orig);
}

Movelist::~Movelist(){
    deallocate();
}

void Movelist::assign(const Movelist& orig){
    
}

Move Movelist::get(int p)const{
    return moves[p];
}

void Movelist::set(int p, Move &m){
    moves[p] = m;
    
}

int Movelist::find( const Move &mov) const{
    for(int i = 0; i < nMove; i++){
        if(get(i).getCol() == mov.getCol())
            if(get(i).getRow() == mov.getRow())
                if(get(i).isHorizontal() == mov.isHorizontal())
                    if(get(i).getScore() == mov.getScore())
                        if(get(i).getLetters() == mov.getLetters())
                            return i;  
    }
    
    return -1;
    
}



void Movelist::add(Move mov){
   
    Move* mAux = new Move[nMove+1];
    
    for(int i = 0; i < nMove; i++)
        mAux[i] = moves[i];
    
    mAux[nMove] = mov;
    
    deallocate();
    allocate(nMove+1);
    moves = mAux;
    
}

void Movelist::remove(Move &mov){
    if(find(mov)!= -1)
        remove(find(mov));
    
}

void Movelist::remove(int p){
    
    Move* mAux = new Move[nMove-1];
    
    for(int i = 0; i < nMove; i++){
        if(i != p)
            mAux[i] = moves[i];
    }
    
    deallocate();
    allocate(nMove+1);
    moves = mAux;
    
}

void Movelist::zip(Language l){
    for(int i = 0; i < nMove; i++){
        if(l.query(get(i).getLetters())){
            this->remove(i);
        }
    }
    
}

void Movelist::clear(){
    if(nMove > 0){
        nMove = 0;
        deallocate();
    }
}

int Movelist::getScore(){
    return 0;
    
}

bool Movelist::print(std::ostream &os, bool scores) const {
    bool res=true;
    for (int i=0; i<size() && res; i++) {
        get(i).print(os);
        if (scores)
            os << " ("<<get(i).getScore()<<") - ";
        else
            os << " - ";
        if (os.bad())
            res=false;
    }
    return res;
}

bool Movelist::read(std::istream& is){
    return false;
    
}

