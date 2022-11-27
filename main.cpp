#include "astar.h"

// por que en total existen 20 ciudades en la imagen
const int MAX_CIUDADES = 20;
// las ciudades estan ordenadas alfabeticamente
enum ENUM_CIUDADES {
  // Arad lo ponemos el numero cero para ilustrar que es la primera ciudad
  Arad = 0,
  Bucharest,
  Craiova,
  Drobeta,
  Eforie,
  Fagaras,
  Giurgiu,
  Hirsova,
  Iasi,
  Lugoj,
  Mehadia,
  Neamt,
  Oradea,
  Pitesti,
  Rimnicu_Vilcea,
  Sibiu,
  Timisoara,
  Urziceni,
  Vaslui,
  Zerind
};
// creamos un vector de ciudades de tamano 20
vector<string> NombresCiudades(MAX_CIUDADES);
float MapaRomania[MAX_CIUDADES][MAX_CIUDADES];

class BusquedaRuta {
public:
  ENUM_CIUDADES ciudad;
  // constructor
  BusquedaRuta() { ciudad = Arad; }
  BusquedaRuta(ENUM_CIUDADES in) { ciudad = in; }
  // esta clase posee un numero de 6 metodos
  bool MismoEstado(BusquedaRuta &ejemplo);
  float DistanciaEstimada(BusquedaRuta &nodoMeta);
  bool EsMeta(BusquedaRuta &nodoMeta);
  bool ConseguirSucesores(BusquedaEstrella<BusquedaRuta> *busquedaEstrella,
                          BusquedaRuta *nodoPadre);
  float ConseguirCosto(BusquedaRuta &successor);
  void InformacionNodo();
};

// revisamos si el nodo this es igual a ejemplo
bool BusquedaRuta::MismoEstado(BusquedaRuta &ejemplo) {
  if (ciudad == ejemplo.ciudad)
    return true;
  else
    return false;
}

// contamos la distancia entre la ciudad y bucharest
float BusquedaRuta::DistanciaEstimada(BusquedaRuta &nodoMeta) {
  // la meta siempre es bucharest
  switch (ciudad) {
  case Arad:
    return 366;
    break;
  case Bucharest:
    // 0 por que ya es bucharest
    return 0;
    break;
  case Craiova:
    return 160;
    break;
  case Drobeta:
    return 242;
    break;
  case Eforie:
    return 161;
    break;
  case Fagaras:
    return 176;
    break;
  case Giurgiu:
    return 77;
    break;
  case Hirsova:
    return 151;
    break;
  case Iasi:
    return 226;
    break;
  case Lugoj:
    return 244;
    break;
  case Mehadia:
    return 241;
    break;
  case Neamt:
    return 234;
    break;
  case Oradea:
    return 380;
    break;
  case Pitesti:
    return 100;
    break;
  case Rimnicu_Vilcea:
    return 193;
    break;
  case Sibiu:
    return 253;
    break;
  case Timisoara:
    return 329;
    break;
  case Urziceni:
    return 80;
    break;
  case Vaslui:
    return 199;
    break;
  case Zerind:
    return 374;
    break;
  }
  return 0;
}

// revisar si es el nodo meta
bool BusquedaRuta::EsMeta(BusquedaRuta &nodoMeta) {
  if (ciudad == Bucharest)
    return true;
  else
    return false;
}

// genera el sucesor del nodo actual
bool BusquedaRuta::ConseguirSucesores(
    BusquedaEstrella<BusquedaRuta> *busquedaEstrella, BusquedaRuta *nodoPadre) {
  BusquedaRuta NewNode;
  for (int c = 0; c < MAX_CIUDADES; c++) {
    if (MapaRomania[ciudad][c] < 0)
      continue;
    NewNode = BusquedaRuta((ENUM_CIUDADES)c);
    busquedaEstrella->AddSuccessor(NewNode);
  }
  return true;
}

// el costo de ir del nodo actual al nodo sucesor
float BusquedaRuta::ConseguirCosto(BusquedaRuta &successor) {
  return MapaRomania[ciudad][successor.ciudad];
}

// imprime informacion acerca del nodo actual
void BusquedaRuta::InformacionNodo() {
  cout << " " << NombresCiudades[ciudad] << endl;
}

