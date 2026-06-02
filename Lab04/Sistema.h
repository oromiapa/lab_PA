#ifndef SISTEMA_H
#define SISTEMA_H

#include <string>
#include "./ICollection/collections/OrderedDictionary.h"
#include "./ICollection/interfaces/IDictionary.h"
#include "./DataTypes/DtDireccion.h"
#include "./DataTypes/DtFecha.h"

class Usuario;
class Cliente;
class Propietario;
class Inmobiliaria;
class Inmueble;
class Casa;
class Apartamento;
class TipoTecho;

class Sistema {

private:
    IDictionary* usuarios;
    IDictionary* inmuebles;
    IDictionary* inmobiliarias;
    Inmobiliaria* inmobiliariaActual;
    int contadorInmuebles;

public:
    Sistema();
    ~Sistema();

    bool existeUsuario(const std::string & nickname);
    void altaCliente(const std::string & nickname, const std::string & nombre, const std::string & email, const std::string & contrasenia, const std::string & apellido, const std::string & documento);
    void altaPropietario(const std::string & nickname, const std::string & nombre, const std::string & email, const std::string & contrasenia, const std::string & telefono, int cuentaBancaria);
    int autoincremental();
    void crearCasa(const DtDireccion & direccion, const DtFecha & añoConstruccion, float superficie, bool propiedadHorizontal, TipoTecho tipoTecho);
    void crearApartamento(const DtDireccion & direccion, const DtFecha & añoConstruccion, float superficie, int piso, bool TieneAscensor, const float & gastosComunes);
    void altaInmobiliaria(const std::string & nickname, const std::string & nombre, const std::string & email, const std::string & contrasenia, const DtDireccion & direccionInmobiliaria, const std::string & telefono, const std::string & URL);
    ICollection* listarPropietarios();
    
    void vincularPropietario(Propietario* p);

};

#endif 