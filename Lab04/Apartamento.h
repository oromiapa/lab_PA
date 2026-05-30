#ifndef APARTAMENTO_H
#define APARTAMENTO_H

#include "Inmueble.h"

class Apartamento : public Inmueble {
private:
    int numeroPiso;
    bool TieneAscensor;    
    float gastosComunes;

public:
    Apartamento();
    Apartamento(const DtDireccion& direccion, const std::string& superficie,
                const DtFecha& anioConstruccion, int numeroID,
                int numeroPiso, bool ascensor, float gastosComunes);

    int getNumeroPiso() const;
    bool tieneAscensor() const;  
    float getGastosComunes() const;
};

#endif
