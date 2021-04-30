
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "item.h"
#include "first_keyspace.h"
#include "second_keyspace.h"
#include "input.h"
#include "dialog.h"
#include "table.h"
#include "menu.h"
#include "dialog.h"

#define _CRTDBG_MAP_ALLOC //
#include <crtdbg.h> //

int main()
{
    struct Table* MyTab = NULL;

    menu(&MyTab);

    Terminate(MyTab);

    _CrtDumpMemoryLeaks();

    return 0;
}