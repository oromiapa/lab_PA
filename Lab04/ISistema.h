#ifndef ISISTEMA_H
#define ISISTEMA_H

#include <string>
#include <set>
#include <memory>

// DTOs forward
struct DataInmobiliaria;
struct DataInmueble;
struct DataPropietario;
struct DataFiltro;

class Inmobiliaria;
class Inmueble;
class Publicacion;

class ISistema {
public:
    virtual ~ISistema() = default;

    // Métodos principales (interfaz pura)
    virtual bool existeUsuario(const std::string& nickname) = 0;

    virtual void altaCliente(const std::string& contrasenia, const std::string& email,
                             const std::string& nombre, const std::string& apellido,
                             const std::string& documento) = 0;

    virtual void altaPropietario(const std::string& contrasenia, const std::string& email,
                                 const std::string& nombre, int cuentaBancaria,
                                 const std::string& telefono) = 0;

    virtual void crearCasa(const std::string& direccion, const std::string& anioConstruccion,
                           float superficie, bool propiedadHorizontal, const std::string& tipoTecho) = 0;

    virtual void crearApartamento(const std::string& direccion, const std::string& anioConstruccion,
                                  float superficie, int piso, bool tieneAscensor,
                                  float gastosComunes) = 0;

    virtual void altaInmobiliaria(const std::string& contrasenia, const std::string& email,
                                  const std::string& nombre, const std::string& direccion,
                                  const std::string& telefono, const std::string& url) = 0;

    virtual std::set<DataPropietario> listarPropietarios() = 0;
    virtual void vincularPropietario(const std::string& nickname) = 0;

    virtual std::set<DataInmobiliaria> listarInmobiliarias() = 0;
    virtual std::shared_ptr<Inmobiliaria> seleccionarInmobiliaria(const std::string& nickname) = 0;

    virtual std::set<DataInmueble> listarInmuebles() = 0;
    virtual std::shared_ptr<Inmueble> seleccionarInmueble(int numeroID) = 0;

    virtual void altaPublicacion(const std::string& nickname, const std::string& texto,
                                 int precio, bool tipoPublicacion) = 0;

    virtual std::set<DataFiltro> filtrarPublicaciones(bool tipoPublicacion,
                                                      float precioMinimo,
                                                      float precioMaximo,
                                                      int tipoInmueble) = 0;

    virtual std::shared_ptr<Publicacion> seleccionarPublicacion(int id) = 0;

    virtual std::set<DataPropietario> listarInmueblesxPropietario() = 0;

    virtual void eliminarInmueble(int numeroID) = 0;

    virtual int autoincremental() = 0;
};

#endif // ISISTEMA_H
