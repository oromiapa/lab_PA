#ifndef DTPUBLICACION_H
#define DTPUBLICACION_H

#include <string>

#include <stdexcept>
#include "../ICollection/interfaces/ICollectible.h"

//DataTypes
#include "DtFecha.h"
#include "TipoInmueble.h"



class DtPublicacion : public ICollectible {

private:
    int id ;
    DtFecha fechapub ;
    std::string texto ;
    TipoInmueble tipo ;

public:
//Constructor y Destructor
    DtPublicacion(const int idpub , const DtFecha &fecha , const char* text , const TipoInmueble &types) ;
    ~DtPublicacion() ;

//Gets
    int getID() const ;
    DtFecha getFechaPublicacion() const ;
    std::string getTexto() const ;
    TipoInmueble getTipo() const ;


};



#endif