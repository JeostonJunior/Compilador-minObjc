#include "Anasint.h"
#include "Analex.h"
#include "Funcaux.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Prog() {
  if (mostraArvore)
    PrintNodo("<Prog>", AVANCA);
  t = AnaLex(fd);
  while (t.cat != FIM_ARQ) {
    ObjDef();
    // Decl();
    Func();
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
        erro("Esperando: '{'");
      // t = AnaLex(fd);
      if (t.codigo == F_CHAVE) {
        PrintNodo("}", MANTEM);
        t = AnaLex(fd);
      } else
        erro("Esperando: '}'");
    } else
      erro("Esperando: ID");
  } else
    return;
}

void verificaVirgula() {}

void Decl() {
  PrintNodo("<Decl>", AVANCA);
  if (!verificaTipo()) {
    erro("Esperando: 'TYPE'");
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
                PrintNodo(")", MANTEM);
                t = AnaLex(fd);
              }
            } else {
              erro("Esperando '('");
            }
          } else {
            erro("Esperando ID");
          }
        }
        if (t.codigo != PONTO_VIRG) {
          erro("Esperando: ';'");
        } else {
          PrintNodo(";", MANTEM);
          return;
        }
      } else {
        erro("Esperando ')'");
      }
    }
  } else if (t.codigo == IDENTIF_PONTEIRO) {
    PrintNodo("^", AVANCA);
    DeclListVar();
    PrintNodo(";", AVANCA);
    return;
  } else {
    erro("Esperando ID");
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
        erro("Esperando: 'LIST_VAR'");
      do {
        DeclListVar();
        // t = AnaLex(fd);
        if (t.codigo != PONTO_VIRG)
          erro("Esperando: ';'");
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
    PrintNodo("^", AVANCA);
    t = AnaLex(fd);
  }
  DeclVar();
  // t = AnaLex(fd);
  while (t.codigo == VIRGULA) {
    t = AnaLex(fd);
    if (t.codigo == IDENTIF_PONTEIRO) {
      PrintNodo("^", AVANCA);
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
    PrintNodo(t.lexema, AVANCA);
    t = AnaLex(fd);
    if (t.codigo == A_COLCHETE) {
      PrintNodo("[", AVANCA);
      t = AnaLex(fd);
      if (t.cat == CT_I) {
        PrintNodoInt(t.valInt, AVANCA);
      } else
        erro("Esperando: CT_I");
      t = AnaLex(fd);
      if (t.codigo == F_COLCHETE) {
        PrintNodo("", RETROCEDE);
        PrintNodo("]", AVANCA);
        t = AnaLex(fd);
      } else
        erro("Esperado ']'");
    }
  } else
    erro("Esperando: ID");
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
    PrintNodo("<ε>", MANTEM);
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
      erro("Esperando: '('");
  } else
    erro("Esperando: ID");
  t = AnaLex(fd);
  if (t.codigo == PONTO_VIRG) {
    PrintNodo(";", MANTEM);
    t = AnaLex(fd);
  } else
    erro("Esperando: ';'");
}

void TiposParam() {
  PrintNodo("<TiposParam>", AVANCA);
  do {
    if (t.codigo == VIRGULA) {
      t = AnaLex(fd);
      if (!verificaTipo()) {
        erro("Esperando ')'");
      }
      PrintNodo(",", MANTEM);
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
          erro("Esperando: ID");
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
              erro("Esperando: ']'");
          }
        } else
          erro("Esperando: ID");
      }
    } else if (t.cat == ID) {
      erro("Esperando: 'TYPE'");
    } else {
      PrintNodo("", RETROCEDE);
      PrintNodo("ε", MANTEM);
      return;
    }
  } while (t.codigo == VIRGULA);
}

