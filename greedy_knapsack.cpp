#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <cmath>
#include <string.h>

using namespace std;

//Knapsack Struct
struct knapsackItems{
	int itemNumber;	
	int weight;	
	int profit;	
	double benefit_Per_UnitItem;
};

int elements_In_Knapsack=0;
int capacity = 0;


//Read files and save given data in to kanpsack Struct
vector<knapsackItems> readFile()
{
	 vector<knapsackItems> item(1000);
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

    //Calculate the benefit by weight ratio for each item.
    for(m=1;m<=elements_In_Knapsack;m++){
		item[m].benefit_Per_UnitItem = (item[m].profit/(double)item[m].weight);
    }
	
	//Read Knapsack capacity
	if(fgets(line, 200, (FILE*)fp) != NULL)
	{
		capacity=atoi(line);
	}

	 fclose(fp);

	 return item;
}

//If the criteria is minimum weight, then sort in ascending order.	
vector<knapsackItems> sortAscending(vector<knapsackItems> items,int elements_In_Knapsack){
int index=0;
knapsackItems temp;

for (int i = 1; i <= elements_In_Knapsack; i++) {
			index = i;
			for (int j = i + 1; j <= elements_In_Knapsack; j++) {
				//If the sort is on weight, then find min weight and store the index.	
					if (items[j].weight< items[index].weight)
						index = j;					
			}
			//Put the min element in the sorted sublist of input vector.
			temp=items[index];
			items[index]=items[i];
			items[i]=temp;
		}

	 return items;
}
//If the criteria is maximum benefit or maximum weight, then sort in descending order.
vector<knapsackItems> sortDescending(vector<knapsackItems> items, bool isWeight, int elements_In_Knapsack){
	int index = 0;
	knapsackItems temp;
	
	 	for (int i = 1; i <= elements_In_Knapsack; i++) {
			index = i;
			for (int j = i + 1; j <= elements_In_Knapsack; j++) {
			
				//If the sort is not on weight, then it is on profit, so find max profit and store the index.
				if(!isWeight){
					if (items[j].profit > items[index].profit)
						index = j;
				}else{
				//If the sort is on weight, then find max weight and store the index.	
					if (items[j].weight > items[index].weight)
						index = j;				
				}
			}
			//Put the max element at the end of sorted sublist of input vector.
			temp=items[index];
			items[index]=items[i];
			items[i]=temp;
			
		}
	 
	 return items;
}

//Sort the items benefit per unit item
vector<knapsackItems> sortProfitPerUnit(vector<knapsackItems> items, int elements_In_Knapsack){
	int index = 0;
	knapsackItems temp;
	
	for (int i = 1; i <= elements_In_Knapsack; i++) {
		index = i;
		for (int j = i + 1; j <= elements_In_Knapsack; j++) {
			//find index of item with maximum benefit by weight ratio.
			if (items[j].benefit_Per_UnitItem > items[index].benefit_Per_UnitItem)
				index = j;
		}
		//Put the max element at the end of sorted sublist of input vector.
			temp=items[index];
			items[index]=items[i];
			items[i]=temp;
			
	}
	return items;
}

//greedy1(Maximum profit first)
void greedy1(vector<knapsackItems> &items, int capacity, int elements_In_Knapsack){
	int totalWeight = 0, totalProfit = 0;
	
	//Sort items based on profit in descending order.
	vector<knapsackItems> sortedItems = sortDescending(items,false, elements_In_Knapsack);
	
   
	//Compute total weight and profit and print the results.
	printf("greedy1: Selected Items");
     for (int n = 1; n <= elements_In_Knapsack; n++) {
    	if(capacity > 0 && capacity >= sortedItems[n].weight){
     		totalWeight = totalWeight + sortedItems[n].weight;
     		totalProfit = totalProfit + sortedItems[n].profit;
     		printf("\nItem number = %d  profit = %d  weight = %d", sortedItems[n].itemNumber, sortedItems[n].profit, sortedItems[n].weight);
     		capacity = capacity - sortedItems[n].weight;
     	}
     }
     
  
     printf("\nTotal weight: %d", totalWeight);
     printf("\nTotal profit: %d\n", totalProfit);
}

