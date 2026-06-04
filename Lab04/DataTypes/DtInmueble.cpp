#include "DtInmueble.h"

DtInmueble::DtInmueble(int id, const DtDireccion &dir, float sup, const DtFecha &fecha) 
    : numid(id), direccion(dir), superficie(sup), anioConstruccion(fecha) {}
    
DtInmueble::~DtInmueble() {}

int DtInmueble::getNumId() const {
    return numid;
}

DtDireccion DtInmueble::getDireccion() const {
    return direccion;
}

float DtInmueble::getSuperficie() const {
    return superficie;
}

DtFecha DtInmueble::getAnioConstruccion() const {
    return anioConstruccion;
}

