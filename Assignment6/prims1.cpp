#include <iostream>

#define INT_MAX 2000000
#define V 5 
  
int minimumKeyIndex(int key[], bool mstSet[]) { 
    int minimumValue = INT_MAX;
    int minimumIndex; 
  
    for (int v = 0; v < V; v++) 
        if (mstSet[v] == false && key[v] < minimumValue) {
            minimumValue = key[v];
            minimumIndex = v; 
        }
  
    return minimumIndex; 
} 

void display(int parent[], int graph[V][V]) { 
    std::cout<<"EDGE \tWEIGHT\n"; 
    for (int i = 1; i < V; i++) 
        std::cout << parent[i] << "-" << i << " \t" << graph[i][parent[i]] << " \n"; 
} 

void prims(int graph[V][V]) { 
    int parent[V]; 
    int key[V]; 
    bool visited[V]; 

    for (int i = 0; i < V; i++) {
        key[i] = INT_MAX;
        visited[i] = false; 
    }
 
    key[0] = 0; 
    parent[0] = -1; 

    for (int count = 0; count < V - 1; count++){ 
        int minimumIndex = minimumKeyIndex(key, visited); 
        visited[minimumIndex] = true; 
  
        for (int v = 0; v < V; v++){
            if (graph[minimumIndex][v] && visited[v] == false && graph[minimumIndex][v] < key[v]){
                    parent[v] = minimumIndex;
                    key[v] = graph[minimumIndex][v]; 
            }
        }
    } 

    display(parent, graph); 
} 
  

int main(){ 
    int graph[V][V] = { { 0, 2, 0, 6, 0 }, 
                        { 2, 0, 3, 8, 5 }, 
                        { 0, 3, 0, 0, 7 }, 
                        { 6, 8, 0, 0, 9 }, 
                        { 0, 5, 7, 9, 0 } }; 
  
    prims(graph); 
    return 0; 
} 
  