/**
 * @file movelist.cpp
 * @author DECSAI
 * @note To be implemented by students
 * @warning Complete the code
 *  */
#include <iostream>

#include "movelist.h"

using namespace std;


//reserva memoria. No hace falta usar deallocate() en ella porque 
//ya liberamos memoria del vector moves con delete [] moves.
void Movelist::allocate(int n){
        Move* nPuntero = new Move [n];
     
        delete []moves;
        moves = nPuntero;
        nMove = n;        
}


//Libera memoria
void Movelist::deallocate(){
        delete [] moves;
        nMove = 0;

}


//Copia los parámetros de un objeto en el actual.
//esta realizado con this aunque no hay mucha diferencia en hacerlo sin el
void Movelist::copy(const Movelist& ml){

    this->nMove = ml.size();
    allocate(nMove);

    for(int i = 0; i < nMove; i++)
        this->moves[i] = ml.moves[i];
   

}


//Constructor vacío, inicia a 0 y apunta moves a nullptr para evitar problemas
//a la larga
Movelist::Movelist(){
    moves = nullptr;
    nMove = 0;
}


//constructor con argumento de tamaño, este inicia el vector moves con tamaño
//nmov reservandole memoria y también asigna a nMove el valor nmov
Movelist::Movelist(int nmov){
    nMove = nmov;
    allocate(nmov);
}


//Constructor de copia, este simplemente llama al metodo privado copy()
//copia los datos de un objeto al otro
Movelist::Movelist(const Movelist &orig){
    copy(orig);
}


//Destructor de clase, este elimina un objeto de la clase cuando este se deja de usar,
//llama a deallocate porque es la forma definida aquí para liberar su memoria.
//Normalmente este método se llama de forma automática cuando un objeto deja de usarse
//asi que no hace falta llamarlo CASI nunca. En esta práctica no se ha llamado ni una vez.
Movelist::~Movelist(){
    deallocate();
}




//Este metodo hace lo mismo que copy. LITERALMENTE lo mismo, asi que en realidad se
// puede definir también de la siguiente forma: 
/*
void Movelist::assign(const Movelist& orig){
    copy(orig);
}
 */
//
//Puedes cambiarlo si quieres, yo lo voy a dejar así de momento por si no te gusta como
//queda de la otra forma
void Movelist::assign(const Movelist& orig){
   
    this->nMove = orig.size();
    this->allocate(orig.size());
    
    
    for(int i = 0; i < nMove; i++){
        this->moves[i] = orig.moves[i];
    }
     
    
}


//Obtiene el movimiento que está en la posicion p
Move Movelist::get(int p)const{
    return moves[p];
}



//Es un set simple
void Movelist::set(int p, Move &m){
    moves[p] = m;
    
}


//Este se utiliza para encontrar un elemento determinado.
//Como en la parte del h dice que ambos objetos tienen que ser objetos completamente identicos
//he comparado todos sus parametros.
//Parece lioso si se ve de lejos, pero en realidad son if anidados, cada uno compara
//los elementos de los objetos MOVE
//si se cumple, devuelve la posicion e inmediatamente sale del bucle.
//usar el return en vez de una variable ahorra espacio en memoria.
//si no encuentra nada simplemente sale del bucle y devuelve -1
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


//Añade un elemento. El procedimiento lo voy a ir comentando linea a linea

void Movelist::add(Move &mov){
    int nuevoNMove = nMove+1;
    
    //crea un objeto de la clase movelist auxiliar
    Movelist mAux;
    
    //reserva memoria para este nuevo objeto, como 
    //vamos a añadir un elemento reservaremos la memoria 
    //actual reservada +1
    mAux.allocate(nuevoNMove);
    
    
    //si el numero de elementos es mayor que 0
    //realiza un bucle para copiarlos.
    //Si no es mayor que 0 significa que vamos a añadir un elemento
    //por primera vez, por tanto no hay que hacer ningún bucle, porque
    //no hay nada que recorrer
    if(nMove > 0){
        for(int i = 0; i < nMove; i++){
            mAux.set(i, moves[i]);
        }
    }
    
    
    //asigno el nuevo elemento en la posición tope de mi objeto auxiliar
    mAux.set(nuevoNMove-1, mov);
    
    //copia los datos del objeto auxiliar en el actual
    assign(mAux);
    
}


//Elimina un elemento mov
//Utiliza el metodo find para buscar el elemento dentro del
//vector de movimientos que tengo
//si lo encuentra, me devuele su posicion y paso al metodo remove por posicion
//si no lo encuentra, no hace nada
void Movelist::remove(Move &mov){
    if(find(mov)!= -1)
        remove(find(mov));
    
}

