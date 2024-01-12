#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>

#include "list.h"
#include "interface.h"

#define HOME "HOME"

void select_option(int *option)
{
        printf("Actions: \n");
        printf("1 - Add new address (to the end)\n2 - Incert new address\n3 - Find address by position\n4 - Find address by criteria\n5 - Delete address by position \n6 - Delete whole address book\n\n");
        printf("Type in the action number and press enter\n");
        printf("Action number: ");
        scanf(" %d", option);
        flush_input();
        printf("\n");
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
        flush_input();

        printf("Type in the surname:");
        scanf("%50s", temp->surname);
        flush_input();

        printf("Type in the email:");
        scanf("%100s", temp->email);
        flush_input();

        printf("Type in the phone number:");
        scanf("%20s", temp->phone_num);
        flush_input();

        temp->next = NULL;
        printf("\n");

        return temp;
}

void exe_option(Address **list, int *option)
{
        Address *temp = NULL;
        int index = 0;
        char criteria[100];
        char yn;
        int response;

        switch (*option)
        {
        case 1:
                temp = input_address();
                add_to_end(list, temp);
                print_list(*list, "New addres was added:");
                break;
        case 2:
                temp = input_address();
                printf("Type in the index: ");
                if (scanf(" %d", &index) != 1)
                {
                        printf("Error: wrong input type, should be an integer\n\n");
                        flush_input();
                        break;
                }
                flush_input();
                printf("\n");
                response = add_by_index(list, temp, index);
                if (response == -1)
                {
                        printf("Error: index must be greater or equal to 0\n\n");
                        break;
                }
                if (response == -2)
                {
                        printf("Error: - Index out of bounds of the list\n\n");
                        break;
                }
                print_list(*list, "New addres was added:");
                break;
        case 3:
                printf("Type in the index: ");
                if (scanf("%d", &index) != 1)
                {
                        printf("Error: wrong input type! should be an integer\n\n");
                        flush_input();
                        break;
                }
                flush_input();
                printf("\n");
                temp = get_by_index(list, index);
                if (temp == NULL)
                {
                        printf("Error: node with the given index was not found\n\n");
                        break;
                }
                printf("Address:\n");
                print_node(temp);
                break;
        case 4:
                printf("Type any of these criterias - name, surname, email, phone\n\n");
                printf("Criteria: ");
                scanf("%99s", criteria);
                printf("\n");
                temp = get_by_criteria(list, criteria);
                if (temp == NULL)
                {
                        printf("Error: node with the given criteria was not found\n\n");
                        break;
                }
                print_list(temp, "\nMatches:");
                delete_all(&temp);
                break;
        case 5:
                printf("Type in the index: ");
                if (scanf("%d", &index) != 1)
                {
                        printf("Error: wrong input type! should be an integer\n\n");
                        flush_input();
                        break;
                }
                flush_input();
                printf("\n");
                response = delete_by_index(list, index);
                if (response == -1)
                {
                        printf("Error: index must be greater or equal to 0\n\n");
                        break;
                }
                if (response == -2)
                {
                        printf("Error: Index out of bounds of the list\n\n");
                        break;
                }
                printf("Address was deleted succsesfully\n\n");
                break;
        case 6:
                response = delete_all(list);
                if (response == 0)
                {
                        printf("List was deleted succsesfully\n\n");
                }
                break;
        default:
                printf("Error: action does not exist!\n\n");
                break;
        }

        printf("Do you want to continue ? (y/n)\n");
        scanf(" %c", &yn);
        if (yn == 'y')
        {
                *option = -1;
                printf("--------------------------------------------------------------------------------\n");
                print_list(*list, "Address book:");
                select_option(option);
                exe_option(list, option);
        }
        else if (yn != 'n')
        {
                *option = -1;
                printf("Error: options are (y/n) (yes/no)\n\n");
                exe_option(list, option);
        }
}

void flush_input()
{
        int c;
        while ((c = getchar()) != '\n')
        {
                // Consuming characters till \n
        }
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
                print_list(*list, "Address book:");
                fclose(initial_data);
        }
        else
        {
                printf("Error: failed to load data from addresses.csv file\n");
        }
}
