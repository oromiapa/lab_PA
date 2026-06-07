#ifndef VISITA_H
#define VISITA_H

#include <string>
#include <stdexcept>

// DataTypes
#include "./DataTypes/DtFecha.h"

//ICollection/interfaces
#include "./ICollection/interfaces/ICollectible.h"


class Visita {

private:
    DtFecha fechavisita;
    std::string contacto;

public:
//Constructor y Destructor
    Visita(const DtFecha& fechavisita, const char* contacto);
    ~Visita();

//Gets
    DtFecha getFechaVisita() ;
    std::string getContacto() ;

//Sets
    void setFechaVistia() ;
    void setContacto() ;

};

#endif 