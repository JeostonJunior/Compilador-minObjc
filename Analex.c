#include "Analex.h"
#include "Funcaux.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM_LEXEMA 50
#define TAM_NUM 20

void error(char msg[], int estado) {
  printf("%s no estado:%d", msg, estado);
  exit(1);
}

TOKEN AnaLex(FILE *fd) {
  int estado;
  char lexema[TAM_LEXEMA] = "";
  int tamL = 0;
  char digitos[TAM_NUM] = "";
  int tamD = 0;
  estado = 0;
  t.processado = FALSE;
  char PALAVRAS_RESERVADAS[16][10] = {
      "class", "data:", "code:", "intern:", "void", "char",   "int",    "float",
      "bool",  "if",    "else",  "while",   "for",  "return", "delete", "new"};
  while (1) {
    char caracter = fgetc(fd);
    switch (estado) {
    case 0:
      if (caracter == ' ' || caracter == '\t' || caracter == '\n') {
        estado = 0;
      } else if (caracter >= 'a' && caracter <= 'z' ||
                 caracter >= 'A' && caracter <= 'Z') {
        estado = 1;
        lexema[tamL] = caracter;
        lexema[++tamL] = '\0';
      } else if (caracter >= '0' && caracter <= '9') {
        estado = 2;
        digitos[tamD] = caracter;
        digitos[++tamD] = '\0';
      } else if (caracter == '+') {
        t.cat = SN;
        t.codigo = ADICAO;
        return t;
      } else if (caracter == '-') {
        t.cat = SN;
        t.codigo = SUBTRACAO;
        return t;
      } else if (caracter == '*') {
        t.cat = SN;
        t.codigo = MULTIPLICACAO;
        return t;
      } else if (caracter == '/') {
        estado = 7;
        lexema[tamL] = caracter;
        lexema[++tamL] = '\0';
      } else if (caracter == '=') {
        estado = 12;
        lexema[tamL] = caracter;
        lexema[++tamL] = '\0';
      } else if (caracter == '(') {
        t.cat = SN;
        t.codigo = ABRE_PARENTESES;
        return t;
      } else if (caracter == ')') {
        t.cat = SN;
        t.codigo = FECHA_PARENTESES;
        return t;
      } else if (caracter == '{') {
        t.cat = SN;
        t.codigo = ABRE_CHAVES;
        return t;
      } else if (caracter == '}') {
        t.cat = SN;
        t.codigo = FECHA_CHAVES;
        return t;
      } else if (caracter == '[') {
        t.cat = SN;
        t.codigo = ABRE_COLCHETES;
        return t;
      } else if (caracter == ']') {
        t.cat = SN;
        t.codigo = FECHA_COLCHETES;
        return t;
      } else if (caracter == ';') {
        t.cat = SN;
        t.codigo = PONTO_VIRGULA;
        return t;
      } else if (caracter == '<') {
        estado = 14;
        lexema[tamL] = caracter;
        lexema[++tamL] = '\0';
      } else if (caracter == '>') {
        estado = 16;
        lexema[tamL] = caracter;
        lexema[++tamL] = '\0';
      } else if (caracter == '%') {
        t.cat = SN;
        t.codigo = MODIFICADOR;
        return t;
      } else if (caracter == '\"') {
        estado = 34;
      } else if (caracter == '\'') {
        estado = 31;
      } else if (caracter == '&') {
        estado = 18;
        lexema[tamL] = caracter;
        lexema[++tamL] = '\0';
      } else if (caracter == '!') {
        estado = 20;
        lexema[tamL] = caracter;
        lexema[++tamL] = '\0';
      } else if (caracter == '|') {
        estado = 22;
        lexema[tamL] = caracter;
        lexema[++tamL] = '\0';
      } else if (caracter == '~') {
        t.cat = SN;
        t.codigo = TIL;
        return t;
      } else if (caracter == '^') {
        t.cat = SN;
        t.codigo = CIRCUNFLEXO;
        return t;
      } else if (caracter == ':') {
        estado = 35;
        lexema[tamL] = caracter;
        lexema[++tamL] = '\0';
      } else if (caracter == EOF) {
        t.cat = FIM_ARQ;
        return t;
      } else
        error("Caracter invalido na expressao!", estado);
      break;
    case 1:
      if ((caracter >= 'a' && caracter <= 'z') ||
          (caracter >= 'A' && caracter <= 'Z') ||
          (caracter >= '0' && caracter <= '9') || (caracter == '_') ||
          (caracter == ':')) {
        estado = 1;
        lexema[tamL] = caracter;
        lexema[++tamL] = '\0';
      } else {
        ungetc(caracter, fd);
        strcpy(t.lexema, lexema);
        for (int i = 0; i < 16; i++) {
          if (strcmp(t.lexema, PALAVRAS_RESERVADAS[i]) == 0) {
            t.cat = PR;
            t.codigo = i + 1;
            return t;
          }
        }
        t.cat = ID;
        return t;
      }
      break;
    case 2:
      if (caracter >= '0' && caracter <= '9') {
        estado = 2;
        digitos[tamD] = caracter;
        digitos[++tamD] = '\0';
      } else if (caracter == '.') {
        estado = 3;
        digitos[tamD] = caracter;
        digitos[++tamD] = '\0';
      } else {
        ungetc(caracter, fd);
        t.cat = CT_I;
        t.valInt = atoi(digitos);
        return t;
      }
      break;
    case 3:
      if (caracter >= '0' && caracter <= '9') {
        estado = 3;
        digitos[tamD] = caracter;
        digitos[++tamD] = '\0';
      } else {
        ungetc(caracter, fd);
        t.cat = CT_F;
        t.valFloat = atof(digitos);
        return t;
      }
    case 7:
      if (caracter == '*') {
        estado = 8;
      } else {
        ungetc(caracter, fd);
        t.cat = SN;
        t.codigo = DIVISAO;
        return t;
      }
      break;
    case 8:
      if (caracter == '*') {
        estado = 9;
      } else {
        estado = 8;
      }
      break;
    case 9:
      if (caracter == '/') {
        estado = 0;
      } else {
        estado = 8;
      }
      break;
    case 12:
      if (caracter == '=') {
        lexema[tamL] = caracter;
        lexema[++tamL] = '\0';
        t.cat = SN;
        t.codigo = COMPARACAO;
        return t;
      } else {
        t.cat = SN;
        t.codigo = ATRIBUICAO;
        return t;
      }
      break;
    case 14:
      if (caracter == '=') {
        lexema[tamL] = caracter;
        lexema[++tamL] = '\0';
        t.cat = SN;
        t.codigo = MENOR_IGUAL;
        return t;
      } else {
        t.cat = SN;
        t.codigo = MENOR_QUE;
        return t;
      }
      break;
    case 16:
      if (caracter == '=') {
        lexema[tamL] = caracter;
        lexema[++tamL] = '\0';
        t.cat = SN;
        t.codigo = MAIOR_IGUAL;
        return t;
      } else {
        t.cat = SN;
        t.codigo = MAIOR_QUE;
        return t;
      }
      break;
    case 18:
      if (caracter == '&') {
        lexema[tamL] = caracter;
        lexema[++tamL] = '\0';
        t.cat = SN;
        t.codigo = E_LOGICO;
        return t;
      } else {
        t.cat = SN;
        t.codigo = AMPERSAND;
        return t;
      }
      break;
    case 20:
      if (caracter == '=') {
        lexema[tamL] = caracter;
        lexema[++tamL] = '\0';
        t.cat = SN;
        t.codigo = DESIGUALDADE;
        return t;
      } else {
        t.cat = SN;
        t.codigo = NOT;
        return t;
      }
      break;
    case 22:
      if (caracter == '|') {
        lexema[tamL] = caracter;
        lexema[++tamL] = '\0';
        t.cat = SN;
        t.codigo = OU_LOGICO;
        return t;
      } else {
        error("Caracter invalido", estado);
      }
      break;
    case 31:
      if ((caracter == '\n' || caracter == '\0' || isprint(caracter)) &&
          caracter != '\\' && caracter != '\'') {
        estado = 32;
        lexema[tamL] = caracter;
        lexema[++tamL] = '\0';
      } else if (caracter == '\'') {
        t.cat = CT_C;
        strcpy(t.caracter, lexema);
        return t;
      } else {
        error("Char invalido", estado);
      }
      break;
    case 32:
      if (caracter == '\'') {
        t.cat = CT_C;
        strcpy(t.caracter, lexema);
        return t;
      } else {
        error("Mais de um char", estado);
      }
      break;
    case 34:
      if (isprint(caracter) && caracter != '\n' && caracter != '\"') {
        estado = 34;
        lexema[tamL] = caracter;
        lexema[++tamL] = '\0';
      } else if (caracter == '\"') {
        t.cat = CT_S;
        strcpy(t.lexema, lexema);
        return t;
      } else {
        error("Faltando aspas de fechamento", estado);
      }
      break;
    case 35:
      if (caracter == ':') {
        lexema[tamL] = caracter;
        lexema[++tamL] = '\0';
        t.cat = SN;
        t.codigo = NAMESPACE;
        return t;
      } else {
        error("Caracter invalido", estado);
      }
      break;
    }
  }
}
