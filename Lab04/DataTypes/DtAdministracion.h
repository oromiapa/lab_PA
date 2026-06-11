#ifndef DTADMINISTRACION_H
#define DTADMINISTRACION_H

#include <string>
#include <stdexcept>

#include "DtFecha.h"

#include "../ICollection/interfaces/ICollectible.h"


class DtAdministracion : public ICollectible {

private:
    DtFecha fechaInicio;

public:
//Constructor y Destructor
    DtAdministracion(const DtFecha &fechaInicio);
    virtual ~DtAdministracion();

//Gets
    DtFecha getFechaInicio() const ;

};

#endif
