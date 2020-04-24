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
        Move* nPuntero = new Move [n];
     
        delete []moves;
        moves = nPuntero;
        nMove = n;        
}

void Movelist::deallocate(){
        delete [] moves;
        nMove = 0;

}


//REVISAR!!!!!
void Movelist::copy(const Movelist& ml){

    this->nMove = ml.size();
    deallocate();
    allocate(nMove);

    for(int i = 0; i < nMove; i++)
        this->moves[i] = ml.moves[i];
   

}

Movelist::Movelist(){
    moves = nullptr;
    nMove = 0;
}

Movelist::Movelist(int nmov){
    nMove = nmov;
    allocate(nmov);
}


//Revisar!!!!!
Movelist::Movelist(const Movelist &orig){
    copy(orig);
}

Movelist::~Movelist(){
    deallocate();
}



///FALTAAAA!!!
void Movelist::assign(const Movelist& orig){
   
    this->nMove = orig.size();
    this->allocate(orig.size());
    
    
    for(int i = 0; i < nMove; i++){
        this->moves[i] = orig.moves[i];
    }
    
    
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



void Movelist::add(Move &mov){
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

void Movelist::remove(Move &mov){
    if(find(mov)!= -1)
        remove(find(mov));
    
}

void Movelist::remove(int p){
    int newNMoves = nMove-1;
    Move* mAux = new Move[newNMoves];
    
    for(int i = 0; i < nMove; i++){
        if(i==p){
            while(i < nMove-1){
                mAux[i]=moves[i+1];
                i++;
            }
        break;
        }
    }
    
    allocate(newNMoves);
    moves = mAux;
    
}

void Movelist::zip(Language l){
    
    for(int i = 0; i < nMove; i++){
        string letras = get(i).getLetters();

        if(!l.query(letras)){
            remove(i);
                    cout << "Entra aqui" << endl;

        }
    }
    
}

void Movelist::clear(){
    if(nMove > 0){
        nMove = 0;
        deallocate();
    }
}



int Movelist::getScore()const{
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


//FALTAAAAAAA
bool Movelist::read(std::istream& is){
    string finalizador = normalizeWord("@");
    int lectura = 0;
    bool finalizadorEncontrado = false;
    
    do{
        lectura++;
        cout << "Lectura numero: " << lectura << endl;
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

