/**
 * @file main.cpp
 * @author DECSAI
 * @note To be implemented by students either completely or by giving them
 * key functions prototipes to guide the implementation
 */



#include <string>
#include <cassert>
#include <iostream>
#include <random>
#include <fstream>
#include <cmath>
#include "language.h"
#include "bag.h"
#include "player.h"
#include "move.h"
#include "movelist.h"
#include "tiles.h"
#include "window.h"
#include "AnsiTerminal.h"
using namespace std;


#define ERROR_ARGUMENTS 1
#define ERROR_OPEN 2
#define ERROR_DATA 3
#define GENERAL_ERROR 4
#define PASSWORD "MPALABRADOS-V2"

// Alumno1: apellidos nombre
// Alumno2: apellidos nombre

/**
 * @brief Reports an important error and exits the program
 * @param errorcode An integer representing the error detected, which is represented
 * by several symbolic constants: ERROR_ARGUMENTS, ERROR_OPEN y ERROR_DATA
 * @param errorinfo Additional information regarding the error: "" (empty string) for 
 * errors parsing the arguments to main() and, for the case of errors opening or 
 * reading/writing data, the name of the file thas has failed.
 */
void errorBreak(int errorcode, const string & errorinfo);

void HallOfFame(bool guardar, const Game &game);

/**
 * @brief Main function. 
 * @return 
 */