//greedy2(Minimum weight first)
void greedy2(vector<knapsackItems> &items, int capacity, int elements_In_Knapsack){
	int totalWeight = 0, totalProfit = 0;
	
	//Sort the items based on weight.
	vector<knapsackItems> sortedItems = sortAscending(items,elements_In_Knapsack);

	//Compute total weight and profit and print the results.
	printf("\ngreedy2: Selected Items");
    for (int n = 1; n <= elements_In_Knapsack; n++) {
    	if(capacity > 0 && capacity >= sortedItems[n].weight){
     		totalWeight = totalWeight + sortedItems[n].weight;
     		totalProfit = totalProfit + sortedItems[n].profit;
     		printf("\nItem number = %d  profit = %d  weight = %d", sortedItems[n].itemNumber, sortedItems[n].profit, sortedItems[n].weight);
     		capacity = capacity - sortedItems[n].weight;
     	}
    }
  
     printf("\nTotal weight: %d", totalWeight);
     printf("\nTotal profit: %d\n", totalProfit);
}

//greedy3(Maximum weight first)
void greedy3(vector<knapsackItems> &items, int capacity,int elements_In_Knapsack){
	int totalWeight = 0, totalProfit = 0;
	
	//Sort the items based on weight
	vector<knapsackItems> sortedItems = sortDescending(items,true,elements_In_Knapsack);

	//Compute total weight and profit and print the results.
	printf("\ngreedy3: Selected Items");
    for (int n = 1; n <= elements_In_Knapsack; n++) {
    	if(capacity > 0 && capacity >= sortedItems[n].weight){
     		totalWeight = totalWeight + sortedItems[n].weight;
     		totalProfit = totalProfit + sortedItems[n].profit;
     		printf("\nItem number = %d  profit = %d  weight = %d", sortedItems[n].itemNumber, sortedItems[n].profit, sortedItems[n].weight);
     		capacity = capacity - sortedItems[n].weight;
     	}
    }
     
   
     printf("\nTotal weight: %d", totalWeight);
     printf("\nTotal profit: %d\n", totalProfit);
}

//greedy4(Maximum benefit per unit item)
void greedy4(vector<knapsackItems> items,int capacity, int elements_In_Knapsack){
	int totalWeight = 0, totalProfit = 0;
	
	//Sort the items based on benefit per unit item.
	vector<knapsackItems> sortedItems = sortProfitPerUnit(items, elements_In_Knapsack);
	
	//Compute total weight and profit and print the results.
	printf("\ngreedy4: Selected Items");
    for (int n = 1; n <= elements_In_Knapsack; n++) {
     	if(capacity > 0 && capacity >= sortedItems[n].weight){
     		totalWeight = totalWeight + sortedItems[n].weight;
     		totalProfit = totalProfit + sortedItems[n].profit;
     		printf("\nItem number = %d  profit = %d  weight = %d benefit per item = %0.2f ", sortedItems[n].itemNumber, sortedItems[n].profit, sortedItems[n].weight, sortedItems[n].benefit_Per_UnitItem);
     		capacity = capacity - sortedItems[n].weight;
     	}
    }
     
     printf("\nTotal weight: %d", totalWeight);
     printf("\nTotal profit: %d\n", totalProfit);
}

//main function 
int main()
{
	vector<knapsackItems> item(1000);
	item = readFile();
	//call to greedy1
	greedy1(item, capacity, elements_In_Knapsack);

	//call to greedy2
	greedy2(item, capacity, elements_In_Knapsack);

	//call to greedy3
	greedy3(item, capacity, elements_In_Knapsack);

	//call to greedy4
	greedy4(item, capacity, elements_In_Knapsack);

    printf("\n");

	return 0;
}