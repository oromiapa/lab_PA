#ifndef DTPROPIETARIO_H
#define DTPROPIETARIO_H

#include <string>
#include <set>
#include "DtInmueble.h"

class DtPropietario {
private:
    std::string nickname;
    std::string nombre;
    std::set<DtInmueble> inmuebles;

public:
    // Constructores
    DtPropietario();
    DtPropietario(const std::string& nickname, const std::string& nombre,
                  const std::set<DtInmueble>& inmuebles);

    // Getters según UML
    std::string getNickname() const;
    std::string getNombre() const;
    std::set<DtInmueble> getInmuebles() const;
};

#endif
