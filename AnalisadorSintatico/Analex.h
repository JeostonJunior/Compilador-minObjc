#ifndef ANALEX

#define ANALEX
#include <stdio.h>
#define TAM_MAX_LEXEMA 31

enum TOKEN_CAT { ID = 1, PR, SN, CT_I, CT_F, CT_C, CT_S, FIM_ARQ };

/* Onde: ID: Identificador, PR: Palavra Reservada; SN: Sinal; CT_*: Constante
 * numÃ©rica ou caracter, LT: cadeia de caracter */

enum PAL_RESERV {
  CLASS = 1,
  CODE,
  DATA,
  INTERN,
  VOID,
  CHAR,
  INT,
  FLOAT,
  BOOL,
  IF,
  ELSE,
  WHILE,
  FOR,
  RETURN,
  DELETE,
  NEW
}; // completar com nomes de cÃ³digos correspondentes Ã s palavras reservadas
   // restantes de MinObjC

enum BOOL { FALSE, TRUE };

enum SINAIS {
  PONTO_VIRG = 1,
  DOIS_PONTOS,
  DIVISAO,
  ATRIBUICAO,
  ADICAO,
  SUBTRACAO,
  MULTIPLICACAO,
  MODIFICADOR,
  A_PARENTESE,
  F_PARENTESE,
  A_CHAVE,
  F_CHAVE,
  MAIOR,
  MENOR,
  A_COLCHETE,
  F_COLCHETE,
  AND,
  NAO,
  VIRGULA,
  OU,
  IDENTIF_PONTEIRO,
  ASPAS_S,
  ASPAS_D,
  PONTO,
  COMPARACAO,
  MAIOR_IGUAL,
  MENOR_IGUAL,
  NAO_IGUAL,
  ENDERECO,
  DESTRUCTO,
  NAMESPACE
}; // completar com nomes de cÃ³digos correspondentes sinais restantes de
   // MinObjC

typedef

    struct {

  enum TOKEN_CAT cat; // deve receber uma das constantes de enum TOKEN_CAT
  enum BOOL processado;

  union { // parte variÃ¡vel do registro

    int codigo; // para tokens das categorias PR e SN

    int indice; // indica o Ã­ndice da tabela onde o Analex armazenou um literal
                // (cadeia de caracter) para tokens da cat. LT

    char lexema[TAM_MAX_LEXEMA]; // cadeia de caractares que corresponde o nome
                                 // do token da cat. ID

    int valInt; // valor da constante ineira em tokens da cat. CT_I

    float valFloat; // valor da constante ineira em tokens da cat. CT_F

    char caracter; // caracter do token da cat. CT_C
  };

} TOKEN; // Tipo TOKEN

extern TOKEN t;
extern FILE *fd;
TOKEN AnaLex(FILE *);

#endif