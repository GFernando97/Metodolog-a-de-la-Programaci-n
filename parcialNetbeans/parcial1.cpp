/*
     * Se trata de gestionar la información de unos robotes que se mueve en un espacio 2D, esto es, 
     * un vector de objetos con coordenadas x, y y hacer operaciones con ellos.
     * Un robot tiene tienen un id (unico), 2 coordenadas y una potencia de acción (alcance).
     * 
     * Con la ayuda de la clase Robot ya definida se pide:
     * dimensionar un vector de Robot original, con el tamaño adecuado para almacenar una serie de robotes leidos desde teclado, 
     * Para la lectura de los datos del vector original, se leen los datos de un robot mientras el id no sea -1, condicion de parada.
     * La lectura y almacenamiento se lleva a cabo mientras id sea positivo.
     * Una vez terminada la lectura de robotes, se lee un nuevo robot inhibidor sobre una variable, (tiene los mismos datos).
     * 
     * Cuando un robot r, se encuentra a una distancia inferior a la potencia de alcance de un inhibidor,
     * el robot r, queda inactivo (muerto).
     * Es necesario elaborar un vector (tambien dinámico) resultante con los robotes originales supervivientes 
     * (no muertos) resultante de aplicar el robot inhibidor.
     * 
     * Se ha preparado el fichero parcial1.dat con los datos siguientes:
     * 
        1 9.1 9.1 1
        2 10.5 10.5 1
        3 11.0 11.0 1
        4 3.5 1.2 2
        5 2.7 10.3 2
        6 4.5 6.7 2
        7 19.9 10.10 3
        8 1.1 4.4 3
        9 10.0 9.0 3
        10 0.0 0.0 1
        -1
        100 9 9 3


        Los vectores que sobrebiben son los que se deben de mostrar en pantalla.
        Se ha informado de que mueren los robots 1, 2, 3, y 9.

        Por tanto La salida es:

        Se filtra el vector de robots 
        4->(3.5,1.2,2),
        5->(2.7,10.3,2),
        6->(4.5,6.7,2),
        7->(19.9,10.1,3),
        8->(1.1,4.4,3),
        10->(0,0,1),


        Tareas a realizar
        0. Rellenar nombre y apellidos en el token Alumno
         

        1. Completar las funciones:
        agnadeRobot
        reservarM
        liberarM
        afectado
        supervivientes

        2. Revisar las cabeceras de las funciones independientes el número y tipos son los correctos.
        La forma de pasar los argumentos (por valor, referencia etc.) lo decides tu

        3. Partir o no el código
        Se puede dejar todo en un solo fichero, en ese caso el ejercicio tan solo se evalua sobre 8.
        Si decide hacer compilación separada usará la estructura de ficheros y directorios habitual:
        robot.h, robot.cpp y parcial1.cpp

        4. Entregar en prado en los ficheros
        robot.zip si opcion en un solo fichero
        robot_separado.zip  si opcion de compilacion separado

        Solo en caso de separado se entrega además el makefile, propio o generado por netbeans.
*/

// Alumno: Gabriel Fernando Lojano Mayaguari

#include "parcial1.h"

Robot::Robot(){
    x = y = 0;
    id = 0;
    potencia = 1;
}
Robot::Robot(long _id){
    x = y = 0;
    if (es_positivo(_id))
        id = _id;
    else {
        id = 0;
    }
    potencia = 1;

}

Robot::Robot( long _id, float _x, float _y, double _potencia=1){
    x = _x;
    y = _y;
    if (es_positivo(_id))
        id = _id;
    else {
        id = 0;
    }
    if (es_positivo(_potencia))
       potencia = _potencia;
    else potencia = 1;
}
unsigned Robot::get_id() const{
    return id;
}
float Robot::get_X() const{
    return x;
}
float Robot::get_Y() const{
    return y;
}
double Robot::get_potencia()const{
    return potencia;
}
void Robot::set_Robot(long _id, float _x, float _y, double _potencia=1){
    x = _x;
    y = _y;
    if (es_positivo(_id))
        id = _id;
    else {
        id = 0;
    }
    if (es_positivo(_potencia))
       potencia = _potencia;
    else potencia = 1;
}

/* _______________ Funciones externas ________________ */

    /**
     * @brief calcula la distancia entre 2 robots
     * da igual el orden de los robots, el calculo de la distancia es
     * simetrica y positiva.
     * @param rb1 robot
     * @param rb2 robot
     * @return devuelve la distancia calculada
     */

