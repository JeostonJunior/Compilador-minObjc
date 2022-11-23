/*  Gramática livre de Contexto de Cálcula

    <ARTIB> ::= ID = <EXPR>
        <EXPR> ::= <TERMO> <RESTO>
        <RESTO> ::= + <TERMO> <RESTO> |	- <TERMO> <RESTO> | e
        <TERMO> ::= <FATOR> <SOBRA>
        <SOBRA> ::= * <FATOR> <SOBRA> | / <FATOR> <SOBRA> | e
        <FATOR> ::= CT_I | ID | (<EXPR>)

   Símbolo de partida: <ATRIB>

*/
#include "Anasint.h"
#include "Analex.h"
#include "Funcaux.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
void Atrib() {
  if (mostraArvore)
    PrintNodo("<Atrib>", AVANCA);
  t = AnaLex(fd);
  if (t.cat != ID) {
    erro("Identificador esperado!");
  }
  if (mostraArvore)
    PrintNodo(t.lexema, MANTEM);
  t = AnaLex(fd);
  if (t.cat != SN || t.codigo != ATRIBUICAO) {
    erro("Sinal de atribuicao esperado!");
  }
  if (mostraArvore)
    PrintNodo("=", MANTEM);
  t.processado = TRUE;
  Expr();
  if (mostraArvore)
    PrintNodo("", RETROCEDE);
}

void Expr() {

  if (mostraArvore)
    PrintNodo("<Expr>", AVANCA);
  Termo();
  Resto();
  if (mostraArvore)
    PrintNodo("", RETROCEDE);
}

void Termo() {

  if (mostraArvore)
    PrintNodo("<Termo>", AVANCA);
  Fator();
  Sobra();
  if (mostraArvore)
    PrintNodo("", RETROCEDE);
}

void Resto() {

  if (mostraArvore)
    PrintNodo("<Resto>", AVANCA);
  if (t.processado)
    t = AnaLex(fd);
  if (t.cat == SN && (t.codigo == ADICAO || t.codigo == SUBTRACAO)) {
    t.processado = TRUE;
    if (mostraArvore) {
      if (t.codigo == ADICAO)
        PrintNodo("+", MANTEM);
      else
        PrintNodo("-", MANTEM);
    }
    Termo();
    Resto();
  } else if (mostraArvore)
    PrintNodo("<e>", MANTEM);

  if (mostraArvore)
    PrintNodo("", RETROCEDE);
}

void Sobra() {

  if (mostraArvore)
    PrintNodo("<Sobra>", AVANCA);
  if (t.processado)
    t = AnaLex(fd);
  if (t.cat == SN && (t.codigo == MULTIPLICACAO || t.codigo == DIVISAO)) {
    t.processado = TRUE;
    if (mostraArvore) {
      if (t.codigo == MULTIPLICACAO)
        PrintNodo("*", MANTEM);
      else
        PrintNodo("/", MANTEM);
    }
    Fator();
    Sobra();
  } else if (mostraArvore)
    PrintNodo("<e>", MANTEM);

  if (mostraArvore)
    PrintNodo("", RETROCEDE);
}

