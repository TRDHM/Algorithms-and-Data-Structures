#include<iostream>
#include<cstdlib>
#include<istream>
#include<fstream>
#include<string>
#include<cstdlib>
#include<climits>
#include<sstream>
#include<vector>
#include<algorithm>



using namespace std;
#include"graph.h"
#include"queue.h"
#include"dsexceptions.h"


typedef struct Vertex {
  string name;
  string lV;
  int distance = INT_MAX;
  bool picked = false;
} vertex;




void handleInput(char *  file, vector<vertex> &V, Graph<string> &G);
int vIndex(vector<vertex> V, string vName);
bool isVertex(vector<vertex> Vertexes, string vName);
void printV(vector<vertex> V, int i);
void d(vector<vertex> &V, string starting, Graph<string> G);
int minDistance(vector<vertex> V);
bool checkDone(vector<vertex> V);
void finishUp(vector<vertex> finalV);




int main(int argv, char* argc[1]) {
  vector<vertex> V(50);
  Graph<string> G;

  string vName;
  //file goes into handleInput
  handleInput(argc[1], V, G);
  
 while(true){
    cout << "Please input starting vertex: " << endl;
    cin >> vName;
  
    if(isVertex(V, vName)){
       d(V, vName, G);
      break;
    }


    else{
      cout << "Not a vertex" << endl;
    }  
  } 
  return 0;
}

 
void handleInput(char* file, vector<vertex> &V, Graph<string> &G){
  
  int j = 0;
  int i = 0;/*
  string name;
  string lV;
  string tD;*/
  string line;
  string str;
  const char delim = ';';
  vector<string> split;
  vector<vertex> tempV(50); 
  ifstream inFile;
  inFile.open(file);

  if(!inFile.is_open()){
   cout << "Invalid File" << endl; 
  }

  

  //uses getline to work through the input file
  //for each loop of getline the segments of each line are added to the split vector
  while(getline(inFile, line)){
      
    stringstream ss(line);
    while(getline(ss, str, delim)){

      split.push_back(str);     
      j++;
      
    }
  } 
    j = 0;

  cout << "--------------------------- DIJKSTRA'S ALGORITHM ---------------------------" << endl;
  cout << " A Weighted Graph Has Been Built For These Cities: " << endl;
   //add the split strings and int into Vertexes and V vector
    for(auto it = split.begin(); it != split.end(); it++){

      string lV;
      string tD;
      string name;


      if(i % 3 == 0 ){
        
	name = split[i];
 	tempV[j].name = name;
      }

      if(i % 3 == 1){

        
        lV = split[i];
        tempV[j].lV = lV;
      }
      
      if(i % 3 == 2){
         
        tD = split[i];	  
        tempV[j].distance = stoi(tD);
        j++;
     }
      i++;
    }
   
    V.resize(j);
    //Add vertexes into graph

    for(int x = 0; x < V.size(); x++){
       if(!isVertex(V, tempV[x].name)){
         
          V[x].name = tempV[x].name;
          G.AddVertex(V[x].name);
          V[x].lV = tempV[x].lV;
	  cout << V[x].name << endl;
	 }
    }


     for(int y = 0; y < V.size(); y++){
        G.AddEdge(tempV[y].lV, tempV[y].name, tempV[y].distance);
       }      
}







//returns index of the vertex if found, 51 if not found
int vIndex(vector<vertex> V, string vName){
  bool found = false;
  for(int i = 0; i < V.size(); i++){
    if(V[i].name ==vName){
      found = true;
      return i;
      break;
    }
  }

  if(found = false){
    return 51;
  }

}





//returns true if vertex exists in current list
bool isVertex(vector<vertex> V, string vName){
  bool found = false;

  for(int i = 0; i < V.size(); i++){   
    if(V[i].name == vName){
      found = true;
      break;
    }
  }
  return found;
}






void printV(vector<vertex> V, int i){
  string name = V[i].name;
  int distance = V[i].distance;
  string lV = V[i].lV;
 
  cout << name << "		"  << distance << "		"  << lV << endl;

}




//gets the index of the next min distance between all Vertexes 
int minDistance(vector<vertex> V){
  int minDistance = INT_MAX;  
  int ind = 0;
   

  for(int i = 0; i < V.size(); i++){
    if(V[i].picked == false && V[i].distance < minDistance){
      ind = i;
    }
  }
  return ind;
}



void d(vector<vertex> &V, string starting, Graph<string> G){
  //minV is index of current index
  int minV = vIndex(V, starting);  
  bool done = false;
  Queue<string> Q(50);
  V[minV].distance = 0;
  V[minV].picked = true;
  V[minV].lV = "N/A";
  int min = INT_MAX;


  //cout << "-----------------------------------------------------------------" << endl;
  int i = 0;
  while(i < V.size()){
    G.GetToVertices(V[minV].name , Q);   
    while(!Q.isEmpty()){
      int curr = vIndex(V, Q.getFront());
      
     
      //if current Vertex distance is greater than Weight + minV distance
      if (V[curr].distance > V[minV].distance + G.WeightIs(V[minV].name,V[curr].name)){
         V[curr].distance = V[minV].distance + G.WeightIs(V[minV].name, V[curr].name);
      }
      if(V[curr].lV != "N/A"){ 
      
	V[curr].lV = V[minV].name;
      }

      Q.dequeue();
   }

    i++;
    V[minV].picked = true;
    minV = minDistance(V);
    G.MarkVertex(V[minV].name);
     
  } 
  finishUp(V);
}




void finishUp(vector<vertex> V){
  int min;
  int count[V.size()]; 
  cout <<"-----------------------------------------------------" << endl;  
  cout <<"Vertex		Distance 	  Previous" <<endl;
  
  for(int i = 0; i < V.size(); i++){
    if(V[i].distance != INT_MAX){
      count[vIndex(V, V[i].name)] = count[vIndex(V, V[i].name)] + 1;
      printV(V, i);   
    }
  } 

  for(int j = 0; j < V.size(); j++){
    if(count[j] > 1){
      cout << "A cycle exists for this graph" << endl;
      break;
    }
  }
}




bool checkDone(vector<vertex> V){
  bool r = true;

  for(int i = 0; i < V.size(); i++){
    if(V[i].picked == false){
      r = false;
    }

  }
  return r;
}
