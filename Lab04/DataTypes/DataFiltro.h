#ifndef DATAFILTRO_H
#define DATAFILTRO_H

#include <string>

#include <stdexcept>
#include "../ICollection/interfaces/ICollectible.h"

//DataTypes
#include "DtInmobiliaria.h"
#include "DtPublicacion.h"


class DataFiltro : public ICollectible {

private:
    DtInmobiliaria datosinm ;
    DtPublicacion datospub ;

public:
//Constructor y Destructor
    DataFiltro(const DtInmobiliaria &datainm , const DtPublicacion &datapub) ;
    virtual ~DataFiltro() ;

//Gets
    DtInmobiliaria getDatosInmobiliaria() const;
    DtPublicacion getDatosPublicacion() const ;

};



#endif