void Func() {
  PrintNodo("<Func>", AVANCA);
  if (!verificaTipo())
    return;
  t = AnaLex(fd);
  if (t.codigo == IDENTIF_PONTEIRO) {
    PrintNodo("^", MANTEM);
    t = AnaLex(fd);
  }
  if (t.cat == ID) {
    PrintNodo(t.lexema, MANTEM);
    t = AnaLex(fd);
  } else
    erro("Esperando: ID");
  if (t.codigo == NAMESPACE) {
    PrintNodo("::", MANTEM);
    t = AnaLex(fd);
    if (t.cat == ID) {
      PrintNodo(t.lexema, MANTEM);
      t = AnaLex(fd);
    } else
      erro("Esperando: ID");
  }
  if (t.codigo == A_PARENTESE) {
    PrintNodo("(", MANTEM);
    t = AnaLex(fd);
    TiposParam();
    if (t.codigo == F_PARENTESE) {
      PrintNodo(")", MANTEM);
      t = AnaLex(fd);
    } else
      erro("Esperando: ')'");
  } else
    erro("Esperando: '('");
  if (t.codigo == A_CHAVE) {
    PrintNodo("{", MANTEM);
    t = AnaLex(fd);
    while (verificaTipo()) {
      t = AnaLex(fd);
      if (t.codigo == IDENTIF_PONTEIRO) {
        PrintNodo("^", MANTEM);
        t = AnaLex(fd);
      }
      DeclVar();
      while (t.codigo == VIRGULA) {
        PrintNodo(",", MANTEM);
        t = AnaLex(fd);
        if (t.codigo == IDENTIF_PONTEIRO) {
          PrintNodo("^", MANTEM);
          t = AnaLex(fd);
        }
        DeclVar();
        // t = AnaLex(fd);
        // printf("cat: %d codigo: %d",t.cat, t.codigo);
      }
      if (t.codigo == PONTO_VIRG) {
        PrintNodo(";", MANTEM);
        t = AnaLex(fd);
      } else
        erro("Esperando: ';'");
    }
    while (t.codigo != F_CHAVE) {
      Cmd();
    }
    if (t.codigo == F_CHAVE) {
      PrintNodo("}", MANTEM);
    } else
      erro("Esperando: '}'");
  }
}

void Cmd() {
  PrintNodo("<Cmd>", AVANCA);
  switch (t.codigo) {
  case IF:
    PrintNodo("IF", MANTEM);
    t = AnaLex(fd);
    if (t.codigo == A_PARENTESE) {
      PrintNodo("(", MANTEM);
      Expr();
      if (t.codigo == F_PARENTESE) {
        PrintNodo(")", MANTEM);
        t = AnaLex(fd);
      } else
        erro("Esperando: ')'");
    } else
      erro("Esperando: '('");
    Cmd();
    if (t.codigo == ELSE) {
      Cmd();
    }
    break;
  case WHILE:
    PrintNodo("WHILE", MANTEM);
    t = AnaLex(fd);
    if (t.codigo == A_PARENTESE) {
      PrintNodo("(", MANTEM);
      t = AnaLex(fd);
      Expr();
      if (t.codigo == F_PARENTESE) {
        PrintNodo(")", MANTEM);
        t = AnaLex(fd);
      } else
        erro("Esperando: ')'");
    } else
      erro("Esperando: '('");
    Cmd();
    break;
  case FOR:
    PrintNodo("FOR", MANTEM);
    t = AnaLex(fd);
    if (t.codigo == A_PARENTESE) {
      PrintNodo("(", MANTEM);
      t = AnaLex(fd);
      if (t.cat == ID) {
        Atrib();
      } else
        erro("Esperando: ID");
      if (t.codigo == PONTO_VIRG) {
        PrintNodo(";", MANTEM);
        Expr();
      } else
        erro("Esperando:  ';'");
      if (t.codigo == PONTO_VIRG) {
        PrintNodo(";", MANTEM);
        Atrib();
      } else
        erro("Esperando:  ';'");
      if (t.codigo == F_PARENTESE) {
        PrintNodo(")", MANTEM);
        t = AnaLex(fd);
      } else
        erro("Esperando: ')'");
    } else
      erro("Esperando: '('");
    Cmd();
    break;
  case RETURN:
    PrintNodo("RETURN", MANTEM);
    t = AnaLex(fd);
    if (t.cat == ID || t.codigo == IDENTIF_PONTEIRO) {
      Expr();
    }
    break;
  case DELETE:
    PrintNodo("DELETE", MANTEM);
    t = AnaLex(fd);
    if (t.cat == ID) {
      PrintNodo(t.lexema, MANTEM);
      t = AnaLex(fd);
    } else
      erro("Esperando: ID");
    break;
  case A_CHAVE:
    PrintNodo("A_CHAVE", MANTEM);
    t = AnaLex(fd);
    while (t.codigo != F_CHAVE || t.codigo != FIM_ARQ)
      Cmd();
    if (t.codigo == F_CHAVE) {
      PrintNodo("A_CHAVE", MANTEM);
      t = AnaLex(fd);
    } else
      erro("Esperando: '}'");
    break;
  case PONTO_VIRG:
    break;
  default:
    if (t.codigo == IDENTIF_PONTEIRO) {
      PrintNodo("^", MANTEM);
      t = AnaLex(fd);
      if (t.cat != ID)
        erro("Esperando: ID");
    }
    if (t.cat == ID) {
      PrintNodo(t.lexema, MANTEM);
      t = AnaLex(fd);
      if (t.codigo == A_COLCHETE || t.codigo == ATRIBUICAO) {
        Atrib();
      } else {
        if (t.codigo == PONTO) {
          PrintNodo(".", MANTEM);
          t = AnaLex(fd);
          if (t.cat == ID) {
            PrintNodo(t.lexema, MANTEM);
            t = AnaLex(fd);
          } else
            erro("Esperando: ID");
        }
        if (t.codigo == A_PARENTESE) {
          PrintNodo("(", MANTEM);
          t = AnaLex(fd);
          Expr();
          while (t.codigo == VIRGULA) {
            Expr();
          }
          if (t.codigo == F_PARENTESE) {
            PrintNodo(")", MANTEM);
            t = AnaLex(fd);
          } else
            erro("Esperando: ')'");
        } else
          erro("Esperando: ID");
      }
    }
    break;
  }
  if (t.codigo == PONTO_VIRG) {
    PrintNodo(";", MANTEM);
    t = AnaLex(fd);
  } else
    erro("Esperando: ';'");
}

