#include "state.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "snake_utils.h"

/* Helper function definitions */
static void set_board_at(game_state_t* state, unsigned int row, unsigned int col, char ch);
static bool is_tail(char c);
static bool is_head(char c);
static bool is_snake(char c);
static char body_to_tail(char c);
static char head_to_body(char c);
static unsigned int get_next_row(unsigned int cur_row, char c);
static unsigned int get_next_col(unsigned int cur_col, char c);
static void find_head(game_state_t* state, unsigned int snum);
static char next_square(game_state_t* state, unsigned int snum);
static void update_tail(game_state_t* state, unsigned int snum);
static void update_head(game_state_t* state, unsigned int snum);

/* Utility function to handle allocation failures. In this
   case we print a message and exit. */
static void allocation_failed() {
    fprintf(stderr, "Out of memory.\n");
    exit(1);
}


game_state_t* create_default_state() {
  game_state_t *default_state = malloc(sizeof(game_state_t));
  if (default_state == NULL) {
    allocation_failed();
  }
  default_state->num_rows = 18;
  default_state->board = malloc(18*sizeof(char*));
  if (default_state->board == NULL) {
    allocation_failed();
  }
  for (int i = 0; i < default_state->num_rows; i++) {
    default_state->board[i] = calloc(20+1, sizeof(char));
    if (default_state->board[i] == NULL) {
      allocation_failed();
    }
  }
  for (int i = 0; i < 20; i++) {
    default_state->board[0][i] = '#';
    default_state->board[17][i] = '#';
  }
  for (int i = 1; i < default_state->num_rows-1; i++) {
    default_state->board[i][0] = '#';
    default_state->board[i][19] = '#';
  }
  for (int i = 1; i < default_state->num_rows-1; i++) {
    for (int j = 1; j < 19; j++) {
      default_state->board[i][j] =  ' ';
    }
  }
  default_state->board[2][2] = 'd';
  default_state->board[2][3] = '>';
  default_state->board[2][4] = 'D';
  default_state->board[2][9] = '*';
  default_state->num_snakes = 1;
  default_state->snakes = malloc(1*sizeof(snake_t));
  if (default_state->snakes == NULL) {
    allocation_failed();
  }
  default_state->snakes[0].head_col = 4;
  default_state->snakes[0].head_row = 2;
  default_state->snakes[0].tail_col = 2;
  default_state->snakes[0].tail_row = 2;
  default_state->snakes[0].live = true;
  return default_state;
}

void free_state(game_state_t* state) {  
  free(state->snakes);
  for (int i = 0; i < state->num_rows; i++) {
    free(state->board[i]);
  }
  free(state->board);
  free(state);
  return;
}

void print_board(game_state_t* state, FILE* fp) {
  for (int i = 0; i < state->num_rows; i++) {
    for (int j = 0; j < strlen(state->board[i]); j++) {
      fprintf(fp, "%c", state->board[i][j]);
      if (j == strlen(state->board[i])-1) {
        fprintf(fp, "\n");
      }
    }
  }
  return;
}

/*
  Saves the current state into filename. Does not modify the state object.
*/
void save_board(game_state_t* state, char* filename) {
  FILE* f = fopen(filename, "w");
  print_board(state, f);
  fclose(f);
}


/*
  Helper function to get a character from the board
*/
char get_board_at(game_state_t* state, unsigned int row, unsigned int col) {
  return state->board[row][col];
}

/*
  Helper function to set a character on the board
*/
static void set_board_at(game_state_t* state, unsigned int row, unsigned int col, char ch) {
  state->board[row][col] = ch;
}

/*
  Returns true if c is part of the snake's tail.
  The snake consists of these characters: "wasd"
  Returns false otherwise.
*/
static bool is_tail(char c) {
  return c == 'w' || c == 'a' || c == 's' || c == 'd';
}

/*
  Returns true if c is part of the snake's head.
  The snake consists of these characters: "WASDx"
  Returns false otherwise.
*/
static bool is_head(char c) {
  return c == 'W' || c == 'A' || c == 'S' || c == 'D' || c == 'x';
}

