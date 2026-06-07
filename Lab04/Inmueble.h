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
class Administracion;

class Inmueble : public ICollectible {

private:
    DtDireccion direccion;
    float superficie;
    DtFecha anioConstruccion;
    int numeroID;
    Propietario* duenio;
    Administracion* administracionAsociada;
    
public:
//Constructor y Destructor
    Inmueble(const DtDireccion& direccion, float superficie, const DtFecha& anioConstruccion, const int numid) ;
    ~Inmueble() ;

//Gets
    DtDireccion getDireccion() ;
    float getSuperficie() ;
    DtFecha getAnioConstruccion() ;
    int getNumeroID() ;
    Propietario* getDuenio() const;
    DtFecha getFechaAdministracion() const;

//Sets
    void setDireccion(const DtDireccion& direccion);
    void setSuperficie(float superficie);
    void setAnioConstruccion(const DtFecha& anioConstruccion);
    void setNumeroID(int numeroID);
    void setDuenio(Propietario* p);
    void setAdministracion(Administracion* admin);

//3er Caso
    void altaPublicacion(const int numid , const char* text , float price , bool tipopub) ;

//4to Caso
    void borrarAdministracion() ;
    void removerPropietario(int numid) ;


};

#endif