#ifndef INMUEBLE_H
#define INMUEBLE_H

#include "Propietario.h"
#include "./DataTypes/DtDireccion.h"
#include "./DataTypes/DtFecha.h"


class Inmueble {

private:
    DtDireccion direccion;
    std::string superficie;
    DtFecha anioConstruccion;
    int numeroID;
public:
    Inmueble() ;
    Inmueble(const DtDireccion& direccion, const std::string& superficie, const DtFecha& anioConstruccion, int numeroID) ;

    DtDireccion getDireccion() ;
    std::string getSuperficie() ;
    DtFecha getAnioConstruccion() ;
    int getNumeroID() ;

    void setDireccion(const DtDireccion& direccion);
    void setSuperficie(const std::string& superficie);
    void setAnioConstruccion(const DtFecha& anioConstruccion);
    void setNumeroID(int numeroID);




};

#endif