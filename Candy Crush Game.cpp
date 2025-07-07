#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<stdlib.h>
#include<ctime>
using namespace std;
ifstream ain;
ofstream aout;
int score = 0;
int const candy1 = 30;
int const candy2 = 30;
int const candy3 = 40;
int const candy4 = 50;
int const candy5 = 60;

// user turns
int turns = 20;
//diaplaying the board on compiler
void display(string board[][9]);

//checking for wrapped candy
void checkWrapped(string board[][9]);

//after displaying we will check that no five or more combo exist 
void checkcombo5(string board[][9]);

//after displaying we will check that no four combo exist 
void checkcombo4(string board[][9]);

//after displaying we will check that no three combo exist 
void checkcombo3(string board[][9]);

//updating the board after checking no combo exist
void update(string board[][9]);

//check if come combination are present in our board
bool checkcombination(string board[][9]);

//swaping arrows
void swaparrow(string board[][9], int& r1, int& c1, int& r2, int& c2);

//swaping numbers
int swap(string board[][9], int r1, int c1, int r2, int c2);

// this function is used for adding delay in bursting and making new candies
void delay(int a);

// this function us used for colour bomb
void bomb(string board[][9], int a, int r1, int c1, int r2, int c2);

//striped candy
void striped(string board[][9], int index, int flag);

//wraped candy
void wraped(string board[][9], int r1, int c1);

//wraped chk
void wrapedchk(string board[][9], int a, int r1, int c1);

//score
void addscore(char ch, int a);


