#include "Analex.h"
#include "Anasint.h"
#include "Funcaux.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Variaveis globais */

TOKEN t;
FILE *fd;
enum BOOL mostraArvore = TRUE;
char TABS[200] = "";
void errorArq() {
  printf("Arquivo não encontrado");
  exit(1);
}

void TestaAnalex() {
  if ((fd = fopen("expressao.dat", "r")) == NULL) {
    errorArq();
  }
  while (1) {
    t = AnaLex(fd);
    switch (t.cat) {
    case PR:
      switch (t.codigo) {
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
      printf("<ID, %s> ", t.lexema);
      break;
    case SN:
      switch (t.codigo) {
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
      printf("<CT_I, %d> ", t.valInt);
      break;
    case CT_C:
      printf("<CT_C, %s> ", t.caracter);
      break;
    case CT_S:
      printf("<CT_S, %s> ", t.lexema);
      break;
    case CT_F:
      printf("<CT_F, %f> ", t.valFloat);
      break;
    case FIM_ARQ:
      printf("\nFim da expressao encontrado.\n");
    }
    if (t.cat == FIM_ARQ) {
      break;
    }
  }
  fclose(fd);
}
void TestaAnasint() {
  if ((fd = fopen("expressao.dat", "r")) == NULL)
    erro("Arquivo de entrada da expressao nao encontrado!");

  Atrib();

  if (t.cat == FIM_ARQ)
    printf("Resultado> Expressao OK!\n");
  else {
    switch (t.cat) {
    case ID:
      printf("<ID, %s> ", t.lexema);
      break;
    case SN:
      switch (t.codigo) {
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
      case ABRE_PARENTESES:
        printf("<SN, ABRE_PARENTESES> ");
        break;
      case FECHA_PARENTESES:
        printf("<SN, FECHA_PARENTESES> ");
        break;
      }
      break;
    case CT_I:
      printf("<CT_I, %d> ", t.valInt);
      break;
    case FIM_ARQ:;
    }
    erro("Erro de sintaxe!");
  }
  fclose(fd);
}

int main() {

  printf("\n[Analise Lexica -------------------]\n");
  TestaAnalex();
  printf("\n[Analise Sintatica ----------------]\n");
  TestaAnasint();
}