#ifndef _ANASINT_
#define _ANASINT_

#include "Analex.h"
#include <stdio.h>

/* Variaveis globais */
extern TOKEN t;
extern FILE *fd;

extern enum BOOL mostraArvore;
extern char TABS[500];

/* Assinaturas das funcoes */
void Prog();
void ObjDef();
void DataSec();
void MethSec();
void DeclListVar();
void Decl();
void DeclVar();
void Tipo();
void TiposParam();
void Func();
void FuncProt();
void Escopo();
void Cmd();
void Atrib();
void Expr();
void ExprSimp();
void Termo();
void Fator();

enum BOOL verificaOpRel();
enum BOOL verificaTipo();

#endif // ANASINT