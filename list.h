#ifndef LIST_H
#define LIST_H

#include <stdio.h>

#define NAME_LENGHT 50
#define SURNAME_LENGHT 50
#define EMAIL_LENGHT 100
#define PHONE_LENGHT 20

typedef struct Address
{
        char name[NAME_LENGHT + 1];
        char surname[SURNAME_LENGHT + 1];
        char email[EMAIL_LENGHT + 1];
        char phone_num[PHONE_LENGHT + 1];
        struct Address *next;
} Address;

/*
 * @brief Function that adds a node to the end of the linked list
 * @param head double pointer to the start of the list
 * @param node a pointer to the node
 * @return 0 - succses, -4 node = NULL
 */
int add_to_end(Address **head, Address *node);
/*
 * @brief Function that adds a node to a certain position in the linked list
 * @param head double pointer to the start of the list
 * @param node a pointer to the node
 * @param index position index where to add a new node
 * @return 0 - succsess, -1 - index < 0, -2 - index out of bounds
 */
int add_by_index(Address **head, Address *node, int index);
/*
 * @brief Function to get all nodes from the linked list that matches a certain criteria
 * @param head double pointer to the start of the list
 * @param hode a pointer to the node
 * @return Pointer to a list of matches or NULL if no matches werefound
 */
Address *get_by_criteria(Address **head, char *criteria);
/*
 * @brief Function that gets a node by position index in linked list
 * @param head double pointer to the start of the list
 * @param index position index where the node is located in the linked list
 * @return Pointer to a node or NULL if node was not found
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
 */
void print_node(Address *node);
/*
 * @brief Function that deletes the entire linked list
 * @param head double pointer to the start of the list
 * @return 0 - succsess, -3 - list already empty
 */
int delete_all(Address **head);
/*
 * @brief Function that deletes a single node by position index
 * @param head double pointer to the start of the list
 * @param index position index where the node is located in the linked list
 * @return 0 - succsess, -1 - index < 0, -2 - index out of bounds
 */
int delete_by_index(Address **head, int index);
/*
 * @brief Function that creates a node
 * @param name name of a person
 * @param surname last name of a person
 * @param email email address
 * @param phone_num phone number
 * @return Pointer to a node or NULL if memory allocation failed
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