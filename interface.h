#ifndef INTERFACE_H
#define INTERFACE_H

#include "list.h"

void select_action(int *action);
Address *input_address();
void exe_address_book(Address **list);
void response_handler(int *response, char *message);
void flush_stdin();
void input_integer(int *index);
void input_criteria(char *criteria);
void response_header();
void get_address_by_index(Address **list, int index);
void get_address_by_criteria(Address **list, char *criteria);
void load_address_book(Address **list);

#endif