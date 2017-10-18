
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<string.h>

//Display the board with tromino tiles.
int board_size;
void displayBoard(int board[][board_size], int board_size) {
int	i = 0, j = 0;
char hole = 'X';

while (i < board_size){
		j = 0;
		while (j < board_size){
			if(board[i][j] == 9999){
				printf("%3c", hole);
			}else{
				printf("%3d", board[i][j]);
			}
			j++;
		}
		printf("\n");
		i++;
	}
printf("\n");
}//end

//Place the tromino tiles in correct positions
static int trominoId = 0;
void trominoTile(int board[][board_size], int board_size, int row, int column, int left_row, int left_column){

	int half_size = board_size/2;
	int i ,j=0;
	//For 2x2 board,only one tromino tile will ne used
	if(board_size == 2){
		trominoId++;
		for(i=0;i<board_size;i++){
			for(j=0;j<board_size;j++){
				if(board[left_row + i][left_column + j] == 0){
					board[left_row + i][left_column + j] = trominoId;
				}
			}
		}
		return;
	}//end
	

	//Apply DivtrominoTileIde and conquer , so only one of the following cases will be true.
	trominoId++;
	int trominoTileId = trominoId;
	if(row >= (left_row + half_size)){

 		board[left_row + half_size-1][left_column + half_size-1] = trominoTileId;
		board[left_row + half_size-1][left_column + half_size] = trominoTileId;	
		if(column < (left_column + half_size)){
			board[left_row + half_size][left_column + half_size] = trominoTileId;
			//hole position is in 3rd quadrant.
			trominoTile(board, half_size, row, column, left_row + half_size, left_column + 0);
			trominoTile(board, half_size, half_size-1, half_size, left_row + 0, left_column + half_size);
			trominoTile(board, half_size, half_size-1, half_size-1, left_row + 0, left_column + 0);
			trominoTile(board, half_size, half_size, half_size, left_row + half_size, left_column + half_size);
		}else{
			board[left_row + half_size][left_column + half_size-1] = trominoTileId;
			//hole position is in 4th quadrant.
			trominoTile(board, half_size, row, column, left_row + half_size, left_column + half_size);
			trominoTile(board, half_size, half_size-1, half_size, left_row + 0, left_column + half_size);
			trominoTile(board, half_size, half_size-1, half_size-1, left_row + 0, left_column + 0);
			trominoTile(board, half_size, half_size, half_size-1, left_row + half_size, left_column + 0);
			}
	}else{

		board[left_row + half_size][left_column + half_size-1] = trominoTileId;
		board[left_row+ half_size][left_column + half_size] = trominoTileId;
		if(column < (left_column + half_size)){
			board[left_row + half_size-1][left_column + half_size] = trominoTileId;
			//hole position is in 2nd quadrant.
			trominoTile(board, half_size, row, column, left_row + 0, left_column + 0);
			trominoTile(board, half_size, half_size - 1, half_size, left_row + 0, left_column + half_size);
			trominoTile(board, half_size, half_size, half_size - 1, left_row + half_size, left_column + 0);
			trominoTile(board, half_size, half_size, half_size, left_row + half_size, left_column + half_size);
		}else{
			board[left_row + half_size-1][left_column + half_size-1] = trominoTileId;
			//hole position is in 1st quadrant.
			trominoTile(board, half_size, row, column, left_row + 0, left_column + half_size);
			trominoTile(board, half_size, half_size-1, half_size-1, left_row + 0, left_column + 0);
			trominoTile(board, half_size, half_size, half_size-1, left_row + half_size, left_column + 0);
			trominoTile(board, half_size, half_size, half_size, left_row + half_size, left_column + half_size);

		}
	}
	
}//end of trominoTile function


int main(int argc, char* argv[]){
	int k=0,  row = 0, column = 0;
	int i,j=0;
	trominoId = 0;
	
	//valtrominoTileIdate the command line arguuments.
	if(argc < 4 || argc > 4){
		printf("\nInvaltrominoTileId number of arguments.Please enter board size , hole position row number and hole position column number!\n");
		exit(1);
	}
	
	//get size of matrix .
	k = atoi(argv[1]);

	//get hole position in matrix
	row = atoi(argv[2]);
	column = atoi(argv[3]);
	
	
	board_size = pow(2,k);

	//Declare board.	
    int board[board_size][board_size];
	
	//initialize the board values.
	while (i < board_size){
			j = 0;
			while (j < board_size){
				board[i][j] = 0;
				j++;
				}
			i++;
		}
		
	//Place hole value in board
	board[row][column]=9999;
			
	//Place the tromino tiles.
	trominoTile(board, board_size, row, column,0,0);

	//display the board after tromino tiling 
	displayBoard(board, board_size);
		
	
}
