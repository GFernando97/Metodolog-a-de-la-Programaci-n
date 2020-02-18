#ifndef _INTERVALO_H_
#define _INTERVALO_H_

#include <iostream>
#include <string>

using namespace std;

class Intervalo{
private:
  bool cerradoInf;
  bool cerradoSup;
  double cotaInf;
  double cotaSup;

  /**
   * @brief comprueba que los argumentos definen un intervalo correcto
   * cotaInferior <= cotaSuperior y algo MAS
   * @param cotaInferior
   * @param cotaSuperior
   * @return @retval true si correcto
   */
  bool valido(double Inf, double Sup, bool closedInf, bool closedSup);

public:

  /**
   *  @brief Intervalo vacio por defectoSup
   *  valorInf = valorSup & abiertoInf + abierto
   */
  Intervalo();

  /**
   * @brief Crea un Intervalo  cerrado por defecto
   * @param Inf
   * @param Sup
   * @precond Inf <= Sup
   */
  Intervalo(double Inf, double Sup);

  /**
   * @brief Crea Intervalo
   * @param closedInf
   * @param closedSup
   * @param Inf
   * @param Sup
   * @precond Inf <= Sup
   */
  Intervalo(double Inf , double Sup, bool closedInf, bool closedSup);

  /**
   * @brief Devuelve la cota inferior del intervalo
   * @return El valor de la cota
   */
  double getCotaInf()const {return cotaInf;}

  /**
   * @brief Devuelve la cota superior del intervalo
   * @return El valor de la cota
   */
  double getCotaSup()const {return cotaSup;}

  /**
   * @brief Consulta si el intervalo es cerrado en su cota inferior
   * @return @retval true si es cerrado @retval false si es cerrado
   */
  bool dentroCotaInf()const {return cerradoInf;}

  /**
   * @brief Consulta si el intervalo es cerrado en su cota superior
   * @return @retval true si es cerrado @retval false si es cerrado
   */
  bool dentroCotaSup()const { return cerradoSup;}

  /**
   * @brief Define los valores del intervalo
   * @param closedInf
   * @param closedSup
   * @param Inf
   * @param Sup
   * @precond Inf <= Sup
   */
  void setIntervalo(double Inf, double Sup, bool closedInf, bool closedSup);

  /**
   * @brief Consulta si el intervalo almacenado es vacío o no
   * @return @retval true si es un intervalo vacío, @retval false en otro caso
   */
  bool esVacio()const {return cotaInf==NULL;}

  /**
   * @brief Consulta si un determinado valor está dentro del intervalo
   * @param n El valor consultado
   * @return @retval true si el valor @p n pertenece al intervalo, @retval false en otro caso
   */
  bool estaDentro(double n)const;

};

#endif
