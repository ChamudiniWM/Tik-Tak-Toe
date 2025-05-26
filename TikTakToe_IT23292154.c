#include <stdio.h>
#define blank ' '


void createBoard(int N); //function to create a board with empty spaces
void dispBoard(int N); //function to print the current board
int checkWinner(char player, int N); //function to check if the current player won
int checkDraw(int N); //function to check if the game is a draw


char board[10][10]; //maximum given size of the board
char player = 'X'; //player who starts the game


int main(){
	int N,j,i,move,row,col; //define variables

	printf("Tic Tac Toe\n"); //print the name of the game

	//get size of the board from the player
	printf("Enter the size of the board you prefer (3 <= N <=10):");
	scanf("%d", &N);


	//check whether N value is within the range. If not inform the player
	while(N < 3 || N > 10){
		printf("Invalid board size. Please enter a valid size.\n");
		printf("Enter the size of the board you prefer (3 <= N <=10):");
		scanf("%d", &N);
	}


	createBoard(N); //function to create a board with empty spaces according to N value
	

	//loop to handle players' turns and progress the game
	for (move = 1; move <= N * N; move++){
		printf("Current board:\n");
		dispBoard(N);

		printf("\nPlayer %c, enter your move (row column):",player);
		scanf("%d %d", &row, &col);


		//check the given move is valid. If not ask player to enter a valid move
		/*
		 row < 0 || row >=N         To check the value for the row is valid
		 col < 0 || col >=N         To check the value for the col is valid
		 board[row][col] != blank   To check whether the move is available on the current board
		 */
		while(row < 0 || row >= N ||col < 0 || col >= N || board[row][col] != blank){
			printf("Invalid move. Try again.\n");
			printf("\nPlayer %c, enter your move (row column):",player);
			scanf("%d %d", &row, &col);
		}



		//update the board
		board[row][col] = player;
	


		//check if the current player has won
		if(checkWinner(player, N)){
			printf("\nCongratulations! Player %c won!\n",player);
			break;
		}


		//check if the game is a draw
		if(checkDraw(N)){
			printf("\nIt is a draw.\n");
			break;
		}


		//switch to the other player for the next turn
		player = (player == 'X')? 'O': 'X';
	}


	dispBoard(N);
	printf("Game over!\n");
        return 0;
}









//function to create a board with empty spaces according to N value
void createBoard(int N){
	int i,j;
	for (i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			board[i][j] = blank;
		}
	}
	return;
}




//function to print the current board
void dispBoard(int N){
	int i,j;

	//open file
	FILE *game;
	game = fopen ("TicTacToe.txt","w");

	
	//check whether the file is a null
	if (game == NULL){
		printf("File doesn't exist.\n");
	}

	

	for (i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			printf("| %c ", board[i][j]);
			fprintf(game,"| %c ",board[i][j]); //print the updated board to the file
		}
		printf("|\n");
		fprintf(game,"|\n");
	}
	fclose(game); //close the file
	return;
}




//function to check if the current player is the winner
int checkWinner(char player, int N){
	int rowWinner = 1;
	int colWinner = 1;
	int diag1Winner = 1;
	int diag2Winner = 1;
	int i,j;

	for (i = 0; i < N; i++){
		for (j = 0; j < N; j++){
			if (board[i][j] != player){
				rowWinner = 0; //this is valid if there's no chance to win in row
			}
			if (board[j][i] != player){
				colWinner = 0; //this is valid if there's no chance to win in column
			}
		}
		if (rowWinner || colWinner){
			return 1; //this is valid if there's a win in a row or a column
		}
	}
	


	for(i = 0; i < N; i++){
		if(board[i][i] != player){
			diag1Winner = 0; //this is valid if there's no chance to win in diagonal which goes left to right
		}
		if(board[i][N-(i+1)] != player){
			diag2Winner = 0; //this is valid if there's no chance to win in diagonal which goes right to left
		}
	}
	if(diag1Winner || diag2Winner){
		return 1; //this is valid if there's a win in a diagonal
	}
	return 0;
}





//function to check whether game is a draw
int checkDraw(int N){
	int i, j;
	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			if(board[i][j] == blank){
				return 0;
			}
		}
	}
	return 1;
}


