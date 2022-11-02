#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "Analex.h"
#define TAM_LEXEMA 50
#define TAM_NUM 20

void error(char msg[], int estado)
{
    printf("%s no estado:%d", msg, estado);
    exit(1);
}
void errorArq()
{
    printf("Arquivo não encontrado");
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
    char PALAVRAS_RESERVADAS[16][10] = {"class", "data:", "code:", "intern:", "void", "char", "int", "float", "bool", "if", "else", "while", "for", "return", "delete", "new"};
    while (1)
    {
        char caracter = fgetc(fd);
        switch (estado)
        {
        case 0:
            if (caracter == ' ' || caracter == '\t' || caracter == '\n')
            {
                estado = 0;
            }
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
                lexema[tamL] = caracter;
                lexema[++tamL] = '\0';
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
            else if (caracter == '\'')
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
            else if (caracter == '~')
            {
                t.cat = SN;
                t.codigo = TIL;
                return t;
            }
            else if (caracter == '^')
            {
                t.cat = SN;
                t.codigo = CIRCUNFLEXO;
                return t;
            }
            else if (caracter == ':')
            {
                estado = 35;
                lexema[tamL] = caracter;
                lexema[++tamL] = '\0';
            }
            else if (caracter == EOF)
            {
                t.cat = FIM_ARQ;
                return t;
            }
            else
                error("Caracter invalido na expressao!", estado);
            break;
        case 1:
            if ((caracter >= 'a' && caracter <= 'z') || (caracter >= 'A' && caracter <= 'Z') || (caracter >= '0' && caracter <= '9') || (caracter == '_') || (caracter == ':'))
            {
                estado = 1;
                lexema[tamL] = caracter;
                lexema[++tamL] = '\0';
            }
            else
            {
                ungetc(caracter, fd);
                strcpy(t.lexema, lexema);
                for (int i = 0; i < 16; i++)
                {
                    if (strcmp(t.lexema, PALAVRAS_RESERVADAS[i]) == 0)
                    {
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
        case 7:
            if (caracter == '*')
            {
                estado = 8;
            }
            else
            {
                ungetc(caracter, fd);
                t.cat = SN;
                t.codigo = DIVISAO;
                return t;
            }
            break;
        case 8:
            if (caracter == '*')
            {
                estado = 9;
            }
            else
            {
                estado = 8;
            }
            break;
        case 9:
            if (caracter == '/')
            {
                estado = 0;
            }
            else
            {
                estado = 8;
            }
            break;
        case 12:
            if (caracter == '=')
            {
                lexema[tamL] = caracter;
                lexema[++tamL] = '\0';
                t.cat = SN;
                t.codigo = COMPARACAO;
                return t;
            }
            else
            {
                t.cat = SN;
                t.codigo = ATRIBUICAO;
                return t;
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
                t.cat = SN;
                t.codigo = MENOR_QUE;
                return t;
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
                t.cat = SN;
                t.codigo = MAIOR_QUE;
                return t;
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
                t.cat = SN;
                t.codigo = AMPERSAND;
                return t;
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
                t.cat = SN;
                t.codigo = NOT;
                return t;
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
                error("Caracter invalido", estado);
            }
            break;
        case 31:
            if ((caracter == '\n' || caracter == '\0' || isprint(caracter)) && caracter != '\\' && caracter != '\'')
            {
                estado = 32;
                lexema[tamL] = caracter;
                lexema[++tamL] = '\0';
            }
            else if (caracter == '\'')
            {
                t.cat = CT_C;
                strcpy(t.caracter, lexema);
                return t;
            }
            else
            {
                error("Char invalido", estado);
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
                error("Mais de um char", estado);
            }
            break;
        case 34:
            if (isprint(caracter) && caracter != '\n' && caracter != '\"')
            {
                estado = 34;
                lexema[tamL] = caracter;
                lexema[++tamL] = '\0';
            }
            else if (caracter == '\"')
            {
                t.cat = CT_S;
                strcpy(t.lexema, lexema);
                return t;
            }
            else
            {
                error("Faltando aspas de fechamento", estado);
            }
            break;
        case 35:
            if (caracter == ':')
            {
                lexema[tamL] = caracter;
                lexema[++tamL] = '\0';
                t.cat = SN;
                t.codigo = NAMESPACE;
                return t;
            }
            else
            {
                error("Caracter invalido", estado);
            }
            break;
        }
    }
}

int main()
{
    FILE *fd;
    TOKEN tk;
    if ((fd = fopen("expressao.dat", "r")) == NULL)
        errorArq();
    while (1)
    {
        tk = AnaLex(fd);
        switch (tk.cat)
        {
        case PR:
            switch (tk.codigo)
            {
            case CLASS:
                printf("<PR, CLASS> ");
                break;
            case DATA:
                printf("<PR, DATA> ");
                break;
            case CODE:
                printf("<PR, CODE> ");
                break;
            case INTERN:
                printf("<PR, INTERN> ");
                break;
            case RETURN:
                printf("<PR, RETURN> ");
                break;
            case DELETE:
                printf("<PR, DELETE> ");
                break;
            case NEW:
                printf("<PR, NEW> ");
                break;
            case IF:
                printf("<PR, IF> ");
                break;
            case ELSE:
                printf("<PR, ELSE> ");
                break;
            case FOR:
                printf("<PR, FOR> ");
                break;
            case WHILE:
                printf("<PR, WHILE> ");
                break;
            case VOID:
                printf("<PR, VOID> ");
                break;
            case CHAR:
                printf("<PR, CHAR> ");
                break;
            case INT:
                printf("<PR, INT> ");
                break;
            case BOOL:
                printf("<PR, BOOL> ");
                break;
            case FLOAT:
                printf("<PR, FLOAT> ");
                break;
            }
            break;
        case ID:
            printf("<ID, %s> ", tk.lexema);
            break;
        case SN:
            switch (tk.codigo)
            {
            case ATRIBUICAO:
                printf("<SN, ATRIBUICAO> ");
                break;
            case ADICAO:
                printf("<SN, ADICAO> ");
                break;
            case SUBTRACAO:
                printf("<SN, SUBTRACAO> ");
                break;
            case MULTIPLICACAO:
                printf("<SN, MULTIPLICACAO> ");
                break;
            case DIVISAO:
                printf("<SN, DIVISAO> ");
                break;
            case MODIFICADOR:
                printf("<SN, MODIFICADOR> ");
                break;
            case COMPARACAO:
                printf("<SN, COMPARACAO> ");
                break;
            case DESIGUALDADE:
                printf("<SN, DESIGUALDADE> ");
                break;
            case MAIOR_QUE:
                printf("<SN, MAIOR_QUE> ");
                break;
            case MENOR_QUE:
                printf("<SN, MENOR_QUE> ");
                break;
            case MENOR_IGUAL:
                printf("<SN, MENOR_IGUAL> ");
                break;
            case MAIOR_IGUAL:
                printf("<SN, MAIOR_IGUAL> ");
                break;
            case PONTO_VIRGULA:
                printf("<SN, PONTO_VIRGULA> ");
                break;
            case ABRE_CHAVES:
                printf("<SN, ABRE_CHAVES> ");
                break;
            case FECHA_CHAVES:
                printf("<SN, FECHA_CHAVES> ");
                break;
            case ABRE_COLCHETES:
                printf("<SN, ABRE_COLCHETES> ");
                break;
            case FECHA_COLCHETES:
                printf("<SN, FECHA_COLCHETES> ");
                break;
            case ABRE_PARENTESES:
                printf("<SN,  ABRE_PARENTESES> ");
                break;
            case FECHA_PARENTESES:
                printf("<SN, FECHA_PARENTESES> ");
                break;
            case OU_LOGICO:
                printf("<SN, OU_LOGICO> ");
                break;
            case E_LOGICO:
                printf("<SN, E_LOGICO> ");
                break;
            case AMPERSAND:
                printf("<SN,  AMPERSAND> ");
                break;
            case PONTO:
                printf("<SN, PONTO> ");
                break;
            case NOT:
                printf("<SN, NOT> ");
                break;
            case TIL:
                printf("<SN, TIL> ");
                break;
            case CIRCUNFLEXO:
                printf("<SN, CIRCUNFLEXO> ");
                break;
            case NAMESPACE:
                printf("<SN, NAMESPACE> ");
                break;
            }
            break;
        case CT_I:
            printf("<CT_I, %d> ", tk.valInt);
            break;
        case CT_C:
            printf("<CT_C, %s> ", tk.caracter);
            break;
        case CT_S:
            printf("<CT_S, %s> ", tk.lexema);
            break;
        case CT_F:
            printf("<CT_F, %f> ", tk.valFloat);
            break;
        case FIM_ARQ:
            printf("\nFim da expressao encontrado.\n");
        }
        if (tk.cat == FIM_ARQ)
        {
            break;
        }
    }
    fclose(fd);
    return 0;
}
