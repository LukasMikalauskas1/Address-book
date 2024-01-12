#ifndef LIST_H
#define LIST_H

#include <stdio.h>

typedef struct Address
{
        char name[50];
        char surname[50];
        char email[100];
        char phone_num[20];
        struct Address *next;
} Address;

/*
 * @brief Function that adds a node to the end of the linked list
 * @param head double pointer to the start of the list
 * @param node a pointer to the node
 */
void add_to_end(Address **head, Address *node);
/*
 * @brief Function that adds a node to a certain position in the linked list
 * @param head double pointer to the start of the list
 * @param node a pointer to the node
 * @param index position index where to add a new node
 */
void add_by_index(Address **head, Address *node, int index);
/*
 * @brief Function to get all nodes from the linked list that matches a certain criteria
 * @param head double pointer to the start of the list
 * @param hode a pointer to the node
 * @return Pointer to a list of matches
 */
Address *get_by_criteria(Address **head, char *criteria);
/*
 * @brief Function that gets a node by position index in linked list
 * @param head double pointer to the start of the list
 * @param index position index where the node is located in the linked list
 * @return Pointer to a node
 */
Address *get_by_index(Address **head, int index);
/*
 * @brief Function that prints the contents of the linked list
 * @param head double pointer to the start of the list
 * @param header line that is printed before the contents
 */
void print_list(Address *head, char *header);
/*
 * @brief Function that prints a single node
 * @param node a pointer to a node
 * @param header line that is printed before the contents
 */
void print_node(Address *node, char *header);
/*
 * @brief Function that deletes the entire linked list
 * @param head double pointer to the start of the list
 */
void delete_all(Address **head);
/*
 * @brief Function that deletes a single node by position index
 * @param head double pointer to the start of the list
 * @param index position index where the node is located in the linked list
 */
void delete_by_index(Address **head, int index);
/*
 * @brief Function that creates a node
 * @param name name of a person
 * @param surname last name of a person
 * @param email email address
 * @param phone_num phone number
 * @return Pointer to a node
 */
Address *create_node(char *name, char *surname, char *email, char *phone_num);
/*
 * @brief Function that reads and loads the data from a file to a linked list
 * @param path path to a file
 * @param head double pointer to the start of the list
 */
void load_initial_data(FILE *path, Address **head);
/*
 * @brief Function that splits line from a file and creates a node
 * @param line of a file
 * @return Pointer to a node
 */
Address *create_address_node(char *line);

#endif