float distancia( const Robot &rb1,  const Robot &rb2){
	float x = fabs(rb1.get_X() - rb2.get_X());
	float y = fabs(rb1.get_Y() - rb2.get_Y());

	return(sqrt( x*x + y*y ));
}
 /**
 * @brief indica si un robot se ve afectado "muerto" por la influencia de
 * un inhibidor con un rango de potencia.
 * @param rt, robot que se comprueba si está muerto o no
 * @param robot inhibidor, con su posicion x y potencia interna
 * @return devuelve true si queda afectado, esta muerto, falso si esta activo.
 */

bool afectado( Robot rt,  Robot inhibidor){
	float dist = distancia(rt, inhibidor);

    if(inhibidor.get_potencia() >= dist)
        return true;

    else return false;
}

void imprimirVector(const Robot *v, int n)  {
	for (int i=0; i<n; i++)
		cout << v[i].get_id() << "->(" << v[i].get_X() << "," << v[i].get_Y() << "," << v[i].get_potencia()<< ")," << endl;
}
/**
 * @brief reserva memoria para  n robots,
 * @param n número de robots a reservar
 * @return direcion de inicio de memoria reservada
 */

Robot * reservaM(int n) {
    Robot * reservado=new Robot [n];

    return reservado;

}

/**
 * @brief Libera la memoria correspondiente a un vector
 * @param v vector de robotes, se ve modificado
 */

void liberarM(Robot *v) {
    delete [] v;


}
/**
 * @brief crea un nuevo vector con un robot adicional, para lo que ha de
 * volcar todos los robots anteriores y añadir el nuevo robot
 * @param nuevo, elemento a introducir en el vector v
 * @param v, vector de robotes devuelve un nuevo vector redimensionado
 * @param tam, numero de componentes devuelve el nuevo tamaño
 */
/**
 * 
 * 
 */
void agnadeRobot( Robot nuevo, Robot *  &v,  int &tam){
    int nuevoTam = tam+1;
    
    Robot *rAux = reservaM(nuevoTam);

    if(tam > 0){
        for(int i= 0; i < tam; i++){
            rAux[i] =  v[i];
        }
    }

    rAux[tam]=nuevo;
    tam = nuevoTam;

    liberarM(v);
    v = rAux;      


}
/**
 * @brief realiza un  filtrado de cada uno de los robots de v_original
 * con respecto al robot inhibidor y su rango de accion, se queda con
 * los robots no afectados en un vector resultante
 * @param entrada de vector de original
 * @param entrada del tamaño de original
 * @param entrada de robot inhibidor
 * @param entrada de rango de accion del inhibidor
 * @param devuelve el vector de salida
 * @param devuelve el nuevo tamaño
 */

void supervivientes(Robot * &v_original, int n,  const Robot &inhibidor, Robot * &v_salida, int &n_salida){
    for(int i = 0; i < n; i++){
        if(!afectado(v_original[i], inhibidor))
            agnadeRobot( v_original[i], v_salida,  n_salida);

    }


}


int main(int argc, char** argv)  {
	Robot *v_org = nullptr;     // vector de robots original
	Robot *v_rsult = nullptr;   // vector de robots resultante
	int n_org, n_rsult; // longitudes respectivas

	float x, y;  // variables de usar y tirar para la lectura
	unsigned id;
	double potencia;



    n_org = 0;
    n_rsult = 0;


    // leer vector original 

    cout << "id (-1 para terminar):";
    cin >> id;

    while (id != -1 ){
        cin >> x >>  y >> potencia;
        Robot local(id, x, y, potencia);

        agnadeRobot( local, v_org,  n_org);

        cin >> id;
    }
    
       


	cout << "\nVector de robots originales " << endl;
	imprimirVector(v_org,n_org);

        // leer Robot inhibidor

    cin >> id >> x >> y >> potencia;

    Robot auxInhibidor(id, x, y, potencia);

	cout << "\n\n\n Se filtra el vector de robots " << endl;
	supervivientes(v_org, n_org, auxInhibidor, v_rsult, n_rsult);

	imprimirVector(v_rsult, n_rsult);

	// liberar espacio si procede
    liberarM(v_org);
    liberarM(v_rsult);

	return 0;
}
