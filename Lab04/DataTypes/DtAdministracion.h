#ifndef DTADMINISTRACION_H
#define DTADMINISTRACION_H

#include <set>
#include "DtFecha.h"
#include "DtInmobiliaria.h"
#include "DtInmueble.h"
#include "DtPublicacion.h"

class DtAdministracion {
private:
    DtFecha fechaInicio;
    std::set<DtInmobiliaria> inmobiliarias;
    std::set<DtInmueble> inmuebles;
    std::set<DtPublicacion> publicaciones;

public:
    // Constructores
    DtAdministracion();
    DtAdministracion(const DtFecha& fechaInicio,
                     const std::set<DtInmobiliaria>& inmobiliarias,
                     const std::set<DtInmueble>& inmuebles,
                     const std::set<DtPublicacion>& publicaciones);

    // Getters según UML
    DtFecha getFechaInicio() const;
    std::set<DtInmobiliaria> getInmobiliarias() const;
    std::set<DtInmueble> getInmuebles() const;
    std::set<DtPublicacion> getPublicaciones() const;
};

#endif
