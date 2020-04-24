/**
 * @file move.h
 * @author DECSAI
 * @note To be implemented by students
 * @warning Adjust const and references when needed
 */

// Alumno1: Adrián López Castro
// Alumno2: Fernando Lojano Mayaguari

#ifndef MOVE_H
#define MOVE_H

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>

#include "language.h"
/**
 * @class Move
 * @brief Class to represent both a single movement, which might not be
 * a recognizable word, and a crossword in the table, which must be a known
 * word in the chosen language.
 * 
 * **Please note that all the characters are stored in ISO8859 standard and in uppercase**
*/
class Move {
private:
	int row, column;		/// Coordinates of the first letter
	bool ishorizontal;	/// Horizontal or vertical
	std::string letters;	/// Letters of the movement
	int score;				/// Total value of movement according to the language chosen
public:
	/**
	 * @brief Basic constructor e initializator
	 */
	Move();
	/**
	 * @brief Sets the main data of the class 
	 * @param r row
	 * @param c column
	 * @param h 'H' horizontal or 'V' vertical
	 * @param l letters
	 */
	void set(int r, int c, char h, const std::string  &l);
	/**
	 * @brief Sets the main data of the class 
	 * @param r row
	 */
	void setRow(int r);
	/**
	 * @brief Sets the main data of the class 
	 * @param c Column
	 */
	void setCol(int c);
	/**
	 * @brief Sets the main data of the class 
	 * @param h 'H' horizontal or 'V' vertical
	 */
	void setHorizontal(char h);
	/**
	 * @brief Sets the main data of the class 
	 * @param l Letters
	 */
	void setLetters(const std::string &l);
	/**
	 * @brief Calculates the value of the movement by adding the value 
	 * each letter according to the chosen language. If the word contained in 
	 * the set of letters does not belong to the language, its score would be -1 
	 * @param l The language
	 * @return The sum of individual values according to the language, or -1 if the 
	 * word does not belong to the language.
	 */
	int findScore(const Language &l)const;
	/**
	 * @brief Sets the value of the movement which have been calculated elsewhere 
	 * @param s The value of the movement
	 */
	void setScore(int s);
	/**
	 * @brief Query data stored in the class
	 * @return The value stored
	 */
	int getScore() const;
	/**
	 * @brief Query data stored in the class
	 * @return The row stored
	 */
	int getRow() const;
	/**
	 * @brief Query data stored in the class
	 * @return The column stored
	 */
	int getCol() const;
	/**
	 * @brief Query data stored in the class
	 * @return @retval true if it is a horizontal move, @retval false otherwise
	 */
	bool isHorizontal() const;
	/**
	 * @brief Query data stored in the class
	 * @return The letters
	 */
	std::string getLetters() const;

	/**
	 * @brief Shows the values stored in the screen, except score 
	 */
	void print(std::ostream &os) const;
	/**
	 * @brief Reads from keyboard the values of the class, except score 
	 */
	void read(std::istream &is);
};
#endif /* MOVE_H */



/*
 * 
 * *
1. El main() recibe como parámetros obligatorios "-l <ID>" y
"-p <playfile>" y como parámetro opcional "-r <random>" ,
en cualquier orden entre los tres. En este caso, el parámetro
"-p" hace referencia a una partida guardada, la cual, por aho-
ra, sólo tiene los movimientos. Si se especifica "-r" se define
el aleatorio con el número indicado, si no, no se define aleatorio.
 * 
2. Crear una instancia de la clase Language con el anterior ID y
mostrar el conjunto de caracteres permitido para ese lenguaje.
 * 
3. Crear una instancia de la clase Bag, inicializar el generador de
números aleatorios con el número aleatorio anterior, si es que
se ha indicado, y definir su contenido en base al lenguaje que
se ha declarado anteriormente.
 * 
4. Crear una instancia de la clase Player y llenarla por comple-
to con caracteres de la bolsa. Este objeto player deberá estar
siempre ordenado de la A a la Z.
 * 
5. Crear una instancia de la clase bf Movelist llamada original
y leer todos los movimientos desde el fichero indicado en el
parámetro -p usando el método read(...)
 * 
6. Crear una instancia de Movelist llamada legal que contenga
sólo los movimientos de original que están en el diccionario
del lenguaje elegido. Usar, para ello, el método zip(...)
 * 
7. Crear dos instancias adicionales de Movelist y llamarlas accepted
y rejected
 * 
8. Recorrer toda la lista de movimientos leı́da y, por cada uno de
ellos.
a) Si el movimiento está en el diccionario, añadir la palabra a
la lista accepted , marcarla, calcular su puntuación, según
el idioma, y mostrarlo en la pantalla.
b) En otro caso añadirla a la lista rejected y marcarla.
c) Todos estos mensajes en pantalla no afectan a la validación
de la práctica, ası́ que el alumno puede implementarlas a
su propio parecer.
 * 
9. Terminar con la llamada a HallOfFame para visualizar los re-
sultados. Esta llamada es la que se utilizará para validar los
datos.
 * 
10. Si en cualquier momento se presenta un error en los argumen-
tos, en la apertura de ficheros o en la lectura de datos del fiche-
ro, se debe usar la función errorBreak(...) para notificar el error
y parar el programa.
*/
 
