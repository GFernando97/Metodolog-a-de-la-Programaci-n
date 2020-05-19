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
#include "tiles.h"

using namespace std;


#define ERROR_ARGUMENTS 1
#define ERROR_OPEN 2
#define ERROR_DATA 3
#define PASSWORD "MPALABRADOS-V1"
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
 * @param t Final tiles
 * @param original
 * @param legal
 * @param accepted
 * @param rejected
 */
void HallOfFame(const Language &l, int score, int alto, int ancho, const Tiles &t,
                const Bag &b, const Player &p, bool guardar);


/**
 * @brief Main function. 
 * @return 
 */
int main(int nargs, char * args[]) {
    
    bool encontrado=false;
    bool nueva=true;
    string lang="";
    bool lenguaobligatorio=false;
    int ancho=0, alto=0, random;
    bool anchoobligatorio=false;
    bool altoobligatorio=false;
    string partida="";
    bool partidaobligatorio=false;
    string movimientos="";
    bool movimientosobligatorio=false;
    string guardar="";
    string bolsa="";
    bool haybolsa=true;
    bool guardarpartida=false;
    Language language;
    Bag bag;
    Player player;
    Tiles tablero;
    ifstream archivopartida, archivomovimientos; ofstream archivoguardar;
    istream *input=&cin; ostream *output=&cout;
    string nombre="";
    int puntuacion=0;
    int numerobolsa;
    int numeroplayer;
    string letrasplayer="";
    Movelist original,accepted,rejected;
    
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
 
    if(nueva==true){
        
        if(nargs < 9 || nargs > 15){
            
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
            else if(parametro=="-p"){
                
                movimientos=siguienteparametro;
                movimientosobligatorio=true;
            }
            else if(parametro=="-r"){
                
                random=stoi(siguienteparametro);
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
        
        if(nargs < 5 || nargs > 7){
            
            errorBreak(1,"");
        }
        
        for(int i=0;i<nargs-1;i++){
            
            string parametro=args[i];
            string siguienteparametro=args[i+1];
            
            if(parametro=="-open"){
                
                partida=siguienteparametro;
                partidaobligatorio=true;
            }
            else if(parametro=="-p"){
                
                movimientos=siguienteparametro;
                movimientosobligatorio=true;
            }
            else if(parametro=="-save"){
                
                guardar=siguienteparametro;
                guardarpartida=true;
            }
        }
    }

    if(nueva==true){
        
        if(lenguaobligatorio==false || anchoobligatorio==false || 
           altoobligatorio==false || movimientosobligatorio==false){
            
            errorBreak(1,"");
        }
    }
    else{
        
        if(partidaobligatorio==false || movimientosobligatorio==false){
            
            errorBreak(1,"");
        }
    }
    
    if(nueva==true){
        
        language.setLanguage(lang);
        bag.define(lang);
        bag.setRandom(random);
        
        if(haybolsa){
            
            bolsa=toISO(bolsa);
            bag.set(bolsa);
        }
        
        string extraer=bag.extract(7-player.size());
        
        player.add(extraer);
        
        tablero.setSize(alto,ancho);
        
        for(int i=1;i<alto+1;i++){
            
            for(int j=1;j<ancho+1;j++){
                
                tablero.set(i,j,'.');
            }
        }
    }
    else{
        
        archivopartida.open(partida.c_str());
                
        if(!archivopartida){
                
            errorBreak(2,partida);
        }
        
        input=&archivopartida;
        
        (*input)>>nombre;
        (*input)>>puntuacion;
        (*input)>>lang;

        language.setLanguage(lang);
        bag.define(lang);

        (*input)>>alto;
        (*input)>>ancho;

        tablero.setSize(alto,ancho);

        tablero.read(*input);
        
        (*input)>>numeroplayer;
        (*input)>>letrasplayer;
        letrasplayer=toISO(letrasplayer);
        
        player.add(letrasplayer);
        
        (*input)>>numerobolsa;
        (*input)>>bolsa;
        bag.set(bolsa);
        
        archivopartida.close();     
    }
    
    archivomovimientos.open(movimientos.c_str());
    
    if(!archivomovimientos){
                
            errorBreak(2,movimientos);
    }
    
    archivomovimientos>>original;
    
    if(archivomovimientos.eof()){
        
        errorBreak(3,movimientos);
    }
    
    archivomovimientos.close();
    
    Movelist legal(original);
    
    legal.zip(lang);

    for(int i = 0; i < legal.size(); i++){
        
        string extraer=bag.extract(7-player.size());
        
        player.add(extraer);
        
        Move mov = legal.get(i);
        
        string letrasMov = mov.getLetters();
        
        if(player.isValid(letrasMov)){
            
            if(language.query(letrasMov)){
                
                accepted.add(mov);
                
                puntuacion=puntuacion+mov.findScore(lang);
                mov.setScore(puntuacion);
                tablero.add(mov);
            }
            else{
                
                rejected.add(mov);
            }
            
            player.extract(letrasMov);
        }
        else{
            
            rejected.add(mov);
        }
        
        string aniadir=bag.extract(7-player.size());
        
        player.add(aniadir);
    }
    
    if(guardarpartida==true){
        
        archivoguardar.open(guardar.c_str());
        
        if(!archivoguardar){
            
            errorBreak(2,guardar);
        }
        
        output=&archivoguardar;
        
        (*output)<<"MPALABRADOS-V1"<<endl;
        (*output)<<puntuacion<<endl;
        (*output)<<lang<<endl;
        (*output)<<alto<<" ";
        (*output)<<ancho<<endl;
        
        tablero.print(*output);
        
        (*output)<<player.size()<<" ";
        (*output)<<player.to_string()<<endl;
        (*output)<<bag.size()<<" ";
        (*output)<<bag.to_string();
        
        archivoguardar.close();
    }
    
    HallOfFame(lang, puntuacion, alto, ancho, tablero, bag, player,guardarpartida);
    
/*

 * 1) El main() recibe múltiples parámetros de entrada, distinguiendo
entre dos modos de funcionamiento.

    * a) Empezar una partida nueva. Para ello los parámetros de
llamada serán
-l <lang> -w <int> -h <int> -p <pfile> [-r <int> -b <bag> -save <matchfile>]
especificando el diccionario, el ancho y alto del tablero de
juego, el fichero de movimientos registrados y, opcional-
mente, el número aleatorio la bolsa suministrada y la posibilidad de salvar la la
jugada en un fichero con extensión .match con la opción
-save . En caso de que no se indique esta última opción,
entonces deberá mostrar el estado final de la partida con el
mismo formato (ver Sección ??).

     * b) Continuar una partida existente. Para ello los parámetros
de llamada serán
-open <matchfile> -p <playfile> [-save <matchfile>]
indicando la apertura de un fichero .match desde el que
se restaura el estado anterior de la partida, y un fichero
de movimientos. Opcionalmente, se podrá grabar la partida
final si se indica el parámetro -save comentado antes.

 * 2. Crear una instancia de la clase Language con el ID indicado.

 * 3. Crear una instancia de la clase Bag, si es una partida nueva,
inicializar la bolsa, en otro caso, cargarla directamente desde el
fichero .match

 * 4. Crear una instancia de la clase Player y inicializarla por com-
pleto con caracteres de la bolsa o bien leerla del fichero .match.

 * 5. Crear una instancia de la clase Tiles y dimensionarla según
los parámetros leı́dos, bien desde la lı́nea de comandos, bien
desde el fichero .match.

 * 6. Crear una instancia de la clase bf Movelist llamada original
y leer todos los movimientos desde el fichero indicado en el
parámetro -p usando operador sobrecargado >>

 * 7. Crear una instancia de Movelist llamada legal que contenga
sólo los movimientos de original que están en el diccionario
del lenguaje elegido. Usar, para ello, el método zip(...)

 * 8. Crear dos instancias adicionales de Movelist y llamarlas accepted
y rejected

 * 9. Recorrer toda la lista de movimientos leı́da y, por cada uno de
ellos.

     * a) Si el movimiento está en el diccionario, añadir la palabra a
la lista accepted , calcular su puntuación, según el idioma
y acumularla. A continuación, se deberá colocar cada mo-
vimiento en su posición correspondiente en la instancia de
Tiles creada anteriormente, ignorando aquellos caracteres
que caigan fuera de las dimensiones permitidas y sobrees-
cribiendo los caracteres que se crucen.

     * b) En otro caso añadirla a la lista rejected .

 * 10. Terminar mostrando el estado de la partida en pantalla o guardándo-
lo en disco según la presencia o no de -save .
11. Si en cualquier momento se presenta un error en los argumen-
tos, en la apertura de ficheros o en la lectura de datos del fiche-
ro, se debe usar la función errorBreak(...) para notificar el error
y parar el programa 
 */
    
    return 0;
}


void errorBreak(int errorcode, const string &errordata) {
    cerr << endl << "%%%OUTPUT" << endl;
    switch(errorcode) {
        case ERROR_ARGUMENTS:
            cerr<<"Error in call. Please use either:"<<endl;
            cerr<< "-l <language> -w <width> -h <height> -p <playfile> [-b <bag> -r <randomnumber> -save <matchfile>]"<<endl;
            cerr<< "-open <matchfile> -p <playfile> [-save <matchfile>]"<<endl;            
            break;
        case ERROR_OPEN:
            cerr<<"Error opening file "<<errordata << endl;
            break;
        case ERROR_DATA:
            cerr<<"Data error in file "<<errordata << endl;
            break;
    }
    std::exit(1);
}

/**@warning HallOfFame() */

void HallOfFame(const Language &l, int score, int alto, int ancho, const Tiles &t, const Bag &b, const Player &p, bool guardar) {
    cout << endl << "%%%OUTPUT" << endl;
    if(guardar==true){
        cout<<"MPALABRADOS-V1"<<endl;
    }
    cout<< score << endl << l.getLanguage()<< endl<< alto << " "<< ancho <<endl;
    t.print(cout); cout << endl << p.size() << " " << toUTF(p.to_string()) << endl << b.size() << " " << toUTF(b.to_string())<<endl;
}