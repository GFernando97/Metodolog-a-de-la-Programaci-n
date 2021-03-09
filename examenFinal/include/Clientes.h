
#ifndef CLIENTES_H
#define CLIENTES_H
#include <iostream>
#include "Cliente.h"

class Clientes {
private:
    int num_clientes; // Num.casillas ocupadas
    Cliente * los_clientes; 
    
    void allocate(int numeroReserva);
    void deallocate();
    void copy(const Clientes &original);
    bool esta(const Cliente &nuevoCl);
    

public:
    
/*Constructor sin parámetros*/ 
 Clientes();
    
/*Destructor*/
 ~Clientes();
 
/*Constructor de copia*/
 Clientes(const Clientes &orig);
 
 
/*Constructor con nombre de fichero*/
 Clientes(char *nombreFichero);
    
    
/* Devuelve el numero  de clientes */
 int NumClientes ( ) const; 

 /* Genera un id_cliente que no existe */
int GeneraIdCliente ( ) const; 

/*Acceso a cliente específico*/
Cliente getCliente(int indice)const;

/**/
void EscribirCLientes(const std::string nombre)const;

const Clientes & operator=(const Clientes & Clorig);

const Clientes &operator +=(const Cliente& nuevoCl);

const Clientes & operator+(const Clientes & otrosCl);



friend std::ostream& operator<<(std::ostream &os, const Clientes &clients);
friend std::istream& operator>>(std::istream &is, Clientes & clients);




};








int Clientes::GeneraIdCliente()const{
    int x; return x;
}

#endif /* CLIENTES_H */