int main()
{
	//game board
	string board[9][9];
	//character that contain random candy
	char candy;
	//input variable
	int input, input2;
	char start,start1;
	//variable for selecting
	int flag = 0;
	//index variables
	int r1 = 0, c1 = 0, r2 = 0, c2 = 0;
	//after swaping check which type of candies are swaped
	int match = 0;

	//to genrate new random number every time
	srand(time(0));
	//start of game
	cout << "\t\t\t\t";
	for (int i = 0; i < 30; i++)
		cout << "*";
	cout << endl << "\t\t\t\t*";
	cout << "    <CANDY CRUSH GAME>      *" << endl;
	cout << "\t\t\t\t";
	for (int i = 0; i < 30; i++)
		cout << "*";
	cout << endl << endl << endl << endl;
	cout << "\t\t\t\t";
	for (int i = 0; i < 33; i++)
		cout << "*";
	cout << endl << "\t\t\t\t*\t\t     \t\t*";
	cout << endl << "\t\t\t\t*\t\tStart\t\t*";
	cout << endl << "\t\t\t\t*\t\t     \t\t*";
	cout << endl << "\t\t\t\t*\t\t     \t\t*";
	cout << endl << "\t\t\t\t*\t        Resume\t\t*";
	cout << endl << "\t\t\t\t*\t              \t\t*";
	cout << endl << "\t\t\t\t*\t              \t\t*";
	cout << endl << "\t\t\t\t*\t     Instructions\t*";
	cout << endl << "\t\t\t\t*\t                 \t*";
	cout << endl << "\t\t\t\t*\t                 \t*";
	cout << endl << "\t\t\t\t*\t\tQuite\t\t*";
	cout << endl << "\t\t\t\t*\t\t     \t\t*";
	cout << endl << "\t\t\t\t*\t\t     \t\t*";
	cout << endl << "\t\t\t\t";
	for (int i = 0; i < 33; i++)
		cout << "*";
	cout << endl;
	cin >> start;
	if (start == 's' || start == 'S' || start == 'r' || start == 'R')
	{
		if (start == 's' || start == 'S')
		{
			for (int row = 0; row < 9; row++)
				for (int col = 0; col < 9; col++)
				{
					candy = rand() % 5 + 34;
					board[row][col] = { ' ',' ',candy,' ',' ' };
				}
		}
		else if(start == 'r' || start == 'R')
		{
			string candy1;
			int m = 0, n = 0, o = 0;
			ain.open("Save Game.txt");
			for (int row = 0; row < 9; row++)
			{
				for (int col = 0; col < 9; col++)
				{
					getline(ain,candy1);
					board[row][col] = candy1;
				}
			}
			ain.close();
			ain.open("turns.txt");
			ain >> turns;
			ain.close();
			ain.open("score.txt");
			ain >> score;
			ain.close();
		}
		//displaying board
		display(board);
		update(board);
		//this loop run till all combinations distroyed and update them
		while (checkcombination(board) == true)
		{
			//checking if combination exist and distroying them
			checkcombo5(board);
			checkWrapped(board);
			checkcombo4(board);
			checkcombo3(board);
			//update board after checking combos
			update(board);
			//display board
			system("cls");
			display(board);
		}
		//arrows on board 
		board[0][0].at(0) = '<';
		board[0][0].at(4) = '>';
		system("cls");
		display(board);
		r1 = 0;
		c1 = 0;
		r2 = 0;
		c2 = 0;
		while (turns != 0)
		{
			//this loop shows user that which candy is selected at this time
			while (flag != 5)
			{
				cin >> input;
				switch (input)
				{
				case 6:
					r2 = r1;
					c2 = c1 + 1;
					if (c2 <= 8)
					{
						swaparrow(board, r1, c1, r2, c2);
					}
					break;

				case 8:
					r2 = r1 - 1;
					c2 = c1;
					if (r2 >= 0)
					{
						swaparrow(board, r1, c1, r2, c2);
					}
					break;

				case 4:
					r2 = r1;
					c2 = c1 - 1;
					if (c2 >= 0)
					{
						swaparrow(board, r1, c1, r2, c2);
					}

					break;

				case 2:
					r2 = r1 + 1;
					c2 = c1;
					if (r2 <= 8)
					{
						swaparrow(board, r1, c1, r2, c2);
					}

					break;

				default:
					flag = 5;
				}
				system("cls");
				display(board);
				cout << endl << endl << endl;
			}
			flag = 0;
			//after selecting candy now we have swap candy with other candy to make combination
			cout << "Swap with candy(from 8,4,2,6): ";
			cin >> input2;
			switch (input2)
			{
			case 4:
				r2 = r1;
				c2 = c1 - 1;
				break;

			case 6:
				r2 = r1;
				c2 = c1 + 1;
				break;

			case 8:
				r2 = r1 - 1;
				c2 = c1;
				break;

			case 2:
				r2 = r1 + 1;
				c2 = c1;
				break;

			default:
				cout << "You enter wrong input";
				break;
			}
			match = swap(board, r1, c1, r2, c2);
			//this this work if there is some special move is made
			if (match == 0)
			{
				if (checkcombination(board) == true)
				{
					while (checkcombination(board) == true)
					{
						//checking if combination exist and distroying them
						checkcombo5(board);
						checkWrapped(board);
						checkcombo4(board);
						checkcombo3(board);
						//update board after checking combos
						update(board);
						//display board
						system("cls");
						display(board);
					}
					turns--;
				}
				else
				{
					swap(board, r1, c1, r2, c2);
				}
			}
			else if (match == 1)
			{
				turns--;
				bomb(board, 1, r1, c1, r2, c2);
				striped(board, 0, 3);
				update(board);
			}
			else if (match == 2)
			{
				turns--;
				bomb(board, 2, r1, c1, r2, c2);
				update(board);
			}
			else if (match == 3)
			{
				turns--;
				bomb(board, 3, r1, c1, r2, c2);
				wrapedchk(board, 1, r1, c1);
				update(board);
			}
			else if (match == 4)
			{
				turns--;
				wrapedchk(board, 2, r1, c1);
				update(board);
			}
			else if (match == 5)
			{
				turns--;
				wrapedchk(board, 3, r1, c1);
				update(board);
			}
			else if (match == 6)
			{
				turns--;
				bomb(board, 6, r1, c1, r2, c2);
				update(board);
			}
			while (checkcombination(board) == true)
			{
				//checking if combination exist and distroying them
				checkcombo5(board);
				checkWrapped(board);
				checkcombo4(board);
				checkcombo3(board);
				//update board after checking combos
				update(board);
				//display board
				system("cls");
				display(board);
			}
			for (int row = 0; row < 9; row++)
			{
				for (int col = 0; col < 9; col++)
				{
					if (board[row][col].at(0) == '<' && board[row][col].at(4) == '>')
					{
						board[row][col].at(0) = ' ';
						board[row][col].at(4) = ' ';
					}
				}
			}
			board[0][0].at(0) = '<';
			board[0][0].at(4) = '>';
			r1 = 0;
			c1 = 0;
			r2 = 0;
			c2 = 0;
			system("cls");
			display(board);
		}
		
	}
	else if (start == 'i' || start == 'I')
	{
		system("cls");
		cout << endl << endl;
		cout << "'' == 30 points" << endl << endl;
		cout << "# == 30 points" << endl << endl;
		cout << "$ == 40 points" << endl << endl;
		cout << "% == 50 points" << endl << endl;
		cout << "& == 60 points" << endl << endl;
		cout << "()  Striped Candy: It is created when 4 similar plain candies lie in same column, or row of grid." << endl << endl;
		cout << "[] Wrapped Candy: It is created by matching 5 candies of same color in L or T shape." << endl << endl;
		cout << "'B' Color Bomb: It is created by matching 5 candies of same color in row or column." << endl << endl;
		cout << "Plain Candy + Striped Candy: When 3 similar color candies lie in same column, or row of	grid, they will be crushed.If any of them is a striped candy then the corresponding rows or	columns, which contains the striped candies, will be cleared.The decision to clear the row or column will be made according to direction of stripes on candy." << endl << endl;
		cout << "Plain Candy + Wrapped candy: When 3 similar color candies lie in same column, or row of  grid, they will be crushed.If any of them is a wrapped candy then the candies in(3 x 3) square  area of board around wrapped candy will also be crushed." << endl;
		cout << "Color Bomb + Plain Candy: If player swaps color bomb with any plain candy then all candies,	of that particular color, will be crushed." << endl << endl;
		cout << " Color Bomb + Color Bomb: If player swaps color bomb with another color bomb, then all candies from board will be crushed and board will be reloaded with all new candies." << endl << endl;
		cout << "Striped Candy + Color Bomb: If player swaps color bomb with striped candy, then all	candies will be transformed into striped candies of same color as of striped candy.All of them then clear their respective rows / columns." << endl << endl;
		cout << "Wrapped Candy + Color Bomb: If player swaps color bomb with wrapped candy, then all candies will be transformed into wrapped candies of same color of wrapped candy.All candies in(3 x 3) square area, around swapped wrapped candy, will also be crushed." << endl << endl;
		cout << "Striped Candy + Wrapped Candy: If player swaps striped candy with wrapped candy, then 3 rows and 3 columns centered on the candy that was swapped will be cleared." << endl << endl;
		cout << "Wrapped Candy + Wrapped Candy: If player swaps wrapped candy with another wrapped	candy, then all candies will be crushed in(5 x 5) square area around swapped candies." << endl << endl;
	}
	else if (start == 'q' || start == 'Q')
	{
	system("cls");
		cout << endl << endl << endl << endl << endl << endl << "\t\t\t\tSee you next time:)"<<endl;
	}
	system("pause");
}

