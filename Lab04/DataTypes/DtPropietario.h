#ifndef DTPROPIETARIO_H
#define DTPROPIETARIO_H

#include <string>
#include "../ICollection/interfaces/ICollectible.h" 

class DtPropietario : public ICollectible {

private:
    std::string nickname;
    std::string nombre;

public:
    DtPropietario(std::string nick, std::string nom);
    virtual ~DtPropietario();

    std::string getNickname() const ;
    std::string getNombre() const;

};

#endif