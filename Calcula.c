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
      case NAO_IGUAL:
        printf("<SN, NAO_IGUAL> ");
        break;
      case MAIOR:
        printf("<SN, MAIOR> ");
        break;
      case MENOR:
        printf("<SN, MENOR> ");
        break;
      case MENOR_IGUAL:
        printf("<SN, MENOR_IGUAL> ");
        break;
      case MAIOR_IGUAL:
        printf("<SN, MAIOR_IGUAL> ");
        break;
      case PONTO_VIRG:
        printf("<SN, PONTO_VIRG> ");
        break;
      case A_CHAVE:
        printf("<SN, A_CHAVE> ");
        break;
      case F_CHAVE:
        printf("<SN, F_CHAVE> ");
        break;
      case A_COLCHETE:
        printf("<SN, A_COLCHETES> ");
        break;
      case F_COLCHETE:
        printf("<SN, F_COLCHETE> ");
        break;
      case A_PARENTESE:
        printf("<SN,  A_PARENTESE> ");
        break;
      case F_PARENTESE:
        printf("<SN, F_PARENTESE> ");
        break;
      case OU:
        printf("<SN, OU> ");
        break;
      case AND:
        printf("<SN, AND> ");
        break;
      case ENDERECO:
        printf("<SN,  ENDERECO> ");
        break;
      case PONTO:
        printf("<SN, PONTO> ");
        break;
      case NAO:
        printf("<SN, NAO> ");
        break;
      case DESTRUCTO:
        printf("<SN, DESTRUCTO> ");
        break;
      case IDENTIF_PONTEIRO:
        printf("<SN, IDENTIF_PONTEIRO> ");
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
      printf("<CT_C, %c> ", t.caracter);
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

  Prog();

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
      case A_PARENTESE:
        printf("<SN, A_PARENTESES> ");
        break;
      case F_PARENTESE:
        printf("<SN, F_PARENTESES> ");
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