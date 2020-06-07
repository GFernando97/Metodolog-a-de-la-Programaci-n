#include <string>
#include "tiles.h"
#include <cassert>
#include <iostream>
#include "move.h"

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
}

void Tiles::set(int r, int c, char l){
    
    assert ((r>0 && r<= getHeight()) && (c > 0 && c <= getWidth()));
    
    cell[r-1][c-1] = l; 
}

void Tiles::add(const Move& m){
    
    string letters = m.getLetters();
    int espacio=0;
    bool empezar=true;
    
    if(m.isHorizontal()){
        
        for(int i=m.getCol();i<=columns && empezar;i++){
            
            if(get(m.getRow(),i)=='.'){
                
                espacio++;
            }
            else{
                
                if(i==m.getCol()){
                    espacio=0;
                    empezar=false;
                }
            }
        }
    }
    else{
        
        for(int i=m.getRow();i<=rows && empezar;i++){
            
            if(get(i,m.getCol())=='.'){
                
                espacio++;
            }
            else{
                
                if(i==m.getRow()){
                    
                    espacio=0;
                    empezar=false;
                }
            }
        }
    }
    
    if(m.getRow() <= rows && m.getCol()<= columns && espacio>=letters.size()){
        
        for(int i = 0; i < letters.size(); i++){
            
            bool puesta=false;
            
            if(m.isHorizontal()){
                
                for(int j=m.getCol();j<=columns && !puesta;j++){
                
                    if(get(m.getRow(),j) == '.'){
                    
                        set(m.getRow(), j, letters[i]);
                        puesta=true;
                    }
                }
            }
            else{
                
                for(int j=m.getRow();j<=rows && !puesta;j++){
                
                    if(get(j,m.getCol()) == '.'){
                    
                        set(j, m.getCol(), letters[i]);
                        puesta=true;
                    }
                }
            }
        }
    }
    
}

