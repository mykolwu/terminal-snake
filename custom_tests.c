#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "asserts.h"
// Necessary due to static functions in state.c
#include "state.c"

/* Look at asserts.c for some helpful assert functions */

int greater_than_forty_two(int x) { return x > 42; }

bool is_vowel(char c) {
  char* vowels = "aeiouAEIOU";
  for (int i = 0; i < strlen(vowels); i++) {
    if (c == vowels[i]) {
      return true;
    }
  }
  return false;
}

/*
  Example 1: Returns true if all test cases pass. False otherwise.
    The function greater_than_forty_two(int x) will return true if x > 42. False otherwise.
    Note: This test is NOT comprehensive
*/
bool test_greater_than_forty_two() {
  int testcase_1 = 42;
  bool output_1 = greater_than_forty_two(testcase_1);
  if (!assert_false("output_1", output_1)) {
    return false;
  }

  int testcase_2 = -42;
  bool output_2 = greater_than_forty_two(testcase_2);
  if (!assert_false("output_2", output_2)) {
    return false;
  }

  int testcase_3 = 4242;
  bool output_3 = greater_than_forty_two(testcase_3);
  if (!assert_true("output_3", output_3)) {
    return false;
  }

  return true;
}

/*
  Example 2: Returns true if all test cases pass. False otherwise.
    The function is_vowel(char c) will return true if c is a vowel (i.e. c is a,e,i,o,u)
    and returns false otherwise
    Note: This test is NOT comprehensive
*/
bool test_is_vowel() {
  char testcase_1 = 'a';
  bool output_1 = is_vowel(testcase_1);
  if (!assert_true("output_1", output_1)) {
    return false;
  }

  char testcase_2 = 'e';
  bool output_2 = is_vowel(testcase_2);
  if (!assert_true("output_2", output_2)) {
    return false;
  }

  char testcase_3 = 'i';
  bool output_3 = is_vowel(testcase_3);
  if (!assert_true("output_3", output_3)) {
    return false;
  }

  char testcase_4 = 'o';
  bool output_4 = is_vowel(testcase_4);
  if (!assert_true("output_4", output_4)) {
    return false;
  }

  char testcase_5 = 'u';
  bool output_5 = is_vowel(testcase_5);
  if (!assert_true("output_5", output_5)) {
    return false;
  }

  char testcase_6 = 'k';
  bool output_6 = is_vowel(testcase_6);
  if (!assert_false("output_6", output_6)) {
    return false;
  }

  return true;
}

/* Task 4.1 */

bool test_is_tail() {
  // TODO: Implement this function.
  char testcase_1 = 'w';
  bool output_1 = is_tail(testcase_1);
  if (!assert_true("output_1", output_1)) {
    return false;
  }

  char testcase_2 = 'a';
  bool output_2 = is_tail(testcase_2);
  if (!assert_true("output_2", output_2)) {
    return false;
  }

  char testcase_3 = 's';
  bool output_3 = is_tail(testcase_3);
  if (!assert_true("output_3", output_3)) {
    return false;
  }

  char testcase_4 = 'd';
  bool output_4 = is_tail(testcase_4);
  if (!assert_true("output_4", output_4)) {
    return false;
  }

  char testcase_5 = 'k';
  bool output_5 = is_tail(testcase_5);
  if (!assert_false("output_5", output_5)) {
    return false;
  }

  char testcase_6 = 'x';
  bool output_6 = is_tail(testcase_6);
  if (!assert_false("output_6", output_6)) {
    return false;
  }
  return true;
}

