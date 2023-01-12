#include <stdio.h>
#include <string.h>

#include "snake_utils.h"
#include "state.h"

int main(int argc, char* argv[]) {
  char* in_filename = NULL;
  char* out_filename = NULL;
  game_state_t* state = NULL;

  // Parse arguments
  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-i") == 0 && i < argc - 1) {
      in_filename = argv[i + 1];
      i++;
      continue;
    }
    if (strcmp(argv[i], "-o") == 0 && i < argc - 1) {
      out_filename = argv[i + 1];
      i++;
      continue;
    }
    fprintf(stderr, "Usage: %s [-i filename] [-o filename]\n", argv[0]);
    return 1;
  }


  // Read board from file, or create default board
  if (in_filename != NULL) {
    // Load the board from in_filename
    state = load_board(in_filename);
    // If the file doesn't exist, return -1
    if (!fopen(in_filename, "r")) {
      return -1;
    }
    // Then call initialize_snakes on the state you made
    state = initialize_snakes(state);
  } else {
    // Create default state
    state = create_default_state();
  }

  // Update state. Use the deterministic_food function
  // (already implemented in snake_utils.h) to add food.
  update_state(state, deterministic_food);

  // Write updated board to file or stdout
  if (out_filename != NULL) {
    // TODO: Save the board to out_filename
    save_board(state, out_filename);
  } else {
    // Print the board to stdout
    print_board(state, "stdout");
  }

  // Free the state
  free_state(state);
  return 0;
}