int main(int nargs, char * args[]) {
    Move move;
    Game game;
    int w=-1, h=-1, wait=0;
    string lang="",ifilematch="", ofilematch="", word;
    ifstream ifile, archivopartida; ofstream ofile,archivoguardar;
    istream *input=&cin;ostream *output=&cout;
    bool end=false;
	 char c;
    bool encontrado=false;
    bool nueva=true;
    bool lenguaobligatorio=false;
    int ancho=0, alto=0, random;
    bool anchoobligatorio=false;
    bool altoobligatorio=false;
    string partida="";
    bool partidaobligatorio=false;
    string guardar="";
    string bolsa="";
    bool haybolsa=false;
    bool guardarpartida=false;
    bool numeroaleatorio=false;
    string nombre="", letrasplayer="";
    int puntuacion;
    int numeroplayer,numerobolsa;
    int movimientosaceptados, movimientosrechazados;
    int score=0, tirada=1;
    bool valido=true;
    Movelist totalmov;
    
    /// Check arguments

    for(int i=1; i<nargs && encontrado==false; i++){
        
        string opcion=args[i];
        
        if(opcion=="-l"){
            
            nueva=true;
            encontrado=true;
        }
        else if(opcion=="-open"){
            
            nueva=false;
            encontrado=true;
        }
    }
 
    if(nueva){
        
        if(nargs < 6 || nargs > 13){
            
            errorBreak(1,"");
        }
        
        for(int i=1; i<nargs-1;i++){
            
            string parametro=args[i];
            string siguienteparametro=args[i+1];
            
            if(parametro=="-l"){
                
                lang=siguienteparametro;
                lenguaobligatorio=true;
            }
            else if(parametro=="-w"){
                
                ancho=stoi(siguienteparametro);
                anchoobligatorio=true;
            }
            else if(parametro=="-h"){
                
                alto=stoi(siguienteparametro);
                altoobligatorio=true;
            }
            else if(parametro=="-r"){
                
                random=stoi(siguienteparametro);
                numeroaleatorio=true;
            }
            else if(parametro=="-b"){
                
                bolsa=siguienteparametro;
                haybolsa=true;
            }
            else if(parametro=="-save"){
                
                guardar=siguienteparametro;
                guardarpartida=true;
            }
        }
    }
    else{
        
        if(nargs < 3 || nargs > 5){
            
            errorBreak(1,"");
        }
        
        for(int i=0;i<nargs-1;i++){
            
            string parametro=args[i];
            string siguienteparametro=args[i+1];
            
            if(parametro=="-open"){
                
                partida=siguienteparametro;
                partidaobligatorio=true;
            }
            else if(parametro=="-save"){
                
                guardar=siguienteparametro;
                guardarpartida=true;
            }
        }
    }
    
    if(nueva){
        
        if(!lenguaobligatorio || !anchoobligatorio || !altoobligatorio){
            
            errorBreak(1,"");
        }
    }
    else{
        
        if(!partidaobligatorio){
            
            errorBreak(1,"");
        }
    }
         
    // Process arguments
    
    if(nueva){
        
        game.language.setLanguage(lang);
        game.bag.define(lang);
        game.tiles.setSize(alto,ancho);
        
        for(int i=1;i<alto+1;i++){
            
            for(int j=1;j<ancho+1;j++){
                
                game.tiles.set(i,j,'.');
            }
        }
        
        game.bag.setRandom(random);
        
        if(haybolsa){
            
            bolsa=toISO(bolsa);
            game.bag.set(bolsa);
        }
        
        string extraer=game.bag.extract(7-game.player.size());
        
        game.player.add(extraer);
        
        game.score=0;
    }
    else{
        
        archivopartida.open(partida.c_str());
                
        if(!archivopartida){
                
            errorBreak(2,partida);
        }
        
        input=&archivopartida;
        
        (*input)>>game;
        
        if((*input).eof()){
            
            errorBreak(3,partida);
        }
        
        archivopartida.close();
    }
    
    /// load data from file, if asked to in arguments

    // Game's main loop 
    // 1) First set the size of the window according to the size (rows & columns) of
    // the new Tiles
    
    game.setWindowSize();
    
    while (!end)  {
        // 2) Given the inner data members, it pretty-prints the screen
        
        game.doPaint();
        
        // 3) Reads the movement from cin
        
        string extraer=game.bag.extract(7-game.player.size());
        
        game.player.add(extraer);
        
        setCursorOn();
        cin >> move;
        setCursorOff();
        word = move.getLetters();
        
        if (word=="_")
            end=true;
        
        // Checks whether the movement is valid accoring to the letters in player
        if(!end){
            
            score=0;
            valido=true;
        
            if(game.player.isValid(word)){
            
                // Finds all the crosswords produced by move

                game.crosswords = game.tiles.findCrosswords(move,game.language.getLanguage());

                //Checks that the crosswords are valid, that is either has a positive score
                //      or produces at least a cross with other existin letters
                
                for(int i=0;i<game.crosswords.size() && valido;i++){
                
                    if(game.crosswords.get(i).getScore() < 0){
                    
                        if(tirada==1){
                        
                            int puntuacion=game.crosswords.get(0).findScore(game.language.getLanguage());
                            
                            Move cp;
                            char direccion;
        
                            if(game.crosswords.get(0).isHorizontal()){
        
                                direccion='h';
                            }
                            else{
        
                            direccion='v';
                            }
        
                            cp.set(game.crosswords.get(0).getRow(),game.crosswords.get(0).getCol(),direccion,game.crosswords.get(0).getLetters());
                            cp.setScore(puntuacion);
            
                            game.crosswords.set(0,cp);
                        }
                        else{
                        
                            valido=false;
                        }
                    }
                }
                // If valid, computes the score and adds it
                if(valido){
                
                    if(game.crosswords.size()  > 0){
                        
                        game.tiles.add(move);
                        game.acceptedmovements.add(move);

                        for(int i=0;i<totalmov.size();i++){
                    
                            for(int j=0;j<game.crosswords.size();j++){

                                if(game.crosswords.get(j).getLetters()==totalmov.get(i).getLetters() &&
                                   game.crosswords.get(j).getCol()==totalmov.get(i).getCol() &&
                                   game.crosswords.get(j).getRow()==totalmov.get(i).getRow() &&
                                   game.crosswords.get(j).isHorizontal()==totalmov.get(i).isHorizontal()){
                            
                                    game.crosswords.remove(j);
                                    j=0;
                                }
                            }
                        }

                        for(int i=0;i<game.crosswords.size();i++){
                    
                            totalmov.add(game.crosswords.get(i));
                            score +=game.crosswords.get(i).getScore();
                        }
                    
                        game.score=game.score+score;
                        cout << "Scored "<<score<<" points"<<endl; 
                
                        // Show crosswords found
                
                        game.showCrosswords();
                        game.player.extract(word);
                    }
                    else{
                        
                        game.rejectedmovements.add(move);
                        game.showCrosswords();
                        cout << "Bad crosswords"<<endl;
                    }
                }
                else{
                
                // If it is a bad crosswords
                
                    game.rejectedmovements.add(move);
                
                // Show crosswords found

                    game.showCrosswords();
                    cout << "Bad crosswords"<<endl;
                }
            }
            else{
            
                // If not valid w.r.t. player
                move.setScore(INFEASIBLE_WORD);
                game.crosswords.add(move);
                game.rejectedmovements.add(move);
                game.showCrosswords();
            
                cout <<"Infeasible word"<<endl;
            }        
                // Waits for the next move

            bool confirmar= game.doConfirmCrosswords("confirmar movimiento?");
                
            tirada++;
        
            string aniadir=game.bag.extract(7-game.player.size());
        
            game.player.add(aniadir);
            cout<<toUTF(game.player.to_string())<<endl;
            
        }
    }

    // End of game
    // Save file or print screen
    
    if(guardarpartida){
        
        archivoguardar.open(guardar.c_str());
        
        if(!archivoguardar){
            
            errorBreak(2,guardar);
        }
        
        output=&archivoguardar;
        
        (*output)<<game;
    }
    
    HallOfFame(guardarpartida,game);
    
    return 0;
}