//function that display all candies on board
void display(string board[][9])
{
	aout.open("Save Game.txt");
	cout << "\t\t\t\t";
	for (int i = 0; i < 30; i++)
		cout << "*";
	cout << endl << "\t\t\t\t*";
	cout << "    <CANDY CRUSH GAME>      *" << endl;
	cout << "\t\t\t\t";
	for (int i = 0; i < 30; i++)
		cout << "*";
	cout << endl << endl << endl << endl;

	for (int i = 0; i < 9; i++)
	{
		cout << "\t\t";
		for (int i = 0; i < 64; i++)
			cout << "-";
		cout << endl << "\t\t";
		for (int j = 0; j < 9; j++)
		{
			cout <<"|"<< board[i][j] << " ";
			aout << board[i][j]<<endl;
		}
		cout << "|";
		cout << endl ;
	}
	cout << "\t\t";
	for (int i = 0; i < 64; i++)
		cout << "-";
	cout << endl<<endl<<endl;
	aout.close();
	aout.open("score.txt");
	aout << score;
	aout.close();
	cout << "\t\tscore: " << score << "\t\t\tTurns Left: " << turns;
	aout.open("turns.txt");
	aout << turns;
	aout.close();
}
//check if some combination are present in our board
bool checkcombination(string board[][9])
{
	bool present = false;
	//checking if combination are present in rows
	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			if (col < 7)
			{
				if (board[row][col].at(2) != ' ')
				{
					if (board[row][col].at(2) == board[row][col + 1].at(2) && board[row][col].at(2) == board[row][col + 2].at(2))
					{
						present = true;
						return present;
					}
				}
			}
		}
	}
	for (int col = 0; col < 9; col++)
	{
		for (int row = 0; row < 9; row++)
		{
			if (row < 7)
			{
				if (board[row][col].at(2) != ' ')
				{
					if (board[row][col].at(2) == board[row + 1][col].at(2) && board[row][col].at(2) == board[row + 2][col].at(2))
					{
						present = true;
						return present;
					}
				}
			}
		}
	}
	return present;
}
//after displaying we will check that no five or more combo exist in col
void checkcombo5(string board[][9])
{
	// stripedcandies 
	char candy;
	int i = 0, j = 0;
	for (int col = 0; col < 9; col++)
	{
		for (int row = 0; row < 9; row++)
		{
			candy = board[row][col].at(2);
			j = row;
			i = row;
			if (row < 5)
			{
				if (board[row][col].at(2) != ' ')
				{
					if (board[row][col].at(2) == board[row + 1][col].at(2) && board[row][col].at(2) == board[row + 2][col].at(2) && board[row][col].at(2) == board[row + 3][col].at(2) && board[row][col].at(2) == board[row + 4][col].at(2))
					{
						for (int k = 0; k < 5; k++)
						{
							if (i != j)
							{
								if (board[row + k][col].at(1) == '(' && board[row + k][col].at(3) == ')')
								{
									board[row + k][col].at(1) = ' ';
									board[row + k][col].at(3) = ' ';
									striped(board, row + k, 2);
									i++;
								}
								else if (board[row + k][col].at(1) == '[' && board[row + k][col].at(3) == ']')
								{
									board[row + k][col].at(1) = ' ';
									board[row + k][col].at(3) = ' ';
									wraped(board, row + k, col);
									i++;
								}
								else
								{
									board[row + k][col].at(2) = ' ';
									system("cls");
									display(board);
									delay(1);
									i++;
								}
							}
							else
							{
								if (board[row + k][col].at(1) == '(' && board[row + k][col].at(3) == ')')
								{
									striped(board, row + k, 2);
									board[row + k][col].at(2) = 'B';
									system("cls");
									display(board);
									delay(1);
									i++;
								}
								else if (board[row + k][col].at(1) == '[' && board[row + k][col].at(3) == ']')
								{
									wraped(board, row + k, col);
									board[row + k][col].at(1) = ' ';
									board[row + k][col].at(3) = ' ';
									board[row + k][col].at(2) = 'B';
									system("cls");
									display(board);
									delay(1);
									i++;
								}
							}
						}
						addscore(candy, 5);
					}
				}
			}
		}
	}
	i = 0;
	j = 0;
	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			candy = board[row][col].at(2);
			j = col;
			i = col;
			if (col < 5)
			{
				if (board[row][col].at(2) != ' ')
				{
					if (board[row][col].at(2) == board[row][col + 1].at(2) && board[row][col].at(2) == board[row][col + 2].at(2) && board[row][col].at(2) == board[row][col + 3].at(2) && board[row][col].at(2) == board[row][col + 4].at(2))
					{
						for (int k = 0; k < 5; k++)
						{
							if (i != j)
							{
								if (board[row][col + k].at(1) == '(' && board[row][col + k].at(3) == ')')
								{
									board[row][col + k].at(1) = ' ';
									board[row][col + k].at(3) = ' ';
									striped(board, col + k, 1);
									i++;
								}
								else if (board[row][col + k].at(1) == '[' && board[row][col + k].at(3) == ']')
								{
									board[row][col + k].at(1) = ' ';
									board[row][col + k].at(3) = ' ';
									wraped(board, row, col + k);
									i++;
								}
								else
								{
									board[row][col + k].at(2) = ' ';
									system("cls");
									display(board);
									delay(1);
									i++;
								}
							}
							else
							{
								if (board[row][col + k].at(1) == '(' && board[row][col + k].at(3) == ')')
								{
									striped(board, col + k, 1);
									board[row][col + k].at(2) = 'B';
									system("cls");
									display(board);
									delay(1);
									i++;

								}
								else if (board[row][col + k].at(1) == '[' && board[row][col + k].at(3) == ']')
								{
									wraped(board, row, col + k);
									board[row][col + k].at(1) = ' ';
									board[row][col + k].at(3) = ' ';
									board[row][col + k].at(2) = 'B';
									system("cls");
									display(board);
									delay(1);
									i++;

								}

							}
						}
						addscore(candy, 5);
					}
				}
			}
		}
	}
}
//check wrapped candy
void checkWrapped(string board[][9])
{
	int prow = 0, nrow = 0, pcol = 0, ncol = 0;
	char candy;
	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			candy = board[row][col].at(2);
			for (int k = 0; k < 9; k++)
			{
				if (col + k < 9)
				{
					if (board[row][col].at(2) == board[row][col + k].at(2))
					{
						pcol++;
					}
					else
						break;
				}
			}
			for (int k = 0; k < 9; k++)
			{
				if (col - k >= 0)
				{
					if (board[row][col].at(2) == board[row][col - k].at(2))
					{
						ncol++;
					}
					else
						break;
				}
			}
			for (int k = 0; k < 9; k++)
			{
				if (row - k >= 0)
				{
					if (board[row][col].at(2) == board[row - k][col].at(2))
					{
						nrow++;
					}
					else
						break;
				}
			}
			for (int k = 0; k < 9; k++)
			{
				if (row + k < 9)
				{
					if (board[row][col].at(2) == board[row + k][col].at(2))
					{
						prow++;
					}
					else
						break;
				}
			}
			if (pcol > 2 && prow > 2)
			{
				for (int k = 0; k < pcol; k++)
				{
					board[row][col + k].at(2) = ' ';
				}
				for (int k = 0; k < prow; k++)
				{
					board[row + k][col].at(2) = ' ';
				}
				board[row][col].at(2) = candy;
				board[row][col].at(1) = '[';
				board[row][col].at(3) = ']';
				addscore(candy, pcol + prow);
			}
			else if (pcol > 2 && nrow > 2)
			{
				for (int k = 0; k < pcol; k++)
				{
					board[row][col + k].at(2) = ' ';
				}
				for (int k = 0; k < nrow; k++)
				{
					board[row - k][col].at(2) = ' ';
				}
				board[row][col].at(2) = candy;
				board[row][col].at(1) = '[';
				board[row][col].at(3) = ']';
				addscore(candy, pcol + nrow);
				update(board);
			}
			else if (nrow > 1 && pcol > 2 && prow > 1)
			{
				for (int k = 0; k < pcol; k++)
				{
					board[row][col + k].at(2) = ' ';
				}
				for (int k = 0; k < prow; k++)
				{
					board[row + k][col].at(2) = ' ';
				}
				for (int k = 0; k < nrow; k++)
				{
					board[row - k][col].at(2) = ' ';
				}
				board[row][col].at(2) = candy;
				board[row][col].at(1) = '[';
				board[row][col].at(3) = ']';
				addscore(candy, pcol + prow+nrow);
			}
			else if (ncol > 2 && prow > 2)
			{
				for (int k = 0; k < ncol; k++)
				{
					board[row][col - k].at(2) = ' ';
				}
				for (int k = 0; k < prow; k++)
				{
					board[row + k][col].at(2) = ' ';
				}
				board[row][col].at(2) = candy;
				board[row][col].at(1) = '[';
				board[row][col].at(3) = ']';
				addscore(candy, ncol + prow);
			}
			else if (nrow > 1 && ncol > 2 && prow > 1)
			{
				for (int k = 0; k < ncol; k++)
				{
					board[row][col - k].at(2) = ' ';
				}
				for (int k = 0; k < prow; k++)
				{
					board[row + k][col].at(2) = ' ';
				}
				for (int k = 0; k < nrow; k++)
				{
					board[row - k][col].at(2) = ' ';
				}
				board[row][col].at(2) = candy;
				board[row][col].at(1) = '[';
				board[row][col].at(3) = ']';
				addscore(candy, ncol + prow+nrow);
			}
			else if (ncol > 1 && nrow > 2 && pcol > 1)
			{
				for (int k = 0; k < ncol; k++)
				{
					board[row][col - k].at(2) = ' ';
				}
				for (int k = 0; k < nrow; k++)
				{
					board[row - k][col].at(2) = ' ';
				}
				for (int k = 0; k < pcol; k++)
				{
					board[row + k][col].at(2) = ' ';
				}
				board[row][col].at(2) = candy;
				board[row][col].at(1) = '[';
				board[row][col].at(3) = ']';
				addscore(candy, pcol + nrow+ncol);
			}
			else if (ncol > 1 && prow > 2 && pcol > 1)
			{
				for (int k = 0; k < ncol; k++)
				{
					board[row][col - k].at(2) = ' ';
				}
				for (int k = 0; k < prow; k++)
				{
					board[row + k][col].at(2) = ' ';
				}
				for (int k = 0; k < pcol; k++)
				{
					board[row + k][col].at(2) = ' ';
				}
				board[row][col].at(2) = candy;
				board[row][col].at(1) = '[';
				board[row][col].at(3) = ']';
				addscore(candy, pcol + prow+ncol);
			}
			pcol = 0;
			ncol = 0;
			prow = 0;
			nrow = 0;
		}
	}
}
//after displaying we will check that no four combo exist in col
void checkcombo4(string board[][9])
{
	// stripedcandies 
	char candy;
	int i = 0, j = 0;
	for (int col = 0; col < 9; col++)
	{
		for (int row = 0; row < 9; row++)
		{
			candy = board[row][col].at(2);
			j = row;
			i = row;
			if (row < 6)
			{
				if (board[row][col].at(2) != ' ')
				{
					if (board[row][col].at(2) == board[row + 1][col].at(2) && board[row][col].at(2) == board[row + 2][col].at(2) && board[row][col].at(2) == board[row + 3][col].at(2))
					{
						for (int k = 0; k < 4; k++)
						{
							if (i != j)
							{
								if (board[row + k][col].at(1) == '(' && board[row + k][col].at(3) == ')')
								{
									board[row + k][col].at(1) = ' ';
									board[row + k][col].at(3) = ' ';
									striped(board, row + k, 2);
									i++;
								}
								else if (board[row + k][col].at(1) == '[' && board[row + k][col].at(3) == ']')
								{
									board[row + k][col].at(1) = ' ';
									board[row + k][col].at(3) = ' ';
									wraped(board, row + k, col);
									i++;
								}
								else
								{
									board[row + k][col].at(2) = ' ';
									system("cls");
									display(board);
									delay(1);
									i++;
								}

							}
							else
							{
								candy = board[row + k][col].at(2);
								if (board[row + k][col].at(1) == '(' && board[row + k][col].at(3) == ')')
								{
									striped(board, row + k, 2);
									board[row + k][col].at(1) = '(';
									board[row + k][col].at(3) = ')';
									board[row + k][col].at(2) = candy;
									i++;
								}
								else if (board[row + k][col].at(1) == '[' && board[row + k][col].at(3) == ']')
								{
									wraped(board, row + k, col);
									board[row + k][col].at(1) = '(';
									board[row + k][col].at(3) = ')';
									board[row + k][col].at(2) = candy;
									i++;
								}
								else
								{
									board[row + k][col].at(1) = '(';
									board[row + k][col].at(3) = ')';
									board[row + k][col].at(2) = candy;
									i++;
								}

							}
						}
						addscore(candy, 4);
					}
				}
			}
		}
	}
	i = 0;
	j = 0;
	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			candy = board[row][col].at(2);
			j = col;
			i = col;
			if (col < 6)
			{
				if (board[row][col].at(2) != ' ')
				{
					if (board[row][col].at(2) == board[row][col + 1].at(2) && board[row][col].at(2) == board[row][col + 2].at(2) && board[row][col].at(2) == board[row][col + 3].at(2))
					{
						for (int k = 0; k < 4; k++)
						{
							if (i != j)
							{
								if (board[row][col + k].at(1) == '(' && board[row][col + k].at(3) == ')')
								{
									board[row][col + k].at(1) = ' ';
									board[row][col + k].at(3) = ' ';
									striped(board, col + k, 1);
									i++;
								}
								if (board[row][col + k].at(1) == '[' && board[row][col + k].at(3) == ']')
								{
									board[row][col + k].at(1) = ' ';
									board[row][col + k].at(3) = ' ';
									wraped(board, row, col + k);
									i++;
								}
								else
								{
									board[row][col + k].at(2) = ' ';
									system("cls");
									display(board);
									delay(1);
									i++;
								}

							}
							else
							{
								if (board[row][col + k].at(1) == '(' && board[row][col + k].at(3) == ')')
								{
									candy = board[row][col + k].at(2);
									striped(board, col + k, 1);
									board[row][col + k].at(1) = '(';
									board[row][col + k].at(3) = ')';
									board[row][col + k].at(2) = candy;
									i++;
								}
								else if (board[row][col + k].at(1) == '[' && board[row][col + k].at(3) == ']')
								{
									candy = board[row][col + k].at(2);
									wraped(board, row, col + k);
									board[row][col + k].at(1) = '(';
									board[row][col + k].at(3) = ')';
									board[row][col + k].at(2) = candy;
									i++;
								}
								else
								{
									candy = board[row][col + k].at(2);
									board[row][col + k].at(1) = '(';
									board[row][col + k].at(3) = ')';
									board[row][col + k].at(2) = candy;
									i++;
								}

							}
						}
						addscore(candy, 4);
					}
				}
			}
		}
	}
}
//after displaying we will check that no three combo exist in column 
void checkcombo3(string board[][9])
{
	char candy;
	for (int col = 0; col < 9; col++)
	{
		for (int row = 0; row < 9; row++)
		{
			candy = board[row][col].at(2);
			if (row < 7)
			{
				if (board[row][col].at(2) != ' ')
				{
					if (board[row][col].at(2) == board[row + 1][col].at(2) && board[row][col].at(2) == board[row + 2][col].at(2))
					{
						for (int k = 0; k < 3; k++)
						{
							if (board[row + k][col].at(1) == '(' && board[row + k][col].at(3) == ')')
							{
								board[row + k][col].at(1) = ' ';
								board[row + k][col].at(3) = ' ';
								striped(board, row + k, 2);
							}
							else if (board[row + k][col].at(1) == '[' && board[row + k][col].at(3) == ']')
							{
								board[row + k][col].at(1) = ' ';
								board[row + k][col].at(3) = ' ';
								wraped(board, row + k, col);
							}
							else
							{
								board[row + k][col].at(2) = ' ';
								system("cls");
								display(board);
								delay(1);
							}
						}
						addscore(candy, 3);
					}
				}
			}
		}
	}
	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			candy = board[row][col].at(2);
			if (col < 7)
			{
				if (board[row][col].at(2) != ' ')
				{
					if (board[row][col].at(2) == board[row][col + 1].at(2) && board[row][col].at(2) == board[row][col + 2].at(2))
					{
						for (int k = 0; k < 3; k++)
						{
							if (board[row][col + k].at(1) == '(' && board[row][col + k].at(3) == ')')
							{
								board[row][col + k].at(1) = ' ';
								board[row][col + k].at(3) = ' ';
								striped(board, col + k, 1);
							}
							else if (board[row][col + k].at(1) == '[' && board[row][col + k].at(3) == ']')
							{
								board[row][col + k].at(1) = ' ';
								board[row][col + k].at(3) = ' ';
								wraped(board, row, col + k);
							}
							else
							{
								board[row][col + k].at(2) = ' ';
								system("cls");
								display(board);
								delay(1);
							}
						}
						addscore(candy, 3);
					}
				}
			}
		}
	}
}
//After checking for matched candies this function update those candies
void update(string board[][9])
{
	srand(time(0));
	char ch1, ch2;
	int counter = 0;
	string temp;
	for (int col = 0; col < 9; col++)
	{
		for (int i = 0; i < 8; i++)
		{
			for (int row = 8; row > 0; row--)
			{
				if (board[row][col].at(2) == ' ')
				{
					temp = board[row][col];
					board[row][col] = board[row - 1][col];
					board[row - 1][col] = temp;
				}
			}
		}
	}
	int i = 0;
	for (int row = 0; row < 9; row++)
	{
		counter = 0;
		if (board[row][i].at(2) == ' ')
		{
			counter = 1;
			board[row][i].at(2) = rand() % 5 + 34;
		}
		if (board[row][i + 1].at(2) == ' ')
		{
			counter = 1;
			board[row][i + 1].at(2) = rand() % 5 + 34;
		}
		if (board[row][i + 2].at(2) == ' ')
		{
			counter = 1;
			board[row][i + 2].at(2) = rand() % 5 + 34;
		}
		if (board[row][i + 3].at(2) == ' ')
		{
			counter = 1;
			board[row][i + 3].at(2) = rand() % 5 + 34;
		}
		if (board[row][i + 4].at(2) == ' ')
		{
			counter = 1;
			board[row][i + 4].at(2) = rand() % 5 + 34;
		}
		if (board[row][i + 5].at(2) == ' ')
		{
			counter = 1;
			board[row][i + 5].at(2) = rand() % 5 + 34;
		}
		if (board[row][i + 6].at(2) == ' ')
		{
			counter = 1;
			board[row][i + 6].at(2) = rand() % 5 + 34;
		}
		if (board[row][i + 7].at(2) == ' ')
		{
			counter = 1;
			board[row][i + 7].at(2) = rand() % 5 + 34;
		}
		if (board[row][i + 8].at(2) == ' ')
		{
			counter = 1;
			board[row][i + 8].at(2) = rand() % 5 + 34;
		}
		if (counter == 1)
		{
			system("cls");
			display(board);
			delay(1);
		}
	}
}
//this function is swaping arrows on board
void swaparrow(string board[][9], int& r1, int& c1, int& r2, int& c2)
{
	char temp;
	temp = board[r1][c1].at(0);
	board[r1][c1].at(0) = board[r2][c2].at(0);
	board[r2][c2].at(0) = temp;

	temp = board[r1][c1].at(4);
	board[r1][c1].at(4) = board[r2][c2].at(4);
	board[r2][c2].at(4) = temp;

	r1 = r2;
	c1 = c2;
	r2 = 0;
	c2 = 0;
}
//wraped candy
void wraped(string board[][9], int r1, int c1)
{
	char candy;
	int i = 0, j = 0;
	if (r1 > 0 && r1 < 8)
	{
		if (c1 > 0 && c1 < 8)
		{
			for (int row = r1 - 1; i < 3; row++)
			{
				j = 0;
				for (int col = c1 - 1; j < 3; col++)
				{
					candy = board[row][col].at(2);
					board[row][col].at(2) = ' ';
					addscore(candy, 1);
					j++;
				}
				i++;
			}
		}
	}
	i = 0;
	j = 0;
	if (r1 == 0)
	{
		if (c1 == 0)
		{
			for (int row = r1; i < 2; row++)
			{
				j = 0;
				for (int col = c1; j < 2; col++)
				{
					candy = board[row][col].at(2);
					board[row][col].at(2) = ' ';
					addscore(candy,1);
					j++;
				}
				i++;
			}
		}
		else if (c1 == 8)
		{
			for (int row = r1; i < 2; row++)
			{
				j = 0;
				for (int col = c1 - 1; j < 2; col++)
				{
					candy = board[row][col].at(2);
					board[row][col].at(2) = ' ';
					addscore(candy, 1);
					j++;
				}
				i++;
			}
		}
		else
		{
			for (int row = r1; i < 2; row++)
			{
				j = 0;
				for (int col = c1 - 1; j < 3; col++)
				{
					candy = board[row][col].at(2);
					board[row][col].at(2) = ' ';
					addscore(candy, 1);
					j++;
				}
				i++;
			}
		}
	}
	i = 0;
	j = 0;
	if (r1 == 8)
	{
		if (c1 == 0)
		{
			for (int row = r1 - 1; i < 2; row++)
			{
				j = 0;
				for (int col = c1; j < 2; col++)
				{
					candy = board[row][col].at(2);
					board[row][col].at(2) = ' ';
					addscore(candy, 1);
					j++;
				}
				i++;
			}
		}
		else if (c1 == 8)
		{
			for (int row = r1 - 1; i < 2; row++)
			{
				j = 0;
				for (int col = c1 - 1; j < 2; col++)
				{
					candy = board[row][col].at(2);
					board[row][col].at(2) = ' ';
					addscore(candy, 1);
					j++;
				}
				i++;
			}
		}
		else if (c1 > 0 && c1 < 8)
		{
			for (int row = r1 - 1; i < 2; row++)
			{
				j = 0;
				for (int col = c1 - 1; j < 3; col++)
				{
					candy = board[row][col].at(2);
					board[row][col].at(2) = ' ';
					addscore(candy, 1);
					j++;
				}
				i++;
			}
		}
	}
}
//wraped chk
void wrapedchk(string board[][9], int a, int r1, int c1)
{
	char candy;
	int i = 0, j = 0;
	if (a == 1)
	{
		for (int row = 0; row < 9; row++)
		{
			for (int col = 0; col < 9; col++)
			{
				if (board[row][col].at(1) == '[' && board[row][col].at(3) == ']')
				{
					board[row][col].at(1) = ' ';
					board[row][col].at(3) = ' ';
					wraped(board, row, col);
					system("cls");
					display(board);
					delay(1);
				}
			}
		}
	}
	if (a == 2)
	{
		if (c1 > 0 && c1 < 8)
		{
			if (r1 > 0 && r1 < 8)
			{
				for (int col = c1 - 1; i < 3; col++)
				{
					for (int row = 0; row < 9; row++)
					{
						candy = board[row][col].at(2);
						board[row][col].at(1) = ' ';
						board[row][col].at(2) = ' ';
						board[row][col].at(3) = ' ';
						addscore(candy, 1);
					}
					i++;
				}
				i = 0;
				for (int row = r1 - 1; i < 3; row++)
				{
					for (int col = 0; col < 9; col++)
					{
						candy = board[row][col].at(2);
						board[row][col].at(1) = ' ';
						board[row][col].at(2) = ' ';
						board[row][col].at(3) = ' ';
						addscore(candy, 1);
					}
					i++;
				}
			}

		}
		else if (c1 == 0)
		{
			for (int col = c1; i < 2; col++)
			{
				for (int row = 0; row < 9; row++)
				{
					candy = board[row][col].at(2);
					board[row][col].at(1) = ' ';
					board[row][col].at(2) = ' ';
					board[row][col].at(3) = ' ';
					addscore(candy, 1);
				}
				i++;
			}
			i = 0;
			for (int row = r1; i < 2; row++)
			{
				for (int col = 0; col < 9; col++)
				{
					candy = board[row][col].at(2);
					board[row][col].at(1) = ' ';
					board[row][col].at(2) = ' ';
					board[row][col].at(3) = ' ';
					addscore(candy, 1);
				}
				i++;
			}
		}
		else if (c1 == 8)
		{
			for (int col = c1 - 1; i < 2; col++)
			{
				for (int row = 0; row < 9; row++)
				{
					candy = board[row][col].at(2);
					board[row][col].at(1) = ' ';
					board[row][col].at(2) = ' ';
					board[row][col].at(3) = ' ';
					addscore(candy, 1);
				}
				i++;
			}
			i = 0;
			for (int row = r1 - 1; i < 2; row++)
			{
				for (int col = 0; col < 9; col++)
				{
					candy = board[row][col].at(2);
					board[row][col].at(1) = ' ';
					board[row][col].at(2) = ' ';
					board[row][col].at(3) = ' ';
					addscore(candy, 1);
				}
				i++;
			}
		}
	}
	i = 0;
	j = 0;
	if (a == 3)
	{
		if (r1 > 1 && r1 < 7)
		{
			if (c1 > 1 && c1 < 7)
			{
				for (int row = r1 - 2; i < 5; row++)
				{
					j = 0;
					for (int col = c1 - 2; j < 5; col++)
					{
						candy = board[row][col].at(2);
						board[row][col].at(1) = ' ';
						board[row][col].at(2) = ' ';
						board[row][col].at(3) = ' ';
						addscore(candy, 1);
						j++;
					}
					i++;
				}
			}
			i = 0;
			j = 0;
		}
		else if (r1 == 0 || r1 == 1)
		{
			for (int row = r1; i < 5; row++)
			{
				j = 0;
				for (int col = c1; j < 5; col++)
				{
					if (c1 + j < 9)
					{
						candy = board[row][col].at(2);
						board[row][col].at(1) = ' ';
						board[row][col].at(2) = ' ';
						board[row][col].at(3) = ' ';
						addscore(candy, 1);
						j++;
					}
					else
					{
						j++;
						break;
					}
				}
				i++;
			}
			i = 0;
			j = 0;
		}
		else if (r1 == 7 || r1 == 8)
		{
			for (int row = r1; i < 5; row--)
			{
				j = 0;
				for (int col = c1; j < 5; col++)
				{
					if (c1 + j < 9)
					{
						candy = board[row][col].at(2);
						board[row][col].at(1) = ' ';
						board[row][col].at(2) = ' ';
						board[row][col].at(3) = ' ';
						addscore(candy, 1);
						j++;
					}
					else
					{
						j++;
						break;
					}
				}
				i++;
			}
		}
	}
}
//swaping candies
int swap(string board[][9], int r1, int c1, int r2, int c2)
{
	string ch1, ch2;
	ch1 = board[r1][c1];
	ch2 = board[r2][c2];
	string temp;
	temp = board[r1][c1];
	board[r1][c1] = board[r2][c2];
	board[r2][c2] = temp;
	if (ch1.at(2) == 'B' && ch2.at(2) == 'B')
	{
		return 2;
	}
	else if (ch1.at(2) == 'B' || ch2.at(2) == 'B')
	{
		if (ch1.at(1) == '(' && ch1.at(3) == ')' || ch2.at(1) == '(' && ch2.at(3) == ')')
		{
			return 1;
		}
		if (ch1.at(1) == '[' && ch1.at(3) == ']' || ch2.at(1) == '[' && ch2.at(3) == ']')
		{
			return 3;
		}
		return 6;
	}
	else if (ch1.at(1) == '(' && ch1.at(3) == ')' || ch2.at(1) == '(' && ch2.at(3) == ')')
	{
		if (ch1.at(1) == '[' && ch1.at(3) == ']' || ch2.at(1) == '[' && ch2.at(3) == ']')
		{
			return 4;
		}
	}
	else if (ch1.at(1) == '[' && ch1.at(3) == ']' && ch2.at(1) == '[' && ch2.at(3) == ']')
	{
		return 5;
	}
	else
	{
		return 0;
	}
}
//colour bomb
void bomb(string board[][9], int a, int r1, int c1, int r2, int c2)
{
	char candy;
	string rCandy, cCandy, cCandy2;
	if (board[r1][c1].at(2) != 'B')
	{
		rCandy = board[r1][c1];
		cCandy = board[r2][c2];
	}
	else if (board[r2][c2].at(2) != 'B')
	{
		rCandy = board[r2][c2];
		cCandy = board[r1][c1];
	}
	else
	{
		cCandy = board[r1][c1];
		cCandy2 = board[r2][c2];
	}
	if (a == 6)
	{
		for (int row = 0; row < 9; row++)
		{
			for (int col = 0; col < 9; col++)
			{
				if (board[row][col].at(2) == rCandy.at(2))
				{
					candy = board[row][col].at(2);
					board[row][col].at(2) = ' ';
					addscore(candy, 1);
				}
			}
		}
		system("cls");
		display(board);
	}
	else if (a == 2)
	{
		for (int row = 0; row < 9; row++)
		{
			for (int col = 0; col < 9; col++)
			{
				candy = board[row][col].at(2);
				board[row][col].at(2) = ' ';
				addscore(candy, 1);

			}
		}
		system("cls");
		display(board);
	}
	if (a == 1)
	{
		for (int row = 0; row < 9; row++)
		{
			for (int col = 0; col < 9; col++)
			{
				if (board[row][col].at(2) == rCandy.at(2))
				{
					board[row][col].at(1) = '(';
					board[row][col].at(3) = ')';
				}
			}
		}
		system("cls");
		display(board);
	}
	if (a == 3)
	{
		for (int row = 0; row < 9; row++)
		{
			for (int col = 0; col < 9; col++)
			{
				if (board[row][col].at(2) == rCandy.at(2))
				{
					board[row][col].at(1) = '[';
					board[row][col].at(3) = ']';
				}
			}
		}
		system("cls");
		display(board);
	}

}
//striped candy
void striped(string board[][9], int index, int flag)
{
	char candy;
	if (flag == 1)
	{
		for (int k = 0; k < 9; k++)
		{
			if (board[k][index].at(1) == '(' && board[k][index].at(3) == ')')
			{
				board[k][index].at(1) = ' ';
				board[k][index].at(3) = ' ';
				system("cls");
				display(board);
				delay(1);
			}
			candy = board[k][index].at(2);
			board[k][index].at(2) = ' ';
			addscore(candy, 1);
			system("cls");
			display(board);
			delay(1);
		}
		system("cls");
		display(board);
	}
	if (flag == 2)
	{
		for (int k = 0; k < 9; k++)
		{
			if (board[index][k].at(1) == '(' && board[index][k].at(3) == ')')
			{
				board[index][k].at(1) = ' ';
				board[index][k].at(3) = ' ';
				system("cls");
				display(board);
				delay(1);
			}
			candy = board[index][k].at(2);
			board[index][k].at(2) = ' ';
			addscore(candy, 1);
			system("cls");
			display(board);
			delay(1);
		}
		system("cls");
		display(board);
	}
	if (flag == 3)
	{
		for (int row = 0; row < 9; row++)
		{
			for (int col = 0; col < 9; col++)
			{
				if (board[row][col].at(1) == '(' && board[row][col].at(3) == ')')
				{
					for (int k = 0; k < 9; k++)
					{
						if (board[k][col].at(1) == '(' && board[k][col].at(3) == ')')
						{
							board[k][col].at(1) = ' ';
							board[k][col].at(3) = ' ';
							system("cls");
							display(board);
							delay(1);
						}
						candy = board[k][col].at(2);
						board[k][col].at(2) = ' ';
						addscore(candy, 1);
						system("cls");
						display(board);
						delay(1);
					}
				}
			}
		}
	}

}
//delay 
void delay(int a)
{
	int time, add = 0, i;
	time = a * 100000000;
	for (i = 0; i < time; i++)
	{
		add *= i;
		add++;
		add++;
	}
}
//score
void addscore(char ch,int a)
{
	switch (ch)
	{
	case 34:
		score = score + (candy1 * a);
		break;
	case 35:
		score = score + (candy2 * a);
		break;
	case 36:
		score = score + (candy3 * a);
		break;
	case 37:
		score = score + (candy4 * a);
		break;
	case 38:
		score = score + (candy5 * a);
		break;
	}
}