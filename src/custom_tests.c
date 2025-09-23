#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "asserts.h"
// Necessary due to static functions in game.c
#include "game.c"

/* Look at asserts.c for some helpful assert functions */

int greater_than_forty_two(int x) { return x > 42; }

bool is_vowel(char c) {
  char *vowels = "aeiouAEIOU";
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
    if (!is_tail('w')) {
        printf("FAIL: is_tail('w')\n");
        return false;
    }

    if (!is_tail('a')) {
        printf("FAIL: is_tail('a')\n");
        return false;
    }

    if (!is_tail('s')) {
        printf("FAIL: is_tail('s')\n");
        return false;
    }

    if (is_tail('^')) {
        printf("FAIL: is_tail('^')\n");
        return false;
    }

    return true;
}

bool test_is_head() {
    if (!is_head('W')) {
        printf("FAIL: is_head('W')\n");
        return false;
    }

    if (!is_head('A')) {
        printf("FAIL: is_head('A')\n");
        return false;
    }
    if (!is_head('D')) {
        printf("FAIL: is_head('D')\n");
        return false;
    }

    if (!is_head('x')) {
        printf("FAIL: is_head('x')\n");
        return false;
    }

    if (is_head('w')) {
        printf("FAIL: is_head('w')\n");
        return false;
    }

    return true;
}

bool test_is_snake() {
    char snake_chars[] = {'w','a','s','d','^','<','v','>','W','A','S','D','x'};
    for (int i = 0; i < 13; i++) {
        if (!is_snake(snake_chars[i])) {
            printf("FAIL: is_snake('%c')\n", snake_chars[i]);
            return false;
        }
    }

    if (is_snake('#')) {
        printf("FAIL: is_snake('#')\n");
        return false;
    }

    if (is_snake(' ')) {
        printf("FAIL: is_snake(' ')\n");
        return false;
    }

    return true;
}

bool test_body_to_tail() {
    if (body_to_tail('^') != 'w') {
        printf("FAIL: body_to_tail('^')\n");
        return false;
    }

    if (body_to_tail('<') != 'a') {
        printf("FAIL: body_to_tail('<')\n");
        return false;
    }

    if (body_to_tail('v') != 's') {
        printf("FAIL: body_to_tail('v')\n");
        return false;
    }

    if (body_to_tail('>') != 'd') {
        printf("FAIL: body_to_tail('>')\n");
        return false;
    }

    return true;
}

bool test_head_to_body() {
    if (head_to_body('W') != '^') {
        printf("FAIL: head_to_body('W')\n");
        return false;
    }

    if (head_to_body('A') != '<') {
        printf("FAIL: head_to_body('A')\n");
        return false;
    }

    if (head_to_body('S') != 'v') {
        printf("FAIL: head_to_body('S')\n");
        return false;
    }

    if (head_to_body('D') != '>') {
        printf("FAIL: head_to_body('D')\n");
        return false;
    }

    return true;
}

bool test_get_next_row() {
    if (get_next_row(5, 'v') != 6) {
        printf("FAIL: get_next_row(5, 'v')\n");
        return false;
    }

    if (get_next_row(5, 's') != 6) {
        printf("FAIL: get_next_row(5, 's')\n");
        return false;
    }
    if (get_next_row(5, '^') != 4) {
        printf("FAIL: get_next_row(5, '^')\n");
        return false;
    }

    if (get_next_row(5, 'w') != 4) {
        printf("FAIL: get_next_row(5, 'w')\n");
        return false;
    }
    if (get_next_row(5, '>') != 5) {
        printf("FAIL: get_next_row(5, '>')\n");
        return false;
    
    }
    return true;
}

bool test_get_next_col() {
    if (get_next_col(5, '>') != 6) {
        printf("FAIL: get_next_col(5, '>')\n");
        return false;
    }
    if (get_next_col(5, 'd') != 6) {
        printf("FAIL: get_next_col(5, 'd')\n");
        return false;
    }

    if (get_next_col(5, 'D') != 6) {
        printf("FAIL: get_next_col(5, 'D')\n");
        return false;
    }
    if (get_next_col(5, 'a') != 4) {
        printf("FAIL: get_next_col(5, 'a')\n");
        return false;
    }

    if (get_next_col(5, '^') != 5) {
        printf("FAIL: get_next_col(5, '^')\n");
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
  if (!test_get_next_row()) {
    printf("%s\n", "test_get_next_row failed");
    return false;
  }
  if (!test_get_next_col()) {
    printf("%s\n", "test_get_next_col failed");
    return false;
  }
  return true;
}

int main(int argc, char *argv[]) {
  init_colors();

  if (!test_and_print("custom", test_customs)) {
    return 0;
  }

  return 0;
}
