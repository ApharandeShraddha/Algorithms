#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <limits.h>


//To display SquareMatrix
void display_SquareMatrix(int column, float matrix[][column]) {
int	i = 0, j = 0;
while (i < column){
		j = 0;
		while (j < column){
		printf("%7.2f  ", *(matrix[i] + j));
			j++;
		}
		printf("\n");
		i++;
	}
printf("\n");
}//end of display_SquareMatrix


//To display NonSquareMatrix
void display_NonSquareMatrix(int column, float matrix[][column] , int difference) {
int	i = 0, j = 0;
while (i < column-difference){
		j = 0;
		while (j < column-difference){
		printf("%7.2f  ", *(matrix[i] + j));
			j++;
		}
		printf("\n");
		i++;
	}
printf("\n");
}//end of display_NonSquareMatrix


//insert random float values to matrices range(-5.0 to 5.0)
void insert_SquareMatrix(int column,float matrix[][column]){
int	i = 0, j = 0;
float min;
float max;
min = -5.0;
max = 5.0;

	while (i < column){
		j = 0;
		while (j < column){
			float value = (max - min) * ((float)rand() / RAND_MAX) + min;
			*(matrix[i] + j) = ceilf(value * 100) / 100 ;
			j++;
		}
		i++;
	}
}//end of insert_SquareMatrix

//insert random float values to matrices range(-5.0 to 5.0)
void insert_NonSquareMatrix(int column,float matrix[][column]){
int	i = 0, j = 0;
float min;
float max;
min = -5.0;
max = 5.0;

	while (i < column-1){
		j = 0;
		while (j < column-1){
			float value = (max - min) * ((float)rand() / RAND_MAX) + min;
			*(matrix[i] + j) = ceilf(value * 100) / 100 ;
			j++;
		}
		i++;
	}
}//end of insert_NonSquareMatrix


//Check input is power of 2 or not
int isPowerTwo(unsigned int param){
	unsigned int no = 1;
	while (no < INT_MAX && no < param)
		no = 2 * no;
	if(no == param)
		return 1;
	else
		return 0;
}//end of function isPowerTwo


//find next nearest power of 2 for given input
int newMatrixSize(unsigned int matrixSize){
	int  nextNearestPower  =  1 ;
	while  ( matrixSize >= nextNearestPower)
		{
			nextNearestPower  =  nextNearestPower  <<  1 ;
		}
   return nextNearestPower;
 }//end of newMatrixSize function


