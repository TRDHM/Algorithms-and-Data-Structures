#include "graph.h"
#include <string>
#include <climits>
#include <iostream>

int main(){
  Graph<string> g;

  g.AddVertex("Washington");
  g.AddVertex("Atlanta");
  g.AddEdge("Washington", "Atlanta", 600);
  cout << "done ";
  return 0;


}
