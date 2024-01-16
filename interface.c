#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>

#include "list.h"
#include "interface.h"

#define HOME "HOME"

void select_action(int *action)
{
        printf("--------------------------------------------------------\n");
        printf("SELECT ACTION:\n");
        printf("0 - Display address book\n");
        printf("1 - Add new address (to the end)\n");
        printf("2 - Insert new address\n");
        printf("3 - Find address by position\n");
        printf("4 - Find address by criteria\n");
        printf("5 - Delete address by position\n");
        printf("6 - Delete whole address book\n");
        printf("7 - Exit program\n\n");
        printf("Type in the action number and press enter: ");
        input_integer(action);
}

Address *input_address()
{
        Address *temp = NULL;
        temp = (Address *)malloc(sizeof(Address));

        // returns null if memory allocation fails
        if (temp == NULL)
        {
                return NULL;
        }

        printf("Type in the data for a new address:\n");

        printf("Type in the name:");
        scanf("%50s", temp->name);
        flush_stdin();

        printf("Type in the surname:");
        scanf("%50s", temp->surname);
        flush_stdin();

        printf("Type in the email:");
        scanf("%100s", temp->email);
        flush_stdin();

        printf("Type in the phone number:");
        scanf("%20s", temp->phone_num);
        flush_stdin();

        temp->next = NULL;
        printf("\n");

        return temp;
}

void exe_address_book(Address **list)
{
        // Variable for execution:
        int response;
        int index;
        int action;
        char criteria[100];
        Address *temp = NULL;

        while (1)
        {
                action = 0;
                select_action(&action);
                switch (action)
                {
                case 0:
                        printf("--------------------------------------------------------\n");
                        print_list(*list, "ADDRESS BOOK:\n");
                        break;
                case 1: // Add to end
                        temp = input_address();
                        response = add_to_end(list, temp);
                        response_header();
                        response_handler(&response, "added to the end of the list");
                        if (response != 0)
                        {
                                free(temp);
                        }

                        break;
                case 2: // Add by index
                        temp = input_address();
                        printf("Type in the position: ");
                        input_integer(&index);
                        response = add_by_index(list, temp, index);
                        response_header();
                        response_handler(&response, "added new address");
                        if (response != 0)
                        {
                                free(temp);
                        }
                        break;
                case 3: // Get by index
                        printf("Type in the position: ");
                        input_integer(&index);
                        response_header();
                        get_address_by_index(list, index);
                        break;
                case 4: // Get by criteria
                        input_criteria(criteria);
                        response_header();
                        get_address_by_criteria(list, criteria);
                        break;
                case 5: // Delete at index
                        printf("Type in the position: ");
                        input_integer(&index);
                        response_header();
                        response = delete_by_index(list, index);
                        response_handler(&response, "address deleted");
                        break;
                case 6: // Delete all
                        response_header();
                        response = delete_all(list);
                        response_handler(&response, "address book deleted");
                        break;
                case 7:
                        return;
                default: // Wrong input
                        response_header();
                        printf("Error: action dosent exist\n\n");
                        break;
                }
        }
}

void response_handler(int *response, char *message)
{
        switch (*response)
        {
        case 0:
                printf("Succsess: %s\n\n", message);
                break;
        case -1:
                printf("Error: index must be equal or greater than 0\n\n");
                break;
        case -2:
                printf("Error: index out of bounds of the list\n\n");
                break;
        case -3:
                printf("Error: list is empty\n\n");
                break;
        case -4:
                printf("Error: addres was empty\n\n");
                break;
        }
}

void input_integer(int *num)
{
        while (1)
        {
                if (scanf("%d", num) == 1)
                {
                        flush_stdin();
                        printf("\n");
                        break;
                }
                else
                {
                        printf("\nError: invalid input, must be an integer \n");
                        printf("\nType again: ");
                        flush_stdin();
                }
        }
}

void input_criteria(char criteria[100])
{
        printf("Type in the criteria (name, surname, email, phone): ");
        scanf("%100s", criteria);
        flush_stdin();
        printf("\n");
}

void flush_stdin()
{
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
                ;
}

void response_header()
{
        printf("--------------------------------------------------------\n");
        printf("RESPONSE:\n");
}

void get_address_by_index(Address **list, int index)
{
        Address *temp = get_by_index(list, index);
        if (temp == NULL)
        {
                printf("Address dosent exist!\n\n");
                return;
        }
        printf("Address at a given position:\n");
        print_node(temp);
}

void get_address_by_criteria(Address **list, char *criteria)
{
        Address *temp = get_by_criteria(list, criteria);
        if (temp == NULL)
        {
                printf("Address dosent exist!\n\n");
                return;
        }
        print_list(temp, "Address that matched the criteria:\n");
        free(temp);
}

void load_address_book(Address **list)
{
        char file_path[100];
        const char *home_dir = getenv(HOME);

        DIR *dir;
        struct dirent *entry;
        dir = opendir(home_dir);

        while ((entry = readdir(dir)) != NULL)
        {
                if (strcmp(entry->d_name, "addresses.csv") == 0)
                {
                        sprintf(file_path, "%s/%s", home_dir, "addresses.csv");
                }
        }
        closedir(dir);

        FILE *initial_data = NULL;

        initial_data = fopen(file_path, "r");

        if (initial_data != NULL)
        {
                load_initial_data(initial_data, list);
                fclose(initial_data);
        }
        else
        {
                printf("Error: failed to load data from addresses.csv file\n");
        }
}
