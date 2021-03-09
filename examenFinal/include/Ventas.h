#ifndef VENTAS_H
#define VENTAS_H
#include <iostream>
#include <string>

class Ventas {
private:
    int   num_ventas; // Num.casillas ocupadas
    Venta   * las_ventas; 

public:

	/* Devuelve num. de ventas */
	int NumVentas ( ) const; 

	/* Guarda el contenido de una coleccion "Ventas" en un fichero de texto llamado "nombre".*/
	void EscribirVentas (const std::string & nombre) const;

	/* Lee una coleccion "Ventas" a partir 
         * de los datos presentes en el fichero de texto llamado "nombre". */
	void LeerVentas (const std::string & nombre);

	/* Operador << Inserta un conjunto "Ventas" en un flujo de texto.*/
	friend std::ostream & operator << (std::ostream & out, const Ventas & ventas);

	/* Operador >>  Extrae un conjunto "Ventas" de un flujo de texto.*/
	
        friend std::istream & operator >> (std::istream & in, Ventas & ventas);

        bool operator==(const Ventas &otrasVentas)const;
        bool operator>(const Ventas &otrasVentas)const;
        
        
        double mediaVentas()const ;

};
























void Ventas::EscribirVentas (const std::string & nombre) const{
    
}

void Ventas::LeerVentas (const std::string & nombre){
    
}

std::ostream & operator << (std::ostream & out, const Ventas & ventas){
    return out;
}

 std::istream & operator >> (std::istream & in, Ventas & ventas){
     return in;
 }
#endif /* VENTAS_H */