//metodo remove por posicion
//Lo explico por linea
void Movelist::remove(int p){
    int newNMoves = nMove-1;
    
    //Creo un objeto auxiliar de la clase movelist
    Movelist mAux;
    
    //reserva memoria para el nuevo objeto, como vamos a borrar
    //la nueva memoria tiene una unidad menos que la actual
    mAux.allocate(newNMoves);
    
    
    //realizo un bucle for para recorrer el vector
   for(int i = 0; i < nMove; i++){
       
       //si me encuentro en la posicion deseada, 
       //me meto en un nuevo bucle que tiene como limite 
       //el numero de elementos actual menos 1
       //de esta forma voy asignando en la posicion actual del vector auxiliar
       //la posicion que le corresponde al siguiente valor del actual, para saltarme
       //un elemento
        if(i==p){
            while(i < nMove-1){
                mAux.set(i, moves[i+1]);
                i++;
            }
        break;
        }
        
        //si no me he encontrado con la posicion todavía, simplemente copio 
        //cada elemento del vector original en su posicion correspondiente
        //en el vector auxiliar
        else mAux.set(i, moves[i]);
    }
    
    //copio los valores del vector auxiliar en el original
    assign(mAux);
    
}


//este metodo filtra todas las palabras que encuentra en cada movimiento,
//dejando solo aquellos que son compatibles con el lenguaje seleccionado
//y que se pasa por parámetro
void Movelist::zip(Language &l){
    
    //básicamente recorre el vector de movimientos obteniendo las letras de cada
    //uno y realiza un query para comprobar si la palabra está dentro del diccionario
    //del idioma seleccionado, si no está en él, borra el elemento.
    for(int i = 0; i < nMove; i++){
        string letras = get(i).getLetters();

        if(!l.query(letras)){
            remove(i);
            //AL ELIMINAR ELEMENTOS DE FORMA DINÁMICA, 
            //LA ÚNICA FORMA DE ASEGURAR QUE AL VOLVER
            //A RECORREL EL VECTOR DE NUEVO DESPUÉS DE ELIMINAR
            //UN ELEMENTO NO SALTEMOS UNO DE ELLOS, ES VOLVIENDO A RECORRER
            //DE NUEVO EL VECTOR EDITADO.
            i = 0;
        }
    }
    
    
}


// es un clear simple
void Movelist::clear(){
    if(nMove > 0){
        nMove = 0;
        deallocate();
    }
}



//este se utiliza para obtener la puntuación total que tenemos en el vector de moves
//recorre el vector y va acumulando en una variable el valor total.
//como dice en el .h si encuentra un -1, cancela toda la operacion y devuelve ese valor
//es lo que hace return, si encuentro el valor -1, inmediatamente sale de la función 
//devolviendo -1
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

//Este ya estaba
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


//Este lee todos los elementos de un tiron
//me he inspirado un poco en la lectura que tenias tu implementada en el main
//de la sesion anterior
//voy a señalar los cambios notables
bool Movelist::read(std::istream& is){
    string finalizador = normalizeWord("@");
    bool finalizadorEncontrado = false;
    
    do{

        Move aux;
        
        //se realiza la lectura individual
        aux.read(is);
        
        string letrasMov = aux.getLetters();
        
        //con esto busca el finalizador en el string de letras
        //devuelve la posicion si encuentra el elemento
        //si no lo encuentra devuelve un valor apuntando al final
        //del string. Ese valor se conoce como npos, siempre se conoce así
        //no es que yo lo haya definifo
        size_t found = aux.getLetters().find(finalizador);

        //el primer caso es si found apunta a una posicion diferente a la
        //del final del string y si el tamaño del string es 1.
        //lo he hecho así porque como el finalizador normalizado solo tiene un elemento
        //y es _ ambas condiciones se cumplen solo si se encuentra @
        //si se encuentra señalamos como true la variable de abajo para poder terminar
        //el bucle y la lectura
        if ((found!=std::string::npos) and (letrasMov.size()==1)){
            finalizadorEncontrado=true;
        }
        
        //Si no hemos encontrado @ pero aún así el string está vacío
        //debemos de salir del metodo de lectura, pues estamos leyendo un valor vacío
        //para eso uso return, que provoca la salida inmediata de la función y devolviendo el
        //valor false, pues se ha producido un error.
        else if((!finalizadorEncontrado) and (letrasMov.size() < 1)){
            return false;
        }
        
        //si ninguno de los casos se da, puedo añadir el elemento con tranquiliad, pues
        //es correcto.
        else add(aux);
    }while(!finalizadorEncontrado );

    //devolverá verdadero siempre en realidad, pues en el bucle nos encargamos de 
    //que haga la lectura correcta.
    //Por tanto, si sale del bucle, lo ha hecho porque todo ha ido bien y ha leido correctamente
return finalizadorEncontrado;
    
}

