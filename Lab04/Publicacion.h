#ifndef PUBLICACION_H
#define PUBLICACION_H

#include <string>
#include <stdexcept>


// DataTypes
#include "./DataTypes/DtFecha.h"

// ICollection/interfaces
#include "./ICollection/interfaces/ICollectible.h"
#include "./ICollection/interfaces/ICollection.h"


class Publicacion : public ICollectible {
private:
    int id;
    std::string texto;
    float precio;
    DtFecha fechaPublicacion;
    bool tipoPublicacion; // TRUE = Venta, FALSE = Alquiler
    bool activa;

public:
// Constructor y Destructor
    Publicacion(int id, const char* texto, float precio, const DtFecha& fecha, bool tipoPub, bool activa);
    virtual ~Publicacion();

// Gets
    int getID() const;
    std::string getTexto() const;
    float getPrecio() const;
    DtFecha getFechaPublicacion() const;
    bool getTipoPublicacion() const;
    bool getActiva() const;

// Sets
    void setTexto(const char* texto);
    void setPrecio(float precio);
    void setFechaPublicacion(const DtFecha& fecha);
    void setTipoPublicacion(bool tipoPub);
    void setActiva(bool activa);

//3er Caso
    bool comprobarTipo(bool tipoPub) const;
    bool mismaFecha(const DtFecha& fecha) const;

};

#endif