void Atrib() {
  PrintNodo("<Atrib>", AVANCA);
  if (t.cat == ID || t.codigo == ATRIBUICAO || t.codigo == A_COLCHETE) {
    if (t.cat == ID) {
      PrintNodo(t.lexema, MANTEM);
      t = AnaLex(fd);
    }
    if (t.codigo == A_COLCHETE) {
      PrintNodo("[", MANTEM);
      t = AnaLex(fd);
      Expr();
      if (t.codigo == F_COLCHETE) {
        PrintNodo("]", MANTEM);
        t = AnaLex(fd);
      } else
        erro("Esperando: ']'");
    }
    if (t.codigo == ATRIBUICAO) {
      PrintNodo("=", MANTEM);
      t = AnaLex(fd);
      if (t.codigo == NEW && t.cat == PR) {
        PrintNodo("NEW", MANTEM);
        t = AnaLex(fd);
        if (!verificaTipo())
          erro("Esperando: 'TYPE'");
      } else {
        t.processado = FALSE;
        Expr();
      }
    }
  }
}

void Expr() {
  PrintNodo("<Expr>", AVANCA);
  if (t.processado)
    t = AnaLex(fd);
  t.processado = TRUE;
  ExprSimp();
  // t = AnaLex(fd);
  if (verificaOpRel())
    t = AnaLex(fd);
  ExprSimp();
}

void ExprSimp() {
  PrintNodo("<ExprSimp>", AVANCA);
  if (t.codigo == ADICAO) {
    PrintNodo("+", MANTEM);
    t = AnaLex(fd);
  } else if (t.codigo == SUBTRACAO) {
    PrintNodo("-", MANTEM);
    t = AnaLex(fd);
  }
  Termo();
  while (t.codigo == ADICAO || t.codigo == SUBTRACAO || t.codigo == OU) {
    switch (t.codigo) {
    case ADICAO:
      PrintNodo("+", MANTEM);
      t = AnaLex(fd);
      break;
    case SUBTRACAO:
      PrintNodo("-", MANTEM);
      t = AnaLex(fd);
      break;
    case OU:
      PrintNodo("||", MANTEM);
      t = AnaLex(fd);
      break;
    }
    Termo();
  }
}

