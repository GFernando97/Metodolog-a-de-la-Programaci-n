/**
 * @file main.cpp
 * @author DECSAI
 * @note To be implemented by students either completely or by giving them
 * key functions prototipes to guide the implementation
 */

#include <iostream>
#include <string>
#include <fstream>

#include "language.h"
#include "bag.h"
#include "move.h"
#include "player.h"
#include "movelist.h"
using namespace std;

#define ERROR_ARGUMENTS 1
#define ERROR_OPEN 2
#define ERROR_DATA 3
/**
 * @brief Reports an important error and exits the program
 * @param errorcode An integer representing the error detected, which is represented
 * by several symbolic constants: ERROR_ARGUMENTS, ERROR_OPEN y ERROR_DATA
 * @param errorinfo Additional information regarding the error: "" (empty string) for 
 * errors parsing the arguments to main() and, for the case of errors opening or 
 * reading/writing data, the name of the file thas has failed.
 */
void errorBreak(int errorcode, const string & errorinfo);

/**
 * @brief Shows final data
 * @param l Language
 * @param random Random seed
 * @param b Final bag
 * @param p Final player
 * @param original
 * @param legal
 * @param accepted
 * @param rejected
 */
void HallOfFame(const Language &l, int random, const Bag &b, const Player &p, 
        const Movelist& original,const Movelist& legal,
        const Movelist& accepted,const Movelist& rejected);



/**
 * @brief Main function. 
 * @return 
 */
int main(int nargs, char * args[]) {
    Bag bag;
    Player player;
    Language language;
    Move move;
    Movelist movements,        /// Original list of movements
            legalmovements,    /// Movements with legal words upon the dictionary
            acceptedmovements, /// Movements accepted in the game
            rejectedmovements; /// Movements not accepted in the game
    string lang="", goodmoves="", badmoves="", ifilename="", ofilename="";
    int random=-1, nwords=0, score=0;
    ifstream ifile; ofstream ofile;
    istream *input=&cin; ostream *output;
    bool Lobligatorio=false, Pobligatorio = false, haybolsa=false;
    int contador=0;
    string fichero="",bolsa="";
    /// @warning: Declare more vars when needed
    
    /// @warning: Check arguments

    if(nargs < 3 || nargs > 9){
        
        errorBreak(1,"");
    }
    
    for(int i = 1; i < nargs-1; i++){
        
        string parametro = args[i];
        string siguienteparametro = args[i+1];
        
        
        if(parametro == "-l"){
                
            lang=siguienteparametro;
            language.setLanguage(lang);
            cout <<"LANGUAGE: "<<lang<<endl;
            cout << "ALLOWED LETTERS: " << toUTF(language.getLetterSet()) <<endl;
            Lobligatorio=true;
        }
        
        else if(parametro == "-p"){
            Pobligatorio = true;
             ifilename=siguienteparametro;
            ifile.open(ifilename.c_str());
            
            if(!ifile){
                
                errorBreak(2,ifilename);
            }
            
            input=&ifile;
            
            
        }

        else if(parametro == "-r"){
            
            random=stoi(siguienteparametro);
        }
        else if(parametro == "-b"){
            
            bolsa=siguienteparametro;
            haybolsa=true;
        }
    }
    
    
    if(!Lobligatorio or !Pobligatorio){
        
        errorBreak(1,"");
    }
    
    if(haybolsa==false){
        
        bag.setRandom(random);
        bag.define(language);
        cout<<"SEED: "<<random<<endl;
        cout<<"BAG"<<" ("<<bag.size()<<") :"<<bag.to_string()<<endl;
    }
    else{
        
        bolsa=toISO(bolsa);
        bag.set(bolsa);
        cout<<"SEED: "<<random<<endl;
        cout<<"BAG"<<" ("<<bag.size()<<") :"<<bag.to_string()<<endl;
    }
    

    cout<<"Reading from "<<ifilename<<endl;
    bool leido = movements.read(*input);

    if(!leido){
       errorBreak(3, ifilename);
    }
    
    
    else{
        
        //Crea Lista de movimientos legales en el lenguaje
        legalmovements.assign(movements);
        legalmovements.zip(language); 
        
        
        for(int i = 0; i < movements.size(); i++){
            string extraer=bag.extract(7-player.size());

            player.add(extraer);

            cout<<"PLAYER: "<<player.to_string()<<endl<<endl;
            
            
            Move aux = movements.get(i);
            int pos = legalmovements.find(aux);
            string letrasMov = aux.getLetters();
            
            //SI LA PALABARA ES VALIDA PARA EL JUGADOR
            //Y SE ENCUENTRA DENTRO DEL DICCIONARIO DEL LENGUAJE
            //SE INTRODUCE DENTRO DE LOS MOV ACEPTADOS
            if(player.isValid(letrasMov)){
                if(pos != -1){

                    int puntuacion = aux.findScore(language);
                    aux.setScore(puntuacion);
                    acceptedmovements.add(aux);
                    cout <<"WORD " << letrasMov << " FOUND! "<<puntuacion<<" points"<<endl<<endl;
                }
                
            player.extract(letrasMov);

            }
            
            //SI LA PALABRA NO SE ENCUENTRA DENTRO DEL DICCIONARIO
            //ES  INVALIDA
            else if(pos == -1){
                    cout<<"WORD " << letrasMov << "INVALID!"<<endl<<endl;
            }
            
            //SI LA PALABRA SE ENCUENTRA DENRO DEL DICCIONARIO
            //PERO NO ES VALIDA PARA EL JUGADOR, SE RECHAZA Y
            //SE INTRODUCE EN MOV REJECTED
            else  {
                rejectedmovements.add(aux);

            }
            
        }
         
    }
        
    if(input != &cin){
        
        ifile.close();
    }
    


    HallOfFame(language, random, bag, player, 
            movements, legalmovements, acceptedmovements, rejectedmovements);
    return 0;
};