//Function to calculate matrix  using straussens algorithm   
int curr_size;
void customRecusriveStrassensMultFunction(float mat1[curr_size][curr_size], float mat2[curr_size][curr_size], float result[curr_size][curr_size], int Glo_size)
{

int half = (curr_size/2);
float m1[half][half];
float m2[half][half];
float m3[half][half];
float m4[half][half];
float m5[half][half];
float m6[half][half];
float m7[half][half];
float store1[half][half];
float store2[half][half];

if (curr_size >= 2){
int  i, j;

//First Term
	i=0; j=0;
	while(i < half){
		j=0;
		while(j < half){
			//A11 + A22
			store1[i][j] = *(mat1[i]+j) + *(mat1[i + half]+j + half);      
			j++;
		}
	i++;
	}

	i=0; j=0;
	while(i < half){
		j=0;
		while(j < half){
			//B11 + B22
			store2[i][j] = *(mat2[i]+j) + *(mat2[i + half]+j+ half);      
			j++;
		}
	i++;
	}
curr_size = half;
customRecusriveStrassensMultFunction(store1, store2, m1, curr_size);


//Second Term
	i=0; j=0;
		while(i < half){
			j=0;
			while(j < half){
			//A21 + A22
			store1[i][j] = *(mat1[i + half]+j) + *(mat1[i + half]+j+ half);           
		j++;
		}
		i++;
	}

	i=0; j=0;
		while(i < half){
		j=0;
		while(j < half){
		//B11
		store2[i][j] = *(mat2[i]+j);                              
	j++;
	}
	i++;
	}
curr_size = half;
customRecusriveStrassensMultFunction(store1, store2, m2, half);

//Third Term
	i=0; j=0;
	while(i < half){
		j=0;
		while(j < half){
			//A11
			store1[i][j] = *(mat1[i]+j);                  
		j++;
	}
	i++;
	}

	i=0; j=0;
	while(i < half){
		j=0;
		while(j < half){
			//B12 - B22
			store2[i][j] = *(mat2[i]+j + half) - *(mat2[i + half]+j +half);        
		j++;
	}
	i++;
	}
curr_size = half;
customRecusriveStrassensMultFunction(store1, store2, m3, half);

//Fourth Term
		i=0; j=0;
	while(i < half){
		j=0;
		while(j < half){
			//A22
			store1[i][j] = *(mat1[i + half]+j+ half);            
		j++;
		}
	i++;
	}

		i=0; j=0;
	while(i < half){
		j=0;
		while(j < half){
			//B21 - B11
			store2[i][j] = *(mat2[i + half]+j) - *(mat2[i]+j);  
		j++;
		}
	i++;
	}
curr_size = half;
customRecusriveStrassensMultFunction(store1, store2, m4, half);

//Fifth Term
	i=0; j=0;
	while(i < half){
		j=0;
		while(j < half){
			//A11 + A12
			store1[i][j] = *(mat1[i]+j) + *(mat1[i]+j + half);  
		j++;
		}
	i++;
	}

	i=0; j=0;
	while(i < half){
	j=0;
		while(j < half){
			//B22
			store2[i][j] = *(mat2[i + half]+j +half);            
		j++;
		}
	i++;
	}
curr_size = half;
customRecusriveStrassensMultFunction(store1, store2, m5, half);

//Sixth term
	i=0; j=0;
	while(i < half){
		j=0;
		while(j < half){
			//A21 - A11
			store1[i][j] = *(mat1[i + half]+j) - *(mat1[i]+j);          
		j++;
		}
	i++;
	}

	i=0; j=0;
	while(i < half){
		j=0;
		while(j < half){
			//B11 + B12
			store2[i][j] = *(mat2[i]+j) + *(mat2[i]+j + half);          
		j++;
		}
	i++;
	}
curr_size = half;
customRecusriveStrassensMultFunction(store1, store2, m6, half);

//Seventh Term
	i=0; j=0;
	while(i < half){
		j=0;
		while(j < half){
			//A12 - A22
			store1[i][j] = *(mat1[i]+j +half) - *(mat1[i + half]+j + half);        
		j++;
		}
	i++;
	}

	i=0; j=0;
	while(i < half){
		j=0;
		while(j < half){
			 //B21 + B22
			store2[i][j] = *(mat2[i + half]+j) + *(mat2[i + half]+j + half);      
		j++;
		}
	i++;
	}
curr_size = half;
customRecusriveStrassensMultFunction(store1, store2, m7, half);

//First Term
	i=0; j=0;
	while(i < half){
		j=0;
		while(j < half){
			//C11 = M1+M4 - M5+M7
			result[i][j] = m1[i][j] + m4[i][j] - m5[i][j] + m7[i][j];       
		j++;
		}
	i++;
	}

//second TERM
	i=0; j=0;
	while(i < half){
		j=0;
		while(j < half){
			//C12 = M3+M5
			result[i][j + half] = m3[i][j] + m5[i][j];              
		j++;
		}
	i++;
	}

//third TERM
	i=0; j=0;
	while(i < half){
		j=0;
		while(j < half){
			//C21 = M2+M4
			result[i + half][j] = m2[i][j] + m4[i][j];              
		j++;
		}
	i++;
	}

//Fourth Term
	i=0; j=0;
	while(i < half){
		j=0;
		while(j < half){
			//C22 = M1+M3 - M2+M6
			result[i + half][j + half] = m1[i][j] + m3[i][j] - m2[i][j] + m6[i][j];     
			j++;
			}
		i++;
		}

	}
	//Base condition when matrix will be 1*1
	else if (curr_size == 1){
			result[0][0] = mat1[0][0] * mat2[0][0];
	}
}//End of customRecusriveStrassensMultFunction