void Termo() {
  PrintNodo("<Termo>", AVANCA);
  Fator();
  while (t.codigo == MULTIPLICACAO || t.codigo == DIVISAO || t.codigo == AND) {
    switch (t.codigo) {
    case MULTIPLICACAO:
      PrintNodo("*", MANTEM);
      break;
    case DIVISAO:
      PrintNodo("/", MANTEM);
      break;
    case AND:
      PrintNodo("&&", MANTEM);
      break;
    }
    Fator();
  }
}

void Fator() {
  PrintNodo("<Fator>", AVANCA);
  if (t.codigo == IDENTIF_PONTEIRO) {
    PrintNodo("^", MANTEM);
    t = AnaLex(fd);
    if (t.cat != ID)
      erro("Esperando: ID");
  }
  if (t.cat == ID) {
    PrintNodo(t.lexema, MANTEM);
    t = AnaLex(fd);
    if (t.codigo == PONTO) {
      PrintNodo(".", MANTEM);
      t = AnaLex(fd);
    }
    if (t.cat == ID) {
      PrintNodo(t.lexema, MANTEM);
      t = AnaLex(fd);
      if (t.codigo == A_PARENTESE) {
        PrintNodo("(", MANTEM);
        t = AnaLex(fd);
        Expr();
        while (t.codigo == VIRGULA) {
          Expr();
        }
        if (t.codigo == F_PARENTESE) {
          PrintNodo(")", MANTEM);
          t = AnaLex(fd);
        } else
          erro("Esperando: ')'");
      } else
        erro("Esperando: ID");
    }
    if (t.codigo == A_COLCHETE) {
      PrintNodo("[", MANTEM);
      t = AnaLex(fd);
      Expr();
      if (t.codigo == F_COLCHETE) {
        PrintNodo("]", MANTEM);
        t = AnaLex(fd);
      } else
        erro("Esperando: ']'");
    }
  }
  if (t.cat == CT_I) {
    PrintNodoInt(t.valInt, MANTEM);
    t = AnaLex(fd);
  } else if (t.cat == CT_F) {
    PrintNodoFloat(t.valFloat, MANTEM);
    t = AnaLex(fd);
  } else if (t.cat == CT_C) {
    PrintNodoChar(t.caracter, MANTEM);
    t = AnaLex(fd);
  }
  if (t.codigo == NAO) {
    PrintNodo("!", MANTEM);
    Fator();
  }
  if (t.codigo == A_PARENTESE) {
    PrintNodo("(", MANTEM);
    t = AnaLex(fd);
    Expr();
    if (t.codigo == F_PARENTESE) {
      PrintNodo(")", MANTEM);
      t = AnaLex(fd);
    } else
      erro("Esperando: ')'");
  }
}
enum BOOL verificaTipo() {
  switch (t.codigo) {
  case VOID:
    PrintNodo("VOID", AVANCA);
    break;
  case INT:
    PrintNodo("INT", AVANCA);
    break;
  case CHAR:
    PrintNodo("CHAR", AVANCA);
    break;
  case FLOAT:
    PrintNodo("FLOAT", AVANCA);
    break;
  case BOOL:
    PrintNodo("BOOL", AVANCA);
    break;
  default:
    return FALSE;
  }
  return TRUE;
}

enum BOOL verificaOpRel() {
  switch (t.codigo) {
  case COMPARACAO:
    PrintNodo("COMPARACAO", AVANCA);
    break;
  case NAO_IGUAL:
    PrintNodo("NAO_IGUAL", AVANCA);
    break;
  case MENOR_IGUAL:
    PrintNodo("MENOR_IGUAL", AVANCA);
    break;
  case MENOR:
    PrintNodo("MENOR", AVANCA);
    break;
  case MAIOR:
    PrintNodo("MAIOR", AVANCA);
    break;
  case MAIOR_IGUAL:
    PrintNodo("MAIOR_IGUAL", AVANCA);
    break;
  default:
    return FALSE;
  }
  return TRUE;
}
