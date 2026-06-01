#ifndef DTPUBLICACION_H
#define DTPUBLICACION_H

#include <string>
#include "DtFecha.h"
#include "Tipo.h"

class DtPublicacion {
private:
    int codigoID;
    DtFecha fechaPublicacion;
    std::string texto;
    std::string nombre;
    Tipo tipo;

public:
    // Constructores
    DtPublicacion();
    DtPublicacion(int codigoID, const DtFecha& fechaPublicacion,
                  const std::string& texto, const std::string& nombre,
                  Tipo tipo);

    // Getters según UML
    int getCodigoID() const;
    DtFecha getFechaPublicacion() const;
    std::string getTexto() const;
    std::string getNombre() const;
    Tipo getTipo() const;
};

#endif
