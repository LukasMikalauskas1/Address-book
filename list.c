#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

#define DELIMITER ","

void add_to_end(Address **head, Address *node)
{
        Address *current = *head;

        if (current == NULL)
        {
                *head = node;
                return;
        }

        while (current->next != NULL)
        {
                current = current->next;
        }

        current->next = node;
}

void print_list(Address *head, char *header)
{
        Address *current = head;
        int counter = 0;

        printf("%s\n", header);

        while (current != NULL)
        {
                printf("Nr. %d - %s %s %s %s\n", counter, current->name, current->surname, current->email, current->phone_num);
                current = current->next;
                counter++;
        }
        printf("\n");
}

void print_node(Address *node, char *header)
{
        printf("%s\n", header);
        printf("%s %s %s %s", node->name, node->surname, node->email, node->phone_num);
        printf("\n\n");
}

void load_initial_data(FILE *path, Address **head)
{
        char line[128];

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

        if (temp == NULL)
        {
                printf("error - Failed to allocate memory in create_node()\n");
                return NULL;
        }

        strcpy(temp->name, name);
        strcpy(temp->surname, surname);
        strcpy(temp->email, email);
        strcpy(temp->phone_num, phone_num);
        temp->next = NULL;

        return temp;
}

void add_by_index(Address **head, Address *node, int index)
{
        if (index < 0)
        {
                printf("error - index must be greater or equal to 0\n");
                return;
        }
        if (index == 0)
        {
                node->next = *head;
                *head = node;
                return;
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
                printf("error - Index out of bounds of the list\n");
                return;
        }

        node->next = current->next;
        current->next = node;
}

void delete_all(Address **head)
{
        Address *current = *head;
        Address *next;

        while (current != NULL)
        {
                next = current->next;
                free(current);
                current = next;
        }

        *head = NULL;
}

void delete_by_index(Address **head, int index)
{
        if (index < 0)
        {
                printf("error - index must be greater or equal to 0\n");
                return;
        }

        Address *temp = *head;

        if (index == 0)
        {
                *head = (*head)->next;
                free(temp);
                return;
        }

        int counter = 0;

        while (temp != NULL && counter < index - 1)
        {
                temp = temp->next;
                counter++;
        }

        if (temp == NULL || temp->next == NULL)
        {
                printf("Index out of bounds or attempting to delete the last node!\n");
                return;
        }

        Address *node_to_delete = temp->next;

        temp->next = temp->next->next;

        free(node_to_delete);
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

        printf("error - node with %d index was not found\n", index);
        return NULL;
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

                        strcpy(temp->name, current->name);
                        strcpy(temp->surname, current->surname);
                        strcpy(temp->email, current->email);
                        strcpy(temp->phone_num, current->phone_num);
                        temp->next = NULL;

                        add_to_end(&match_list, temp);
                        printf("added a new node!\n");
                }

                current = current->next;
        }

        return match_list;
}