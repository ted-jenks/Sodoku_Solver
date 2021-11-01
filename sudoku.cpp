/*
File: sudoku.cpp
Owner: Edward Jenks 
Username: ej3718
Last edited: 28/10/21
Last editor: Edward Jenks
Description: Function file to conatin all work for 'Intro to C++'
                coursework submission. The assignment is to program a reccursive
                sudoku solver and answer some questions on the result.
Comments: Commenting style taken from 'Problem Solving with C++ - Savitch'.
                Helper functions have been used in the design style to help break
                the code into sections and make it more readable.
*/

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>

#include <algorithm> // Used for shuffle function in question 5 extension.

#include "sudoku.h"

using namespace std;

/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------ HELPER FUNCTION DECLARATION -------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

/* Helper function to check cell coordinates are within bounds. True if in bounds  */
bool check_bounds(int column_index, int row_index);
/* Helper function to check for row and column repeats of a digit in a 9x9 board.  True if no repeats  */
bool check_row_column(const char board[9][9], int row_index, int column_index, char digit);
/* Helper function to check for repeats of a digit in a 3x3 subcell of a 9x9 grid. True if no repeats */
bool check_3x3(const char board[9][9], int row_index, int column_index, char digit);
/* Helper function to check a move is allowed. Returns true if it is and false if not */
bool is_valid(const char position[], char digit, const char board[9][9]);
/* Helper function to count the number of cells occupied by numbers in a board */
int count_cells(const char board[9][9]);
/* Helper function to determine constraints on cells in a board. Returns how many cells have 1, 2, 3... possible digits */
void possible_moves(const char board[9][9], int constraints[9]);
/* Helper function to read a cell from a position array */
char read_cell(const char board[9][9], const char position[]);
/* Function to check if a character is in 1-9 */
bool in_1_to_9(char character);
/* Helper function to write a character to a cell based on a position array */
void write_cell(char board[9][9], const char position[], char digit);
/* Helper function to count the number of cells occupied by numbers in a board */
int count_cells(const char board[9][9]);
/* Helper function to determine constraints on cells in a board. Returns how many cells have 1, 2, 3... possible digits */
void possible_moves(const char board[9][9], int constraints[9]);
/* Helper function to run custom starting position solves on the board */
bool custom_looper(char board[9][9], char character_order[9], char number_order[2], int &calls);
/* Helper function to build arrays for custom order for loops */
void loop_order_builder(char array[], char pos, char min, char max);
/* Helper function to copy a 9x9 board to another 9x9 board */
void copy_board(const char board[9][9], char board_copy[9][9]);
/* Helper function to check for null pointers */
void check_no_null(const char board[9][9]);

/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------PRE-SUPPLIED FUNCTIONS----------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

/* Pre-supplied function to load a Sudoku board from a file */
void load_board(const char *filename, char board[9][9])
{
  cout << "Loading Sudoku board from file '" << filename << "'... ";

  ifstream in(filename);
  if (!in)
  {
    cout << "Failed!\n";
  }
  assert(in);

  char buffer[512];

  int row = 0;
  in.getline(buffer, 512);
  while (in && row < 9)
  {
    for (int n = 0; n < 9; n++)
    {
      assert(buffer[n] == '.' || isdigit(buffer[n]));
      board[row][n] = buffer[n];
    }
    row++;
    in.getline(buffer, 512);
  }

  cout << ((row == 9) ? "Success!" : "Failed!") << '\n';
  assert(row == 9);
}

/* Internal helper function */
void print_frame(int row)
{
  if (!(row % 3))
  {
    cout << "  +===========+===========+===========+\n";
  }
  else
  {
    cout << "  +---+---+---+---+---+---+---+---+---+\n";
  }
}

/* Internal helper function */
void print_row(const char *data, int row)
{
  cout << (char)('A' + row) << " ";
  for (int i = 0; i < 9; i++)
  {
    cout << ((i % 3) ? ':' : '|') << " ";
    cout << ((data[i] == '.') ? ' ' : data[i]) << " ";
  }
  cout << "|\n";
}

/* Pre-supplied function to display a Sudoku board */
void display_board(const char board[9][9])
{
  cout << "    ";
  for (int r = 0; r < 9; r++)
  {
    cout << (char)('1' + r) << "   ";
  }
  cout << '\n';
  for (int r = 0; r < 9; r++)
  {
    print_frame(r);
    print_row(board[r], r);
  }
  print_frame(9);
}

/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------SUBMISSION STARTS HERE----------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

