#ifndef DTAPARTAMENTO_H
#define DTAPARTAMENTO_H

#include "DtInmueble.h"

class DtApartamento : public DtInmueble {
private:
    int numeroPiso;
    bool tieneAscensor;
    float gastosComunes;

public:
    DtApartamento(int id, const DtDireccion& dir, float sup, const DtFecha& fecha, int numeroPiso, bool tieneAscensor, float gastosComunes) ;

    int getNumeroPiso() const ;
    bool hayAscensor() const ;
    float getGastosComunes() const ;
    
};

#endif