/* EXAMEN FINAL DE METODOLOGIA DE LA PROGRAMACION
 * DOBLE GRADO INFORMATICA Y ADE
 */

/* 
 * File:   examenFinal.cpp
 * Author: Gabriel Fernando Lojano Mayaguari
 * DNI: 77142950F
 * GRUPO: B3
 * 
 */
#include <cassert>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include "Cliente.h"
#include "Clientes.h"
#include "Venta.h"
#include "Ventas.h"
#define CABECERA "FICHEROCLIENTES"


using namespace std;

/* EJERCICIO 0:
 * Hacer los métodos necesarios para obtener el numero total de clientes y ventas 
 * para las clases Clientes y Ventas.  ¿En necesario poner un argumento para estos metodos?
 */

/* >>>> SOLUCION EJERCICIO 0 */

/* Respuesta Razonada: No necesita ningun argumento porque bla, bla, bla. 
 *  Además teniendo en cuenta que la la la,  si pero no...
 */

int Clientes::NumClientes() const{
    return num_clientes;
}
int Ventas::NumVentas() const{
    return num_ventas;
}

/* >>>> SOLUCION EJERCICIO 1.1  */

//Se crearan métodos auxiliares de allocate y deallocate y copy para reservar 
//y liberar la memoria necesaria para el vector dinamico existente en la clase 
//clientes y el metodo copy para encapsular el proceso de copia de un objeto
//y evitar repetir codigo;

void Clientes::allocate(int numeroReserva){
    if(numeroReserva>0){
        los_clientes =  new Cliente[numeroReserva];
        this->num_clientes=numeroReserva;
    }
    
}

void Clientes::deallocate(){
    if(num_clientes!=0){   //revisar
        delete [] los_clientes;
        num_clientes=0;
        
    }
}

void Clientes::copy(const Clientes &original){
    num_clientes = original.NumClientes();
    for(int i =0; i < original.NumClientes(); i++)
        los_clientes[i] = original.los_clientes[i];
    
}


Cliente::Cliente(){
    id_cliente =0;
}


Clientes::Clientes(){
    num_clientes=0;
    los_clientes = 0;
}




//En el caso de Cliente no es necesario implementar ni un destructor
//ni un constructor de copia, pues ya existe uno por defecto implementado por 
//la clase que funcionan bien si la copia o la destrucción de parámetros no
//implica memoria diámica. El destructor de clientes y el constructor copia si
//que deben ser implementados

/* >>>> SOLUCION EJERCIO 1.2  */


Clientes::~Clientes(){
    deallocate();
}
/* >>>> SOLUCION EJERCICIO 1.3 */



Clientes::Clientes(const Clientes &orig){
    allocate(orig.NumClientes());
    copy(orig);
    
}

const Clientes &Clientes::operator=(const Clientes &Clorig){
    if(this != &Clorig){
        deallocate();
        allocate(Clorig.NumClientes());
        copy(Clorig);
    }
    
    return *this;
}
 


/* >>>> SOLUCION EJERCICIO 2.1 */
//Creamos un metodo privado para comprobar si el nuevo objeto que intentamos 
//insertar se encuentra en el vector de clientes

bool Clientes::esta(const Cliente& nuevoCl){
    for(int i = 0; i < num_clientes; i++){
        if(nuevoCl.GetNIFCliente() == los_clientes[i].GetNIFCliente())
            return true;
    }
    
    return false;   
}



const Clientes &Clientes::operator +=(const Cliente& nuevo){
    
    
    if(!esta(nuevo)){
        Cliente nuevoCl(nuevo);
        int nuevoId = GeneraIdCliente();
        nuevoCl.SetIdCliente(nuevoId);
        Clientes aux(*this);
        deallocate();
        allocate(aux.num_clientes+1);
        copy(aux);
        los_clientes[num_clientes+1] =  nuevoCl;
      
    }
    return *this;
}



