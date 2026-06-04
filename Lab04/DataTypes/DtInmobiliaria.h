#ifndef DTInmobiliaria_H
#define DTInmobiliaria_H

#include <string>
#include "./ICollection/interfaces/ICollectible.h" 

class DtInmobiliaria : public ICollectible {

private:
    std::string nickname;
    std::string nombre;

public:
    DtInmobiliaria( const char* nick, const char* nom );
    virtual ~DtInmobiliaria();

    std::string getNickname() const ;
    std::string getNombre() const;

};

#endif