/* Helper function to check for null pointers */
void check_no_null(const char board[9][9])
{
  if (board == nullptr)
  {
    cerr << "Board is null ptr";
    exit(1);
  }
}

/* Function to check if a character is in 1-9 */
bool in_1_to_9(char character)
{
  if (static_cast<int>(character) > 48 && static_cast<int>(character) < 58)
    return true;
  return false;
}

/* Function to take board and report true if all positions are taken by digits */
bool is_complete(const char board[9][9])
{
  check_no_null(board);
  char position[2];
  /* check rows */
  for (position[0] = 'A'; position[0] <= 'I'; position[0]++)
  {
    /* check columns */
    for (position[1] = '1'; position[1] <= '9'; position[1]++)
    {
      /* if character is not in 1-9 */
      if (!in_1_to_9(read_cell(board, position)))
        return false; // board not complete
    }
  }
  return true; // if all charcters are in 1-9 the board is complete
}

/* Helper function to check cell coordinates are within bounds. Yrue if in bounds  */
bool check_bounds(int column_index, int row_index)
{
  /* check column and row bounds */
  if (column_index >= 0 && column_index <= 8 && row_index >= 0 && row_index <= 8)
    return true;
  return false;
}

/* Helper function to check for row and column repeats of a digit in a 9x9 board.  True if no repeats  */
bool check_row_column(const char board[9][9], int row_index, int column_index, char digit)
{
  check_no_null(board);
  /* check row/column repeats */
  for (int i = 0; i < 9; i++)
  {
    if (board[i][column_index] == digit || board[row_index][i] == digit)
      return false;
  }
  return true;
}

/* Helper function to check for repeats of a digit in a 3x3 subcell of a 9x9 grid. True if no repeats */
bool check_3x3(const char board[9][9], int row_index, int column_index, char digit)
{
  check_no_null(board);
  /* identify the 3x3 subsquare of the cell */
  int subsquare_row = row_index / 3, subsquare_column = column_index / 3;

  /* iterate over subsquare rows */
  for (int i = (3 * subsquare_row); i < ((3 * subsquare_row) + 3); i++)
  {
    /* iterate over subsquare columns */
    for (int j = (3 * subsquare_column); j < ((3 * subsquare_column) + 3); j++)
    {
      /* disallow repeats */
      if (board[i][j] == digit)
        return false;
    }
  }
  return true;
}

/* Helper function to check a move is allowed. Returns true if it is and false if not */
bool is_valid(const char position[], char digit, const char board[9][9])
{
  check_no_null(board);
  int column_index = position[1] - 49, row_index = toupper(static_cast<int>(position[0])) - 65;

  /* if cell already full */
  if (!in_1_to_9(digit))
    return false;

  /* check coordinates are in bounds */
  if (!check_bounds(column_index, row_index))
    return false;

  /* check move follows sudoku rules */
  if (!check_row_column(board, row_index, column_index, digit) || !check_3x3(board, row_index, column_index, digit))
    return false;

  return true;
}

/* If position is invalid, return false, and board should be unaltered 
   otherwise, the return value of the function should be true and board should be updated */
bool make_move(const char position[], char digit, char board[9][9])
{
  check_no_null(board);
  /* check move is valid */
  if (!is_valid(position, digit, board))
    return false;

  /* make move */
  write_cell(board, position, digit);
  return true; // confirm that move is valid
}

/* Function to save board to file. Returns true if successful and false if there's a failure */
bool save_board(const char filename[], const char board[9][9])
{
  check_no_null(board);
  char position[2];
  ofstream out_stream;

  /* open/create the file */
  out_stream.open(filename);

  /* check file has been opened successfully */
  if (!out_stream)
    return false;

  /* 'put' board in file */
  for (position[0] = 'A'; position[0] <= 'I'; position[0]++)
  {
    for (position[1] = '1'; position[1] <= '9'; position[1]++)
    {
      out_stream.put(read_cell(board, position));
    }
    out_stream.put('\n');
  }

  /* check for curruption */
  if (!out_stream)
    return false;

  /* close stream */
  out_stream.close();
  return true;
}

/* Helper function to read cell from board from position array */
char read_cell(const char board[9][9], const char position[])
{
  check_no_null(board);
  int row_index = toupper(static_cast<int>(position[0])) - 65, column_index = position[1] - 49;
  if (!check_bounds(column_index, row_index))
  {
    cerr << "Read index out of bounds";
    exit(1);
  }
  return board[row_index][column_index];
}

