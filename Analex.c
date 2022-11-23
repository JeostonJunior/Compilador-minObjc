#include "Analex.h"
#include "Funcaux.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define TAM_LEXEMA 50
#define TAM_NUM 20

void error(char msg[], int estado) {
  printf("%s no estado:%d", msg, estado);
  exit(1);
}


TOKEN AnaLex(FILE *fd)
{

  int estado;

  char lexema[TAM_LEXEMA] = "";

  int tamanho_lexema = 0;

  char digitos[TAM_NUM] = "";

  int tamanho_digito = 0;

  TOKEN token;

  estado = 0;

  t.processado = FALSE;

  while (1)
  {

    char c = fgetc(fd);

    switch (estado)
    {

    case 0:
      if (c == ' ' || c == '\t'|| c=='\n')
        estado = 0;
      else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
      { // inicio de identificador - inicializa lexema

        estado = 1;

        lexema[tamanho_lexema] = c;

        lexema[++tamanho_lexema] = '\0';
      }

      else if (c >= '1' && c <= '9')
      { // inicio de constante inteira - inicializa digitos

        estado = 10;

        digitos[tamanho_digito] = c;

        digitos[++tamanho_digito] = '\0';
      }

      else if (c == ';')
      {

        token.cat = SN;

        token.codigo = PONTO_VIRG;

        return token;
      }

      else if (c == ':')
      {
        estado = 16;
      }

      else if (c == '+')
      {

        token.cat = SN;

        token.codigo = ADICAO;

        return token;
      }

      else if (c == '-')
      { // sinal de subtracao - monta e devolve token

        token.cat = SN;

        token.codigo = SUBTRACAO;

        return token;
      }

      else if (c == '*')
      { // sinal de multiplicacao - monta e devolve token

        token.cat = SN;

        token.codigo = MULTIPLICACAO;

        return token;
      }

      else if (c == '/')
      { // sinal de divisao - monta e devolve token
        estado = 13;
      }

      else if (c == '=')
      { // sinal de atribuicao - monta e devolve token
        estado = 5;
      }

      else if (c == '%')
      {

        token.cat = SN;

        token.codigo = MODIFICADOR;

        return token;
      }

      else if (c == '(')
      { // sinal de abre parenteses - monta e devolve token

        token.cat = SN;

        token.codigo = A_PARENTESE;

        return token;
      }

      else if (c == ')')
      { // sinal de fecha parenteses - monta e devolve token

        token.cat = SN;

        token.codigo = F_PARENTESE;

        return token;
      }

      else if (c == '{')
      {

        token.cat = SN;

        token.codigo = A_CHAVE;

        return token;
      }

      else if (c == '}')
      {

        token.cat = SN;

        token.codigo = F_CHAVE;

        return token;
      }

      else if (c == '>')
      {
        estado = 6;
      }

      else if (c == '<')
      {
        estado = 7;
      }

      else if (c == '[')
      {

        token.cat = SN;

        token.codigo = A_COLCHETE;

        return token;
      }

      else if (c == ']')
      {

        token.cat = SN;

        token.codigo = F_COLCHETE;

        return token;
      }

      else if (c == '&')
      {
        estado = 8;
      }

      else if (c == '!')
      {
        estado = 9;
      }

      else if (c == ',')
      {

        token.cat = SN;

        token.codigo = VIRGULA;

        return token;
      }

      else if (c == '~')
      {

        token.cat = SN;

        token.codigo = DESTRUCTO;

        return token;
      }

      else if (c == '|')
      {
        estado = 12;
      }

      else if (c == '^')
      {

        token.cat = SN;

        token.codigo = IDENTIF_PONTEIRO;

        return token;
      }

      else if (c == '\'')
      {

        estado = 2;
      }

      else if (c == '"')
      {

        estado = 4;
      }

      else if (c == EOF)
      { // fim da expressao encontrado

        token.cat = FIM_ARQ;

        return token;
      }

      else

        error("Caracter invalido na expressao!", estado); // sem transicao valida no AFD

      break;

    case 1:
      if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || (c == '_'))
      {

        estado = 1;

        lexema[tamanho_lexema] = c; // acumula caracteres lidos em lexema

        lexema[++tamanho_lexema] = '\0';
      }

      else
      { // transicao OUTRO* do estado 1 do AFD
        ungetc(c, fd);
        // tratamento de palavras reservadas
        if (strcmp("class", lexema) == 0)
        {
          token.cat = PR;
          token.codigo = CLASS;
          return token;
        }
        else if (strcmp("code", lexema) == 0)
        {
          token.cat = PR;
          token.codigo = CODE;
          return token;
        }
        else if (strcmp("data", lexema) == 0)
        {
          token.cat = PR;
          token.codigo = DATA;
          return token;
        }
        else if (strcmp("intern", lexema) == 0)
        {
          token.cat = PR;
          token.codigo = INTERN;
          return token;
        }
        else if (strcmp("void", lexema) == 0)
        {
          token.cat = PR;
          token.codigo = VOID;
          return token;
        }
        else if (strcmp("char", lexema) == 0)
        {
          token.cat = PR;
          token.codigo = CHAR;
          return token;
        }
        else if (strcmp("int", lexema) == 0)
        {
          token.cat = PR;
          token.codigo = INT;
          return token;
        }
        else if (strcmp("float", lexema) == 0)
        {
          token.cat = PR;
          token.codigo = FLOAT;
          return token;
        }
        else if (strcmp("bool", lexema) == 0)
        {
          token.cat = PR;
          token.codigo = BOOL;
          return token;
        }
        else if (strcmp("if", lexema) == 0)
        {
          token.cat = PR;
          token.codigo = IF;
          return token;
        }

        else if (strcmp("else", lexema) == 0)
        {
          token.cat = PR;
          token.codigo = ELSE;
          return token;
        }

        else if (strcmp("while", lexema) == 0)
        {
          token.cat = PR;
          token.codigo = WHILE;
          return token;
        }

        else if (strcmp("for", lexema) == 0)
        {
          token.cat = PR;
          token.codigo = FOR;
          return token;
        }

        else if (strcmp("return", lexema) == 0)
        {
          token.cat = PR;
          token.codigo = RETURN;
          return token;
        }
        else if (strcmp("delete", lexema) == 0)
        {
          token.cat = PR;
          token.codigo = DELETE;
          return token;
        }
        else
        {
          token.cat = ID;

          strcpy(token.lexema, lexema);

          return token;
        }
        // monta token identificador e retorna
      }

      break;
    case 2:
      if ((isprint(c) || c == '\n' || c == '\0') && c != '\'' && c != '\\')
      {
        estado = 3;
        lexema[tamanho_lexema] = c;
        lexema[++tamanho_lexema] = '\0';
      }
      else
        error("caracter invalido na expressao", estado);
      break;

    case 3:
      if (c == '\'')
      {
        token.cat = CT_C;

        token.caracter = lexema[tamanho_lexema - 1];

        return token;
      }
      break;

    case 4:
      if (isprint(c) && c != '"' && c != '\n')
      {
        lexema[tamanho_lexema] = c;
        lexema[++tamanho_lexema] = '\0';
      }
      else if (c == '"')
      {
        token.cat = CT_S;

        strcpy(token.lexema, lexema);
        return token;
      }
      break;
    case 5:
      if (c == '=')
      {
        token.cat = SN;
        token.codigo = COMPARACAO;
        return token;
      }
      else
      {
        ungetc(c, fd);

        token.cat = SN;

        token.codigo = ATRIBUICAO;

        return token;
      }
      break;

    case 6:
      if (c == '=')
      {
        token.cat = SN;
        token.codigo = MAIOR_IGUAL;
        return token;
      }
      else
      {
        ungetc(c, fd);

        token.cat = SN;

        token.codigo = MAIOR;

        return token;
      }
      break;

    case 7:
      if (c == '=')
      {
        token.cat = SN;
        token.codigo = MENOR_IGUAL;
        return token;
      }
      else
      {
        ungetc(c, fd);

        token.cat = SN;

        token.codigo = MENOR;

        return token;
      }
      break;

    case 8:
      if (c == '&')
      {
        token.cat = SN;
        token.codigo = AND;
        return token;
      }
      else
      {
        ungetc(c, fd);

        token.cat = SN;

        token.codigo = ENDERECO;

        return token;
      }
      break;

    case 9:
      if (c == '=')
      {
        token.cat = SN;
        token.codigo = NAO_IGUAL;
        return token;
      }
      else
      {
        ungetc(c, fd);

        token.cat = SN;

        token.codigo = NAO;

        return token;
      }
      break;

    case 10:
      if (c >= '0' && c <= '9')
      {

        estado = 10;

        digitos[tamanho_digito] = c; // acumula digitos lidos na variaavel digitos

        digitos[++tamanho_digito] = '\0';
      }
      else if (c == '.')
      {
        estado = 11;

        digitos[tamanho_digito] = c;

        digitos[++tamanho_digito] = '\0';
      }
      else
      { // transicao OUTRO* do estado 10 do AFD

        // monta token constante inteira e retorna

        ungetc(c, fd);

        token.cat = CT_I;

        token.valInt = atoi(digitos);

        return token;
      }
      break;

    case 11:
      if (c >= '0' && c <= '9')
      {
        digitos[tamanho_digito] = c;

        digitos[++tamanho_digito] = '\0';
      }
      else
      {
        ungetc(c, fd);

        token.cat = CT_F;

        token.valFloat = atof(digitos);

        return token;
      }
      break;

    case 12:
      if (c == '|')
      {
        token.cat = SN;
        token.codigo = OU;
        return token;
      }
      else
      {
        error("caracter invalido na expressao", estado);
      }
      break;
    // Tratamento de comentario
    case 13:
      if (c == '*')
        estado = 14;
      else
      {
        ungetc(c, fd);

        token.cat = SN;

        token.codigo = DIVISAO;

        return token;
      }
      break;
    case 14:
      if (c == '*')
        estado = 15;
      else
        estado = 14;
      break;

    case 15:
      if (c == '/')
        estado = 0;
      else
        estado = 14;
      break;

    case 16:
      if (c == ':')
      {
        token.cat = SN;
        token.codigo = NAMESPACE;
        return token;
      }
      else
      {
        ungetc(c, fd);

        token.cat = SN;

        token.codigo = DOIS_PONTOS;

        return token;
      }
      break;
    }
  }
}
/*
int main()
{

  FILE *fd;

  TOKEN tk;

  if ((fd = fopen("expressao.dat", "r")) == NULL)

    error("Arquivo de entrada da expressao nao encontrado!");

  while (1)
  {

    tk = AnaLex(fd);

    switch (tk.cat)
    {

    case ID:
      printf("<ID, %s> ", tk.lexema);

      break;

    case SN:
      switch (tk.codigo)
      {

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

      case ATRIBUICAO:
        printf("<SN, ATRIBUICAO> ");

        break;

      case COMPARACAO:
        printf("<SN, COMPARACAO> ");

        break;

      case MENOR_IGUAL:
        printf("<SN, MENOR IGUAL> ");

        break;

      case A_PARANETESE:
        printf("<SN, ABRE_PARENTESES> ");

        break;

      case F_PARENTESE:
        printf("<SN, FECHA_PARENTESES> ");

        break;
      }

      break;

    case CT_I:
      printf("<CT_I, %d> ", tk.valInt);

      break;

    case CT_F:
      printf("<CT_F, %f> ", tk.valFloat);

      break;
    case CT_C:
      printf("<CT_C, %c> ", tk.caracter);
      break;
    case CT_S:
      printf("<CT_S, %s> ", tk.lexema);
      break;
    case PR:
      switch (tk.codigo)
      {
      case CLASS:
        printf("<PR, CLASS> ");
        break;
      case CODE:
        printf("<PR, CODE> ");
        break;
      case DATA:
        printf("<PR, DATA> ");
        break;
      case INTERN:
        printf("<PR, INTERN> ");
        break;
      }
      break;
    case FIM_ARQ:
      printf("\nFim da expressao encontrado.\n");
    }

    if (tk.cat == FIM_ARQ)
      break;
  }

  fclose(fd);

  return 0;
}
*/