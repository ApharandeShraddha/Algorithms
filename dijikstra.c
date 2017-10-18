#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>	


using namespace std;

int noOfVertices=0;

//Create adjacency matrix vector.
	vector<int> inner (100);
    vector< vector<int> > adjacency(100,inner);

//Calculate number of vertices from given input matrix
int populateNoOfVertices(){
	char *token;
	FILE *fp;
	char line[200];
	

	fp = fopen("matrix_input.txt", "r");
	if(fp == NULL)
	{
		printf("can't open file:%s \n","matrix_input.txt");
		exit(0);
	}

	if(fgets(line, 200, (FILE*)fp) != NULL){
		  token = strtok(line,",");	
		   while(token !=NULL){
			noOfVertices++;
			token = strtok(NULL,",");	
		   }
	}
	
	fclose(fp);

}
    
//Generated adjacency matrix with input file data
void addDataToAdjacencyMatrix(){
	char *token;

	FILE *fp;
	char line[200];

	fp = fopen("matrix_input.txt", "r");
	if(fp == NULL)
	{
		printf("can't open file:%s \n","matrix_input.txt");
		exit(0);
	}

	int i,j=0;
	while(fgets(line, 200, (FILE*)fp) != NULL){
	  j=0;
	  token = strtok(line,",");	
	   while(token !=NULL){
		int weight=atoi(token);
		adjacency[i][j]=weight;
		token = strtok(NULL,",");	
		j++;
	   }
	  i++;
	}
	   fclose(fp);
}

// Find the vertex with minimum distance value, from
// the set of vertices not yet included in shortest path tree
int findMinimumDistance(int distance[], bool shortestPathSet[])
{
   // Initialize min value
   int min = 999, min_index;
 
   for (int v = 0; v < noOfVertices; v++)
     if (distance[v] <= min && shortestPathSet[v] == false)
         min = distance[v], min_index = v;
 
   return min_index;
}

// Dijkstra's algorithm
void dijkstra()
{
	int source=0;
    int distance[noOfVertices];     // The output array. dist[i] will hold the shortest distance (src to i)
 
    bool shortestPathSet[noOfVertices]; // shortestPathSet[i] will be true if vertex i is included in shortest
                     		  				  
    // Initialize all distances as INFINITE=999 and shortestPathSet[] as false
     for (int i = 0; i < noOfVertices; i++)
    {
     	 distance[i] = 999;
         shortestPathSet[i] = false;
	}
       
    // Distance of source vertex from itself is always 0.
     distance[source] = 0;
 
     // Find shortest path for all vertices
     for (int count = 0; count < noOfVertices-1; count++)
     {
       // Pick the minimum distance vertex from the set of vertices not
        int min_index = findMinimumDistance(distance, shortestPathSet);
 
       // Mark the picked vertex as processed
       shortestPathSet[min_index] = true;
 
       // Update dist value of the adjacent vertices of the picked vertex.
       for (int v = 0; v < noOfVertices; v++)
         if (!shortestPathSet[v] && adjacency[min_index][v] && distance[min_index]+adjacency[min_index][v] < distance[v] && distance[min_index] != 999 )
            distance[v] = distance[min_index] + adjacency[min_index][v];
     }
 
     // print the constructed distance array
      printf("\nVertex  Distance_from_Source");
      printf("\n-----------------------------\n");
      for (int i = 0; i < noOfVertices; i++)
      printf("%d \t\t %d\n", i, distance[i]);
}

int main()
{
	//Parse input file to find total number of vertices
   	populateNoOfVertices();
	
    //Generate adjacency matrix from input file
    addDataToAdjacencyMatrix();
   
    printf("\nResult:");
    //call dijkstra's greedy algorithm.
	dijkstra();
	

	return 0;
}
