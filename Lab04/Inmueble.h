#ifndef INMUEBLE_H
#define INMUEBLE_H

#include <string>
#include <stdexcept>

//DataTypes
#include "./DataTypes/DtDireccion.h"
#include "./DataTypes/DtFecha.h"

//ICollection/interfaces
#include "./ICollection/interfaces/ICollectible.h"


class Propietario;
class Inmobiliaria;

class Inmueble : public ICollectible {

private:
    DtDireccion direccion;
    float superficie;
    DtFecha anioConstruccion;
    int numeroID;
    Propietario* duenio;
    
public:
    Inmueble(const DtDireccion& direccion, float superficie, const DtFecha& anioConstruccion, const int numid) ;
    ~Inmueble() ;

    DtDireccion getDireccion() ;
    float getSuperficie() ;
    DtFecha getAnioConstruccion() ;
    int getNumeroID() ;
    Propietario* getDuenio() const;

    void setDireccion(const DtDireccion& direccion);
    void setSuperficie(float superficie);
    void setAnioConstruccion(const DtFecha& anioConstruccion);
    void setNumeroID(int numeroID);
    void setDuenio(Propietario* p);




};

#endif