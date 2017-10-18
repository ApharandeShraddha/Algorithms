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

vector<int> bestSet (50);
vector<int> include (50);
int maxProfit = -1, finalWeight;

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

//Sort the items 
vector<knapsackItems> sort(vector<knapsackItems> items, int elements_In_Knapsack){
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


//Compute upper bound.
int bound(vector<knapsackItems> items, int n, int capacity, int currentProfit, int currentWeight,int k)
{
	int b = currentProfit;
	int c = currentWeight;
	
	//If there are more items
	for(int i=k;i<=n;i++)
	{
		c = c+items[i].weight;
		//If knapsack is not full, then add profit of next item.
		if(c <= capacity)
			b = b +items[i].profit;
		else
			return (b+(1-(c-capacity)/ items[i].weight)*items[i].profit);
	}
	return b;
}

//Find out the best solution.
void knapsack(vector<knapsackItems> &items, int n, int capacity, int k,int currentProfit, int currentWeight)
{
	//Save the best solution which fits in the knapsack.
	if(currentWeight+items[k].weight <= capacity)
	{
		include[k] = 1;
		if(k <= n)
			knapsack(items, n, capacity, k+1, currentProfit+items[k].profit, currentWeight+items[k].weight);
		if(((currentProfit+items[k].profit) > maxProfit) && ( k == n))
		{
			maxProfit = currentProfit+items[k].profit;
			finalWeight = currentWeight+items[k].weight;
			for(int j=1;j<=n;j++)
				bestSet[j] = include[j];
		}
	}
	// best solution for that.
	int sol=bound(items,n,capacity,currentProfit,currentWeight,k);
	if(sol >= maxProfit)
	{
		include[k] = 0;
		if( k <= n)
			knapsack(items,n,capacity,k+1,currentProfit,currentWeight);
			if((currentProfit > maxProfit) && (k == n))
			{
				maxProfit = currentProfit;
				finalWeight = currentWeight;
				for(int j=1;j<=n;j++)
					bestSet[j] = include[j];
			}
	}
}


//Dynamic programming approach
void dynamicProgramming(vector<knapsackItems> &items,int capacity, int elements_In_Knapsack)
{

	int totalWeight = 0, totalProfit = 0;
	
	//Sort the items
	vector<knapsackItems> sortedItems = sort(items, elements_In_Knapsack);
	
	//Find best solution.
	knapsack(sortedItems, elements_In_Knapsack, capacity, 1, 0, 0);
	
	//display selected items
	for(int i=1;i<=elements_In_Knapsack;i++)
		if(bestSet[i]==1)
		{
			printf("\nItem number = %2d  profit = %2d  weight = %2d ", items[i].itemNumber, items[i].profit, items[i].weight);			
			totalProfit += items[i].profit * bestSet[i];
			totalWeight += items[i].weight * bestSet[i];
		}

	printf("\nTotal weight: %d", totalWeight);
    printf("\nTotal profit: %d\n", totalProfit);

}


int main()
{
	int totalProfit = 0;
	int totalWeight = 0;

	//call to read method function
	vector<knapsackItems> item(1000);
	item = readFile();
    
    //call to dynamic
    dynamicProgramming(item,capacity,elements_In_Knapsack);
    
	return 0;
}