/* Helper function to write a character to a cell based on a position array */
void write_cell(char board[9][9], const char position[], char digit)
{
  check_no_null(board);
  int row_index = toupper(static_cast<int>(position[0])) - 65, column_index = position[1] - 49;
  if (!check_bounds(column_index, row_index))
  {
    cerr << "Write index out of bounds";
    exit(1);
  }
  if (in_1_to_9(read_cell(board, position)) && in_1_to_9(digit))
  {
    cerr << "Cannot overwrite filled cell";
    exit(1);
  }
  board[row_index][column_index] = digit;
}

/* Function to solve board. Returns true on success, false on failure. */
bool solve_board(char board[9][9])
{
  check_no_null(board);
  char position[2], cell_value;

  /* iterate rows */
  for (position[0] = 'A'; position[0] <= 'I'; position[0]++)
  {
    /* iterate columns */
    for (position[1] = '1'; position[1] <= '9'; position[1]++)
    {
      cell_value = read_cell(board, position);

      /* if cell doesn't have a character in 1-9 */
      if (!in_1_to_9(cell_value))
      {
        /* iterate over characters */
        for (char digit = '1'; digit <= '9'; digit++)
        {
          /* if move is valid, make the move */
          if (make_move(position, digit, board))
          {
            if (is_complete(board))
              return true; // solver finished
            /* recursively call to solve next cell (if possible) */
            if (solve_board(board))
              return true; // reached for a valid solution
            /* if no digits work, replace cell with . character */
            write_cell(board, position, '.');
          }
        }
        return false; // invalid solution
      }
    }
  }
  return false; // safety feature, only reached if full sudoku is passed to solver. returns false as solution is not checked.
}

/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ----------------------------------------------------------------------QUESTION 5  EXTENSIONS----------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

/* Helper function to count the number of cells occupied by numbers in a board */
int count_cells(const char board[9][9])
{
  check_no_null(board);
  int count = 0;    // cell count variable
  char position[2]; // array to hold coordinates
  /* check rows */
  for (position[0] = 'A'; position[0] <= 'I'; position[0]++)
  {
    /* check columns */
    for (position[1] = '1'; position[1] <= '9'; position[1]++)
    {
      /* if character is  in 1-9 */
      if (in_1_to_9(read_cell(board, position)))
      {
        count++; // add to count
      }
    }
  }
  return count;
}

/* Helper function to determine constraints on cells in a board. Fills array how many cells have 1, 2, 3... possible digits for each index */
void possible_moves(const char board[9][9], int constraints[9])
{
  check_no_null(board);
  int count;        // counter variable
  char position[2]; // array to hold coordinates

  /* check rows */
  for (position[0] = 'A'; position[0] <= 'I'; position[0]++)
  {
    /* check columns */
    for (position[1] = '1'; position[1] <= '9'; position[1]++)
    {
      /* check in 1 - 9 */
      if (!in_1_to_9(read_cell(board, position)))
      {
        count = 0; // reset count
        /* check how many digits are valid for cell */
        for (char digit = '1'; digit <= '9'; digit++)
        {
          if (is_valid(position, digit, board))
            count++;
        }
        if (count != 0)
          constraints[count - 1]++; // add 1 to the apprpriate entry of the 'constraints' array.
      }
    }
  }
}

/* Helper function to create an empty board */
void create_empty_board(char board[9][9])
{
  check_no_null(board);
  char position[2];
  /* initialise board empty */
  for (position[0] = 'A'; position[0] <= 'I'; position[0]++)
  {
    for (position[1] = '1'; position[1] <= '9'; position[1]++)
    {
      write_cell(board, position, '.');
    }
  }
}

/* Function to asses the difficulty of the boards based on how many initial moves can be made */
int initial_move_difficulty_assessment(char board[9][9])
{
  check_no_null(board);
  cout << "Initial Difficulty Assessment Based on Possible Initial Moves: ";
  int constraints[9] = {} /* constraint array */, initial_moves = 0, /* how many initial moves allowed?*/ //
      out_of_ten /* board difficulty rating out of ten */;
  possible_moves(board, constraints);

  /* create copy of board */
  char board_copy[9][9];
  create_empty_board(board_copy);
  copy_board(board, board_copy);
  /* check board is possible */
  if (!solve_board(board_copy))
  {
    cout << "\n\n------------------------------------------\n";
    cout << "                IMPOSSIBLE                \n";
    cout << "------------------------------------------\n\n\n\n";
    return 0;
  }

  /* interperet constraint results */
  for (int i = 0; i < 9; i++)
  {
    initial_moves += constraints[i] * (i + 1);
  }

  out_of_ten = (((initial_moves - 190) / 36.) * 10); // difficulty rating based on puzzles provided
  /* print difficulty bar */
  cout << "\n\n------------------------------------------\n";
  cout << " Easy ";
  for (int i = 0; i < 10; i++)
  {
    if (i < out_of_ten)
      cout << "|||";
    else
      cout << "   ";
  }
  cout << " Hard\n";
  cout << "------------------------------------------\n\n\n\n";

  return initial_moves;
}