/*
  Returns true if c is part of the snake.
  The snake consists of these characters: "wasd^<v>WASDx"
*/
static bool is_snake(char c) {
  return is_tail(c) || is_head(c) || c == '^' || c == '>' || c == '<' || c == 'v';
}

/*
  Converts a character in the snake's body ("^<v>")
  to the matching character representing the snake's
  tail ("wasd").
*/
static char body_to_tail(char c) {
  if (c == '^') {
    return 'w';
  } else if (c == '<') {
    return 'a';
  } else if (c == 'v') {
    return 's';
  } else if (c == '>') {
    return 'd';
  }
  return '?';
}

/*
  Converts a character in the snake's head ("WASD")
  to the matching character representing the snake's
  body ("^<v>").
*/
static char head_to_body(char c) {
  if (c == 'W') {
    return '^';
  } else if (c == 'A') {
    return '<';
  } else if (c == 'S') {
    return 'v';
  } else if (c == 'D') {
    return '>';
  }
  return '?';
}

/*
  Returns cur_row + 1 if c is 'v' or 's' or 'S'.
  Returns cur_row - 1 if c is '^' or 'w' or 'W'.
  Returns cur_row otherwise.
*/
static unsigned int get_next_row(unsigned int cur_row, char c) {
  if (c == 'v' || c == 's' || c == 'S') {
    return cur_row + 1;
  } else if (c == '^' || c == 'w' || c == 'W') {
    return cur_row - 1;
  }
  return cur_row;
}

/*
  Returns cur_col + 1 if c is '>' or 'd' or 'D'.
  Returns cur_col - 1 if c is '<' or 'a' or 'A'.
  Returns cur_col otherwise.
*/
static unsigned int get_next_col(unsigned int cur_col, char c) {
  if (c == '>' || c == 'd' || c == 'D') {
    return cur_col + 1;
  } else if (c == '<' || c == 'a' || c == 'A') {
    return cur_col - 1;
  }
  return cur_col;
}

/*
  Helper function for update_state. Return the character in the cell the snake is moving into.

  This function should not modify anything.
*/
static char next_square(game_state_t* state, unsigned int snum) {
  int found_snakes = 0;
  for (int i = 0; i < state->num_rows; i++) {
    for (int j = 0; j < strlen(state->board[i]); j++) {
      if (is_tail(get_board_at(state, i, j))) {
        if (found_snakes == snum) {
          char cur_char = get_board_at(state, i, j);
          int cur_row = i;
          int cur_col = j;
          while (!is_head(cur_char)) {
            cur_row = get_next_row(cur_row, cur_char);
            cur_col = get_next_col(cur_col, cur_char);
            cur_char = get_board_at(state, cur_row, cur_col);
          }
          cur_row = get_next_row(cur_row, cur_char);
          cur_col = get_next_col(cur_col, cur_char);
          cur_char = get_board_at(state, cur_row, cur_col);
          return cur_char;
        } else {
          found_snakes++;
        }
      }
    }
  }
}

/*
  Helper function for update_state. Update the head...

  ...on the board: add a character where the snake is moving

  ...in the snake struct: update the row and col of the head

  Note that this function ignores food, walls, and snake bodies when moving the head.
*/
static void update_head(game_state_t* state, unsigned int snum) {

  int cur_row = state->snakes[snum].head_row;
  int cur_col = state->snakes[snum].head_col;
  char cur_char = get_board_at(state, cur_row, cur_col);
  state->board[cur_row][cur_col] = head_to_body(cur_char);
  cur_row = get_next_row(cur_row, cur_char);
  cur_col = get_next_col(cur_col, cur_char);
  state->snakes[snum].head_row = cur_row;
  state->snakes[snum].head_col = cur_col;
  state->board[cur_row][cur_col] = cur_char;
}

