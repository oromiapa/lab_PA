#include "DtInmXProp.h"


DtInmXProp::DtInmXProp(int id, const DtDireccion &dir, const DtPropietario &prop) : numid(id), direccion(dir), propietariovinculado(prop) {}

DtInmXProp::~DtInmXProp() {}


int DtInmXProp::getNumId() const {
    return numid;
}

DtDireccion DtInmXProp::getDireccion() const {
    return direccion;
}

DtPropietario DtInmXProp::getPropietariovinculado() const {
    return this->propietariovinculado;
}