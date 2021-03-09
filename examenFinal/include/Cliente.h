#ifndef CLIENTE_H
#define CLIENTE_H

#include <string>
#include <iostream>
class Cliente {
private:
	int 	id_cliente; 
	double 	descuento; 
	std::string 	nombre; 
	std::string 	NIF;        
public: 
    
    Cliente();
     /* Constructor con argumentos  */
     Cliente (const std::string & el_NIF, double el_descuento, 
	      const std::string & el_nombre, int el_id_cliente=0); 

    /* Modifica el id_cliente  */
	void SetIdCliente (int el_id_cliente);
        
    /* Devuelve el id_clientede un "Cliente"  */
	int GetIdCliente ( ) const;
        
    /* Devuelve el descuento de un "Cliente" */
	double GetDescuentoCliente ( ) const;
        
    /* Devuelve el nombre de un "Cliente" */
	std::string GetNombreCliente ( ) const;
        
     /* Devuelve el NIF de un "Cliente" */
        std::string GetNIFCliente (void) const;

    /* Operador << Inserta un "Cliente" en un flujo de texto. */
	friend std::ostream & operator << (std::ostream & out, const Cliente & un_cliente);

    /* Operador >> Extrae un "Cliente" de un flujo de texto. */
	friend std::istream & operator >> (std::istream & in, Cliente & un_cliente);
    

};


































  Cliente::Cliente (const std::string & el_NIF, double el_descuento, 
	      const std::string & el_nombre, int el_id_cliente){
      
  } 

   void Cliente::SetIdCliente (int el_id_cliente){
       
   }
        
  
	int Cliente::GetIdCliente ( ) const{
        int x; return x;
        }
        
   
	double Cliente::GetDescuentoCliente ( ) const{
        double x; return x;   
        }        
   
	std::string Cliente::GetNombreCliente ( ) const{
            std::string x; return x;
        }
        
        std::string Cliente::GetNIFCliente () const{
                        std::string x; return x;

        }
 
        std::ostream & operator << (std::ostream & out, const Cliente & un_cliente){
            return out;
     
 }

	 std::istream & operator >> (std::istream & in, Cliente & un_cliente){
             return in;
        }
   


#endif /* CLIENTE_H */

