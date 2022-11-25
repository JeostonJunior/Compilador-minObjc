#include "Funcaux.h"
#include "Analex.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void erro(char msg[]) {
  printf("%s\n", msg);
  exit(1);
}

void PrintNodo(char info[], int movim) {

  if (movim == AVANCA) {
    printf("%s%s\n", TABS, info);
    strcat(TABS, "\t");
  } else if (movim == MANTEM) {
    printf("%s%s\n", TABS, info);
  } else if (movim == RETROCEDE) {
    TABS[strlen(TABS) - 1] = '\0';
  }
}

void PrintNodoInt(int val, int movim) {

  if (movim == AVANCA) {
    printf("%s%d\n", TABS, val);
    strcat(TABS, "\t");
  } else if (movim == MANTEM) {
    printf("%s%d\n", TABS, val);
  } else if (movim == RETROCEDE) {
    TABS[strlen(TABS) - 1] = '\0';
  }
}
void PrintNodoFloat(float val, int movim) {

  if (movim == AVANCA) {
    printf("%s%f\n", TABS, val);
    strcat(TABS, "\t");
  } else if (movim == MANTEM) {
    printf("%s%f\n", TABS, val);
  } else if (movim == RETROCEDE) {
    TABS[strlen(TABS) - 1] = '\0';
  }
}
void PrintNodoChar(char val, int movim) {

  if (movim == AVANCA) {
    printf("%s%c\n", TABS, val);
    strcat(TABS, "\t");
  } else if (movim == MANTEM) {
    printf("%s%c\n", TABS, val);
  } else if (movim == RETROCEDE) {
    TABS[strlen(TABS) - 1] = '\0';
  }
}