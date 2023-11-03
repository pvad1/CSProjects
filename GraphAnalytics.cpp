#include "graph.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include "infinity.h"
#include <string>
#include <unordered_map>
#include <queue>
using namespace std;

bool IsValidVertex(string vertex);

typedef pair<int, char> holdpair;

struct Vertex {
    int distance;
    bool visited;
    int numUpdates;
};

const int MAX_VERTICES = 100;
int distances[MAX_VERTICES];
vector<vector<int> > adjMatrix(0, vector<int>(0));
unordered_map<char, Vertex> vertices;
const string str_vertex = "[Vertices]";
const string str_edge = "[Edges]";
bool isValidVertexinGraph = false;
bool isValidEdgeGraph = false;
void printVertix();
string trimspaces(string str);
char starVertex ;

// Constructor/Destructor for Graph.
Graph::Graph(){
    adjMatrix = vector<vector<int> >();
    for (int i = 0; i < MAX_VERTICES; i++) {
        distances[i] = GetINFINITY();

    }
}
Graph::~Graph() {
    vertices.clear();
    adjMatrix.clear();
}



// Loads the graph.
void Graph::LoadGraph(const char *graphFileName) {
   
    vertices.clear();
    adjMatrix.clear();

    fstream inputFile;
    inputFile.open(graphFileName);
    string line;
    if ( ! inputFile.is_open() ) {
      //  cout << "Couldn't open file\n";
        return;
    }
    // check if file is empty 
    if(inputFile.peek() == std::ifstream::traits_type::eof()) {
        return;
    }
    
    // Read vertices section
    getline(inputFile, line); // Read [Vertices] header
    line = trimspaces(line);
    while (line.length() == 0 ||  line == "\r" ) {
            getline(inputFile, line);
    }
    // validate its a [Vertex]
    if(line != str_vertex ) { 
        // cerr << "Error: Invalid vertex syntax: " << line << endl;
        isValidVertexinGraph = false;
        vertices.clear();
        adjMatrix.clear();
        return;
     }
    
    while (getline(inputFile, line) && ( line != str_edge) ) {
         line = trimspaces(line);
        //ignore any spaces 
        if (line.length() == 0 ||  line == "\r"  || line.empty()) {
           continue;
        }
        
        // Validate vertex name
        if (! IsValidVertex(line)) {
        // cerr << "Error: Invalid vertex name: " << line << endl;
            isValidVertexinGraph = false;
            vertices.clear();
            adjMatrix.clear();
            return;
        }
        // Add vertex to graph
        AddVertex(line[0]);
    } // end while 
   // cout << "Reading Edges now " << endl;
   //ignore spaces 
    while (line.length() == 0 ||  line == "\r" ) {
            getline(inputFile, line);
    }
    // validate its a [Edge]
    if(line != str_edge ) {
        // cerr << "Error: Invalid edge syntax " << line << endl;
        isValidEdgeGraph = false;
         vertices.clear();
         adjMatrix.clear();
        return;
    }

    // Read edges section
     while (getline(inputFile, line)) {
    
        //ignore any spaces 
        if (line.length() == 0 ||  line == "\r" ) {
           continue;
        }
        // go thru source vertex, destination vertex, and weight
        istringstream iss(line);
        char src, dest;
        int weight;
        if(!(iss >> src >> dest >> weight)){
           // cout << "Error: Invalid edge: " << line << endl;
           isValidEdgeGraph = false;
            vertices.clear();
            adjMatrix.clear();
            return;
        }
       
        // Ignore self-loops and edges with negative weights
        //if (src == dest || weight < 0){
          if ( weight < 0){  
            isValidEdgeGraph = false;
            vertices.clear();
            adjMatrix.clear();
            return;
        }
        // Validate vertices and add edge to graph
        if ((vertices.find(src) == vertices.end()) ||  (vertices.find(dest) == vertices.end())) {
            //cout << "Error: Invalid vertex in edge: " << line << endl;
             isValidEdgeGraph = false;
             vertices.clear();
             adjMatrix.clear();
            return;
        }
        AddEdge(src, dest, weight);
    }
    if(!isValidEdgeGraph || !isValidVertexinGraph) {
       // vertices.clear();
        adjMatrix.clear();
    }

    //printMatrix();
   // printVertix();

}



