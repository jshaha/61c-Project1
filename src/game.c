#include "game.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "snake_utils.h"

/* Helper function definitions */
static void set_board_at(game_t *game, unsigned int row, unsigned int col, char ch);
static bool is_tail(char c);
static bool is_head(char c);
static bool is_snake(char c);
static char body_to_tail(char c);
static char head_to_body(char c);
static unsigned int get_next_row(unsigned int cur_row, char c);
static unsigned int get_next_col(unsigned int cur_col, char c);
static void find_head(game_t *game, unsigned int snum);
static char next_square(game_t *game, unsigned int snum);
static void update_tail(game_t *game, unsigned int snum);
static void update_head(game_t *game, unsigned int snum);

/* Task 1 */
game_t *create_default_game() {
  // TODO: Implement this function.

  game_t *game = malloc(sizeof(game_t));
    if (game == NULL) {
        free(game);
        printf("*game memory allocated failed\n");
        return NULL;
    }
    game->num_rows = 18;
    game->board = malloc(18 * sizeof(char*));
    if (game->board == NULL) {
        free(game);
        printf("game->board memory failed\n");
        return NULL;
    }
    game->num_snakes = 1;

    //struct defining
    game->snakes = malloc(sizeof(snake_t));
    if (game->snakes == NULL) {
        free(game->board);
        free(game);
        printf("snake struct memory allocation failed\n");
        return NULL;
    }
    game->snakes[0].tail_row = 2;
    game->snakes[0].tail_col = 2;
    game->snakes[0].head_row = 2;
    game->snakes[0].head_col = 4;
    game->snakes[0].live = true;

    //game roof
    game->board[0] = malloc(22 * sizeof(char));
    strcpy(game->board[0], "####################\n");

    //border of board & starting point
    for(int i = 1; i < 17; i++) { 
        game->board[i] = malloc(22 * sizeof(char));
        if (i == 2) { 
            strcpy(game->board[i], "# d>D    *         #\n");
        } else { 
            strcpy(game->board[i], "#                  #\n");
        }
    }

    // game floor
    game->board[17] = malloc(22 * sizeof(char));
    strcpy(game->board[17], "####################\n");

 return game;
}

/* Task 2 */
void free_game(game_t *game) {
  // TODO: Implement this function.

    for (int i = 0; i < game->num_rows; i++) { 
        free(game->board[i]);
    }
    free(game->board);
    free(game->snakes);
    free(game);

  return;
}

/* Task 3 */
void print_board(game_t *game, FILE *fp) {
  // TODO: Implement this function.
  for(int i = 0; i < game->num_rows; i++) {
    fprintf(fp,"%s", game->board[i]);
  }
  return;
}

/*
  Saves the current game into filename. Does not modify the game object.
  (already implemented for you).
*/
void save_board(game_t *game, char *filename) {
  FILE *f = fopen(filename, "w");
  print_board(game, f);
  fclose(f);
}

/* Task 4.1 */

/*
  Helper function to get a character from the board
  (already implemented for you).
*/
char get_board_at(game_t *game, unsigned int row, unsigned int col) { return game->board[row][col]; }

/*
  Helper function to set a character on the board
  (already implemented for you).
*/
static void set_board_at(game_t *game, unsigned int row, unsigned int col, char ch) {
  game->board[row][col] = ch;
}

/*
  Returns true if c is part of the snake's tail.
  The snake consists of these characters: "wasd"
  Returns false otherwise.
*/
static bool is_tail(char c) {
  // TODO: Implement this function.
  if (c == 'w' || c == 'a'|| c == 's' || c == 'd') {
  return true;
  }
  return false; 
}

/*
  Returns true if c is part of the snake's head.
  The snake consists of these characters: "WASDx"
  Returns false otherwise.
*/
static bool is_head(char c) {
  // TODO: Implement this function.
    if (c == 'W' || c == 'A'|| c == 'S' || c == 'D' || c == 'x') {
  return true;
  }
  return false;
}

/*
  Returns true if c is part of the snake.
  The snake consists of these characters: "wasd^<v>WASDx"
*/
static bool is_snake(char c) {
  // TODO: Implement this function.
if (c == 'w' || c == 'a'|| c == 's' || c == 'd' || c == 'x' || c == 'W' || c == 'A'|| c == 'S' || c == 'D'|| c == '^' || c == '<' || c == '>' || c == 'v') {
  return true;
  }
  return false;
}


