#include <stdio.h>
#include <string.h>

#include "snake_utils.h"
#include "game.h"

int main(int argc, char *argv[]) {
  bool io_stdin = false;
  char *in_filename = NULL;
  char *out_filename = NULL;
  game_t *game = NULL;

  // Parse arguments
  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-i") == 0 && i < argc - 1) {
      if (io_stdin) {
        fprintf(stderr, "Usage: %s [-i filename | --stdin] [-o filename]\n", argv[0]);
        return 1;
      }
      in_filename = argv[i + 1];
      i++;
      continue;
    } else if (strcmp(argv[i], "--stdin") == 0) {
      if (in_filename != NULL) {
        fprintf(stderr, "Usage: %s [-i filename | --stdin] [-o filename]\n", argv[0]);
        return 1;
      }
      io_stdin = true;
      continue;
    }
    if (strcmp(argv[i], "-o") == 0 && i < argc - 1) {
      out_filename = argv[i + 1];
      i++;
      continue;
    }
    fprintf(stderr, "Usage: %s [-i filename | --stdin] [-o filename]\n", argv[0]);
    return 1;
  }

  // Do not modify anything above this line.

  /* Task 7 */

  // Read board from file, or create default board
  //


  if (in_filename != NULL) {
      FILE* file = fopen(in_filename, "r");
    // TODO: Load the board from in_filename
    if(file == NULL) {
        return -1;
  }
    game_t *game = load_board(file);
  initialize_snakes(game);
  fclose(file);
  } else if (io_stdin) {
    // TODO: Load the board from stdin
    game_t *game = load_board(stdin);
    // TODO: Then call initialize_snakes on the game you made
    initialize_snakes(game);
  } else {
    // TODO: Create default game
    game_t *game = create_default_game();
  }

  // TODO: Update game. Use the deterministic_food function
  // (already implemented in snake_utils.h) to add food.
  //
  update_game(game, deterministic_food);

  // Write updated board to file or stdout
  if (out_filename != NULL) {
    // TODO: Save the board to out_filename
    FILE* file_out = fopen(out_filename, "w");
    print_board(game,file_out);
    fclose(file_out);
  } else {
    // TODO: Print the board to stdout
    print_board(game, stdout);
  }

  // TODO: Free the game
    free_game(game);
  return 0;
}
