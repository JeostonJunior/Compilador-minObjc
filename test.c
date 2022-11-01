#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char teste[10] = "corno";
    char teste2[10];
    teste2[10] = teste;
    printf(teste2);
    return 0;
}