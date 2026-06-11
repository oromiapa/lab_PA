#ifndef DTCASA_H
#define DTCASA_H

#include "DtInmueble.h"
#include "TipoTecho.h"

class DtCasa : public DtInmueble {
    
private:
    bool propiedadHorizontal;
    TipoTecho techo;

public:
    DtCasa(int id, const DtDireccion& dir, float sup, const DtFecha& fecha, bool propiedadHorizontal, TipoTecho techo) ;

    bool getPropiedadHorizontal() const ;
    TipoTecho getTecho() const ;


};

#endif