void Tiles::print(std::ostream& os) const{
    
    for(int i=0; i<rows; i++){
        
        for(int j=0; j<columns; j++){
            
            os<<toUTF(cell[i][j])<<" ";
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
    
    for(int i = 1; i < getHeight()+1; i++){
        for(int j = 1; j < getWidth()+1; j++)
            set(i,j, t.get(i,j));
    }
}

Move Tiles::findMaxWord(int r, int c, bool hrz) const{
    
    string palabra="";
    bool pos=false, fin=false;
    int fila,columna;
    char letra, horizontal;
    Move MaxWord;
    
    if(hrz){
        
        for(int i=c;i>=1 && !pos;i--){
            
            if(get(r,i) != '.'){
                
                fila=r;
                columna=i;
            }
            else{
                
                pos=true;
            }
        }
        
        for(int i=columna;i<=getWidth() && !fin;i++){
            
            if(get(r,i) == '.'){
                
                fin=true;
            }
            
            if(!fin){
            
                letra=get(r,i);
                palabra=palabra+letra;
            }
        }
        
        horizontal='h';
        
        MaxWord.set(fila,columna,horizontal,palabra);
    }
    else{
        
        for(int i=r;i>=1 && !pos;i--){
            
            if(get(i,c) != '.'){
                
                fila=i;
                columna=c;
            }
            else{
                
                pos=true;
            }
        }
        
        for(int i=fila;i<=getHeight() && !fin;i++){
            
            if(get(i,c) == '.'){
                
                fin=true;
            }
            
            if(!fin){
            
                letra=get(i,c);
                palabra=palabra+letra;
            }
        }
        
        horizontal='v';
        
        MaxWord.set(fila,columna,horizontal,palabra);
    }
    
    return MaxWord;
}

Movelist Tiles::findCrosswords(const Move& m, const Language& l) const{

    Movelist cruces;
    Move aux;
    char horizontal;
    
    if(m.isHorizontal()){
        
        horizontal='h';
    }
    else{
        
        horizontal='v';
    }
    
    aux.set(m.getRow(),m.getCol(),horizontal,m.getLetters());
    
    string movimiento=m.getLetters();
    Tiles copia(*this);
    int longitud=0, pos=0,espacio=0;
    bool fin=false,empezar=true;

    if(m.isHorizontal()){
        
        for(int i=m.getCol();i<=columns && empezar;i++){
            
            if(get(m.getRow(),i)=='.'){
                
                espacio++;
            }
            else{
                
                if(i==m.getCol()){
                    espacio=0;
                    empezar=false;
                }
            }
        }
    }
    else{
        
        for(int i=m.getRow();i<=rows && empezar;i++){
            
            if(get(i,m.getCol())=='.'){
                
                espacio++;
            }
            else{
                
                if(i==m.getRow()){
                    
                    espacio=0;
                    empezar=false;
                }
            }
        }
    }

    if(espacio>=m.getLetters().size()){
        
        copia.add(m);

        if(m.isHorizontal()){
        
            for(int i=m.getCol();i<=getWidth() && !fin;i++){
            
                if(copia.get(m.getRow(),i) != '.'){
                
                    longitud++;
                }
                else{
                
                    fin=true;
                }
            }
        }
        else{
        
            for(int i=m.getRow();i<=getHeight() && !fin;i++){
            
                if(copia.get(i,m.getCol()) != '.'){
                
                    longitud++;
                }
                else{
                
                    fin=true;
                }
            }
        }
    }
    
    
    for(int i=0; i<longitud;i++){
        
        if(m.isHorizontal()){
            
            if(copia.get(m.getRow(),m.getCol()+i)==movimiento[pos]){
            
                if(i==0){
                
                    Move cw1=copia.findMaxWord(m.getRow(),m.getCol()+i,m.isHorizontal());
                    Move cw2=copia.findMaxWord(m.getRow(),m.getCol()+i,!m.isHorizontal());
                    
                    if(cw1.getLetters().size() > 1){
                        
                        cruces.add(cw1);
                    }
                    
                    if(cw2.getLetters().size() > 1){
                        
                        cruces.add(cw2);
                    }
                }
                else{
                    
                    Move cw3=copia.findMaxWord(m.getRow(),m.getCol()+i,!m.isHorizontal());
                    
                    if(cw3.getLetters().size() > 1){
                        
                        cruces.add(cw3);
                    }
                }
                
                pos++;
            }
        }
        else{
            
            if(copia.get(m.getRow()+i,m.getCol())==movimiento[pos]){
                
                if(i==0){
                    
                    Move cw1=copia.findMaxWord(m.getRow()+i,m.getCol(),m.isHorizontal());
                    Move cw2=copia.findMaxWord(m.getRow()+i,m.getCol(),!m.isHorizontal());
                    
                    if(cw1.getLetters().size() > 1){
                        
                        cruces.add(cw1);
                    }
                    
                    if(cw2.getLetters().size() > 1){
                        
                        cruces.add(cw2);
                    }
                }
                else{
                    
                    Move cw3=copia.findMaxWord(m.getRow()+i,m.getCol(),!m.isHorizontal());
                    
                    if(cw3.getLetters().size() > 1){
                        
                        cruces.add(cw3);
                    }
                }
                
                pos++;
            }
        }
    }
    
    if(espacio==0){
        
        aux.setScore(NOT_FREE);
        cruces.add(aux);
    }
    else if(espacio < m.getLetters().size()){
        
        aux.setScore(BOARD_OVERFLOW);
        cruces.add(aux);
    }
    else if(cruces.size()==1 &&  cruces.get(0).getLetters()==m.getLetters()){
        
        Move cp;
        char direccion;
        
        if(aux.isHorizontal()){
        
            direccion='h';
        }
        else{
        
            direccion='v';
        }
        
        cp.set(cruces.get(0).getRow(),cruces.get(0).getCol(),direccion,cruces.get(0).getLetters());
        cp.setScore(MISSING_CROSSWORDS);
        
        cruces.set(0,cp);
    }
    else if(cruces.size()==1 && cruces.get(0).getLetters()!=m.getLetters()){
        
        Move cp;
        char direccion;
        int puntuacion=0;
        
        if(aux.isHorizontal()){
        
            direccion='h';
        }
        else{
        
            direccion='v';
        }
        
        cp.set(cruces.get(0).getRow(),cruces.get(0).getCol(),direccion,cruces.get(0).getLetters());
        
        if(l.query(cp.getLetters())){
            
            puntuacion=cp.findScore(l);
        }
        else{
            
            puntuacion=NONEXISTENT_WORD;
        }
        
        cp.setScore(puntuacion);
        
        cruces.set(0,cp);
    }
    else if(cruces.size() > 1){
        
        for(int i=0;i<cruces.size();i++){
            
            Move cp;
            char direccion;
            int puntuacion=0;
        
            if(cruces.get(i).isHorizontal()){
        
                direccion='h';
            }
            else{
        
                direccion='v';
            }
            
            cp.set(cruces.get(i).getRow(),cruces.get(i).getCol(),direccion,cruces.get(i).getLetters());
        
            if(l.query(cp.getLetters())){

                puntuacion=cp.findScore(l);
            }
            else{

                puntuacion=NONEXISTENT_WORD;
            }
        
            cp.setScore(puntuacion);
        
            cruces.set(i,cp);
        }
    }
    
    return cruces;
}

ostream&  operator<<(ostream &os, const Tiles &tile){
    
    for(int i=0; i<tile.getHeight(); i++){
        
        for(int j=0; j<tile.getWidth(); j++){
            
            os<< toUTF(tile.get(i+1, j+1)) << " ";
        }
        
        os<<endl;
    }
    
    return os;
}

istream& operator>>(istream &is, Tiles &tile){
    
    char letra;
   
    for (int f = 1; f < tile.getHeight()+1; f++) {
        for (int c = 1; c < tile.getWidth()+1; c++) {
            is >> letra;
            tile.set(f,c, letra);
        }
    }
    
    return is;
}
