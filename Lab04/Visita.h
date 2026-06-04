#ifndef VISITA_H
#define VISITA_H

#include <string>
#include <stdexcept>
#include "./DataTypes/DtFecha.h"
#include "Cliente.h"
#include "Publicacion.h"


class Visita {

private:
    DtFecha fechavisita;
    std::string contacto;

public:
    Visita(const DtFecha& fechavisita, const std::string& contacto);
    ~Visita();

    DtFecha getFechaVisita() ;
    std::string getContacto() ;

};

#endif 