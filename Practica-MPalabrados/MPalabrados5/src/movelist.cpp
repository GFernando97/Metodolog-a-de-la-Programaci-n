/**
 * @file movelist.cpp
 * @author DECSAI
 * @note To be implemented by students
 */
#include <iostream>
#include <fstream>
#include <cmath>
#include <cassert>
#include "move.h"
#include "movelist.h"

using namespace std;

Movelist::Movelist() {
    initialize();
}

Movelist::Movelist(int nmov)  {
    initialize();
    allocate(nmov);
}

Movelist::Movelist(const Movelist& orig) {
    initialize();
    copy(orig);
}

Movelist::~Movelist() {
    deallocate();
}

void Movelist::assign(const Movelist& orig) {

    if (this != &orig) {
        deallocate();
        copy(orig);
    }
}

Movelist& Movelist::operator=(const Movelist& orig) {
    if (this != &orig) {
        deallocate();
        copy(orig);
    }
    return *this;
}


Move Movelist::get(int p) const {    
    assert (0 <= p && p < size());
    return moves[p];
}

void Movelist::set(int p, const Move & m) {
    assert (0 <= p && p < size());
    moves[p] = m;
}


int Movelist::find(const Move& mov) const {
   for (int i = 0; i < size(); i++) {
        if (mov.getLetters() == get(i).getLetters()) { // OJO a completar posteriormetne
            return i;
        }
    }
    return -1;    
}    

void Movelist::add(const Move &mov) {
    Movelist aux(size()+1);
    for (int i=0; i<size(); i++)
        aux.set(i,get(i));
    aux.set(aux.size()-1, mov);
    deallocate();
    copy(aux);
    
    /*
    allocate(this->nMove+1);
    for (int i=0; i<size(); i++)
        set(i, aux.get(i));*/
    
}

void Movelist::remove(const Move &mov) {
    int p = find(mov);
    if (p>=0)
        remove(p);
}



void Movelist::clear() {
    deallocate();
}

int Movelist::getScore() const {
    int score=0;
    for (int i=0; i<size() && score >=0; i++) {
        if (get(i).getScore()>=0){
            score += get(i).getScore();
        } else {
            score = -1;
        }
    }
    return score;
}
void Movelist::remove(int p) {
    assert (p >= 0 && p < size());
    Movelist aux(size()-1);
    for (int i=0, j=0; i<size(); i++)
        if (i != p)
            aux.set(j++,get(i));
    (*this) = aux;
//    allocate(this->nMove-1);
//    for (int i=0; i<size(); i++)
//        set(i, aux.get(i));
}

//void Movelist::zip(const Language &s)  {
//    int pos=0;
//    if (size()==0)
//        return;
//    do {
//        cerr << "QUERY: "<<toUTF(get(pos).getLetters())<<endl;
//        if (!s.query(get(pos).getLetters()))  {
//            cerr << "REMOVE: "<<toUTF(get(pos).getLetters())<<endl;
//            remove(pos);
//        }
//        else
//            pos ++;
//    } while (pos < size());
//}

void Movelist::zip(const Language &s)  {
    for (int pos=0; pos<size();)  {
        if (!s.query(get(pos).getLetters()))  {
            remove(pos);
        }
        else
            pos ++;
    }
}


//
// Privados

void Movelist::allocate(int n) {
    //deallocate();
    if (n > 0) {
        nMove = n;
        moves = new Move[nMove];
    }
}

void Movelist::deallocate() {
    //if (moves != nullptr) { not necessary 
        delete[] moves;
        initialize();
    
}

void Movelist::copy(const Movelist& otro) {
    allocate(otro.size());
    for (int i = 0; i < otro.size(); ++i) {
        set(i,otro.get(i)); 
    }
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

bool Movelist::read(std::istream &is) {
    Move m;
    bool fin = false;
    clear();
    m.read(is);
    while (m.getLetters().size() > 1 && !fin ) { // && m.getLetters() != "_") {
        if (is.eof())
            fin = true;
        else {
            this->add(m);
            m.read(is);
        }
    }
    
    return !fin;
}



//Sobrecarga de operadores
Movelist& Movelist::operator=( Movelist &orig){
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


/**
 * @brief Overload of the insertion operator
 * @param os Output stream (cout)
 * @param m The class to be inserted in the stream
 * @return The output stream (cout)
 */
std::ostream & operator<<(std::ostream & os, const Movelist & i){
    if(i.print(os, false)){
        return os;
    }
    
    return os;
}

/**
 * @brief Overload of the extraction operator
 * @param os Input stream (cin)
 * @param m The class to be extracted from the stream
 * @return The input stream (cin)
 */
std::istream & operator>>(std::istream & is, Movelist & i){
    if(i.read(is)){
        return is;
    }
    
    return is;
}