#include "DtAdministracion.h"


DtAdministracion::DtAdministracion(const DtFecha &fechaInicio) : fechaInicio(fechaInicio) {}
    
DtAdministracion::~DtAdministracion() {}


DtFecha DtAdministracion::getFechaInicio() const {
    return fechaInicio;
}
