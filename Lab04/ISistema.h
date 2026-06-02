#ifndef ISISTEMA_H
#define ISISTEMA_H

#include <string>
#include "./ICollection/Interfaces/ICollection.h" 
#include "./DataTypes/DtDireccion.h"
#include "./DataTypes/DtFecha.h"

class ISistema {

public:
    ~ISistema() ;
    virtual bool existeUsuario(const std::string & nickname) = 0;
    virtual void altaCliente(const std::string & nickname, const std::string & nombre, const std::string & email, const std::string & contrasenia, const std::string & apellido, const std::string & documento) = 0;
    virtual void altaPropietario(const std::string & nickname, const std::string & nombre, const std::string & email, const std::string & contrasenia, const std::string & telefono, int cuentaBancaria) = 0;
    virtual int autoincremental() = 0;
    virtual void crearCasa( const DtDireccion & direccion, const DtFecha & añoConstruccion, float superficie, bool propiedadHorizontal, TipoTecho tipoTecho) = 0;
    virtual void crearApartamento( const DtDireccion & direccion, const DtFecha & añoConstruccion, float superficie, int piso, bool TieneAscensor, const float & gastosComunes) = 0;
    virtual void altaInmobiliaria(const std::string & nickname, const std::string & nombre, const std::string & email, const std::string & contrasenia, const DtDireccion & direccionInmobiliaria, const std::string & telefono, const std::string & URL) = 0;
    virtual ICollection* listarPropietarios() = 0;
    virtual void vincularPropietario(Propietario* p) = 0;


};

#endif