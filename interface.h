#ifndef INTERFACE_H
#define INTERFACE_H

#include "list.h"

/*
 * @brief Function that takes user input and creates a new Address node
 * @return new Address node
 * @param pointer to the options variable
 */
Address *input_address();
/*
 * @brief Function that takes user input for an action
 */
void select_option(int *option);
/*
 * @brief Function that executes action that user inputed
 * @param list double pointer to the start of the list
 * @param pointer to the options variable
 */
void exe_option(Address **list, int *option);
/*
 * @brief Function that clears input buffer
 */
void flush_input();
/*
 * @brief Function that populates list with data
 * @param list double pointer to the start of the list
 */
void load_address_book(Address **list);

#endif