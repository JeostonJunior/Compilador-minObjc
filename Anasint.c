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
    /*TRATAR IDENTIFICADOR*/
  } else if (t.cat == CT_I) {
    t.processado = TRUE;
    if (mostraArvore)
      PrintNodoInt(t.valInt, MANTEM);
    /*TRATAR CONSTANTE INTEIRA*/
  } else if (t.cat == SN && t.codigo == ABRE_PARENTESES) {
    t.processado = TRUE;
    if (mostraArvore)
      PrintNodo("(", MANTEM);
    Expr();
    if (t.cat != SN || t.codigo != FECHA_PARENTESES) {
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