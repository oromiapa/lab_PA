#ifndef DTDIRECCION_H
#define DTDIRECCION_H

#include <string>


class DtDireccion {

private:
    std::string calle ;
    int numero ;
    std::string ciudad ;

public:
    DtDireccion() ;
    DtDireccion( const char* calle, int numero, const char* ciudad ) ;

    std::string getCalle() const ;
    int getNumero() const ;
    std::string getCiudad() const ;

};

#endif
