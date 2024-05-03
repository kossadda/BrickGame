/**
 * @file tests.h
 * @author kossadda (https://github.com/kossadda)
 * @brief Header file collecting all declarations.
 * @version 1.0
 * @date 2024-05-03
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef _MAIN_TEST_H_
#define _MAIN_TEST_H_

#include "./include_test/blocks_test.h"
#include "./include_test/fsm_test.h"
#include "./include_test/init_test.h"
#include "./include_test/shifts_test.h"
#include "./include_test/space_checks_test.h"

#define BLOCKS_ON
#define INIT_ON
#define FSM_ON
#define SHIFTS_ON
#define SPACE_CHECKS_ON

#define GREEN "\033[0;32m"
#define ORANGE "\033[1;33m"
#define BLUE "\033[36m"
#define RED "\033[0;31m"
#define YELLOW "\033[93m"
#define OKCYAN "\033[96m"
#define WHITE "\033[1;37m"
#define RESET "\033[0m"

#endif  // _MAIN_TEST_H_