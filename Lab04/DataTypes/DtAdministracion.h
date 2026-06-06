#ifndef DTADMINISTRACION_H
#define DTADMINISTRACION_H

#include <string>
#include <stdexcept>

//DataTypes internos
#include "DtFecha.h"

#include "../ICollection/interfaces/ICollectible.h"


class DtAdministracion : public ICollectible {

private:
    DtFecha fechaInicio;
public:
    DtAdministracion(const DtFecha &fechaInicio);
    virtual ~DtAdministracion();

    DtFecha getFechaInicio() const ;

};

#endif
