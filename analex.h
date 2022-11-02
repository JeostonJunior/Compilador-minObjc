#ifndef ANALEX
#define ANALEX

#define TAM_MAX_LEXEMA 31

enum TOKEN_CAT
{
    ID = 1,
    PR,
    SN,
    CT_I,
    CT_F,
    CT_C,
    CT_S,
    FIM_ARQ
};
enum PAL_RESERV
{
    CLASS = 1,
    DATA,
    CODE,
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
};
enum SINAIS
{
    ATRIBUICAO = 1,
    ADICAO,
    SUBTRACAO,
    MULTIPLICACAO,
    DIVISAO,
    MODIFICADOR,
    COMPARACAO,
    DESIGUALDADE,
    MAIOR_QUE,
    MENOR_QUE,
    MENOR_IGUAL,
    MAIOR_IGUAL,
    PONTO_VIRGULA,
    ABRE_CHAVES,
    FECHA_CHAVES,
    ABRE_COLCHETES,
    FECHA_COLCHETES,
    ABRE_PARENTESES,
    FECHA_PARENTESES,
    OU_LOGICO,
    E_LOGICO,
    PONTO,
    AMPERSAND,
    TIL,
    NOT,
    CIRCUNFLEXO,
    NAMESPACE
};

typedef struct
{
    enum TOKEN_CAT cat;
    union
    {
        int codigo;
        int indice;
        char lexema[TAM_MAX_LEXEMA];
        int valInt;
        float valFloat;
        char caracter[1];
    };
} TOKEN;
#endif