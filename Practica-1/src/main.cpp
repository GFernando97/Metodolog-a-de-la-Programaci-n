/**
 * **
   @file intervalo.cpp
   @brief Se proporciona parte de la clase intervalo y es necesario definir ciertos métodos para darle operatividad
   @author MP Grupos B, C
   @warning Módulo no definitivo (creado para ser modificado)

   Un ejemplo de ejecución es:

    Cuantos intervalos (max 10):5
    Introduce [ o ( cotaInferior, cotaSuperior ) o ]: [0,10] (0,10] [0,10) (0,10) (10,10)
    Cuantos valores reales (max 10):6
    Introduce valor real: -1 -0.001 0 5.7  9.6  10
    Da como salida:

 [0,10] : 0 5.7 9.6 10
 (0,10] : 5.7 9.6 10
 [0,10) : 0 5.7 9.6
 (0,10) : 5.7 9.6
 (0) :

 */

// meter esta cabecera en todos los .h

#include <iostream>
#include "intervalo.h"
using namespace std;


// funciones externas
/**
* @brief Imprime los valores de un intervalo de forma visual según lo indicado en el guión
* @param  El intervalo
*/
void escribir(const Intervalo &i);

/**
* @brief Lee los valores del intervalo según el formato indicado en el guión
* @param i El intervalo
*/
void leer(Intervalo &i);

/**
* @brief Muestra un mensaje en pantalla indicando si el intervalo es vacío o no
* @param i El intervalo
*/
void comprobarVacio(Intervalo i);



void escribir(const Intervalo & obj) {
    if (obj.esVacio())
        cout << "(0)";
    else {
        if (obj.dentroCotaInf())
         cout << '[';
        else cout << '(';
        cout << obj.getCotaInf() << "," << obj.getCotaSup();
        if (obj.dentroCotaSup())
            cout << ']';
        else cout << ')';
    }
}

void leer(Intervalo & obj){
    // Formato de lectura del intervalo: [|( x,y )|]
    bool cerradoInf = true;
    bool cerradoSup = true;
    double cotaInf, cotaSup;
    char car;
    cin >> car;
    if (car == '(')
        cerradoInf = false;
    cin >> cotaInf;
    cin >> car;
    cin >> cotaSup;
    cin >> car;
    if (car == ')')
        cerradoSup = false;
    obj.setIntervalo(cotaInf, cotaSup, cerradoInf, cerradoSup);
}

void comprobarVacio(Intervalo obj){
	 escribir(obj);
    if (obj.esVacio())
        cout << " Vacio";
    else  cout << " NO Vacio";
    cout << endl;
}


int main(){
    const int CAPACIDAD = 10;
    int i, nintervalos, nvalores;
    Intervalo vacio;
    Intervalo punto(1,1); // intervalo formado por un punto
    Intervalo interv[CAPACIDAD];
    double v[CAPACIDAD];

    cout << "El intervalo creado sin parametros es considerado un intervalo:\n";
    comprobarVacio(vacio);

    cout << "Cuantos intervalos (max 10):";
    do{
        cin >> nintervalos;
    } while (nintervalos >10);

    cout << "Introduce [ o ( cotaInferior, cotaSuperior ) o ]";
    for(i=0; i < nintervalos; i++)
        leer(interv[i]);

    cout << "Cuantos valores reales (max 10):";
    do{
        cin >> nvalores;
    } while (nvalores >10);

    cout << "Introduce valor real: ";
    for(i = 0; i < nvalores; i++)
        cin >> v[i];

    for(i = 0; i < nintervalos; i++){
      escribir(interv[i]);
      cout << " : ";
      for (int j = 0; j < nvalores; j++){
        if (interv[i].estaDentro(v[j]))
            cout << v[j] <<" ";
      }
      cout << endl;
    }
}