int main() {
  // crear un mapa de romania
  for (int i = 0; i < MAX_CIUDADES; i++) {
    for (int j = 0; j < MAX_CIUDADES; j++) {
      MapaRomania[i][j] = -1.0;
    }
  }
  // establecemos las distancias de una ciudad a otra
  MapaRomania[Arad][Sibiu] = 140;
  MapaRomania[Arad][Zerind] = 75;
  MapaRomania[Arad][Timisoara] = 118;
  MapaRomania[Bucharest][Giurgiu] = 90;
  MapaRomania[Bucharest][Urziceni] = 85;
  MapaRomania[Bucharest][Fagaras] = 211;
  MapaRomania[Bucharest][Pitesti] = 101;
  MapaRomania[Craiova][Drobeta] = 120;
  MapaRomania[Craiova][Rimnicu_Vilcea] = 146;
  MapaRomania[Craiova][Pitesti] = 138;
  MapaRomania[Drobeta][Craiova] = 120;
  MapaRomania[Drobeta][Mehadia] = 75;
  MapaRomania[Eforie][Hirsova] = 75;
  MapaRomania[Fagaras][Bucharest] = 211;
  MapaRomania[Fagaras][Sibiu] = 99;
  MapaRomania[Giurgiu][Bucharest] = 90;
  MapaRomania[Hirsova][Eforie] = 86;
  MapaRomania[Hirsova][Urziceni] = 98;
  MapaRomania[Iasi][Vaslui] = 92;
  MapaRomania[Iasi][Neamt] = 87;
  MapaRomania[Lugoj][Timisoara] = 111;
  MapaRomania[Lugoj][Mehadia] = 70;
  MapaRomania[Mehadia][Lugoj] = 70;
  MapaRomania[Mehadia][Drobeta] = 75;
  MapaRomania[Neamt][Iasi] = 87;
  MapaRomania[Oradea][Zerind] = 71;
  MapaRomania[Oradea][Sibiu] = 151;
  MapaRomania[Pitesti][Bucharest] = 101;
  MapaRomania[Pitesti][Rimnicu_Vilcea] = 97;
  MapaRomania[Pitesti][Craiova] = 138;
  MapaRomania[Rimnicu_Vilcea][Pitesti] = 97;
  MapaRomania[Rimnicu_Vilcea][Craiova] = 146;
  MapaRomania[Rimnicu_Vilcea][Sibiu] = 80;
  MapaRomania[Sibiu][Rimnicu_Vilcea] = 80;
  MapaRomania[Sibiu][Fagaras] = 99;
  MapaRomania[Sibiu][Oradea] = 151;
  MapaRomania[Sibiu][Arad] = 140;
  MapaRomania[Timisoara][Arad] = 118;
  MapaRomania[Timisoara][Lugoj] = 111;
  MapaRomania[Urziceni][Bucharest] = 85;
  MapaRomania[Urziceni][Hirsova] = 98;
  MapaRomania[Urziceni][Vaslui] = 142;
  MapaRomania[Vaslui][Urziceni] = 142;
  MapaRomania[Vaslui][Iasi] = 92;
  MapaRomania[Zerind][Arad] = 75;
  MapaRomania[Zerind][Oradea] = 71;

  // asignamos los nombres de cada caso de las ciudades
  // utilizamos el vector anteriormente creado NombresCiudades
  // ordenamos a las ciudades alfabeticamente
  NombresCiudades[Arad].assign("Arad");
  NombresCiudades[Bucharest].assign("Bucharest");
  NombresCiudades[Craiova].assign("Craiova");
  NombresCiudades[Drobeta].assign("Drobeta");
  NombresCiudades[Eforie].assign("Eforie");
  NombresCiudades[Fagaras].assign("Fagaras");
  NombresCiudades[Giurgiu].assign("Giurgiu");
  NombresCiudades[Hirsova].assign("Hirsova");
  NombresCiudades[Iasi].assign("Iasi");
  NombresCiudades[Lugoj].assign("Lugoj");
  NombresCiudades[Mehadia].assign("Mehadia");
  NombresCiudades[Neamt].assign("Neamt");
  NombresCiudades[Oradea].assign("Oradea");
  NombresCiudades[Pitesti].assign("Pitesti");
  NombresCiudades[Rimnicu_Vilcea].assign("Rimnicu_Vilcea");
  NombresCiudades[Sibiu].assign("Sibiu");
  NombresCiudades[Timisoara].assign("Timisoara");
  NombresCiudades[Urziceni].assign("Urziceni");
  NombresCiudades[Vaslui].assign("Vaslui");
  NombresCiudades[Zerind].assign("Zerind");

  cout << "Bienvenido al programa de busqueda de camino a Bucarest" << endl;
  cout << "Estas son las ciudades disponibles" << endl;
  for (int i = 0; i < MAX_CIUDADES; i++) {
    cout << " " << NombresCiudades[i] << endl;
  }

  // aqui es donde nosotros cambiamos desde cual es la ciudad de origen
  ENUM_CIUDADES initCity = Arad; // este es el nucleo del funcionamiento de
  // nuestro programa muy importante

  cout << "En este caso la ciudad de origen es " << NombresCiudades[initCity]
       << endl;

  // Instancia de la clase A*
  BusquedaEstrella<BusquedaRuta> busquedaEstrella;

  int SearchCount = 0;
  int NumSearches = 1;

  while (SearchCount < NumSearches) {
    // creamos un estado inicial
    BusquedaRuta nodeStart;
    nodeStart.ciudad = initCity;

    // muy importante ***
    // el estado final siempre es Bucharest
    // 不要动这里
    BusquedaRuta nodeEnd;
    nodeEnd.ciudad = Bucharest;

    // aqui establecemos el estado inicial y el final
    busquedaEstrella.SetStartAndGoalStates(nodeStart, nodeEnd);

    int SearchState;
    int SearchSteps = 0;

    do {
      SearchState = busquedaEstrella.SearchStep();
      SearchSteps++;
    } while (SearchState == BusquedaEstrella<BusquedaRuta>::ESTADO_BUSQUEDA);

    if (SearchState == BusquedaEstrella<BusquedaRuta>::ESTADO_BUSQUEDA_EXITO) {
      cout << "Hemos encontrado una ruta\n";
      BusquedaRuta *node = busquedaEstrella.SolucionInicio();
      cout << "Mostrando la solucion\n";
      node->InformacionNodo();
      for (;;) {
        node = busquedaEstrella.SolucionSiguienteNodo();
        if (!node)
          break;
        node->InformacionNodo();
      };
      // ya encontrada la solucion podemos liberar los nodos
      busquedaEstrella.LiberarNodos();
    }
    // mostramos el numero de pasos que ha dado la busqueda
    cout << "Pasos a la solucion: " << SearchSteps - 1 << "\n";
    SearchCount++;
    busquedaEstrella.EnsureMemoryFreed();
  }

  return 0;
}