bool test_is_head() {
  // TODO: Implement this function.
  char testcase_1 = 'W';
  bool output_1 = is_head(testcase_1);
  if (!assert_true("output_1", output_1)) {
    return false;
  }

  char testcase_2 = 'A';
  bool output_2 = is_head(testcase_2);
  if (!assert_true("output_2", output_2)) {
    return false;
  }

  char testcase_3 = 'S';
  bool output_3 = is_head(testcase_3);
  if (!assert_true("output_3", output_3)) {
    return false;
  }

  char testcase_4 = 'D';
  bool output_4 = is_head(testcase_4);
  if (!assert_true("output_4", output_4)) {
    return false;
  }

  char testcase_5 = 'k';
  bool output_5 = is_head(testcase_5);
  if (!assert_false("output_5", output_5)) {
    return false;
  }

  char testcase_6 = 'x';
  bool output_6 = is_head(testcase_6);
  if (!assert_true("output_6", output_6)) {
    return false;
  }
  return true;
}

bool test_is_snake() {
  char testcase_0 = '<';
  bool output_0 = is_snake(testcase_0);
  if (!assert_true("output_0", output_0)) {
    return false;
  }

  char testcase_01 = 'v';
  bool output_01 = is_snake(testcase_01);
  if (!assert_true("output_01", output_01)) {
    return false;
  }

  char testcase_02 = '>';
  bool output_02 = is_snake(testcase_02);
  if (!assert_true("output_02", output_02)) {
    return false;
  }

  char testcase_1 = 'w';
  bool output_1 = is_snake(testcase_1);
  if (!assert_true("output_1", output_1)) {
    return false;
  }

  char testcase_2 = 'a';
  bool output_2 = is_snake(testcase_2);
  if (!assert_true("output_2", output_2)) {
    return false;
  }

  char testcase_3 = 's';
  bool output_3 = is_snake(testcase_3);
  if (!assert_true("output_3", output_3)) {
    return false;
  }

  char testcase_4 = 'd';
  bool output_4 = is_snake(testcase_4);
  if (!assert_true("output_4", output_4)) {
    return false;
  }

  char testcase_5 = '^';
  bool output_5 = is_snake(testcase_5);
  if (!assert_true("output_5", output_5)) {
    return false;
  }

  char testcase_6 = 'W';
  bool output_6 = is_snake(testcase_6);
  if (!assert_true("output_6", output_6)) {
    return false;
  }

  char testcase_7 = 'A';
  bool output_7 = is_snake(testcase_7);
  if (!assert_true("output_7", output_7)) {
    return false;
  }

  char testcase_8 = 'S';
  bool output_8 = is_snake(testcase_8);
  if (!assert_true("output_8", output_8)) {
    return false;
  }
  
  char testcase_9 = 'D';
  bool output_9 = is_snake(testcase_9);
  if (!assert_true("output_9", output_9)) {
    return false;
  }

  char testcase_10 = 'x';
  bool output_10 = is_snake(testcase_10);
  if (!assert_true("output_10", output_10)) {
    return false;
  }

  char testcase_11 = '?';
  bool output_11 = is_snake(testcase_11);
  if (!assert_false("output_11", output_11)) {
    return false;
  }

  return true;
}

bool test_body_to_tail() {
  // TODO: Implement this function.
  char testcase_1 = '^';
  char output_1 = body_to_tail(testcase_1);
  if (output_1 != 'w') {
    return false;
  }

  char testcase_2 = '<';
  char output_2 = body_to_tail(testcase_2);
  if (output_2 != 'a') {
    return false;
  }

  char testcase_3 = 'v';
  char output_3 = body_to_tail(testcase_3);
  if (output_3 != 's') {
    return false;
  }

  char testcase_4 = '>';
  char output_4 = body_to_tail(testcase_4);
  if (output_4 != 'd') {
    return false;
  }

  return true;
}

bool test_head_to_body() {
  // TODO: Implement this function.
  char testcase_1 = 'W';
  char output_1 = head_to_body(testcase_1);
  if (output_1 != '^') {
    return false;
  }

  char testcase_2 = 'A';
  char output_2 = head_to_body(testcase_2);
  if (output_2 != '<') {
    return false;
  }

  char testcase_3 = 'S';
  char output_3 = head_to_body(testcase_3);
  if (output_3 != 'v') {
    return false;
  }

  char testcase_4 = 'D';
  char output_4 = head_to_body(testcase_4);
  if (output_4 != '>') {
    return false;
  }
  
  return true;
}