//Function to call recursiove function calculating Matrix multiplication
int newSize;
void strassensMultiplication(float originalMatrixA[curr_size][curr_size], float originalMatrixB[curr_size][curr_size], float strassenResult[curr_size][curr_size], int matrixSize){
   
   //Call to recursive function calculating multiplication using Strassens Algorithm
   customRecusriveStrassensMultFunction(originalMatrixA, originalMatrixB, strassenResult, matrixSize);
   

   //Display the result of Strassen’s Multiplication
   printf("Strassen’s Multiplication Output:\n");
   if(isPowerTwo(matrixSize) !=1){
   		 int difference = newSize - matrixSize;
		 display_NonSquareMatrix(newSize ,strassenResult , difference);
	}else{
		 display_SquareMatrix(matrixSize ,strassenResult);
	}
}//end of strassensMultiplication



//standard Matrix Multiplication
void standardMultiplication(int temp, float mat1[][temp], float mat2[][temp], float result[][temp] ,int original_size){

	int i = 0, j = 0, k;
	float sum = 0;
	for (i = 0; i < temp; i++) {
		for (j = 0; j < temp; j++) {
			for (k = 0; k < temp; k++) {
				sum = sum + mat1[i][k] * mat2[k][j];
			}
			*(result[i] + j) = sum;
			sum = 0;
		}
	}
	//Display the result of Standard Multiplication
	printf("Standard Multiplication Output:\n" );
	if(isPowerTwo(original_size) !=1){
		int difference = temp - original_size;
		display_NonSquareMatrix(temp , result , difference);
	}else{
		display_SquareMatrix(original_size,result);
	}
	
}//End of standardMultiplication


int main(int argc, char const *argv[])
{	
	int checkPower;
	int matrixSize;

 	//Validate Command line arguments
	if(argc < 2 || argc > 2){
		printf("Invalid command line Input .Please enter valid input.\n");
		exit(1);
	}

   //get size of matrix
   curr_size = atoi(argv[1]);

   matrixSize = curr_size;

   //check for whether input is power of 2 or not (Check for square matrix) 
   checkPower =isPowerTwo(matrixSize);

	
      if (checkPower !=1)
      {
      	//Strassens Algorithms with matrix size n where n != 2 pow k i.t for non square matrix 
      	int i ,j;
      	newSize = newMatrixSize(matrixSize);
      	curr_size = newSize;
      
	  	float originalMatrixA[newSize][newSize], originalMatrixB[newSize][newSize];
		float strassenResult[newSize][newSize], standardResult[newSize][newSize];

		//Initialize matrix with zero
		while (i < newSize){
			j = 0;
			while (j < newSize){
				*(originalMatrixA[i] + j) = 0.00 ;
				*(originalMatrixB[i] + j) = 0.00 ;
				j++;
				}
			i++;
		}

		
		insert_NonSquareMatrix(newSize, originalMatrixA);
		insert_NonSquareMatrix(newSize, originalMatrixB);
   		printf("Matrix A:\n");
   		display_SquareMatrix(matrixSize, originalMatrixA);
   		printf("Matrix B:\n");
   		display_SquareMatrix(matrixSize, originalMatrixB);

    	//Call to strassensMultiplication and standardMultiplication if matrix is sqaure
    	strassensMultiplication(originalMatrixA, originalMatrixB, strassenResult, matrixSize);
 		standardMultiplication(newSize,originalMatrixA,originalMatrixB,standardResult ,matrixSize);	
      	
       
      }else{

		//Strassens Algorithms with matrix size n where n == 2 pow k i.e for Square matrix
		float originalMatrixA[matrixSize][matrixSize], originalMatrixB[matrixSize][matrixSize];
		float strassenResult[matrixSize][matrixSize], standardResult[matrixSize][matrixSize];
      	insert_SquareMatrix(matrixSize, originalMatrixA);
   		insert_SquareMatrix(matrixSize, originalMatrixB);
   		printf("Matrix A:\n");
   		display_SquareMatrix(matrixSize, originalMatrixA);
   		printf("Matrix B:\n");
   		display_SquareMatrix(matrixSize, originalMatrixB);

   		//Call to strassensMultiplication and standardMultiplication if matrix is non_sqaure
  		strassensMultiplication(originalMatrixA, originalMatrixB, strassenResult, curr_size);
 		standardMultiplication(matrixSize,originalMatrixA,originalMatrixB,standardResult ,matrixSize);	
 		
	 }
	  

	return 0;
}