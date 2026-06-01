#include "DtAdministracion.h"

DtAdministracion::DtAdministracion() {}

DtAdministracion::DtAdministracion(const DtFecha& fechaInicio,
                                   const std::set<DtInmobiliaria>& inmobiliarias,
                                   const std::set<DtInmueble>& inmuebles,
                                   const std::set<DtPublicacion>& publicaciones)
    : fechaInicio(fechaInicio),
      inmobiliarias(inmobiliarias),
      inmuebles(inmuebles),
      publicaciones(publicaciones) {}

DtFecha DtAdministracion::getFechaInicio() const {
    return fechaInicio;
}

std::set<DtInmobiliaria> DtAdministracion::getInmobiliarias() const {
    return inmobiliarias;
}

std::set<DtInmueble> DtAdministracion::getInmuebles() const {
    return inmuebles;
}

std::set<DtPublicacion> DtAdministracion::getPublicaciones() const {
    return publicaciones;
}
