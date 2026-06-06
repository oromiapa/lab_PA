#include "DtInmuebleAdministrado.h"


DtInmuebleAdministrado::DtInmuebleAdministrado(int id, const DtDireccion &dir, const DtAdministracion &fechaAdm) 
    : numid(id), direccion(dir), fechaAdministracion(fechaAdm) {}

DtInmuebleAdministrado::~DtInmuebleAdministrado() {}


int DtInmuebleAdministrado::getNumId() const {
    return numid;
}

DtDireccion DtInmuebleAdministrado::getDireccion() const {
    return direccion;
}

DtAdministracion DtInmuebleAdministrado::getFechaAdministracion() const {
    return this->fechaAdministracion;
}