/* >>>> SOLUCION EJERCICIO 2.2 */

//Para este caso se ha creado un nuevo metodo para acceder a los valores 
//del vector de clientes.
//Además, se ha utilizado el operador += sobrecargado en el apartado anterior
//ya que la forma de añadir un nuevo cliente es la misma que si tratamos con un vector
//de clientes, con la unica diferencia de que esta vez, implementamos un bucle for
//para recorrer todos los valores del vector existente en el objeto pasado como
//parametro.
Cliente Clientes::getCliente(int indice)const{
    assert(indice > 0 and indice < num_clientes);
    return los_clientes[indice];
    
}


const Clientes &Clientes::operator +(const Clientes& otros){
    Clientes aux(*this);
    Clientes otrosCl(otros);
    
    for(int i = 0 ;i < otrosCl.NumClientes(); i++){
        if(aux.esta(otrosCl.getCliente(i))){
            aux+=otrosCl.getCliente(i);
        }
    }
    
    return aux;
}


/* >>>> SOLUCION EJERCICIO 3.1 */
//Para este ejercicio he supuesto que la sobrecarga de operadores de la clase Cliente está implementada
//y completamente funcional
  /*   
ostream& operator<<(ostream &os, const Clientes &clients){
    for(int i = 0; i < clients.NumClientes(); i++){
        os << clients.getCliente(i).GetIdCliente() << " "
           << clients.getCliente(i).GetDescuentoCliente() << " "
           << clients.getCliente(i).GetNombreCliente() << " "
           << clients.getCliente(i).GetNIFCliente() << endl;
    }
    return os;
}
*/

ostream& operator<<(ostream &os, const Clientes &clients){
    for(int i = 0; i < clients.NumClientes(); i++)
        os << clients.getCliente(i) << endl;
    
    return os;
}




/* >>>> SOLUCION EJERCICIO 3.2 */


istream &operator>>(istream &is, Clientes &clients){
    Cliente aux;
    
    while(!is.eof()){
        string nuevalinea;
        getline(is, nuevalinea, '\n');
        istringstream iss(nuevalinea);
        iss>> aux;
    }
   
        return is;
}




/* >>>> SOLUCION EJERCICIO 4.1 */

Clientes::Clientes(char *nombreFichero){
    ifstream fichero(nombreFichero);
    string palabraClave;
    if(fichero.is_open()){
        //primero comprobamos si la primera linea es correcta
        getline(fichero, palabraClave);
        if(palabraClave.compare(CABECERA)==0)
            fichero >> *this;
    }
    
    fichero.close();
    
}


/* >>>> SOLUCION EJERCICIO 4.2 */
//Para la salida voy a suponer que ay que incluir la cabecera FICHEROCLIENTES definida
//en la primera linea del fichero.

void Clientes::EscribirCLientes(const string nombre) const{
    ofstream ficheroSalida(nombre,ios::out);
   
    if(ficheroSalida.is_open()){
        ficheroSalida << CABECERA << endl;
        ficheroSalida << *this;
        ficheroSalida.close();

    }
    
    else{
        cout << "Error al intentar abrir el archivo\n";
    }
    
}

/* >>>> SOLUCION EJERCICIO 5 */


double Ventas::mediaVentas()const {
    double valorTotal = 0;
    for(int i =0; i< NumVentas(); i++){
        valorTotal +=las_ventas[i].GetTotal();
    }
    
    return valorTotal/NumVentas();
}


bool Ventas::operator==(const Ventas &otrasVentas)const{
if((*this).mediaVentas() == otrasVentas.mediaVentas())
    return true;

else return false;
}

bool Ventas::operator>(const Ventas &otrasVentas)const{
    if((*this).mediaVentas() > otrasVentas.mediaVentas())
        return true;
    else return false;
    
}





/* >>>> SOLUCION EJERCICIO 6 */

int main(int argc, char** argv) {
   
    
    return 0;
}

