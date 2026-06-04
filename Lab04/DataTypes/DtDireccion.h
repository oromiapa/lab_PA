#ifndef DTDIRECCION_H
#define DTDIRECCION_H

#include <string>
#include <stdexcept>


class DtDireccion {

private:
    std::string calle ;
    int numero ;
    std::string ciudad ;

public:
    DtDireccion() ;
    DtDireccion( const std::string & calle, int numero, const std::string & ciudad ) ;

    std::string getCalle() const ;
    int getNumero() const ;
    std::string getCiudad() const ;

};

#endif