void HallOfFame(const Language &l, int random, const Bag &b, const Player &p, 
        const Movelist& original,const Movelist& legal,
        const Movelist& accepted,const Movelist& rejected) {
    cout << endl << "%%%OUTPUT" << endl << "LANGUAGE: "<<l.getLanguage()<< " ID: " << random << endl;
    cout << "BAG ("<<b.size()<<"): " << toUTF(b.to_string()) << endl;
    cout << "PLAYER (" <<p.size() << "): " << toUTF(p.to_string());
    cout << endl << endl << "ORIGINAL ("<<original.size()<<"): "<<endl; original.print(cout);
    cout << endl << endl << "LEGAL ("<<legal.size()<<"): "<<endl; legal.print(cout);
    cout << endl << endl << "ACCEPTED ("<<accepted.size()<<") SCORE "<<accepted.getScore()<< ": "<<endl; accepted.print(cout);
    cout << endl << endl << "REJECTED ("<<rejected.size()<<"): "<<endl; rejected.print(cout);
    cout << endl;
};

void errorBreak(int errorcode, const string &errordata) {
    cerr << endl << "%%%OUTPUT" << endl;
    switch(errorcode) {
        case ERROR_ARGUMENTS:
            cerr<<"Error in call. Please use:\n -l <language> -p <playfile> [-r <randomnumber>]"<<endl;
            break;
        case ERROR_OPEN:
            cerr<<"Error opening file "<<errordata << endl;
            break;
        case ERROR_DATA:
            cerr<<"Data error in file "<<errordata << endl;
            break;
    }
    std::exit(1);
};



/*
 * SI PUEDES ECHARLE UN VISTAZO A ESTOS ERRORES Y VER SI SE PUEDEN ARREGLAR.
 * NO TENGO MUY CLARO DE QUE SALIDAS TENGO QUE DAR EN EL MAIN, DE HECHO
 * TODOS LOS PROBLEMAS QUE TENGO SON DE ESO, LOS RESULTADOS ME DAN BIEN, PERO LA 
 * SALIDA NO SE PARECE A LA DE LOS TESTS.
 * TAMPOCO TENGO MUY CLARO DE SI ESOS SON LOS TEST QUE TENEMOS QUE COMPROBAR, PORQUE
 * POR EJEMPLO EL 8 ES UN TEST DE LA ENTREGA PASADA, EN ESTA PRÁCTICA NO TENEMOS
 * EL PARAMETRO -i, SOLO TENEMOS LOS PARAMETROS -r -l y -p Y SIN EMBARGO ESE TEST
 * TIENE COMO ENTRADA -i. POR ESO DA ERROR.
 * 
 * LO QUE SI, NO HAY NADA QUE HACER CON LA CLASE MOVELIST. ESTÁ TERMINADA COMPLETAMENTE
 * Y FUNCIONA A LA PERFECCIÓN. DE TODAS FORMAS, PUEDES ECHARLE UN VISTAZO
 * A LO MEJOR ME HE PASADO ALGO.
 * TODOS LOS PROBLEMAS SE DAN EN EL MAIN. POR ESO ESTOY UN 
 * POCO PERDIDO....
 * 
 * 
 * HE COMENTADO LAS PARTES QUE CONSIDERO DIFICILES DE LA CLASE MOVELIST, PARA QUE SI 
 * LE HECHAS UN VISTAZO NO TENGAS DIFICULTAD EN COMPRENDER EL CÓDIGO.
 * 
 * 
 * 
 EL TEST 7---> ES_12W3.test da una salida completamente 
  diferente a la que deberia dar HallOfFame
 * 
 * 
 EL TEST 8 ---> ES_17W24.test ni siquiera tiene los argumentos 
 que se supone que deberíamos pasar como parametro en esta práctica
 * 
 * 
 EL TEST 9 ---> FR_74W7.test me da las soluciones correctas pero la salida que
 proporciono en el main no es la misma al principo...
 * 
 * 
 LOS TEST DE ERROR DE CALL OPEN Y DATA me dan el mismo resultado de salida que
 el de los test, pero no me las da por aceptadas....
 *
 * 
 El TEST DE EMPTY me da correcto pero como es mi ordenador el que genera la bolsa
 de forma aleatoria, pues no genera los mismos que el del test. 
  
 
 
 */