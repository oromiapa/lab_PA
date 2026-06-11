#ifndef DTVISITA_H
#define DTVISITA_H

#include "DtFecha.h"
#include "../ICollection/interfaces/ICollectible.h"



class DtVisita : public ICollectible {

private:
    DtFecha fecha;
    int idPublicacion;
    std::string nicknameCliente;

public:
//Constructor y Destructor
    DtVisita(const DtFecha & fecha, int idPublicacion, const std::string & nicknameCliente);
    ~DtVisita();

// Gets
    DtFecha getFecha() const;
    int getIdPublicacion() const;
    std::string getNicknameCliente() const;
};

#endif 