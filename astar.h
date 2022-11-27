#ifndef ASTAR_H
#define ASTAR_H

#include <algorithm>
// con esto podremos utilizar el macro assert()
#include <assert.h>
#include <cfloat>
#include <iostream>
#include <vector>
using namespace std;

// EstadoUsuario es el tipo de estados del usuario
template <class EstadoUsuario> class BusquedaEstrella {

public:
  enum {
    ESTADO_NO_INICIALIZADO,
    ESTADO_BUSQUEDA,
    ESTADO_BUSQUEDA_EXITO,
    ESTADO_BUSQUEDA_FALLA,
    ESTADO_BUSQUEDA_SIN_MEMORIA,
    ESTADO_BUSQUEDA_INVALIDO
  };

public:
  class Nodo {
  public:
    // padre se usa en la busqueda para rastrear el padre de los sucessores de
    // los nodos
    Nodo *padre;
    // hijo es para ver la busqueda en reversa
    Nodo *hijo;
    // g es el costo de llegar a este nodo
    float g;
    // h es la heuristica estimada del costo de llegar al nodo final
    float h;
    // h es la suma acumulada del costo de los predecesores y la heuristica
    float f;

    EstadoUsuario estadoUsuario;
  };

  // la clase Comparar nos permite el valor f de dos nodos
  class Comparacion {
  public:
    bool operator()(const Nodo *x, const Nodo *y) const { return x->f > y->f; }
  };

public:
  // constructor solo inicializa datos
  BusquedaEstrella()
      : estado(ESTADO_NO_INICIALIZADO), solucionNodoActual(NULL), nodoContar(0),
        cancelarSolicitud(false) {}

  BusquedaEstrella(int NodosMax)
      : estado(ESTADO_NO_INICIALIZADO), solucionNodoActual(NULL), nodoContar(0),
        cancelarSolicitud(false) {}

  // llamamos en cualquier momento para cancelar la busqueda y liberar la
  // memoria
  void CancelarBusqueda() { cancelarSolicitud = true; }

  // establecemos el estado inicial y el final
  void SetStartAndGoalStates(EstadoUsuario &Inicio, EstadoUsuario &Meta) {
    cancelarSolicitud = false;

    inicio = AllocateNode();
    meta = AllocateNode();
    // revisar si el inicio y la meta son iguales
    assert((inicio != NULL && meta != NULL));

    inicio->estadoUsuario = Inicio;
    meta->estadoUsuario = Meta;

    estado = ESTADO_BUSQUEDA;

    // inicializamos el nodo de inicio
    // el usuario solo necesita rellenar la informacion del estado
    inicio->g = 0;
    inicio->h = inicio->estadoUsuario.DistanciaEstimada(meta->estadoUsuario);
    inicio->f = inicio->g + inicio->h;
    inicio->padre = 0;

    // agregamos el nodo inicial a la lista
    lista.push_back(inicio); // heap ordenado

    // ordenamos el nodo en el heap
    push_heap(lista.begin(), lista.end(), Comparacion());

    // inicializamos el contador de pasos de busqueda
    pasos = 0;
  }

  int pasosBusqueda() {
    // terminamos si el usuario no ha inicializado la busqueda
    assert((estado > ESTADO_NO_INICIALIZADO) &&
           (estado < ESTADO_BUSQUEDA_INVALIDO));

    // realizar una busqueda paso a paso en caso sea exito o fallo
    if ((estado == ESTADO_BUSQUEDA_EXITO) ||
        (estado == ESTADO_BUSQUEDA_FALLA)) {
      return estado;
    }

    // si la lista esta ya sea vacia o el usuario ha solicitado cancelar la
    // busqueda automaticamente retornamos fallo y liberamos la memoria
    if (lista.empty() || cancelarSolicitud) {
      estado = ESTADO_BUSQUEDA_FALLA;
      return estado;
    }

    // incrementamos el contador de pasos
    pasos++;

    // sacamos el nodo con el menor puntaje de f
    Nodo *n = lista.front(); // get pointer to the node
    pop_heap(lista.begin(), lista.end(), Comparacion());
    lista.pop_back();

    // chequeamos si el nodo se halla en la meta
    if (n->estadoUsuario.EsMeta(meta->estadoUsuario)) {
      // el usuario va a usar el nodo meta que paso
      meta->padre = n->padre;
      meta->g = n->g;

      // si en caso el nodo inicial es igual al nodo final
      if (false == n->estadoUsuario.MismoEstado(inicio->estadoUsuario)) {
        LiberarNodo(n);

        // definimos el puntero hijo en cada nodo (excepto meta que no tiene
        // hijo)
        Nodo *nodoHijo = meta;
        Nodo *nodoPadre = meta->padre;

        do {
          nodoPadre->hijo = nodoHijo;

          nodoHijo = nodoPadre;
          nodoPadre = nodoPadre->padre;

        } while (nodoHijo != inicio);
      }

      estado = ESTADO_BUSQUEDA_EXITO;

      return estado;
    } else // no es la meta
    {
      // vector de nodos sucesores a n
      sucesores.clear();

      bool ret = n->estadoUsuario.ConseguirSucesores(
          this, n->padre ? &n->padre->estadoUsuario : NULL);

      if (!ret) {
        typename vector<Nodo *>::iterator successor;

        // liberamos los nodos que previsamente fueron agregados
        for (successor = sucesores.begin(); successor != sucesores.end();
             successor++) {
          LiberarNodo((*successor));
        }
        // vector vacio de nodos sucesores
        sucesores.clear();
        // liberamos todo lo que previamente asignamos
        LiberarNodo(n);
        estado = ESTADO_BUSQUEDA_SIN_MEMORIA;
        return estado;
      }

      // manejamos cada sucesor del nodo actual
      for (typename vector<Nodo *>::iterator successor = sucesores.begin();
           successor != sucesores.end(); successor++) {
        // el valor de g para este sucesor
        float nuevoG =
            n->g + n->estadoUsuario.ConseguirCosto((*successor)->estadoUsuario);

        typename vector<Nodo *>::iterator openlist_result;

        for (openlist_result = lista.begin(); openlist_result != lista.end();
             openlist_result++) {
          if ((*openlist_result)
                  ->estadoUsuario.MismoEstado((*successor)->estadoUsuario)) {
            break;
          }
        }

        if (openlist_result != lista.end()) {
          // encontramos el siguiente estado en la lista abierta
          if ((*openlist_result)->g <= nuevoG) {
            LiberarNodo((*successor));
            // la abierta tiene un mejor camino, asi que la descartamos
            continue;
          }
        }

        typename vector<Nodo *>::iterator closedlist_result;

        for (closedlist_result = listaCerrada.begin();
             closedlist_result != listaCerrada.end(); closedlist_result++) {
          if ((*closedlist_result)
                  ->estadoUsuario.MismoEstado((*successor)->estadoUsuario)) {
            break;
          }
        }
        if (closedlist_result != listaCerrada.end()) {
          // este estado esta cerrado
          if ((*closedlist_result)->g <= nuevoG) {
            // el cerrado tiene un valor menor a este
            LiberarNodo((*successor));

            continue;
          }
        }
        // Este es el mejor nodo hasta ahora
        (*successor)->padre = n;
        (*successor)->g = nuevoG;
        (*successor)->h =
            (*successor)->estadoUsuario.DistanciaEstimada(meta->estadoUsuario);
        (*successor)->f = (*successor)->g + (*successor)->h;
        // Sucesor en una lista cerrada
        // 1. Actualizar la version anterior de este nodo en la lista cerrada
        // 2. Moverla de la lista cerrada a la abierta
        // 3. Ordenar el heap de nuevo
        if (closedlist_result != listaCerrada.end()) {
          (*closedlist_result)->padre = (*successor)->padre;
          (*closedlist_result)->g = (*successor)->g;
          (*closedlist_result)->h = (*successor)->h;
          (*closedlist_result)->f = (*successor)->f;
          // Liberamos el nodo sucesor
          LiberarNodo((*successor));
          // Agregamos el nodo cerrado a la lista abierta
          lista.push_back((*closedlist_result));
          // Eliminamos el nodo cerrado de la lista cerrada
          listaCerrada.erase(closedlist_result);
          // Ordenamos el elemento de nuevo en el heap
          push_heap(lista.begin(), lista.end(), Comparacion());
        }
        // Successor in open list
        // Sucesor en una lista abierta
        // 1. Actualizar la version anterior de este nodo en la lista abierta
        // 2. Ordenar el heap nuevamente
        else if (openlist_result != lista.end()) {
          // Actualizamos el nodo abierto con la data de EstrellaA
          (*openlist_result)->padre = (*successor)->padre;
          (*openlist_result)->g = (*successor)->g;
          (*openlist_result)->h = (*successor)->h;
          (*openlist_result)->f = (*successor)->f;
          // Liberamos el nodo sucesor
          LiberarNodo((*successor));
          make_heap(lista.begin(), lista.end(), Comparacion());
        }
        // nuevo sucesor
        // 1 - Moverlo de la lista de sucesores a la lista abierta
        // 2 - ordenamos el heap de nuevo en la lista abierta
        else {
          // agregamos el sucesor a la lista abierta
          lista.push_back((*successor));
          // ordenamos el elemento de nuevo en el heap
          push_heap(lista.begin(), lista.end(), Comparacion());
        }
      }
      // agregamos n a la lista cerrada, ya que lo expandimos
      listaCerrada.push_back(n);
    }
    return estado;
  }

  // se llama esto para agregar un sucesor a una lista de sucesores
  bool AgregarSucesor(EstadoUsuario &State) {
    Nodo *node = AllocateNode();
    if (node) {
      node->estadoUsuario = State;
      sucesores.push_back(node);
      return true;
    }
    return false;
  }

  // esto es para limpiar toda la memoria usada por los nodos cuando terminamos
  void LiberarNodos() {
    Nodo *n = inicio;
    if (inicio->hijo) {
      do {
        Nodo *del = n;
        n = n->hijo;
        LiberarNodo(del);
        del = NULL;
      } while (n != meta);

      LiberarNodo(n); // eliminar meta
    } else {
      // si el nodo de inicio es la solucion, solo necesitamos eliminar el nodo
      LiberarNodo(inicio);
      LiberarNodo(meta);
    }
  }

  // nodo de inicio
  EstadoUsuario *SolucionInicio() {
    solucionNodoActual = inicio;
    if (inicio) {
      return &inicio->estadoUsuario;
    } else {
      return NULL;
    }
  }

  // nodo siguiente
  EstadoUsuario *SolucionSiguienteNodo() {
    if (solucionNodoActual) {
      if (solucionNodoActual->hijo) {
        Nodo *hijo = solucionNodoActual->hijo;
        solucionNodoActual = solucionNodoActual->hijo;
        return &hijo->estadoUsuario;
      }
    }
    return NULL;
  }

private: // manejo de memoria
  Nodo *AllocateNode() {
#if !USE_FSA_MEMORY
    nodoContar++;
    Nodo *p = new Nodo;
    return p;
#endif
  }

  void LiberarNodo(Nodo *node) { nodoContar--; }

private:
  vector<Nodo *> lista;
  vector<Nodo *> listaCerrada;
  // sucesores es un vector llenado por el usuario cada vez que se generan los
  // nodos
  vector<Nodo *> sucesores;
  int estado;
  int pasos;
  Nodo *inicio;
  Nodo *meta;
  Nodo *solucionNodoActual;
  int nodoContar;
  bool cancelarSolicitud;
};

#endif
