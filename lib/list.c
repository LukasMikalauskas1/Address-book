#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

#define DELIMITER ","

int add_to_end(Address **head, Address *node)
{
        if (node == NULL)
        {
                return -4; // error - node was null
        }

        Address *current = *head;

        if (current == NULL)
        {
                *head = node;
                return 0;
        }

        while (current->next != NULL)
        {
                current = current->next;
        }

        current->next = node;
        return 0;
}

void print_list(Address *head, char *header)
{
        Address *current = head;
        int counter = 0;

        printf("%s\n", header);

        while (current != NULL)
        {
                printf("Nr. %d - ", counter);
                print_node(current);
                current = current->next;
                counter++;
        }
        printf("\n");
}

void print_node(Address *node)
{
        printf("%s %s %s %s\n", node->name, node->surname, node->email, node->phone_num);
}

void load_initial_data(FILE *path, Address **head)
{
        char line[200];

        while (fgets(line, sizeof(line), path))
        {
                Address *node = NULL;

                if (strcmp(line, "\n") == 0)
                {
                        continue;
                }

                node = create_address_node(line);

                if (node != NULL)
                {
                        add_to_end(head, node);
                }
                else
                {
                        free(node);
                }
        }
}

Address *create_address_node(char *line)
{
        Address *temp = NULL;

        char *name;
        char *surname;
        char *email;
        char *phone_num;

        // finds the position of \n ant replaces it with \0
        size_t len = strcspn(line, "\n");
        line[len] = '\0';

        name = strtok(line, DELIMITER);
        surname = strtok(NULL, DELIMITER);
        email = strtok(NULL, DELIMITER);
        phone_num = strtok(NULL, DELIMITER);

        temp = create_node(name, surname, email, phone_num);
        return temp;
}

Address *create_node(char *name, char *surname, char *email, char *phone_num)
{
        Address *temp = NULL;

        temp = (Address *)malloc(sizeof(Address));

        // Failed to allocate memory
        if (temp == NULL)
        {
                return NULL;
        }

        strcpy(temp->name, name);
        strcpy(temp->surname, surname);
        strcpy(temp->email, email);
        strcpy(temp->phone_num, phone_num);
        temp->next = NULL;

        return temp;
}

int add_by_index(Address **head, Address *node, int index)
{
        if (index < 0)
        {
                return -1; // error - index < 0
        }
        if (index == 0)
        {
                node->next = *head;
                *head = node;
                return 0;
        }

        Address *current = *head;
        int counter = 0;

        while (current != NULL && counter < index - 1)
        {
                current = current->next;
                counter++;
        }

        if (current == NULL)
        {

                return -2; // error - out of bounds
        }

        node->next = current->next;
        current->next = node;

        return 0;
}

int delete_all(Address **head)
{
        Address *current = *head;
        Address *next;

        if (current == NULL)
        {
                return -3; // error - empty list
        }

        while (current != NULL)
        {
                next = current->next;
                free(current);
                current = next;
        }

        *head = NULL;

        return 0;
}

int delete_by_index(Address **head, int index)
{
        if (index < 0)
        {
                return -1; // error - index must be greater or equal to 0
        }

        Address *temp = *head;

        if (temp == NULL)
        {
                return -3; // error - empty list
        }

        if (index == 0)
        {
                *head = (*head)->next;
                free(temp);
                return 0;
        }

        int counter = 0;

        while (temp != NULL && counter < index - 1)
        {
                temp = temp->next;
                counter++;
        }

        if (temp == NULL || temp->next == NULL)
        {
                return -2; // error - index out of bounds or attempting to delete the last node!
        }

        Address *node_to_delete = temp->next;

        temp->next = temp->next->next;

        free(node_to_delete);

        return 0;
}

Address *get_by_index(Address **head, int index)
{
        Address *current = *head;

        int counter = 0;

        while (current != NULL)
        {
                if (counter == index)
                {
                        return current;
                }

                current = current->next;
                counter++;
        }

        return NULL; // Node with the given index was not found
}

Address *get_by_criteria(Address **head, char *criteria)
{
        Address *current = *head;
        Address *match_list = NULL;
        Address *temp = NULL;

        while (current != NULL)
        {
                if (strcmp(current->name, criteria) == 0 ||
                    strcmp(current->surname, criteria) == 0 ||
                    strcmp(current->email, criteria) == 0 ||
                    strcmp(current->phone_num, criteria) == 0)
                {
                        temp = (Address *)malloc(sizeof(Address));

                        if (temp == NULL)
                        {
                                return match_list; // NULL if failed to allocate memory
                        }

                        strcpy(temp->name, current->name);
                        strcpy(temp->surname, current->surname);
                        strcpy(temp->email, current->email);
                        strcpy(temp->phone_num, current->phone_num);
                        temp->next = NULL;

                        add_to_end(&match_list, temp);
                }

                current = current->next;
        }
        return match_list; // NULL if no matches where found
}