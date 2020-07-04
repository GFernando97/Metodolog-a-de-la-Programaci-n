/* Solucion EXAMEN FINAL DE METODOLOGIA DE LA PROGRAMACION
 * GRADO INFORMATICA 
 */

/* 
 * File:   examenFinal.cpp
 * Author: 
 * DNI:
 * GRUPO:
 * 
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include "Cliente.h"
#include "Clientes.h"
#include "Venta.h"
#include "Ventas.h"

using namespace std;

/* EJERCICIO 0:
 * Hacer los métodos necesarios para obtener el numero total de clientes y ventas 
 * para las clases Clientes y Ventas.  ¿En necesario poner un argumento para estos metodos?
 */

/* >>>> SOLUCION EJERCICIO 0 */

/* Respuesta Razonada: No necesita ningun argumento porque bla, bla, bla. 
 *  Además teniendo en cuenta que la la la,  si pero no
 */

int Clientes::NumClientes() const{
    return num_clientes;
}
int Ventas::NumVentas() const{
    return num_ventas;
}

/* >>>> SOLUCION EJERCICIO 1.1  */

/* Es necesario Ctor de Cliente:
 * 1. para poder crear vectores de clientes, ya que al tener el constructor con parámetros ya no está disponible el por defecto.
   2. Para tener un objeto inválido controlado */

Cliente::Cliente(){
	id_cliente = -1;
	descuento = 0; 
	nombre= ""; 
	NIF=""; 
}

Clientes::Clientes() {
    num_clientes = 0; // Num.casillas ocupadas
    los_clientes = nullptr;
}



/* >>>> SOLUCION EJERCIO 1.2  */

void Clientes::deallocate() {
    if (los_clientes != nullptr) { // or (num_clientes > 0)
        delete[] los_clientes;
        los_clientes = nullptr;
        num_clientes = 0;
    }
}
/* no es necesario hacer un destructor para objetos de tipo cliente, ya que los campos estaticos no lo requieren
 y los campos string traen uno ya definido, por lo que cuando acaba con un objeto se tira de los destructores de los campos
 de los que está compuestos cuando lo tienen.*/
Clientes::~Clientes(){
    deallocate();
}
/* >>>> SOLUCION EJERCICIO 1.3 */

void Clientes::allocate(int n) {

    if (n > 0) {
        num_clientes = n;
        los_clientes = new Cliente [n];
    }
    else {
    	num_clientes = 0; // Num.casillas ocupadas
    	los_clientes = nullptr;
    }
}

void Clientes::copy(const Clientes& otro) {
    allocate(otro.num_clientes);
    for (int i = 0; i < otro.num_clientes; ++i) {
        *this->los_clientes[i] = otro.los_clientes[i];
    }
}

Clientes::Clientes(const Clientes& orig) {
    los_clientes = nullptr;
    num_clientes = 0;
    copy(orig);
}

Clientes& Clientes::operator=(const Clientes& orig) {
    if (this != &orig) {
	deallocate();
        copy(orig);
    }
    return *this;
}


/* no es necesario hacer un ctor de copia ni asignación para objetos de tipo cliente, ya que los campos estaticos no lo requieren
 y los campos string traen uno ya definido, por lo que cuando se requieren se tira de los definidos en los campos
 de los que está compuestos cuando lo tienen, los primitivos y los string */

/* >>>> SOLUCION EJERCICIO 2.1 */
/* busca por NIF */
bool Clientes::find(const Cliente & orig) {
    bool found = false;
    for (int i= 0; i < num_clientes && !found; i++)
        if (orig.GetNIFCliente() == los_clientes[i].GetNIFCliente())
            found = true;
    return found;
}

Clientes& Clientes::operator+=(const Cliente & orig) {
    if (!find(orig)) {
        Cliente nuevo = orig;
        nuevo.setId(GeneraIdCliente());
        
        Clientes *aux = new Cliente [num_clientes + 1];  //allocate
        for (int i = 0; i< this->num_clientes; i++)	// copia
            aux[i] = this->los_clientes[i];
        aux[this->num_clientes] = nuevo;		// el último
        deallocate();					// libera
        this->los_clientes = aux;			//actualiza los_clientes
        this->num_clientes++;				//actualiza num_clientes
    }
    return *this;
}

/* >>>> SOLUCION EJERCICIO 2.2 */

