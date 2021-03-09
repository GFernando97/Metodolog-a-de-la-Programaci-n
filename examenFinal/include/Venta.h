
#ifndef VENTA_H
#define VENTA_H
#include <iostream>
class Venta {

private:
	int 	id_cliente; 
	int 	id_producto; 
	double 	total; 

public: 
	/* Constructor con parametros */
	Venta (int el_id_cliente, int el_id_producto, double el_total); 

	/* Devuelve el id_cliente de una "Venta" */
	int GetIdCliente ( ) const;

        /* Devuelve el id_producto de una "Venta" */
	int GetIdProducto ( ) const;

	/* Devuelve el total de una "Venta" */
	double GetTotal ( ) const;

	/* Operador << Inserta una "Venta" en un flujo de texto. */
	friend std::ostream & operator << (std::ostream & out, const Venta & una_venta);

	/* Operador >> Extrae una "Venta" de un flujo de texto. */ 
	friend std::istream & operator >> (std::istream & in, Venta & una_venta);
};

















Venta::Venta (int el_id_cliente, int el_id_producto, double el_total){
    
}
int Venta::GetIdCliente ( ) const{
    int x; return x;
}

int Venta::GetIdProducto ( ) const{
    int x; return x;
}

double Venta::GetTotal ( ) const{
  double x; return x;  
}

 std::ostream & operator << (std::ostream & out, const Venta & una_venta){
     return out;
 }

std::istream & operator >> (std::istream & in, Venta & una_venta){
    return in;
}










#endif /* VENTA_H */