/* Helper function to run custom starting position solves on the board */
bool custom_looper(char board[9][9], char character_order[9], char number_order[2], int &calls)
{
  check_no_null(board);
  char position[2], cell_value;
  calls++; // counter for number of reccursive calls to solve
  /* iterate rows */
  for (int i = 0; i <= 8; i++)
  {
    position[0] = character_order[i]; // select correct row

    /* iterate columns */
    for (int j = 0; j <= 8; j++)
    {
      position[1] = number_order[j];           // select correct column
      cell_value = read_cell(board, position); // read the cell
      /* if cell doesn't have a character in 1-9 */
      if (!in_1_to_9(cell_value))
      {
        char a[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'}; // array of possible digits
        random_shuffle(&a[0], &a[8]);                             // shuffle digit order

        /* iterate through digits */
        for (int k = 0; k < 9; k++)
        {
          char digit = a[k]; // select correct digit
          /* if move is valid, make the move */
          if (make_move(position, digit, board))
          {
            if (is_complete(board))
              return true;
            /* recursively call to solve next cell (if possible) */
            if (custom_looper(board, character_order, number_order, calls))
              return true; // reached for a valid solution
            /* if no digits work, replace cell with . character */
            write_cell(board, position, '.');
          }
        }
        return false; // invalid solution
      }
    }
  }
  return false; // safety feature, only reached if full sudoku is passed to solver. returns false as solution is not checked.
}

/* Helper function to build arrays for custom order for loops */
void loop_order_builder(char array[], char pos, char min, char max)
{
  int i = 0; // counter variable
  /* set array up with correct order */
  for (char character = pos; character <= max; character++)
  {
    array[i] = character;
    i++;
  }
  /* consider wrapping at edge */
  for (char character = min; character < pos; character++)
  {
    array[i] = character;
    i++;
  }
}

/* Overload function for solve_board that takes a starting position and call counter */
bool solve_board(char board[9][9], char position[2], int &calls)
{
  check_no_null(board);
  char character_order[9], number_order[9];

  loop_order_builder(character_order, static_cast<char>(toupper(static_cast<int>(position[0]))), 'A', 'I'); // build row order
  loop_order_builder(number_order, position[1], '1', '9');                                                  // build column array

  /* run the positional board solver */
  if (custom_looper(board, character_order, number_order, calls))
    return true;
  return false;
}

/* Helper function to copy a 9x9 board to another 9x9 board */
void copy_board(const char board[9][9], char board_copy[9][9])
{
  check_no_null(board);
  check_no_null(board_copy);
  char position[2];

  /* copy rows */
  for (position[0] = 'A'; position[0] <= 'I'; position[0]++)
  {
    /* copy columns */
    for (position[1] = '1'; position[1] <= '9'; position[1]++)
    {
      write_cell(board_copy, position, read_cell(board, position)); // write to board copy
    }
  }
}

/* A function to try every starting position for a board and return the median number of calls required to solve */
int average_calls(char board[9][9])
{
  check_no_null(board);
  char position[2], board_copy[9][9];
  int count = 0, running_total = 0, calls, call_array[81];

  /* trial all rows */
  for (position[0] = 'A'; position[0] <= 'I'; position[0]++)
  {
    /* trial all columns */
    for (position[1] = '1'; position[1] <= '9'; position[1]++)
    {
      create_empty_board(board_copy);
      copy_board(board, board_copy); // create a copy of the board
      calls = 0;
      solve_board(board_copy, position, calls); // solve on the board copy
      /* record the function calls required */
      if (calls != 0)
      {
        call_array[count] = calls;
        running_total += calls;
        count++;
      }
    }
  }
  sort(&call_array[0], &call_array[80]);
  int median = call_array[40];
  //int mean = running_total / count;
  //int min = call_array[0];
  return median; // return (this can be edited for mean, min or median)
}
