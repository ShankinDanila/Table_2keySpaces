#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "input.h"


int GetInt(int* number)
{
    int status;
    do
    {
        status = scanf_s("%d", number);
        if (status < 0)
        {
            return 0;
        }
        if (status == 0)
        {
            printf("%s\n", "Error! Please enter integer number.");
            scanf_s("%*[^\n]");
            scanf_s("%*c");
        }
    } while (status == 0);
    scanf_s("%*c");
    return 1;
}

int GetFloat(double* number)
{
    int status;
    do
    {
        status = scanf_s("%lf", number);
        if (status < 0)
        {
            return 0;
        }
        if (status == 0)
        {
            printf("%s\n", "Error! Please enter integer number.");
            scanf_s("%*[^\n]");
            scanf_s("%*c");
        }
    } while (status == 0);
    scanf_s("%*c");
    return 1;
}


char* get_str()
{
    char buf[81] = { 0 };
    char* res = NULL;
    int len = 0;
    int n = 0;
    do {
        n = scanf_s("%80[^\n]", buf, 81);
        if (n < 0) {
            if (!res) {
                return NULL;
            }
        }
        else if (n > 0) {
            int chunk_len = strlen(buf);
            int str_len = len + chunk_len;
            res = (char*)realloc(res, str_len + 1);
            memcpy(res + len, buf, chunk_len);
            len = str_len;
        }
        else {
            scanf_s("%*c");
        }
    } while (n > 0);

    if (len > 0) {
        res[len] = '\0';
    }
    else {
        res = (char*)calloc(1, sizeof(char));
    }

    return res;
}

char* get_line() {
    char* str = NULL;
    str = (char*)malloc(N*sizeof(char));
    str[N] = '\0';
    int c;
    int i = 0;
    while (((c = getchar()) != EOF) && i < N) {
        str[i] = c;
        i++;
    }

    return str;
}