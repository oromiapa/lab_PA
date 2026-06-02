#ifndef APARTAMENTO_H
#define APARTAMENTO_H

#include "Inmueble.h"

class Apartamento : public Inmueble {

private:
    int numeroPiso;
    bool tieneAscensor;
    float gastosComunes;
public:
    Apartamento();
    Apartamento(const DtDireccion& direccion, const std::string& superficie, const DtFecha& anioConstruccion, int numeroID, int numeroPiso, bool tieneAscensor, float gastosComunes);

    int getNumeroPiso() ;
    float getGastosComunes() ;

    void setNumeroPiso(int numeroPiso);
    void setGastosComunes(float gastosComunes);

    bool tieneAscensor() ;

};
#endif
