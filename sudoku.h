/*
File: sudoku.h
Owner: Edward Jenks 
Username: ej3718
Last edited: 28/10/21
Last editor: Edward Jenks
Description: Header file with neccesary declarations for the first 'Intro to C++' 
                coursework submission. The assignment is to program a reccursive
                sudoku solver and answer some questions on the result.
Comments: Commenting style taken from 'Problem Solving with C++ - Savitch'.
*/

#ifndef SUDOKU_H // Safety feature
#define SUDOKU_H

/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------SUBMISSION DECLARATIONS---------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

void load_board(const char *filename, char board[9][9]);
// Pre-provided function to open a board file.
// Precondition: Empty board and filename passed to function.
// Postcondition: Save board loaded in board, success message printed.

void display_board(const char board[9][9]);
// Pre-provided function to display a board.
// Precondition: Board passed to funciton.
// Postcondition: Board printed.

bool is_complete(const char board[9][9]);
// Function to assess if a board is complete.
// Precondition: Pass board of interest to function.
// Postcondition: Returns true if the board is complete.

bool make_move(const char position[2], char digit, char board[9][9]);
// Function to make a move on a sudoku board.
// Precondition: The board and digit/position of move are passed to the functiion.
// Postcondition: Returns true if move is allowed and board is left in 'moved state'.
//                 Else returns false and board unchanged

bool save_board(const char filename[], const char board[9][9]);
// Function to save a board to a file in the working directory.
// Precondition: A filename string and board to save must be passed to the function.
// Postcondition: Returns true if save is successful. Board is saved to file of
//                 filename provided.

bool solve_board(char board[9][9]);
// Function to return the average (median) number of recurrsive function calls taken to
//                 solve a board using the algorithm starting from all possible cell
//                 positions.
// Precondition: The initial board to be investigated is passed to function
// Postcondition: The average number of solve_board() function calls to solve is returned.
//                 The board initially passed to the function remains unchanged.

/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------QUESTION 5  EXTENSIONS----------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

int initial_move_difficulty_assessment(char board[9][9]);
// Function to assess board difficulty based on the constraints of the initial setup.
// Precondition: The initial board is passed to the function.
// Postcondition: A bar representing difficulty based on the number of initial moves
//                 that are possible is printed. If the board is not possible, this is
//                 printed. Returns number of initial moves possible.

bool solve_board(char board[9][9], char position[2], int &calls);
// Overload function of solve_board to take a starting position and record the number
//                 of function calls in a reference variable.
// Precondition: The initial board, a starting cell array and a variable to hold the number
//                 of function calls are passed to the function
// Postcondition: Returns true if the board is solvable. Board left in solved state if
//                 applicable and unchanged if not. Number of function calls left in 'calls'.

int average_calls(char board[9][9]);
// Function to return the average (median) number of recurrsive function calls taken to
//                 solve a board using the algorithm starting from all possible cell
//                 positions.
// Precondition: The initial board to be investigated is passed to function.
// Postcondition: The average number of solve_board() function calls to solve is returned.
//                 The board initially passed to the function remains unchanged.

#endif