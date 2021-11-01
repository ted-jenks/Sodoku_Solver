/*
File: main.cpp
Owner: Edward Jenks 
Username: ej3718
Last edited: 28/10/21
Last editor: Edward Jenks
Description: Main file to conatin all work for 'Intro to C++'
                coursework submission. The assignment is to program a reccursive
                sudoku solver and answer some questions on the result.
Comments: Commenting style taken from 'Problem Solving with C++ - Savitch'.
*/

#include <iostream>
#include <cstdio>
#include "sudoku.h"

using namespace std;

int main()
{
  char board[9][9];

  /* This section illustrates the use of the pre-supplied helper functions. */
  cout << "============= Pre-supplied functions =============\n\n";

  cout << "Calling load_board():\n";
  load_board("easy.dat", board);

  cout << '\n';
  cout << "Displaying Sudoku board with display_board():\n";
  display_board(board);
  cout << "Done!\n\n";

  /* This section demonstartes the is_complete() function working on pre-pprovided boards */
  cout << "=================== Question 1 ===================\n\n";

  load_board("easy.dat", board);
  cout << "Board is ";
  if (!is_complete(board))
  {
    cout << "NOT ";
  }
  cout << "complete.\n\n";

  load_board("easy-solution.dat", board);
  cout << "Board is ";
  if (!is_complete(board))
  {
    cout << "NOT ";
  }
  cout << "complete.\n\n";

  /* This section demonstartes the make_move() function working */
  cout << "=================== Question 2 ===================\n\n";

  load_board("easy.dat", board);

  // Should be OK
  cout << "Putting '1' into I8 is ";
  if (!make_move("I8", '1', board))
  {
    cout << "NOT ";
  }

  cout << "a valid move. The board is:\n";
  display_board(board);

  load_board("easy.dat", board);

  // Should not be OK (invalid character)
  cout << "Putting '0' into I8 is ";
  if (!make_move("I8", '0', board))
  {
    cout << "NOT ";
  }

  cout << "a valid move. The board is:\n";
  display_board(board);

  // Should be OK (use of lower case coordinate)
  cout << "Putting '1' into i8 is ";
  if (!make_move("i8", '1', board))
  {
    cout << "NOT ";
  }

  cout << "a valid move. The board is:\n";
  display_board(board);

  // Should not be OK (out of bounds)
  cout << "Putting '1' into G8 is ";
  if (!make_move("G8", '1', board))
  {
    cout << "NOT ";
  }

  cout << "a valid move. The board is:\n";
  display_board(board);

  // Should not be OK (invalid move)
  cout << "Putting '5' into I8 is ";
  if (!make_move("I8", '5', board))
  {
    cout << "NOT ";
  }

  cout << "a valid move. The board is:\n";
  display_board(board);

  /* This section demonstrates the save_board() function working */
  cout << "=================== Question 3 ===================\n\n";

  /* load and save easy.dat */
  load_board("easy.dat", board);
  display_board(board);
  if (save_board("easy-copy.dat", board))
  {
    cout << "Save board to 'easy-copy.dat' successful.\n";
  }
  else
  {
    cout << "Save board failed.\n";
  }
  cout << '\n';
  /* test saved version */
  load_board("easy-copy.dat", board);
  display_board(board);

  /* This section demonstrates the solve_board() function */
  cout << "=================== Question 4 ===================\n\n";

  /* solve easy.dat */
  load_board("easy.dat", board);
  if (solve_board(board))
  {
    cout << "The 'easy' board has a solution:\n";
    display_board(board);
  }
  else
  {
    cout << "A solution cannot be found.\n";
    display_board(board);
  }
  cout << '\n';

  /* solve medium.dat */
  load_board("medium.dat", board);
  if (solve_board(board))
  {
    cout << "The 'medium' board has a solution:\n";
    display_board(board);
  }
  else
  {
    cout << "A solution cannot be found.\n";
  }
  cout << '\n';

  /* This section shows extension functions built to assess the difficulty of the board with different methods */
  cout << "=================== Question 5 ===================\n\n";

  cout << "\n\n==================================================";

  cout << "\nINITIAL MOVE DIFFICULTY ASSESMENT\n";

  cout << "==================================================\n\n";

  load_board("easy.dat", board);
  initial_move_difficulty_assessment(board);

  load_board("medium.dat", board);
  initial_move_difficulty_assessment(board);

  load_board("mystery1.dat", board);
  initial_move_difficulty_assessment(board);

  load_board("mystery2.dat", board);
  initial_move_difficulty_assessment(board);

  load_board("mystery3.dat", board);
  initial_move_difficulty_assessment(board);

  cout << "\n\n==================================================";

  cout << "\nDEMO OF COUNTING FUNCTION CALLS NOT WORKING\n";

  cout << "==================================================\n\n";

  char position[] = {'A', '1'}; // starting A!
  cout << endl
       << "Starting at A1" << endl;

  int calls = 0; // variable to hold function calls
  load_board("mystery1.dat", board);
  solve_board(board, position, calls);
  cout << "Number of solve_board() calls for 'mystery1.dat': " << calls << endl; // print result

  calls = 0;
  load_board("mystery3.dat", board);
  solve_board(board, position, calls);
  cout << "Number of solve_board() calls for 'mystery3.dat': " << calls << endl;

  char position2[] = {'I', '2'}; // starting I2
  cout << endl
       << "Starting at I2" << endl;

  calls = 0;
  load_board("mystery1.dat", board);
  solve_board(board, position2, calls);
  cout << "Number of solve_board() calls for 'mystery1.dat': " << calls << endl;

  calls = 0;
  load_board("mystery3.dat", board);
  solve_board(board, position2, calls);
  cout << "Number of solve_board() calls for 'mystery3.dat': " << calls << endl;

  cout << "\n\n==================================================";

  cout << "\nALL STARTING POSITIONS WITH RANDOM DIGITS\n(this takes a while)\n";

  cout << "==================================================\n\n";

  /* calculate average function calls per board */
  load_board("easy.dat", board);
  cout << "Average (median) number of solve_board() calls for 'easy.dat': " << average_calls(board) << endl;

  load_board("medium.dat", board);
  cout << "Average (median)  number of solve_board() calls for 'medium.dat': " << average_calls(board) << endl;

  load_board("mystery1.dat", board);
  cout << "Average (median)  number of solve_board() calls for 'mystery1.dat': " << average_calls(board) << endl;

  load_board("mystery3.dat", board);
  cout << "Average (median) number of solve_board() calls for 'mystery3.dat': " << average_calls(board) << endl;

  return 0;
}
