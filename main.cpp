#include "astar.h"
#include <iostream>
using namespace std;

// por que en total existen 20 ciudades en la imagen
const int MAX_CITIES = 20;
// las ciudades estan ordenadas alfabeticamente
enum ENUM_CITIES {
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
vector<string> CityNames(MAX_CITIES);
float RomaniaMap[MAX_CITIES][MAX_CITIES];

class PathSearchNode {
public:
  ENUM_CITIES city;
  // constructor
  PathSearchNode() { city = Arad; }
  PathSearchNode(ENUM_CITIES in) { city = in; }
  // esta clase posee un numero de 6 metodos
  bool IsSameState(PathSearchNode &rhs);
  float GoalDistanceEstimate(PathSearchNode &nodeGoal);
  bool IsGoal(PathSearchNode &nodeGoal);
  bool GetSuccessors(AStarSearch<PathSearchNode> *astarsearch,
                     PathSearchNode *parent_node);
  float GetCost(PathSearchNode &successor);
  void PrintNodeInfo();
};

// revisamos si el nodo this es igual a rhs
bool PathSearchNode::IsSameState(PathSearchNode &rhs) {
  if (city == rhs.city)
    return true;
  else
    return false;
}

// contamos la distancia entre la ciudad y bucharest
float PathSearchNode::GoalDistanceEstimate(PathSearchNode &nodeGoal) {
  // la meta siempre es bucharest
  switch (city) {
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
bool PathSearchNode::IsGoal(PathSearchNode &nodeGoal) {
  if (city == Bucharest)
    return true;
  else
    return false;
}

// genera el sucesor del nodo actual
bool PathSearchNode::GetSuccessors(AStarSearch<PathSearchNode> *astarsearch,
                                   PathSearchNode *parent_node) {
  PathSearchNode NewNode;
  for (int c = 0; c < MAX_CITIES; c++) {
    if (RomaniaMap[city][c] < 0)
      continue;
    NewNode = PathSearchNode((ENUM_CITIES)c);
    astarsearch->AddSuccessor(NewNode);
  }
  return true;
}

// el costo de ir del nodo actual al nodo sucesor
float PathSearchNode::GetCost(PathSearchNode &successor) {
  return RomaniaMap[city][successor.city];
}

// imprime informacion acerca del nodo actual
void PathSearchNode::PrintNodeInfo() { cout << " " << CityNames[city] << endl; }

int main() {
  // crear un mapa de romania
  for (int i = 0; i < MAX_CITIES; i++) {
    for (int j = 0; j < MAX_CITIES; j++) {
      RomaniaMap[i][j] = -1.0;
    }
  }
  // establecemos las distancias de una ciudad a otra
  RomaniaMap[Arad][Sibiu] = 140;
  RomaniaMap[Arad][Zerind] = 75;
  RomaniaMap[Arad][Timisoara] = 118;
  RomaniaMap[Bucharest][Giurgiu] = 90;
  RomaniaMap[Bucharest][Urziceni] = 85;
  RomaniaMap[Bucharest][Fagaras] = 211;
  RomaniaMap[Bucharest][Pitesti] = 101;
  RomaniaMap[Craiova][Drobeta] = 120;
  RomaniaMap[Craiova][Rimnicu_Vilcea] = 146;
  RomaniaMap[Craiova][Pitesti] = 138;
  RomaniaMap[Drobeta][Craiova] = 120;
  RomaniaMap[Drobeta][Mehadia] = 75;
  RomaniaMap[Eforie][Hirsova] = 75;
  RomaniaMap[Fagaras][Bucharest] = 211;
  RomaniaMap[Fagaras][Sibiu] = 99;
  RomaniaMap[Giurgiu][Bucharest] = 90;
  RomaniaMap[Hirsova][Eforie] = 86;
  RomaniaMap[Hirsova][Urziceni] = 98;
  RomaniaMap[Iasi][Vaslui] = 92;
  RomaniaMap[Iasi][Neamt] = 87;
  RomaniaMap[Lugoj][Timisoara] = 111;
  RomaniaMap[Lugoj][Mehadia] = 70;
  RomaniaMap[Mehadia][Lugoj] = 70;
  RomaniaMap[Mehadia][Drobeta] = 75;
  RomaniaMap[Neamt][Iasi] = 87;
  RomaniaMap[Oradea][Zerind] = 71;
  RomaniaMap[Oradea][Sibiu] = 151;
  RomaniaMap[Pitesti][Bucharest] = 101;
  RomaniaMap[Pitesti][Rimnicu_Vilcea] = 97;
  RomaniaMap[Pitesti][Craiova] = 138;
  RomaniaMap[Rimnicu_Vilcea][Pitesti] = 97;
  RomaniaMap[Rimnicu_Vilcea][Craiova] = 146;
  RomaniaMap[Rimnicu_Vilcea][Sibiu] = 80;
  RomaniaMap[Sibiu][Rimnicu_Vilcea] = 80;
  RomaniaMap[Sibiu][Fagaras] = 99;
  RomaniaMap[Sibiu][Oradea] = 151;
  RomaniaMap[Sibiu][Arad] = 140;
  RomaniaMap[Timisoara][Arad] = 118;
  RomaniaMap[Timisoara][Lugoj] = 111;
  RomaniaMap[Urziceni][Bucharest] = 85;
  RomaniaMap[Urziceni][Hirsova] = 98;
  RomaniaMap[Urziceni][Vaslui] = 142;
  RomaniaMap[Vaslui][Urziceni] = 142;
  RomaniaMap[Vaslui][Iasi] = 92;
  RomaniaMap[Zerind][Arad] = 75;
  RomaniaMap[Zerind][Oradea] = 71;

  // asignamos los nombres de cada caso de las ciudades
  // utilizamos el vector anteriormente creado CityNames
  // ordenamos a las ciudades alfabeticamente
  CityNames[Arad].assign("Arad");
  CityNames[Bucharest].assign("Bucharest");
  CityNames[Craiova].assign("Craiova");
  CityNames[Drobeta].assign("Drobeta");
  CityNames[Eforie].assign("Eforie");
  CityNames[Fagaras].assign("Fagaras");
  CityNames[Giurgiu].assign("Giurgiu");
  CityNames[Hirsova].assign("Hirsova");
  CityNames[Iasi].assign("Iasi");
  CityNames[Lugoj].assign("Lugoj");
  CityNames[Mehadia].assign("Mehadia");
  CityNames[Neamt].assign("Neamt");
  CityNames[Oradea].assign("Oradea");
  CityNames[Pitesti].assign("Pitesti");
  CityNames[Rimnicu_Vilcea].assign("Rimnicu_Vilcea");
  CityNames[Sibiu].assign("Sibiu");
  CityNames[Timisoara].assign("Timisoara");
  CityNames[Urziceni].assign("Urziceni");
  CityNames[Vaslui].assign("Vaslui");
  CityNames[Zerind].assign("Zerind");

	// aqui es donde nosotros cambiamos desde cual es la ciudad de origen
  ENUM_CITIES initCity = Neamt; // este es el nucleo del funcionamiento de nuestro programa
	// muy importante

  // An instance of A* search class
  AStarSearch<PathSearchNode> astarsearch;

  int SearchCount = 0;
  int NumSearches = 1;

  while (SearchCount < NumSearches) {
    // Create a start state
    PathSearchNode nodeStart;
    nodeStart.city = initCity;

    // Define the goal state, always Bucharest!
    PathSearchNode nodeEnd;
    nodeEnd.city = Bucharest;

    // Set Start and goal states
    astarsearch.SetStartAndGoalStates(nodeStart, nodeEnd);

    int SearchState;
    int SearchSteps = 0;

    do {
      SearchState = astarsearch.SearchStep();
      SearchSteps++;

#if DEBUG_LISTS

      cout << "Steps:" << SearchSteps << "\n";

      int len = 0;

      cout << "Open:\n";
      PathSearchNode *p = astarsearch.GetOpenListStart();
      while (p) {
        len++;
#endif
      }
      while (SearchState == AStarSearch<PathSearchNode>::SEARCH_STATE_SEARCHING)
        ;

      if (SearchState == AStarSearch<PathSearchNode>::SEARCH_STATE_SUCCEEDED) {
        cout << "Search found the goal state\n";
        PathSearchNode *node = astarsearch.GetSolutionStart();
        cout << "Displaying solution\n";
        int steps = 0;
        node->PrintNodeInfo();
        for (;;) {
          node = astarsearch.GetSolutionNext();
          if (!node)
            break;
          node->PrintNodeInfo();
          steps++;
        };
        cout << "Solution steps " << steps << endl;
        // Once you're done with the solution you can free the nodes up
        astarsearch.FreeSolutionNodes();
      } else if (SearchState ==
                 AStarSearch<PathSearchNode>::SEARCH_STATE_FAILED) {
        cout << "Search terminated. Did not find goal state\n";
      }
      // Display the number of loops the search went through
      cout << "SearchSteps : " << SearchSteps << "\n";
      SearchCount++;
      astarsearch.EnsureMemoryFreed();
    }

    return 0;
  }