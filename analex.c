#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "Analex.h"
#define TAM_LEXEMA 50
#define TAM_NUM 20

void error(char msg[])
{
    printf("%s\n", msg);
    exit(1);
}

TOKEN AnaLex(FILE *fd)
{
    int estado;
    char lexema[TAM_LEXEMA] = "";
    int tamL = 0;
    char digitos[TAM_NUM] = "";
    int tamD = 0;
    TOKEN t;
    estado = 0;
    while (1)
    {
        char caracter = fgetc(fd);
        switch (estado)
        {
        case 0:
            if (caracter == ' ' || caracter == '\t')
                estado = 0;
            else if (caracter >= 'a' && caracter <= 'z' || caracter >= 'A' && caracter <= 'Z')
            {
                estado = 1;
                lexema[tamL] = caracter;
                lexema[++tamL] = '\0';
            }
            else if (caracter >= '0' && caracter <= '9')
            {
                estado = 2;
                digitos[tamD] = caracter;
                digitos[++tamD] = '\0';
            }
            else if (caracter == '+')
            {
                t.cat = SN;
                t.codigo = ADICAO;
                return t;
            }
            else if (caracter == '-')
            {
                t.cat = SN;
                t.codigo = SUBTRACAO;
                return t;
            }
            else if (caracter == '*')
            {
                t.cat = SN;
                t.codigo = MULTIPLICACAO;
                return t;
            }
            else if (caracter == '/')
            {
                estado = 7;
                t.cat = SN;
                t.codigo = DIVISAO;
                return t;
            }
            else if (caracter == '=')
            {
                estado = 12;
                lexema[tamL] = caracter;
                lexema[++tamL] = '\0';
            }
            else if (caracter == '(')
            {
                t.cat = SN;
                t.codigo = ABRE_PARENTESES;
                return t;
            }
            else if (caracter == ')')
            {
                t.cat = SN;
                t.codigo = FECHA_PARENTESES;
                return t;
            }
            else if (caracter == '{')
            {
                t.cat = SN;
                t.codigo = ABRE_CHAVES;
                return t;
            }
            else if (caracter == '}')
            {
                t.cat = SN;
                t.codigo = FECHA_CHAVES;
                return t;
            }
            else if (caracter == '[')
            {
                t.cat = SN;
                t.codigo = ABRE_COLCHETES;
                return t;
            }
            else if (caracter == ']')
            {
                t.cat = SN;
                t.codigo = FECHA_COLCHETES;
                return t;
            }
            else if (caracter == ';')
            {
                t.cat = SN;
                t.codigo = PONTO_VIRGULA;
                return t;
            }
            else if (caracter == '<')
            {
                estado = 14;
                lexema[tamL] = caracter;
                lexema[++tamL] = '\0';
            }
            else if (caracter == '>')
            {
                estado = 16;
                lexema[tamL] = caracter;
                lexema[++tamL] = '\0';
            }
            else if (caracter == '%')
            {
                t.cat = SN;
                t.codigo = MODIFICADOR;
                return t;
            }
            else if (caracter == '\"')
            {
                estado = 34;
            }
            else if (caracter == "'")
            {
                estado = 31;
            }
            else if (caracter == '&')
            {
                estado = 18;
                lexema[tamL] = caracter;
                lexema[++tamL] = '\0';
            }
            else if (caracter == '!')
            {
                estado = 20;
                lexema[tamL] = caracter;
                lexema[++tamL] = '\0';
            }
            else if (caracter == '|')
            {
                estado = 22;
                lexema[tamL] = caracter;
                lexema[++tamL] = '\0';
            }
            else if (caracter == EOF)
            {
                t.cat = FIM_ARQ;
                return t;
            }
            else
                error("Caracter invalido na expressao!");
            break;
        case 1:
            if ((caracter >= 'a' && caracter <= 'z') || (caracter >= 'A' && caracter <= 'Z') || (caracter >= '0' && caracter <= '9') || (caracter == '_'))
            {
                estado = 1;
                lexema[tamL] = caracter;
                lexema[++tamL] = '\0';
            }
            else
            {
                ungetc(caracter, fd);
                t.cat = ID;
                strcpy(t.lexema, lexema);
                return t;
            }
            break;
        case 2:
            if (caracter >= '0' && caracter <= '9')
            {
                estado = 2;
                digitos[tamD] = caracter;
                digitos[++tamD] = '\0';
            }
            else if (caracter == '.')
            {
                estado = 3;
                digitos[tamD] = caracter;
                digitos[++tamD] = '\0';
            }
            else
            {
                ungetc(caracter, fd);
                t.cat = CT_I;
                t.valInt = atoi(digitos);
                return t;
            }
            break;
        case 3:
            if (caracter >= '0' && caracter <= '9')
            {
                estado = 3;
                digitos[tamD] = caracter;
                digitos[++tamD] = '\0';
            }
            else
            {
                ungetc(caracter, fd);
                t.cat = CT_F;
                t.valFloat = atof(digitos);
                return t;
            }
            break;
        case 12:
            if (caracter == '=')
            {
                lexema[tamL] = caracter;
                lexema[++tamL] = '\0';
                t.cat = SN;
                t.codigo = IGUALDADE;
                return t;
            }
            else
            {
                error("Caracter invalido");
            }
            break;
        case 14:
            if (caracter == '=')
            {
                lexema[tamL] = caracter;
                lexema[++tamL] = '\0';
                t.cat = SN;
                t.codigo = MENOR_IGUAL;
                return t;
            }
            else
            {
                error("Caracter invalido");
            }
            break;
        case 16:
            if (caracter == '=')
            {
                lexema[tamL] = caracter;
                lexema[++tamL] = '\0';
                t.cat = SN;
                t.codigo = MAIOR_IGUAL;
                return t;
            }
            else
            {
                error("Caracter invalido");
            }
            break;
        case 18:
            if (caracter == '&')
            {
                lexema[tamL] = caracter;
                lexema[++tamL] = '\0';
                t.cat = SN;
                t.codigo = E_LOGICO;
                return t;
            }
            else
            {
                error("Caracter invalido");
            }
            break;
        case 20:
            if (caracter == '=')
            {
                lexema[tamL] = caracter;
                lexema[++tamL] = '\0';
                t.cat = SN;
                t.codigo = DESIGUALDADE;
                return t;
            }
            else
            {
                error("Caracter invalido");
            }
            break;
        case 22:
            if (caracter == '|')
            {
                lexema[tamL] = caracter;
                lexema[++tamL] = '\0';
                t.cat = SN;
                t.codigo = OU_LOGICO;
                return t;
            }
            else
            {
                error("Caracter invalido");
            }
            break;
        case 31:
            if ((caracter == '\n' || caracter == '\0' || isprint(caracter)) && caracter != "\\" && caracter != "\'")
            {
                estado = 32;
                lexema[tamL] = caracter;
                lexema[++tamL] = '\0';
            }
            else
            {
                error("Caracter invalido");
            }
            break;
        case 32:
            if (caracter == '\'')
            {
                t.cat = CT_C;
                strcpy(t.caracter, lexema);
                return t;
            }
            else
            {
                error("Caracter invalido");
            }
            break;
        case 34:
            if (isprint(caracter) && caracter != "\n" && caracter != "\"")
            {
                estado = 34;
                lexema[tamL] = caracter;
                lexema[++tamL] = '\0';
            }
            else if (caracter == "\"")
            {
                t.cat = CT_S;
                strcpy(t.lexema, lexema);
                return t;
            }
            else
            {
                error("Caracter invalido");
            }
            break;
        }
    }
}
