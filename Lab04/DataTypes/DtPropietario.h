#ifndef DTPROPIETARIO_H
#define DTPROPIETARIO_H

#include <string>
#include <stdexcept>
#include "../ICollection/interfaces/ICollectible.h"

class DtPropietario : public ICollectible {

private:
    std::string nickname;
    std::string nombre;

public:
//Constructor y Destructor
    DtPropietario(std::string nick, std::string nom);
    virtual ~DtPropietario();

//Gets
    std::string getNickname() const ;
    std::string getNombre() const;

};

#endif