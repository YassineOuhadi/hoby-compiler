#ifndef Data_H
#define Data_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SIZE 21




typedef enum{

    ID_TOKEN, // Identifier
    EOF_TOKEN, // END OF FILE
    PRINT_TOKEN, // print(put)
    USE_TOKEN, // use
    

    BOOLEAN_TOKEN, // boolean
    TRUE_TOKEN, // true
    FALSE_TOKEN, // false
    NUMBER_TOKEN, // number
    NUM_TOKEN, // 12345
    STRING_TOKEN, // string
    STR_TOKEN, // "hoby"
    ARRAY_TOKEN, // array
    

    IN_TOKEN, // in
    BETWEEN_TOKEN, // between
    

    FUNCTION_TOKEN, // function
    IF_TOKEN, // if
    ELSE_TOKEN,  // else
    THEN_TOKEN, // then 
    WHILE_TOKEN, // while
    DO_TOKEN, // Do While
    FOR_TOKEN, // for
    BREAK_TOKEN, // break
    RETURN_TOKEN, // return


    PT_TOKEN, // .
    COMMA_TOKEN,  // , 
    SEMICOLON_TOKEN, // ;
    AFF_TOKEN, // :=
    LT_TOKEN, // <
    GT_TOKEN, // >
    ADD_TOKEN, // +
    SUB_TOKEN, // -
    DIV_TOKEN, // /
    MUL_TOKEN, // *
    EQ_TOKEN, // ==
    LET_TOKEN, // <=
    GET_TOKEN, // >=
    OPSQ_TOKEN, // [
    CLSQ_TOKEN, // ]
    OPPAR_TOKEN, // (
    CLPAR_TOKEN, // )
    OPBR_TOKEN, // {
    CLBR_TOKEN, // }
    NOTEQ_TOKEN, // !=
    AND_TOKEN, // AND
    OR_TOKEN, // OR
    COLON_TOKEN, // :
    DIFF_TOKEN // !
}token_code;





extern const char* keywords_list[]= 
{"TRUE", "FALSE", "ARRAY", "BOOLEAN" , "NUMBER", "STRING", "IN", "WHILE", "BETWEEN", "PRINT", "USE", "FUNCTION", "IF", "THEN", "BREAK", "ELSE", "FOR", "RETURN", "AND", "OR", "DO"};

extern token_code keywords_code[]= 
{TRUE_TOKEN, FALSE_TOKEN, ARRAY_TOKEN, BOOLEAN_TOKEN , NUMBER_TOKEN, STRING_TOKEN, IN_TOKEN, WHILE_TOKEN, BETWEEN_TOKEN, PRINT_TOKEN, USE_TOKEN, FUNCTION_TOKEN, IF_TOKEN, THEN_TOKEN, BREAK_TOKEN, ELSE_TOKEN, FOR_TOKEN, RETURN_TOKEN, AND_TOKEN, OR_TOKEN, DO_TOKEN};







extern const char* specialTokens_list[] = 
{ "COLON", "SEMICOLON",  "PT",  "PLUS", "MINUS", "MULT", "DIV", "COMMA", "LT", "GT", "DIFF", "OPENPAR",  "CLOSEPAR", "OPENSQ", "CLOSESQ", "OPENBR", "CLOSEBR"};

extern token_code specialTokens_code[] = 
{ COLON_TOKEN, SEMICOLON_TOKEN, PT_TOKEN, ADD_TOKEN, SUB_TOKEN, MUL_TOKEN, DIV_TOKEN, COMMA_TOKEN, LT_TOKEN, GT_TOKEN, DIFF_TOKEN, OPPAR_TOKEN, CLPAR_TOKEN, OPSQ_TOKEN, CLSQ_TOKEN, OPBR_TOKEN, CLBR_TOKEN};

extern const char* specialTokens_symb[] = 
{   ":",     ";",        ".",    "+",    "-",     "*",    "/",   "," ,  "<",  ">",   "!",      "(",         ")",       "[",       "]",     "{",       "}"};





extern const char* multiCharsSpecialTokens_list[] = 
{"EQUAL", "AFF",  "LET", "GET", "NOTEQUAL"};

extern const char* multiCharsSpecialTokens_symb[] = 
{ "==",   ":=",    "<=", ">=",       "!="};

extern token_code multiCharsSpecialTokens_code[] = 
{EQ_TOKEN, AFF_TOKEN, LET_TOKEN, GET_TOKEN, NOTEQ_TOKEN};




FILE * program;
char currentWord[MAX_SIZE];
int lastIndex = 0;
char currentChar;
int ligneNumber = 1;




typedef struct
{
    token_code tokenCode;
    char tokenName[MAX_SIZE];
    char tokenValue[MAX_SIZE];
} Token;


Token currentToken;




#endif 
