#ifndef DTINMUEBLEADMINISTRADO_H
#define DTINMUEBLEADMINISTRADO_H

//DataTypes internos empaquetados
#include "DtAdministracion.h"
#include "DtDireccion.h"
#include "DtFecha.h"

#include "../ICollection/interfaces/ICollectible.h"


class DtInmuebleAdministrado : public ICollectible {

private:
    int numid;
    DtDireccion direccion;
    DtAdministracion fechaAdministracion;

public:
//Constructor y Destructor
    DtInmuebleAdministrado(int id, const DtDireccion &dir, const DtAdministracion &fechaAdm);
    virtual ~DtInmuebleAdministrado();

//Gets
    int getNumId() const ;
    DtDireccion getDireccion() const ;
    DtAdministracion getFechaAdministracion() const ; 
};


#endif