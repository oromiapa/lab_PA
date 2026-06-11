#ifndef DTInmobiliaria_H
#define DTInmobiliaria_H

#include <string>
#include <stdexcept>
#include "../ICollection/interfaces/ICollectible.h" 

class DtInmobiliaria : public ICollectible {

private:
    std::string nickname;
    std::string nombre;

public:
//Constructor y Destructor
    DtInmobiliaria(std::string nick, std::string nom);
    virtual ~DtInmobiliaria();

//Gets
    std::string getNickname() const ;
    std::string getNombre() const;

};

#endif