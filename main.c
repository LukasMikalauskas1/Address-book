#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#include "list.h"

#define HOME "HOME"

Address *input_address();
void select_option(int *option);
void exe_option(Address **list, int *option);

int main(void)
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
                        closedir(dir);
                }
        }

        Address *list = NULL;

        FILE *initial_data = NULL;

        initial_data = fopen(file_path, "r");

        if (initial_data != NULL)
        {
                load_initial_data(initial_data, &list);
                print_list(list, "Address book:");
                fclose(initial_data);
        }
        else
        {
                perror("Error");
        }

        int option = 0;

        select_option(&option);
        exe_option(&list, &option);
        delete_all(&list);

        return 0;
}

void select_option(int *option)
{
        printf("Actions: \n");
        printf("1 - Add to the end\n2 - Add by index\n3 - Get by index\n4 - Get by criteria\n5 - Delete by index \n6 - Delete all\n\n");
        printf("Type in the action number and press enter\n");
        printf("Action number: ");
        scanf(" %d", option);
        printf("\n");
}

Address *input_address()
{
        Address *temp = NULL;
        temp = (Address *)malloc(sizeof(Address));

        if (temp == NULL)
        {
                printf("error - memory allocation failed! input_address()\n");
                exit(1);
        }

        printf("Type in the data for a new address:\n");
        printf("Type in the name: ");
        scanf("%49s", temp->name);
        printf("Type in the surname: ");
        scanf("%49s", temp->surname);
        printf("Type in the email: ");
        scanf("%99s", temp->email);
        printf("Type in the phone number: ");
        scanf("%19s", temp->phone_num);
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
                scanf("%d", &index);
                add_by_index(list, temp, index);
                break;
        case 3:
                printf("Type in the index: ");
                scanf("%d", &index);
                temp = get_by_index(list, index);
                if (temp == NULL)
                {
                        break;
                }
                print_node(temp, "\nAddress:");
                break;
        case 4:
                printf("Type any of these criterias - name, surname, email, phone\n");
                printf("Criteria: ");
                scanf("%99s", criteria);
                temp = get_by_criteria(list, criteria);
                print_list(temp, "\nAddress:");
                delete_all(&temp);
                break;
        case 5:
                printf("Type in the index: ");
                scanf("%d", &index);
                delete_by_index(list, index);
                break;
        case 6:
                delete_all(list);
                break;
        default:
                printf("error - action does not exist!\n\n");
                break;
        }

        printf("Do you want to continue ? (y/n)\n");
        scanf(" %c", &yn);
        if (yn == 'y')
        {
                printf("--------------------------------------------------------------------------------\n");
                print_list(*list, "Address book:");
                select_option(option);
                exe_option(list, option);
        }
}