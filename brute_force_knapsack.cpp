#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <cmath>
#include <string.h>

using namespace std;

struct knapsackItems{
	int itemNumber;	
	int weight;	
	int profit;	
};

vector<knapsackItems> item(1000);
int elements_In_Knapsack=0;
int capacity = 0;

void readFile()
	{
	 int m=0;
	 FILE *fp;
	 char line[1000];
	 char wt[1000];
	 char pt[1000];
	 char *weight;
     char *profit;
     int i=1;
     int j=1;
     

	 fp = fopen("knapsack.txt", "r");

	 if(fp == NULL)
	 {
		printf("can't open file:%s \n","knapsack.txt");
		exit(0);
	 }

	 //Read total number of elements
	if(fgets(line, 200, (FILE*)fp) != NULL)
		{
			elements_In_Knapsack=atoi(line);
		}

		//Read weights
		if(fgets(line, 200, (FILE*)fp) != NULL)
		{
			strcpy(wt,line);
		}
		
		//Read Profits
		if(fgets(line, 200, (FILE*)fp) != NULL)
		{
			strcpy(pt,line);
		}

	//Add weight of item to struct
   		weight = strtok(wt,",");       
        while(weight !=NULL) 
   		{
   			if(j<=elements_In_Knapsack){
   				item[j].itemNumber=j;
   				item[j].weight=atoi(weight);
   				j++;
    			weight = strtok(NULL,",");		
   			}
     			 
    	}

    //Add profit of item to struct
    	profit = strtok(pt,",");
    	while(profit != NULL){
    		if(i<=elements_In_Knapsack){
   				item[i].profit=atoi(profit);
   				i++;
    			profit = strtok(NULL,",");		
   			}
    	}
	
	//Read Knapsack capacity
	if(fgets(line, 200, (FILE*)fp) != NULL)
	{
		capacity=atoi(line);
	}

	 fclose(fp);
}

//0-1 knapsack problem using bruteforce
void bruteForce(vector<knapsackItems> &items,int capacity, int elements_In_Knapsack){
	//Vector to store all options available using brute force
	vector<int> inner (capacity+1);
    vector< vector<int> > options(elements_In_Knapsack+1, inner);
    
    //Vector to store if given option can be a solution.
    vector<bool> inner2 (capacity+1);
    vector< vector<bool> > solution(elements_In_Knapsack+1, inner2);
    
    int totalWeight = 0, totalProfit = 0;

    for(int i=1; i<=elements_In_Knapsack; i++){
    	for(int j=1; j<=capacity; j++){
    		//Item i not included.
			int option1 = options[i-1][j];
    		
    		// item i is included.
            int option2 = 0;
            if (items[i].weight <= j){
            	option2 = items[i].profit + options[i-1][j-items[i].weight];	
            }

            // select better of two options.
            options[i][j] = max(option1, option2);
            
            //Store flag stating if option2 is selected or not.
            solution[i][j] = (option2 > option1);
    	}
    }
    
    //check if an item is selected or not and store the selected item.
    vector<int> selected(elements_In_Knapsack+1);
    for (int i = elements_In_Knapsack, j = capacity; i >= 0; i--) {
            if (solution[i][j]) {
				selected[i] = 1;  
				j = j - items[i].weight; 
			}else{ 
				selected[i] = 0;
			}
    }  

	// Calculate total profit and total weight of seletced items and print the results.
     printf("\nbrute force:Selected Items");
     for (int n = 1; n <= elements_In_Knapsack ;n++) {
     	if(selected[n] == 1){
     		totalWeight = totalWeight + items[n].weight;
     		totalProfit = totalProfit + items[n].profit;
     		printf("\nItem number = %2d  profit = %2d  weight = %2d",items[n].itemNumber, items[n].profit, items[n].weight);
     	}
     }
     printf("\n");
     printf("\nTotal weight: %d", totalWeight);
     printf("\nTotal profit: %d\n", totalProfit);

}

int main()
{
	readFile();
	//call to bruteForce function
	bruteForce(item,capacity,elements_In_Knapsack);
	return 0;
}