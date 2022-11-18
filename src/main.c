#include <stdio.h>
#include <stdbool.h>
#include "grid.h"

int main(void)
{
    bool run = true;
    while (run)
    {
        char entry = fgetc(stdin);
        switch (entry)
        {
        case 'q':
        {
            run = false;
            break;
        }
        }
    }
}