void Fator() {

  if (mostraArvore)
    PrintNodo("<Fator>", AVANCA);
  if (t.processado)
    t = AnaLex(fd);
  if (t.cat == ID) {
    t.processado = TRUE;
    if (mostraArvore)
      PrintNodo(t.lexema, MANTEM);
    /*TRATAR IDENTIFICADOR*//*
  } else if (t.cat == CT_I) {
    t.processado = TRUE;
    if (mostraArvore)
      PrintNodoInt(t.valInt, MANTEM);
    /*TRATAR CONSTANTE INTEIRA*//*
  } else if (t.cat == SN && t.codigo == A_PARENTESE) {
    t.processado = TRUE;
    if (mostraArvore)
      PrintNodo("(", MANTEM);
    Expr();
    if (t.cat != SN || t.codigo != F_PARENTESE) {
      erro("Fecha parenteses esperado!");
    } else {
      t.processado = TRUE;
      if (mostraArvore)
        PrintNodo(")", MANTEM);
    }
  } else {
    erro("Identificador, constante inteira ou abre parenteses esperado!");
  }
  if (mostraArvore)
    PrintNodo("", RETROCEDE);
}
*/
void Prog() {
  if (mostraArvore)
    PrintNodo("<Prog>", AVANCA);
  t = AnaLex(fd);
  while (t.cat != FIM_ARQ) {
    ObjDef();
    Decl();
    // Func();
    t = AnaLex(fd);
  }
  if (mostraArvore)
    PrintNodo("", RETROCEDE);
}

void ObjDef() {
  if (t.cat == PR && t.codigo == CLASS) {
    PrintNodo("CLASS", MANTEM);
    t = AnaLex(fd);
    if (t.cat == ID) {
      PrintNodo(t.lexema, MANTEM);
      t = AnaLex(fd);
      if (t.codigo == A_CHAVE) {
        PrintNodo("{", MANTEM);
        DataSec();
        MethSec();
      } else
        erro("Esperado abre-chaves");
      // t = AnaLex(fd);
      if (t.codigo == F_CHAVE) {
        PrintNodo("}", MANTEM);
        t = AnaLex(fd);
      } else
        erro("Esperado fecha-chaves");
    } else
      erro("Esperado identificador");
  } else
    return;
}

void Decl() {
  PrintNodo("<Decl>", AVANCA);
  if (!verificaTipo()) {
    erro("Tipo/Void esperado");
  }
  t = AnaLex(fd);
  if (t.cat == ID) {
    PrintNodo(t.lexema, AVANCA);
    t = AnaLex(fd);
    if (t.codigo == A_PARENTESE) {
      PrintNodo("(", MANTEM);
      t = AnaLex(fd);
      TiposParam();
      if (t.codigo == F_PARENTESE) {
        PrintNodo(")", MANTEM);
        t = AnaLex(fd);
        while (t.codigo == VIRGULA) {
          PrintNodo(",", MANTEM);
          t = AnaLex(fd);
          if (t.cat == ID) {
            PrintNodo(t.lexema, AVANCA);
            t = AnaLex(fd);
            if (t.codigo == A_PARENTESE) {
              PrintNodo("(", MANTEM);
              t = AnaLex(fd);
              TiposParam();
              if (t.codigo == F_PARENTESE) {
                PrintNodo(")", AVANCA);
                t = AnaLex(fd);
              }
            }
          }
        }
        if (t.codigo != PONTO_VIRG)
          erro("Esperado ponto e virgula");
        else
          PrintNodo(";", MANTEM);
      } else
        erro("Esperado fecha parentese");
    } else {
      DeclListVar();
      t = AnaLex(fd);
      if (t.codigo != PONTO_VIRG)
        erro("Esperado ponto e virgula");
      else
        PrintNodo(";", MANTEM);
    }
  } else if (t.codigo == IDENTIF_PONTEIRO) {
    PrintNodo("^", AVANCA);
    t = AnaLex(fd);
    DeclListVar();
    t = AnaLex(fd);
    if (t.codigo != PONTO_VIRG)
      erro("Esperado ponto e virgula");
    else
      PrintNodo(";", MANTEM);
  }
}

// printf("cat: %d codigo: %d", t.cat, t.codigo);

/*if (t.codigo == IDENTIF_PONTEIRO) {
  DeclListVar();
}*/

void DataSec() {
  if (mostraArvore)
    PrintNodo("<DataSec>", AVANCA);
  t = AnaLex(fd);
  if (t.codigo == DATA) {
    PrintNodo("DATA", MANTEM);
    t = AnaLex(fd);
    if (t.codigo == DOIS_PONTOS) {
      PrintNodo(":", MANTEM);
      t = AnaLex(fd);
      if (t.codigo != VOID && t.codigo != CHAR && t.codigo != INT &&
          t.codigo != BOOL && t.codigo != FLOAT)
        erro("Esperado Lista de variaveis");
      do {
        DeclListVar();
        // t = AnaLex(fd);
        if (t.codigo != PONTO_VIRG)
          erro("Esperado ponto e virgula");
        else
          PrintNodo(";", MANTEM);
        t = AnaLex(fd);
      } while (t.codigo == VOID || t.codigo == CHAR || t.codigo == INT ||
               t.codigo == BOOL || t.codigo == FLOAT);
    }
  }
  PrintNodo("", RETROCEDE);
}

void DeclListVar() {
  PrintNodo("<DeclListVar>", AVANCA);
  verificaTipo();
  t = AnaLex(fd);
  if (t.codigo == IDENTIF_PONTEIRO) {
    PrintNodo("^", MANTEM);
    t = AnaLex(fd);
  }
  DeclVar();
  // t = AnaLex(fd);
  while (t.codigo == VIRGULA) {
    t = AnaLex(fd);
    if (t.codigo == IDENTIF_PONTEIRO) {
      PrintNodo("^", MANTEM);
      t = AnaLex(fd);
    }
    DeclVar();
    // t = AnaLex(fd);
  }
  PrintNodo("", RETROCEDE);
}

void DeclVar() {
  PrintNodo("<DeclVar>", AVANCA);
  // t = AnaLex(fd);
  if (t.cat == ID) {
    PrintNodo(t.lexema, MANTEM);
    t = AnaLex(fd);
    if (t.codigo == A_COLCHETE) {
      PrintNodo("[", MANTEM);
      t = AnaLex(fd);
      if (t.cat == CT_I) {
        PrintNodoInt(t.valInt, AVANCA);
      } else
        erro("Esperado constante inteira");
      t = AnaLex(fd);
      if (t.codigo == F_COLCHETE) {
        PrintNodo("", RETROCEDE);
        PrintNodo("]", MANTEM);
        t = AnaLex(fd);
      } else
        erro("Esperado fecha colchete");
    }
  } else
    erro("Esperado identificador");
  PrintNodo("", RETROCEDE);
}

void MethSec() {
  if (mostraArvore)
    PrintNodo("<MethSec>", AVANCA);
  if (t.codigo == CODE) {
    PrintNodo("CODE", MANTEM);
    t = AnaLex(fd);
    if (t.codigo == DOIS_PONTOS) {
      PrintNodo(":", MANTEM);
      t = AnaLex(fd);
      do {
        FuncProt();
      } while (verificaTipo());
    }
  }
  if (t.codigo == INTERN) {
    PrintNodo("INTERN", MANTEM);
    t = AnaLex(fd);
    if (t.codigo == DOIS_PONTOS) {
      PrintNodo(":", MANTEM);
      t = AnaLex(fd);
      do {
        FuncProt();
      } while (verificaTipo());
    }
  }
}

void FuncProt() {
  PrintNodo("<FuncProt>", AVANCA);
  if (!verificaTipo()) {
    PrintNodo("<e>", MANTEM);
    PrintNodo("", RETROCEDE);
    return;
  }
  t = AnaLex(fd);
  if (t.codigo == IDENTIF_PONTEIRO) {
    PrintNodo("^", MANTEM);
    t = AnaLex(fd);
  }
  if (t.cat == ID) {
    PrintNodo(t.lexema, MANTEM);
    t = AnaLex(fd);
    if (t.codigo == A_PARENTESE) {
      PrintNodo("(", MANTEM);
      t = AnaLex(fd);
      TiposParam();
      if (t.codigo == F_PARENTESE) {
        PrintNodo(")", MANTEM);
      }
    } else
      erro("Esperado abre parentese");
  } else
    erro("Esperado identificador");
  t = AnaLex(fd);
  if (t.codigo == PONTO_VIRG) {
    PrintNodo(";", MANTEM);
    t = AnaLex(fd);
  } else
    erro("Ponto e virgula necessario");
}

void TiposParam() {
  PrintNodo("<TiposParam>", AVANCA);
  do {
    if (t.codigo == VIRGULA) {
      PrintNodo(",", MANTEM);
      t = AnaLex(fd);
    }
    if (verificaTipo()) {
      t = AnaLex(fd);
      if (t.codigo == ENDERECO) {
        PrintNodo("&", MANTEM);
        t = AnaLex(fd);
        if (t.codigo == IDENTIF_PONTEIRO) {
          PrintNodo("^", MANTEM);
          t = AnaLex(fd);
        }
        if (t.cat == ID) {
          PrintNodo(t.lexema, MANTEM);
          t = AnaLex(fd);
        } else
          erro("Identificador esperado");
      } else {
        if (t.codigo == IDENTIF_PONTEIRO) {
          PrintNodo("^", MANTEM);
          t = AnaLex(fd);
        }
        if (t.cat == ID) {
          PrintNodo(t.lexema, MANTEM);
          t = AnaLex(fd);
          if (t.codigo == A_COLCHETE) {
            PrintNodo("[", MANTEM);
            t = AnaLex(fd);
            if (t.codigo == F_COLCHETE) {
              PrintNodo("]", MANTEM);
              t = AnaLex(fd);
            } else
              erro("Fecha colchete esperado");
          }
        } else
          erro("Identificador esperado");
      }
    } else {
      PrintNodo("", RETROCEDE);
      PrintNodo("<e>", MANTEM);
      return;
    }
  } while (t.codigo == VIRGULA);
}

enum BOOL verificaTipo() {
  switch (t.codigo) {
  case VOID:
    PrintNodo("VOID", AVANCA);
    break;
  case INT:
    PrintNodo("INT", MANTEM);
    break;
  case CHAR:
    PrintNodo("CHAR", MANTEM);
    break;
  case FLOAT:
    PrintNodo("FLOAT", MANTEM);
    break;
  case BOOL:
    PrintNodo("BOOL", MANTEM);
    break;
  default:
    return FALSE;
  }
  return TRUE;
}