/*
  Converts a character in the snake's body ("^<v>")
  to the matching character representing the snake's
  tail ("wasd").
*/
static char body_to_tail(char c) {
  // TODO: Implement this function.
  char body[4] = {'^', '<', 'v', '>'};
  char tail[4] = {'w', 'a', 's', 'd'};
  for(int i = 0; i < 4; i++) {
    if(c == body[i]) {
        return tail[i];
    }
  }
  return c;
}


/*
  Converts a character in the snake's head ("WASD")
  to the matching character representing the snake's
  body ("^<v>").
*/
static char head_to_body(char c) {
  // TODO: Implement this function.
  char head[4] = {'W', 'A', 'S', 'D'};
  char body[4] = {'^', '<', 'v', '>'};
  for(int i = 0; i < 4; i++) {
    if(c == head[i]) {
        return body[i];
    }
  }
  return c;
}

/*
  Converts a character in the snake's head ("WASD")
  to the matching character representing the snake's
  body ("^<v>").
*/

/*
  Returns cur_row + 1 if c is 'v' or 's' or 'S'.
  Returns cur_row - 1 if c is '^' or 'w' or 'W'.
  Returns cur_row otherwise.
*/
static unsigned int get_next_row(unsigned int cur_row, char c) {
  // TODO: Implement this function.
  char allowed[] = {'v' , 's' , 'S'};
  char disallowed[] = {'^', 'w', 'W'};
  for (int i = 0; i < 3; i++) {
    if(c == allowed[i]) {
        return cur_row + 1;
    } else {
        if(c == disallowed[i]) {
            return cur_row - 1;
        }
        }
    }
  return cur_row;
}

/*
  Returns cur_col + 1 if c is '>' or 'd' or 'D'.
  Returns cur_col - 1 if c is '<' or 'a' or 'A'.
  Returns cur_col otherwise.
*/
static unsigned int get_next_col(unsigned int cur_col, char c) {
  // TODO: Implement this function.
  char allowed[] = {'>' , 'd' , 'D'};
  char disallowed[] = {'<', 'a', 'A'};
  for (int i = 0; i < 3; i++) {
    if(c == allowed[i]) {
        return cur_col + 1;
    } else {
        if(c == disallowed[i]) {
            return cur_col - 1;
        }
    }
    }
  return cur_col;
}


/*
  Task 4.2

  Helper function for update_game. Return the character in the cell the snake is moving into.

  This function should not modify anything.
*/
static char next_square(game_t *game, unsigned int snum) {
  // TODO: Implement this function.
    unsigned int snake_row = game->snakes[snum].head_row;
    unsigned int snake_col = game->snakes[snum].head_col;
    char snake_char = get_board_at(game, snake_row, snake_col);

  return get_board_at(game,get_next_row(snake_row, snake_char), get_next_col(snake_col, snake_char));
}

/*
  Task 4.3:

  Helper function for update_game. Update the head...

  ...on the board: add a character where the snake is moving

  ...in the snake struct: update the row and col of the head

  Note that this function ignores food, walls, and snake bodies when moving the head.
*/
static void update_head(game_t *game, unsigned int snum) {
  // TODO: Implement this function.
    unsigned int snake_row = game->snakes[snum].head_row;
    unsigned int snake_col = game->snakes[snum].head_col;
    char snake_char = get_board_at(game, snake_row, snake_col);

    
    set_board_at(game, snake_row, snake_col, head_to_body(snake_char)); 
    game->snakes[snum].head_row = get_next_row(snake_row, snake_char);
    game->snakes[snum].head_col = get_next_col(snake_col, snake_char);

   set_board_at(game, game->snakes[snum].head_row, game->snakes[snum].head_col, snake_char);
}

/*
  Task 4.4

  Helper function for update_game. Update the tail...

  ...on the board: blank out the current tail, and change the new
  tail from a body character (^<v>) into a tail character (wasd)

  ...in the snake struct: update the row and col of the tail
*/
static void update_tail(game_t *game, unsigned int snum) {
  // TODO: Implement this function.
    unsigned int tail_row = game->snakes[snum].tail_row;
    unsigned int tail_col = game->snakes[snum].tail_col;
    char tail_char = get_board_at(game, tail_row, tail_col);
    unsigned int next_row = get_next_row(tail_row, tail_char);
    unsigned int next_col = get_next_col(tail_col, tail_char);
    set_board_at(game, tail_row, tail_col, ' ');
    char replaced = get_board_at(game, next_row, next_col);
    set_board_at(game, next_row, next_col, body_to_tail(replaced));
    game->snakes[snum].tail_row = next_row;
    game->snakes[snum].tail_col = next_col;
    return;
}

