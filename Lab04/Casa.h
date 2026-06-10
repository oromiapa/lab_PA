#ifndef CASA_H
#define CASA_H

//Clases
#include "Inmueble.h"

//DataTypes
#include "./DataTypes/TipoTecho.h"

class Casa : public Inmueble {
private:
    bool propiedadHorizontal;
    TipoTecho techo;

public:
//Constructor y Destructor
    Casa(const DtDireccion& direccion, float superficie, const DtFecha& anioConstruccion, const int numid, bool propiedadHorizontal, TipoTecho techo);
    ~Casa();

//Gets
    bool getPropiedadHorizontal() ;
    TipoTecho getTecho() ;
    bool isPropiedadHorizontal() ;

//Sets
    void setPropiedadHorizontal(bool propiedadHorizontal);
    void setTecho(TipoTecho techo);

//5to Caso
    bool cumpleTipo(TipoInmueble tipo) ;


};

#endif