bool test_get_next_x() {
  // TODO: Implement this function.
  int testcase_1int = 0;
  char testcase_1char = '<';
  int output_1 = get_next_col(testcase_1int, testcase_1char);
  if (output_1 != -1) {
    return false;
  }

  int testcase_2int = 0;
  char testcase_2char = 'a';
  int output_2 = get_next_col(testcase_2int, testcase_2char);
  if (output_2 != -1) {
    return false;
  }
  int testcase_3int = 0;
  char testcase_3char = 'A';
  int output_3 = get_next_col(testcase_3int, testcase_3char);
  if (output_3 != -1) {
    return false;
  }
  int testcase_4int = 0;
  char testcase_4char = 'd';
  int output_4 = get_next_col(testcase_4int, testcase_4char);
  if (output_4 != 1) {
    return false;
  }
  int testcase_5int = 0;
  char testcase_5char = 'D';
  int output_5 = get_next_col(testcase_5int, testcase_5char);
  if (output_5 != 1) {
    return false;
  }
  int testcase_6int = 0;
  char testcase_6char = '>';
  int output_6 = get_next_col(testcase_6int, testcase_6char);
  if (output_6 != 1) {
    return false;
  }
  int testcase_7int = 0;
  char testcase_7char = 'g';
  int output_7 = get_next_col(testcase_7int, testcase_7char);
  if (output_7 != 0) {
    return false;
  }
  
  return true;
}

bool test_get_next_y() {
  int testcase_1int = 0;
  char testcase_1char = 'W';
  int output_1 = get_next_row(testcase_1int, testcase_1char);
  if (output_1 != -1) {
    return false;
  }
  int testcase_2int = 0;
  char testcase_2char = 'w';
  int output_2 = get_next_row(testcase_2int, testcase_2char);
  if (output_2 != -1) {
    return false;
  }
  int testcase_3int = 0;
  char testcase_3char = '^';
  int output_3 = get_next_row(testcase_3int, testcase_3char);
  if (output_3 != -1) {
    return false;
  }
  int testcase_4int = 0;
  char testcase_4char = 'v';
  int output_4 = get_next_row(testcase_4int, testcase_4char);
  if (output_4 != 1) {
    return false;
  }
  int testcase_5int = 0;
  char testcase_5char = 's';
  int output_5 = get_next_row(testcase_5int, testcase_5char);
  if (output_5 != 1) {
    return false;
  }
  int testcase_6int = 0;
  char testcase_6char = 'S';
  int output_6 = get_next_row(testcase_6int, testcase_6char);
  if (output_6 != 1) {
    return false;
  }
  int testcase_7int = 0;
  char testcase_7char = 'g';
  int output_7 = get_next_row(testcase_7int, testcase_7char);
  if (output_7 != 0) {
    return false;
  }
  return true;
}


bool test_customs() {
  if (!test_greater_than_forty_two()) {
    printf("%s\n", "test_greater_than_forty_two failed.");
    return false;
  }
  if (!test_is_vowel()) {
    printf("%s\n", "test_is_vowel failed.");
    return false;
  }
  if (!test_is_tail()) {
    printf("%s\n", "test_is_tail failed");
    return false;
  }
  if (!test_is_head()) {
    printf("%s\n", "test_is_head failed");
    return false;
  }
  if (!test_is_snake()) {
    printf("%s\n", "test_is_snake failed");
    return false;
  }
  if (!test_body_to_tail()) {
    printf("%s\n", "test_body_to_tail failed");
    return false;
  }
  if (!test_head_to_body()) {
    printf("%s\n", "test_head_to_body failed");
    return false;
  }
  if (!test_get_next_x()) {
    printf("%s\n", "test_get_next_x failed");
    return false;
  }
  if (!test_get_next_y()) {
    printf("%s\n", "test_get_next_y failed");
    return false;
  }
  return true;
}

int main(int argc, char* argv[]) {
  init_colors();

  if (!test_and_print("custom", test_customs)) {
    return 0;
  }

  return 0;
}
