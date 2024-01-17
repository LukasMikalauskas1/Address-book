#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

#include "list.h"
#include "interface.h"

void signal_handler(int signal);
Address *list = NULL;

int main(void)
{
        signal(SIGINT, signal_handler);

        load_address_book(&list);
        exe_address_book(&list);
        delete_all(&list);

        return 0;
}

void signal_handler(int signal)
{
        delete_all(&list);
        clean_up();
        exit(1);
}
