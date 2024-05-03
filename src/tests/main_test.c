/**
 * @file tests.c
 * @author kossadda (https://github.com/kossadda)
 * @brief Module for assembling all test modules.
 * @version 1.0
 * @date 2024-05-03
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "./main_test.h"

#include <stdio.h>
#include <string.h>

static void test_function(Suite *(**array)(void), size_t size, char *name,
                          int *passed_count, int *failed_count);
static void conclusion(int passed_count, int failed_count);
static void function_declaration(char *function);
static int test_suite(Suite *test, int *passed_count);
static void greetings();
static void line();

/**
 * @brief Function to start testing modules.
 *
 * @return int - error code.
 * @retval EXIT_SUCCESS = 0 - if the tests pass successfully.
 * @retval EXIT_FAILURE = 1 - if the tests pass unsuccessful.
 */
int main(void) {
  int failed_count = 0;
  int passed_count = 0;

  greetings();

#ifdef BLOCKS_ON
  Suite *(*blocks[])(void) = {
      blocks_test,
  };
  test_function(blocks, sizeof(blocks) / sizeof(blocks[0]), "BLOCKS",
                &passed_count, &failed_count);
#endif

  conclusion(passed_count, failed_count);

  return (failed_count) ? EXIT_FAILURE : EXIT_SUCCESS;
}

/**
 * @brief Function for testing the specified Suite.
 *
 * @param[out] test input Suite test.
 * @param[out] passed_count counter of successfully passed tests.
 *
 * @return int - error code.
 * @retval EXIT_SUCCESS = 0 - if the tests pass successfully.
 * @retval EXIT_FAILURE = 1 - if the tests pass unsuccessful.
 */
static int test_suite(Suite *test, int *passed_count) {
  SRunner *suite_runner = srunner_create(test);

  srunner_run_all(suite_runner, CK_NORMAL);
  int failed_count = srunner_ntests_failed(suite_runner);
  *passed_count += srunner_ntests_run(suite_runner) - failed_count;
  srunner_free(suite_runner);

  return failed_count;
}

/**
 * @brief Prints greeting message.
 */
static void greetings() {
  printf(
      "\033[0;33m __          __  _                            _          _    "
      "        _   _             \n");
  printf(
      " \\ \\        / / | |                          | |        | |          "
      "| | (_)            \n");
  printf(
      "  \\ \\  /\\  / /__| | ___ ___  _ __ ___   ___  | |_ ___   | |_ ___  "
      "___| |_ _ _ __   __ _ \n");
  printf(
      "   \\ \\/  \\/ / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\ | __/ _ \\  | __/ _ "
      "\\/ __| __| | '_ \\ / _` |\n");
  printf(
      "    \\  /\\  /  __/ | (_| (_) | | | | | |  __/ | || (_) | | ||  __/\\__ "
      "\\ |_| | | | | (_| |\n");
  printf(
      "     \\/  \\/ \\___|_|\\___\\___/|_| |_| |_|\\___|  \\__\\___/   "
      "\\__\\___||___/\\__|_|_| |_|\\__, |\n");
  printf(
      "                                                                        "
      "           __/ |\n");
  printf(
      "                                                                        "
      "          |___/ \n");

  printf(
      "                                    _                                   "
      "                  \n");
  printf(
      "                                   | |                                  "
      "                  \n");
  printf(
      "                                   | |__  _   _                         "
      "                  \n");
  printf(
      "                                   | '_ \\| | | |                       "
      "                   \n");
  printf(
      "                                   | |_) | |_| |                        "
      "                  \n");
  printf(
      "                                   |_.__/ \\__, |                       "
      "                   \n");
  printf(
      "                       _                   __/ |   _     _              "
      "     \n");
  printf(
      "                      | |                 |___/   | |   | |             "
      "     \n");
  printf(
      "                      | | _____  ___ ___  __ _  __| | __| | __ _        "
      "     \n");
  printf(
      "                      | |/ / _ \\/ __/ __|/ _` |/ _` |/ _` |/ _` |      "
      "      \n");
  printf(
      "                      |   < (_) \\__ \\__ \\ (_| | (_| | (_| | (_| |    "
      "        \n");
  printf(
      "                      |_|\\_\\___/|___/___/\\__,_|\\__,_|\\__,_|\\__,_| "
      "           \n");
}

/**
 * @brief Collects all functions for testing into a single block.
 *
 * @param array array of function under test.
 * @param size array size.
 * @param name name of the function being tested.
 * @param passed_count number of tests passed.
 * @param failed_count number of failed tests.
 */
static void test_function(Suite *(**array)(void), size_t size, char *name,
                          int *passed_count, int *failed_count) {
  function_declaration(name);
  for (size_t i = 0; i < size; i++) {
    line();
    *failed_count += test_suite(array[i](), passed_count);
  }
  line();
}

/**
 * @brief Prints function declaration message.
 *
 * @param[in] function name of testing function.
 */
static void function_declaration(char *function) {
  char space[5] = {0};
  int str_len = strlen(function);
  if (str_len == 6) {
    strcpy(space, "   ");
  } else if (str_len == 7) {
    strcpy(space, "  ");
  }
  printf(
      "\033[0;33m\n\n "
      "________________________________________________________________________"
      "______________\n");
  printf(
      "|                                                                       "
      "               |\n");
  printf(
      "|                                  %s TESTS %s                          "
      "          |\n",
      function, space);
  printf(
      "|_______________________________________________________________________"
      "_______________|\n\n\n\033[0m");
}

/**
 * @brief Prints the dividing line.
 */
static void line() {
  printf(
      "\033[0;33m**************************************************************"
      "**************************\n\033[0m");
}

/**
 * @brief Prints test results.
 *
 * @param[in] passed_count number of tests passed.
 * @param[in] failed_count number of failed tests.
 */
static void conclusion(int passed_count, int failed_count) {
  printf(
      "\033[0;33m\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
      "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  printf(
      "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ TOTAL RESULTS "
      "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  printf(
      "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
      "~~~~~~~~~~~~~~~~\n");
  printf(
      "                                                                        "
      " \n");
  printf(
      "                               PASSED %d tests from %d                  "
      "      \n",
      passed_count, passed_count + failed_count);
  printf(
      "                                                                        "
      " \n");
  printf(
      "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
      "~~~~~~~~~~~~~~~~\n\033[0m\n");
}