/* Task 4.5 */
void update_game(game_t *game, int (*add_food)(game_t *game)) {
  // TODO: Implement this function.
  for (unsigned int i = 0; i < game->num_snakes; i++) { 
      if (game->snakes[i].live == false) { 
          continue;
      }
      char next = next_square(game, i);
      if (next == '#' || is_snake(next)) { 
          set_board_at(game, game->snakes[i].head_row, game->snakes[i].head_col, 'x');
          game->snakes[i].live = false;
          continue;
      } else if (next == '*') { 
          update_head(game, i);
          add_food(game);
      } else {
          update_head(game, i);
          update_tail(game, i);
      }
  }
  return;
}

/* Task 5.1 */
char *read_line(FILE *fp) {
  // TODO: Implement this function.
    size_t buf_size = 64;
    char* buffer = malloc(buf_size);
    if (buffer == NULL) { 
        printf("buffer malloc failed");
        free(buffer);
        return NULL;
    }

    if (fgets(buffer, (int)buf_size, fp) == NULL) { 
        free(buffer);
        return NULL;
    }

    size_t len = strlen(buffer);
    while (len > 0 && buffer[len-1] != '\n' && len > 0) {
        buf_size *= 2;
        char* double_buf = realloc(buffer, buf_size);
        if (double_buf == NULL) { 
            printf("double_buf realloc failed");
            free(buffer);
            return NULL;
        } else { 
            buffer = double_buf;
        }

        char* result = fgets(buffer + len, (int)(buf_size - len), fp);
        if (result == NULL) { 
            break;
        }
        len = strlen(buffer);
    }

  return buffer;
}

/* Task 5.2 */
game_t *load_board(FILE *fp) {
  // TODO: Implement this function.
  game_t *game = malloc(sizeof(game_t));
    if (game == NULL) {
        printf("*game memory allocated failed\n");
        free(game);
        return NULL;
    }
    game->board = NULL;
    game->num_rows = 0;
    char *line; 

    while ((line = read_line(fp)) != NULL) {
        game->num_rows++;
        game->board = realloc(game->board, game->num_rows * sizeof(char*));
    if (game->board == NULL) 
    {
        for (int k = 0; k < game->num_rows - 1; k++) { 
            free(game->board[k]);
        };
            free(line);
            free(game->board);
            free(game);
        printf("game->board memory failed\n");
        return NULL;
    }
    game->board[game->num_rows - 1] = line;
    }
    game->snakes = NULL;
    game->num_snakes = 0;
    return game;
}

/*
  Task 6.1

  Helper function for initialize_snakes.
  Given a snake struct with the tail row and col filled in,
  trace through the board to find the head row and col, and
  fill in the head row and col in the struct.
*/
static void find_head(game_t *game, unsigned int snum) {
  // TODO: Implement this function.
    unsigned int curr_tail_row = game->snakes[snum].tail_row;
    unsigned int curr_tail_col = game->snakes[snum].tail_col; 
    char tail_char = get_board_at(game, curr_tail_row, curr_tail_col);
    unsigned int new_tail_row;
    unsigned int new_tail_col;
    while(is_head(tail_char) == false) {
        new_tail_row = get_next_row(curr_tail_row, tail_char);
        new_tail_col = get_next_col(curr_tail_col, tail_char);
        curr_tail_row = new_tail_row;
        curr_tail_col = new_tail_col;
        tail_char = get_board_at(game, curr_tail_row, curr_tail_col);
    }
    game->snakes[snum].head_row = curr_tail_row;
    game->snakes[snum].head_col = curr_tail_col;
  return;
}

/* Task 6.2 */
game_t *initialize_snakes(game_t *game) {
  // TODO: Implement this function.

    game->num_snakes = 0;
    game->snakes = NULL;
    for(int i = 0; i < game->num_rows;i++) {
        for(int j = 0; game->board[i][j] != '\0'; j++) {
            char curr_char = game->board[i][j];
            if(is_tail(curr_char)) {
                game->num_snakes++;
                game->snakes = realloc(game->snakes, game->num_snakes * sizeof(snake_t));
                if (game->snakes == NULL) {
                    printf("snake struct memory allocation failed\n");
                    free(game->snakes);
                    return NULL;
                    }
                
                game->snakes[game->num_snakes - 1].tail_row = (unsigned int)i;
                game->snakes[game->num_snakes - 1].tail_col = (unsigned int)j;
                find_head(game, game->num_snakes - 1);
                game->snakes[game->num_snakes - 1].live = true;
            }
        }
    }
  return game;
}
