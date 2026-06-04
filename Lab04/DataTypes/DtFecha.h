#ifndef DTFECHA_H
#define DTFECHA_H

#include <string>
#include <stdexcept>

class DtFecha {

private:
    int dia, mes, anio ;

public:
    DtFecha() ;
    DtFecha( int dia , int mes , int anio ) ;

    int getDia() ;
    int getMes() ;
    int getAnio() ;

};

#endif