/*
  Helper function for update_state. Update the tail...

  ...on the board: blank out the current tail, and change the new
  tail from a body character (^<v>) into a tail character (wasd)

  ...in the snake struct: update the row and col of the tail
*/
static void update_tail(game_state_t* state, unsigned int snum) {
  int cur_row = state->snakes[snum].tail_row;
  int cur_col = state->snakes[snum].tail_col;
  char cur_char = get_board_at(state, cur_row, cur_col);
  state->board[cur_row][cur_col] = ' ';
  cur_row = get_next_row(cur_row, cur_char);
  cur_col = get_next_col(cur_col, cur_char);
  state->snakes[snum].tail_row = cur_row;
  state->snakes[snum].tail_col = cur_col;
  state->board[cur_row][cur_col] = body_to_tail(state->board[cur_row][cur_col]);
}

void update_state(game_state_t* state, int (*add_food)(game_state_t* state)) {
  for (int i = 0; i < state->num_snakes; i++) {
    int cur_row = state->snakes[i].head_row;
    int cur_col = state->snakes[i].head_col;
    char cur_char = get_board_at(state, cur_row, cur_col);
    int old_row = cur_row;
    int old_col = cur_col;
    cur_row = get_next_row(cur_row, cur_char);
    cur_col = get_next_col(cur_col, cur_char);
    cur_char = get_board_at(state, cur_row, cur_col);
    if (cur_char == '#' || is_snake(cur_char)) {
      set_board_at(state, old_row, old_col, 'x');
      state->snakes[i].live = false;
    } else if (cur_char == '*') {
      update_head(state, i);
      add_food(state);
    } else {
      update_head(state, i);
      update_tail(state, i);
    }
  }
}


game_state_t* load_board(char* filename) {
  FILE* f = fopen(filename, "r");
  if (f == NULL) {
    return NULL;
  }

  int rows = 0;
  int cols = 1000000;
  char row[cols];
  while (fgets(row, cols, f)) {
    rows++;
  }
  
  game_state_t *state = (game_state_t*) malloc(sizeof(game_state_t));
  if (state == NULL) {
    allocation_failed();
  }

  state -> num_rows = rows;
  state -> board = calloc(rows, sizeof(char*));
  if (state->board == NULL) {
    allocation_failed();
  }
  
  f = fopen(filename, "r");
  
  for (int i = 0; i < rows; i++) {
    fgets(row, cols, f);
    int row_length = strlen(row);
    row[row_length-1] = '\0';
    state->board[i] = calloc(row_length, sizeof(char));
    if (state->board[i] == NULL) {
      allocation_failed();
    }
    strcpy(state->board[i], row);
  }

  fclose(f);
  return state;

}

/*
  Helper function for initialize_snakes.
  Given a snake struct with the tail row and col filled in,
  trace through the board to find the head row and col, and
  fill in the head row and col in the struct.
*/
static void find_head(game_state_t* state, unsigned int snum) {
  int current_tail_row = state->snakes[snum].tail_row;
  int current_tail_col = state->snakes[snum].tail_col;
  char current_pos = get_board_at(state, current_tail_row, current_tail_col);

  while (!is_head(current_pos)) {
    current_tail_row = get_next_row(current_tail_row, current_pos);
    current_tail_col = get_next_col(current_tail_col, current_pos);
    current_pos = get_board_at(state, current_tail_row, current_tail_col);
  }
  state->snakes[snum].head_row = current_tail_row;
  state->snakes[snum].head_col = current_tail_col;
}

game_state_t* initialize_snakes(game_state_t* state) {
  int num_snakes = 0;

  for (int row = 0; row < state -> num_rows; row++) {
    for (int col = 0; col < strlen(state -> board[row]); col++) {
      if (is_tail(get_board_at(state, row, col))) {
        num_snakes++;
      }
    }
  }

  state -> snakes = (snake_t *) malloc(sizeof(snake_t) * num_snakes);
  if (state->snakes == NULL) {
    allocation_failed();
  }

  state -> num_snakes = num_snakes;
  
  int num_snake_index = 0;
  for (int row = 0; row < state -> num_rows; row++) {
    for (int col = 0; col < strlen(state -> board[row]); col++) {
      if (is_tail(get_board_at(state, row, col))) {
        snake_t snake;
        snake.live = true;
        snake.tail_row = row;
        snake.tail_col = col;
        state -> snakes[num_snake_index] = snake;
        find_head(state, num_snake_index);
        num_snake_index++;
      }
    }
  }
  return state;
}
