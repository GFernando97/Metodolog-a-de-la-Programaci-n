#include "intervalo.h"

bool Intervalo::valido(double Inf, double Sup, bool closedInf, bool closedSup){
  return (( Inf < Sup ) || ( Inf == Sup && closedInf == closedSup));
}

Intervalo::Intervalo(){
  setIntervalo(NULL, NULL, false, false);
}
Intervalo::Intervalo(double Inf, double Sup){
  setIntervalo(Inf, Sup, true, true);
}

Intervalo::Intervalo(double Inf, double Sup, bool closedInf, bool closedSup){
  setIntervalo(Inf, Sup, closedInf, closedSup);
}

void Intervalo::setIntervalo(double Inf, double Sup, bool closedInf, bool closedSup){
  if(valido(Inf, Sup, closedInf, closedSup)){
    this->cotaInf = Inf;
    this->cotaSup = Sup;
    this->cerradoInf = closedInf;
    this->cerradoSup = closedSup;
  }
}

bool Intervalo::estaDentro(double n)const{
  if( (this->getCotaInf() < n) and (n < this->getCotaSup()) )
    return true;

  else if( ((this->getCotaInf()== n) and (this->dentroCotaInf()))
        or ((this->getCotaSup()== n) and (this->dentroCotaSup())) )
    return true;

  else return false;
}