// Runs Dijkstra's algorithm, using the specified vertex as the starting vertex.
void Graph::RunDijkstra(char startVertex) {

    if (vertices.find(startVertex) == vertices.end())  {
        return;
    }
     for(const auto& key_value: vertices) {
      
        char key = key_value.first;
        Vertex value = key_value.second;
        value.distance = GetINFINITY();
     }

    // Set distance of starting vertex to 0
    vertices[startVertex].distance = 0;

    // Initialize priority queue with starting vertex
    priority_queue<holdpair, vector<holdpair>, greater<holdpair > > pq;
    pq.push(make_pair( vertices[startVertex].distance, startVertex));
   // pq.push({0, startVertex});

    // Run Dijkstra's algorithm
    int updates = 0;
    while (!pq.empty()) {
        // Get vertex with smallest distance
        int smallDistance = pq.top().first;
        char curr = pq.top().second;
        pq.pop();

       // cout << "curr char = " << curr << " distance = " << smallDistance <<endl;

        // Skip if already visited
        if (vertices[curr].visited) {
            continue;
        }
        vertices[curr].visited = true;

         int vertexis =  int(curr); //  a index is 32 ), b index 33 , c index 34
        // Update distances of adjacent vertices
        for (int i = 0; i < adjMatrix.size(); i++) {
            char neighbor = i ;
            if (adjMatrix[vertexis][neighbor] != GetINFINITY()) {  // ??? check if the value is set here cannot assume zero 
                int dist = vertices[curr].distance + adjMatrix[vertexis][i];  //  
                if( ! vertices[neighbor].visited) {  // neighbood not visisted 
                    int neighborDistance = vertices[neighbor].distance;
                    // cout << "vertices[neighbor].distance = " << neighborDistance <<endl;
                    if (dist <neighborDistance || neighborDistance == GetINFINITY()) {
                        vertices[neighbor].distance = dist;
                        vertices[neighbor].numUpdates = vertices[neighbor].numUpdates + 1  ;
                        pq.push(make_pair(dist, neighbor));
                    }
                }
                
            }
        }
    }
//cout << "from algo" <<endl;
//printVertix();
}



// Returns the distance of the vertex with the specified name from the starting vertex.
int Graph::GetDistance(char vertexName){
    if ((vertices.find(vertexName) == vertices.end())) {
        return -1;
    }
    return vertices.at(vertexName).distance;
}

// Returns the number of updates made to the vertex's distance during the last call of RunDijkstra.
int Graph::GetNumberOfUpdates(char vertex) {
    if (vertices.find(vertex) == vertices.end()) {
        return -1 ;
    }
    if(vertices.at(vertex).distance == GetINFINITY()) {
        return 0;
    } 
    return vertices.at(vertex).numUpdates;
}

void Graph::AddVertex(char name) {
   //  int n = name - 'A' + 1; // 33 (0 - 31) ( a index is 32 ), b index 33 , c index 34
     int asciiNameInt = int(name) +  1 ; // a= 97 , b : 98 , c : 99  (0 - 97) , our index will be from 1 onwards
    /* cout<< "name = " << name << " asciiNameInt = " <<asciiNameInt -1  << endl;
     cout << "current size of matrix " << adjMatrix.size() << endl;
     cout << "anticipated size of matrix " << asciiNameInt << endl; */
    // Check if vertex already exists
    if (adjMatrix.size() == 0 ) {
        adjMatrix.resize(asciiNameInt,vector<int>(asciiNameInt, GetINFINITY()));
    } else if (asciiNameInt > adjMatrix.size()) {
         adjMatrix.resize(asciiNameInt);
        for (int i = 0; i < asciiNameInt; i++) {
            adjMatrix[i].resize(asciiNameInt, GetINFINITY());
        }
    }
   // cout << "final size of matrix " << adjMatrix.size() << endl;
   // unordered_map<char, Vertex> vertices;
   Vertex newVertex;
   newVertex.distance = GetINFINITY();
   newVertex.numUpdates =0;
   newVertex.visited = false;

   vertices.insert(make_pair(name,newVertex));
   isValidVertexinGraph = true;

}

void Graph::AddEdge(char src, char dest, int weight) {
    // a= 97 , b : 98 , c : 99  (0 - 97)
    int srcIndex = int(src);
    int destIndex = int(dest);
    if (src == dest ){
         adjMatrix[srcIndex][destIndex] = 0;
    }
   else {
        adjMatrix[srcIndex][destIndex] = weight;
   } 
    isValidEdgeGraph = true;
}

bool IsValidVertex(string vertex) {
    if( vertex.size() > 1  && (vertex.at(1) == '\r')) {
        vertex.erase(vertex.size() - 1);
    }
    if(vertex.size () == 1 ) {
        return (isalnum(vertex.at(0)) || isalpha(vertex.at(0)));
    }
    return false;
}

//vector<vector<int> > adjMatrix(0, vector<int>(0));
void Graph::printMatrix() {
     cout << "********Print Matrix " << endl;
    for (int i=0; i < adjMatrix.size(); i++){
       cout << " " << i << " ";
    }
    cout << endl;
    for(int i=0; i < adjMatrix.size(); i++){
       cout << " " << i << " ";
        for (int j = 0; j < adjMatrix[i].size(); j++) {
            cout << " " << adjMatrix[i][j] << " ";
        }
        cout << endl;
    }
     cout << "******************* " << endl;
}

void printVertix() {
    for (auto const &pair: vertices) {
        cout << "{ Index : " << pair.first << ", Distance : " << pair.second.distance <<  ", numUpdates : " << pair.second.numUpdates <<  ", visited : " << pair.second.visited << "}\n";
    }
}
string trimspaces(string str) {
    const char* typeOfWhitespaces = " \t\n\r\f\v";
    str.erase(str.find_last_not_of(typeOfWhitespaces) + 1);
        str.erase(0,str.find_first_not_of(typeOfWhitespaces));
return str;
}