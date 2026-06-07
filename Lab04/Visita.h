#ifndef VISITA_H
#define VISITA_H

#include <string>
#include <stdexcept>

// DataTypes
#include "./DataTypes/DtFecha.h"

// ICollection/interfaces
#include "./ICollection/interfaces/ICollectible.h"


class Visita : public ICollectible {

private:
    DtFecha fechavisita;
    std::string contacto;

public:
// Constructor y Destructor
    Visita(const DtFecha& fechavisita, const char* contacto);
    virtual ~Visita(); 

// Gets
    DtFecha getFechaVisita() const; 
    std::string getContacto() const;

// Sets
    void setFechaVisita(const DtFecha& fechavisita);
    void setContacto(const std::string& contacto);
};

#endif