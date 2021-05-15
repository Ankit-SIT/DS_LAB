#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node *next;
};

struct adjlist{
    struct node *head;

};

struct Graph{
    int vertices;
    struct adjlist *arrayofLists;
    int *visited;
};

struct Graph *Creategraph(int vertices){
    struct Graph *graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->vertices = vertices;
    graph->arrayofLists = (struct adjlist *) calloc(vertices, sizeof (struct adjlist));
    graph->visited = (int *) calloc(vertices,sizeof (int));
    
    int i = 0;
    for(i = 0; i < vertices; i++){
        graph->arrayofLists[i].head = NULL;
        graph->visited[i] = 0;

    }
    return graph;
}

struct node *createNode(int data){
    struct node *newnode=(struct node *) malloc(sizeof (struct node));
    newnode->data = data;
    newnode->next = NULL;
    return newnode;
}

void addEdge(struct Graph *graph,int src,int dest){
      struct node *newnode = createNode(dest);
      newnode->next = graph->arrayofLists[src].head;
      graph->arrayofLists[src].head = newnode;

      newnode = createNode(src);
      newnode->next = graph->arrayofLists[dest].head;
      graph->arrayofLists[dest].head = newnode;
}

void DFS(struct Graph *graph,int vertex) {
    struct node *adjlist = graph->arrayofLists[vertex].head;
    struct node *temp = adjlist;

    graph->visited[vertex]=1;
    printf("visited %d\n" ,vertex);
    while (temp != NULL){
        int connectedVertex = temp->data;
        if (graph->visited[connectedVertex] == 0){
            DFS(graph,connectedVertex);
        }
        temp = temp->next;
    }
};

void display(struct Graph *graph){
    int i;
    for(i = 0;i < graph->vertices; i++){
        struct node *temp = graph->arrayofLists[i].head;
        printf("%d",i);
        while (temp){
            printf("->%d ",temp->data);
            temp=temp->next;
        }
        printf("\n");
    }
}

int main(){
    int vertex;
    int src;
    int dest;
    int choice;

    printf("ENTER VERTICES:\n");
    scanf("%d",&vertex);

    struct Graph *graph = Creategraph(vertex);

    while(1){
        printf("-- MENU --\n");
        printf("1. ADD EDGES\n");
        printf("2. DISPLAY DFS\n");
        printf("3. EXIT\n");
        printf("ENTER CHOICE: ");
        scanf("%d",&choice);

        switch(choice){
            case 1:
                printf("ENTER SOURCE AND DESTINATION: \n");
                scanf("%d%d",&src,&dest);
                addEdge(graph,src,dest);
                break;

            case 2:
                printf("ADJACENCY LIST :\n");
                display(graph);
                DFS(graph,3);
                break;
            
            case 3:
                return 0;
        }   
    }
}