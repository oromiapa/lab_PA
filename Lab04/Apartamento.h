#ifndef APARTAMENTO_H
#define APARTAMENTO_H

//Clases
#include "Inmueble.h"

class Apartamento : public Inmueble {

private:
    int numeroPiso;
    bool tieneAscensor;
    float gastosComunes;

public:
//Constructor y Destructor
    Apartamento(const DtDireccion& direccion, const float superficie, const DtFecha& anioConstruccion, const int numid, int numeroPiso, bool tieneAscensor, float gastosComunes);
    ~Apartamento();

//Gets
    int getNumeroPiso() ;
    float getGastosComunes() ;
    bool hayAscensor() ;

//Sets
    void setNumeroPiso(int numeroPiso);
    void setGastosComunes(float gastosComunes);


};
#endif
