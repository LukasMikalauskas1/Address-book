#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

#include "list.h"
#include "interface.h"

void signal_handler(int signal);
Address *list = NULL;

int main(void)
{
        int option = 0;
        signal(SIGINT, signal_handler);

        load_address_book(&list);
        select_option(&option);
        exe_option(&list, &option);

        delete_all(&list);

        return 0;
}

void signal_handler(int signal)
{
        printf("Cleaning up and terminating...\n");
        delete_all(&list);
        exit(0);
}