ostream & operator<<(ostream & os, const Game & game)  {
    // To implement
    
    //os << "MPALABRADOS-V2" << endl;
    os << game.score << endl;
    os << game.language.getLanguage() << endl;
    os << game.tiles.getHeight() << " " << game.tiles.getWidth() << endl;
    os << game.tiles << endl;
    os << game.player.size() << " " << game.player.to_string() << endl;
    os << game.bag.size() << " " << game.bag.to_string() << endl;
    os << game.acceptedmovements.size()<<endl;
    os << game.acceptedmovements<<endl;
    os << game.rejectedmovements.size()<<endl;
    
    if(game.rejectedmovements.size() > 0){
        
        os << game.rejectedmovements << endl;
    }
    
    return os;
}

istream & operator>>(istream & is, Game &game) {
    // To implement
    string palabraMagica;
    int puntuacionAct;
    string lang;
    int sizePlayer;
    string playerState;
    int sizeBag;
    string bagState;
    int f,c, movimientosaceptados=0,movimientosrechazados=0;
    
    is >> palabraMagica;
    is >> puntuacionAct;
    is >> lang;
    
    is>>f;
    is>>c;
    game.tiles.setSize(f,c);

    is >> game.tiles;
    is>> sizePlayer >> playerState;
    is>> sizeBag >> bagState;
    bagState=toISO(bagState);
    
    
    game.language.setLanguage(lang);
    game.score = puntuacionAct;
    game.player.add(toISO(playerState));
    game.bag.define(game.language);
    game.bag.set(bagState);
    
    is>>movimientosaceptados;
    
    if(movimientosaceptados > 0){
            
        for(int i=0;i<movimientosaceptados;i++){
        
            Move aux;
            char horizontal;
            int fila,col;
            string letras="";
            
            is>>horizontal;
            is>>fila;
            is>>col;
            is>>letras;
            
            aux.set(fila,col,horizontal,letras);
            
            game.acceptedmovements.add(aux);
            }
        }
    
    is>>movimientosrechazados;
        
    if(movimientosrechazados > 0){
            
        for(int i=0;i<movimientosrechazados;i++){
            
            Move aux;
            char horizontal;
            int fila,col;
            string letras="";
            
            is>>horizontal;
            is>>fila;
            is>>col;
            is>>letras;
            
            aux.set(fila,col,horizontal,letras);
            
            game.rejectedmovements.add(aux);
        }
    }
    
    return is;
}
 

void errorBreak(int errorcode, const string &errordata) {
    cerr << endl << "%%%OUTPUT" << endl;
    switch(errorcode) {
        case ERROR_ARGUMENTS:
            cerr<<"Error in call. Please use either:"<<endl;
            cerr<< "-l <language> -w <width> -h <height> [-b <bag> -r <randomnumber> -save <matchfile>]"<<endl;
            cerr<< "-open <matchfile> [-save <matchfile>]"<<endl;            
            break;
        case ERROR_OPEN:
            cerr<<"Error opening file "<<errordata << endl;
            break;
        case ERROR_DATA:
            cerr<<"Data error in file "<<errordata << endl;
            break;
        case GENERAL_ERROR:
            cerr<<"Error: "<<errordata << endl;
            break;
    }
    std::exit(1);
}

void HallOfFame(bool guardar, const Game &game) {
    cout << endl << "%%%OUTPUT" << endl;
    if(guardar==true){
        cout<<"MPALABRADOS-V2"<<endl;
    }
    cout << game;
}