Cliente Clientes::get(int i) const{
    assert ( i >= 0 && i < num_clientes);
    return los_clientes[i];
}
void set(int i, const Cliente & otro){
    assert ( i >= 0 && i < num_clientes);
    los_clientes[i]= otro;
}
/* funcion externa, 2 parametros de entrada y no se pueden acceder a los componentes internos de los objetos*/
Clientes operator+(const Clientes& v1, const Clientes& v2) {
    Clientes resultado(v1); // copia del v1
    
    for (int i = 0; i < v2.NumClientes(); i++) {// para cada elemento del v2
        Cliente nuevo = v2.get(i);
        resultado += nuevo;
     }
    return resultado;
}

/* >>>> SOLUCION EJERCICIO 3.1 */
ostream& operator<<(ostream& os, const Clientes & cli) {
    
    for (int i = 0; i < cli.num_clientes; ++i) {
        os << cli.los_clientes[i] << endl;
    }
    return os;
}


/* >>>> SOLUCION EJERCICIO 3.2 */

istream& operator>>(istream& is, Clientes& cli) {
    Cliente uno;
    cli.deallocate();
    is >> uno;
    while (!is.eof()) {
        cli += uno;
        is >> uno;
    }
    return is;
}
/* >>>> SOLUCION EJERCICIO 4.1 */

#define MAGIC = "FICHEROCLIENTES"

Clientes::inicialize(){
    num_clientes = 0; 
    los_clientes = nullptr;
}

bool Clientes::Clientes(const string nombre) {
    inicialize();
    ifstream flujo(nombre.c_str());
    string magica;
    cout << "Abriendo nombre "<< nombre << endl;
    if (flujo) {
        flujo >> magica;
        if (magica != MAGIC)  {
            cerr << "ERROR: Formato desconocido"<<endl;
            return false;
        }
        flujo >> *this;
        if (flujo) {
            flujo.close();
            return true;
        }
        cerr << "ERROR cargando datos del nombre " << nombre << endl;
        return false;
    } 
    cerr << "ERROR abriendo nombre "<< nombre << endl;
    return false;
}
/* >>>> SOLUCION EJERCICIO 4.2 */
void Clientes::EscribirClientes (const string &nombre) const{
    ofstream flujo(nombre.c_str(), ios::out);
    cout << "Salvando fichero "<< nombre << endl;
    if (flujo) {
        flujo << MAGIC << endl;
        flujo << *this;
        if (flujo)  {
            flujo.close();
            return true;
        }
        cerr << "** ERROR al salvar en " << nombre << endl;
        return false;
    }
    cerr << "** ERROR al abrir "<< nombre << endl;
    return false;
}

/* >>>> SOLUCION EJERCICIO 5 */

Venta Ventas::get(int i) const{
    assert ( i >= 0 && i < num_ventas);
    return las_ventas[i];
}
void set(int i, const Venta & otro){
    assert ( i >= 0 && i < num_ventas);
    las_ventas[i]= otro;
}
double Ventas::ventaMedia() const {
    double acumulado = 0;
    for (int i= 0; i< num_ventas; i++)
        acumulado += get(i).GetTotal();
    if (num_ventas > 0){
        acumulado / num_ventas;
    }
    return acumulado;
}
bool operator<(const  Ventas & v1, const Ventas & v2){
    return (v1.ventaMedia() > v2.ventaMedia());
}

bool operator ==(const  Ventas & v1, const Ventas & v2){
    return (!v1.ventaMedia() > v2.ventaMedia() && ! v2.ventaMedia() > v1.ventaMedia());
}


/* >>>> SOLUCION EJERCICIO 6 */

int main(int argc, char** argv) {
   
    double currentTotal;
    Ventas maxVentas;
    int posMax;

    if (argc > 1) {
    	maxVentas.LeerVentas(argv[1]);  // inicializacion para hallar el máximo
	posMax = 1;
        for (int i = 2; i < argc; i++){  // para hallar el máximo
    	  Ventas delMes;
          delMes.LeerVentas(argv[i]);  // carga de los datos con los métodos disponibles
	  if (maxVentas < delMes) {  	// uso del operador <
             maxVentas = delMes;
             posMax = i;
	  }
    
         cout << "Mejor venta: " << maxVentas.ventaMedia() << endl;

         for (int i = posMax; i < argc; i++){  // para mostrar los que coinciden con el máximo
    	     Ventas delMes;
             delMes.LeerVentas(argv[i]);
	     if (maxVentas == delMes) // uso del operador ==
                 cout << " corresponde a " << argv[i]<< " ";
         }
    }
    else cout << "no hay datos para hallar maximo";
    return 0;
}
