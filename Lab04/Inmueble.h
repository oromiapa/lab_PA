#ifndef INMUEBLE_H
#define INMUEBLE_H

#include "Propietario.h"
#include "./DataTypes/DtDireccion.h"
#include "./DataTypes/DtFecha.h"
#include "./ICollection/Interfaces/ICollectible.h"


class Inmueble : public ICollectible {

private:
    DtDireccion direccion;
    float superficie;
    DtFecha anioConstruccion;
    int numeroID;
public:
    Inmueble(const DtDireccion& direccion, float superficie, const DtFecha& anioConstruccion, const int numid) ;
    ~Inmueble() ;

    DtDireccion getDireccion() ;
    float getSuperficie() ;
    DtFecha getAnioConstruccion() ;
    int getNumeroID() ;

    void setDireccion(const DtDireccion& direccion);
    void setSuperficie(float superficie);
    void setAnioConstruccion(const DtFecha& anioConstruccion);
    void setNumeroID(int numeroID);




};

#endif