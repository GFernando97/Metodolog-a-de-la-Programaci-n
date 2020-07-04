// Alumno: Gabriel Fernando Lojano Mayaguari
#ifndef _parcial_
#define _parcial_

#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class Robot{
public:
    /**
     * @brief Constructor base
     */
    Robot();
    Robot(long _id);
    Robot(float x, float y);
    Robot(long _id, float _x, float _y, double _potencia);

    /**
     * @brief Devuelve el id del robot
     * @return nombre
     */
    unsigned get_id() const;
    /**
     * @brief Devuelve coordenada x del robot
     * @return x
     */
    float get_X() const;
    /**
     * @brief Devuelve coordenada y del robot
     * @return y
     */

    float get_Y() const;
    /**
     * @brief Devuelve potencia  del robot
     * @return potencia
    */
    double get_potencia() const;

    /**
     * @brief Actualiza los datos del robot, si la longitud adecuada,
     *  en otro caso, no se actualiza
     * @param cadena, x e y
     */
    void set_Robot(long _id, float _x, float _y, double _potencia );
    bool es_positivo(double v){
     return v >= 0;
    }
private:
	unsigned id;
	float x,y;
	double potencia;
};

#endif