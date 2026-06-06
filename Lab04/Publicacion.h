#ifndef PUBLICACION_H
#define PUBLICACION_H

#include <string>
#include <stdexcept>

//DataTypes
#include "./DataTypes/DtFecha.h"

//ICollection/interfaces
#include "./ICollection/interfaces/ICollectible.h"
#include "./ICollection/interfaces/ICollection.h"



class Publicacion {

private: 
    DtFecha fechaPublicacion;
    std::string texto;
    float precio;
    int id;
    bool activa;
    bool tipoPublicacion;

public:
    Publicacion();
    Publicacion(const DtFecha& fechaPublicacion, const std::string& texto, float precio, int id, bool activa, bool tipoPublicacion);

    DtFecha getFechaPublicacion() ;
    std::string getTexto() ;
    float getPrecio() ;
    int getId() ;

    void setFechaPublicacion(const DtFecha& fechaPublicacion);
    void setTexto(const std::string& texto);
    void setPrecio(float precio);
    void setId(int id);
    void setActiva(bool activa);
    void setTipoPublicacion(bool tipoPublicacion);

    bool estaActiva() ;
    bool esTipoPublicacion() ;

    

};

#endif