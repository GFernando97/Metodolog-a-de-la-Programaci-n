/**
 * @file movelist.cpp
 * @author DECSAI
 * @note To be implemented by students
 * @warning Complete the code
 *  */
#include <iostream>

#include "movelist.h"
#include <cassert>

using namespace std;

void Movelist::allocate(int n){
    
    if(n>0){
        
        moves = new Move [n];
        nMove = n;
    }
}

void Movelist::deallocate(){
    
    if(moves != nullptr && nMove != 0){
        
        delete []moves;
        
        moves=nullptr;
        nMove=0;
    }
}

void Movelist::copy(const Movelist& ml){
    
    allocate(ml.size());

    for(int i = 0; i < ml.size(); i++){
        
        this->moves[i] = ml.get(i);
    }

}

Movelist::Movelist(){
    
    moves = nullptr;
    nMove = 0;
}

Movelist::Movelist(int nmov){
    
    moves=new Move [nmov];  
    nMove = nmov;
}

Movelist::Movelist(const Movelist &orig){
    
    moves=nullptr;
    nMove=0;
    copy(orig);
}

Movelist::~Movelist(){
    
    deallocate();
}

void Movelist::assign(const Movelist& orig){
    
    if(this != &orig){
        
        deallocate();
        copy(orig);
    }
}

Move Movelist::get(int p) const{
    
    assert(p>=0 && p<size());
    return moves[p];
}

void Movelist::set(int p, const Move &m){
    
    assert(p>=0 && p<nMove);
    moves[p] = m;
}

/*inline Movelist::size(){
    
    
}*/

int Movelist::find(const Move &mov) const{
    
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

void Movelist::add(const Move &mov){
    
    int nuevoNMove = nMove+1;
    
    Movelist mAux;
    
    mAux.allocate(nuevoNMove);
    
    if(nMove > 0){
        for(int i = 0; i < nMove; i++){
            mAux.set(i, moves[i]);
        }
    }
    
    mAux.set(nuevoNMove-1, mov);
    
    assign(mAux);
}

void Movelist::remove(const Move &mov){
    
    if(find(mov)!= -1){
        
        remove(find(mov));
    }
}

void Movelist::remove(int p){
    
    int newNMoves = nMove-1;
    
    Movelist mAux;
    
    mAux.allocate(newNMoves);
    
    for(int i = 0; i < nMove; i++){
        
        if(i==p){
            while(i < nMove-1){
                mAux.set(i, moves[i+1]);
                i++;
            }
            break;
        }
        else mAux.set(i, moves[i]);
    }
    
    assign(mAux);
}

void Movelist::zip(const Language &l){
    
    for(int i = 0; i < size(); i++){
        string letras = get(i).getLetters();
        
        if(!l.query(letras) || letras.size() < 2){
            
            remove(i);
            
            i = 0;
        }
    }
}

void Movelist::clear(){
    
    if(nMove > 0){
        nMove = 0;
        deallocate();
    }
}

int Movelist::getScore() const{
    
    int totalScore = 0;
    
    for(int i = 0; i < nMove; i++){
        if(get(i).getScore() != -1){
            totalScore += get(i).getScore();
        }
        
        else return -1;  
    }
    
    return totalScore;
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
    
    string finalizador = normalizeWord("@");
    bool finalizadorEncontrado = false;
    
    do{

        Move aux;
        
        aux.read(is);
        
        string letrasMov = aux.getLetters();
        
        size_t found = aux.getLetters().find(finalizador);
        
        if ((found!=std::string::npos) and (letrasMov.size()==1)){
            finalizadorEncontrado=true;
        }
        else if((!finalizadorEncontrado) and (letrasMov.size() < 1)){
            return false;
        }
        else add(aux);
        
    }while(!finalizadorEncontrado );
    
    return finalizadorEncontrado;
}

Movelist&  Movelist::operator=( const Movelist &orig){
    
    if (this != &orig) {
        deallocate();
        copy(orig);
    }
    return *this;
}

Movelist&  Movelist::operator+=( Move &mov){
    add(mov);
    return *this;
}

std::ostream & operator<<(std::ostream & os, const Movelist & i){
    
    if(i.print(os, false)){
        return os;
    }
    
    return os;
}

std::istream & operator>>(std::istream & is, Movelist & i){
    
    if(i.read(is)){
        return is;
    }
    
    return is;
}
