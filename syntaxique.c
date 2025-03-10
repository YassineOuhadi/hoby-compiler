#include "includes.h"
#include "data.h"

int analyse_syntaxique(FILE *file);
bool syntaxique_program();
int courant = 0;
bool type();
bool value();
bool number();
bool operation();
bool array_stmt();
bool array_items();
bool print_stmt();
bool use_stmt();
bool function_call();
bool func_identifiers();
bool return_stmt();
bool assign_expr();
bool simple_stmt();
bool stmt();
bool compound_stmt();
bool function_definition();
bool function_body();
bool function_body_stmt();
bool if_stmt();
bool condition_expr();
bool if_body();
bool break_stmt();
bool else_stmt();
bool loop_body();
bool while_stmt();
bool do_stmt();
bool for_stmt();

// La fonction principale
int analyse_syntaxique(FILE *file)
{
    program = file;
    NextChar();
    printf("[INFO] DEBUT Analyse Syntaxique ===================================================\n");
    if (syntaxique_program())
    { //
        printf("All good!!\n");
    }
    else
    {
        printf("Program not working!!\n");
        LigneError();
        exit(1);
    }
    printf("[INFO] FIN Analyse Syntaxique =====================================================\n");
    return 1;
}

// Les fonctions de l’analyseur syntaxique

bool syntaxique_program()
{
    getToken();
    while (stmt())
    {
        getToken();
    }
    getToken();
    if (currentToken.tokenCode == EOF_TOKEN){
        return true;
    }
    return false;
}

void exitWithError()
{
    printf("Something wrong in the line %d\n", ligneNumber);
    exit(1);
}

void ValidToken(char *c)
{
    printf("%d - %s ok\n", courant, c);
    courant++;
}

void LigneError()
{
    printf("Something wrong in the line %d\n", ligneNumber);
}

void TokenError(char *c)
{
    printf("Something wrong in the '%s' token, you write '%s' \n", c, currentToken.tokenValue);
}

const char *getKeywordString(token_code code)
{
    for (int i = 0; i < sizeof(keywords_code) / sizeof(token_code); i++)
    {
        if (keywords_code[i] == code)
        {
            return keywords_list[i];
        }
    }
    return NULL;
}

bool type()
{
    if (currentToken.tokenCode == ARRAY_TOKEN)
    {
        ValidToken(getKeywordString(ARRAY_TOKEN));
        getToken();
        if (currentToken.tokenCode == LT_TOKEN)
        {
            getToken();
            if (type())
            {
                getToken();
                if (currentToken.tokenCode == GT_TOKEN)
                    return true;
                else
                {
                    LigneError();
                    TokenError(getKeywordString(GT_TOKEN));
                    exit(1);
                };
            }
            else
            {
                LigneError();
                exit(1);
            }
        }
        else
        {
            LigneError();
            TokenError(getKeywordString(LT_TOKEN));
            exit(1);
        }
    }

    if (currentToken.tokenCode == NUMBER_TOKEN ||
        currentToken.tokenCode == STRING_TOKEN ||
        currentToken.tokenCode == BOOLEAN_TOKEN)
        return true;

    return false;
}

bool value()
{
    if (currentToken.tokenCode == ID_TOKEN ||
        currentToken.tokenCode == STR_TOKEN ||
        currentToken.tokenCode == TRUE_TOKEN ||
        currentToken.tokenCode == FALSE_TOKEN)
    {
        getToken();
        return true;
    }

    if (number())
    {
        getToken();
        if (currentToken.tokenCode == ADD_TOKEN ||
            currentToken.tokenCode == SUB_TOKEN ||
            currentToken.tokenCode == MUL_TOKEN ||
            currentToken.tokenCode == DIV_TOKEN)
        {
            return operation();
        }

        return true;
    }

    return array_stmt();
}

bool number()
{
    if (currentToken.tokenCode == NUM_TOKEN)
        return true;
    return false;
}

bool operation()
{
    if (currentToken.tokenCode == ADD_TOKEN ||
        currentToken.tokenCode == SUB_TOKEN ||
        currentToken.tokenCode == MUL_TOKEN ||
        currentToken.tokenCode == DIV_TOKEN)
    {
        getToken();
        return number() || value();
    }

    return false;
}

bool array_stmt()
{
    if (currentToken.tokenCode == OPSQ_TOKEN)
    {
        getToken();
        if (currentToken.tokenCode == CLSQ_TOKEN)
            return true;
        while (value())
        {

            if (currentToken.tokenCode == COMMA_TOKEN)
            {
                getToken();
                continue;
            }
            else if (currentToken.tokenCode == CLSQ_TOKEN)
            {
                getToken();
                return true;
            }
        }

        // else if (value())
        // {
        //     printf("an ndkhlou l s7iliga\n");
        //     return array_items();
        // }
        LigneError();
        TokenError(getKeywordString(CLSQ_TOKEN));
        exit(1);
    }
    return false;
}

// bool array_items()
// {
//     printf("in items\n");
//     if (value())
//     {
//         printf("was a vlaue !");
//         getToken();
//         if (currentToken.tokenCode == COMMA_TOKEN)
//         {
//             return array_items();
//         }
//         else if (currentToken.tokenCode == CLSQ_TOKEN)
//         {
//             return true;
//         }
//         LigneError();
//         exit(1);
//     }
//     return false;
// }

bool print_stmt()
{

    if (currentToken.tokenCode == PRINT_TOKEN)
    {

        ValidToken(getKeywordString(PRINT_TOKEN));
        getToken();
        if (currentToken.tokenCode == OPPAR_TOKEN)
        {
            getToken();
            if (value())
            {
                if (currentToken.tokenCode == CLPAR_TOKEN)
                {
                    getToken();
                    return true;
                }
                else
                {

                    LigneError();
                    TokenError(getKeywordString(CLPAR_TOKEN));
                    exit(1);
                }
            }
            else
            {
                LigneError();
                exit(1);
            }
        }
        else
        {
            LigneError();
            TokenError(getKeywordString(OPPAR_TOKEN));
            exit(1);
        }
    }
    return false;
}

bool use_stmt()
{
    if (currentToken.tokenCode == USE_TOKEN)
    {
        ValidToken(getKeywordString(USE_TOKEN));
        getToken();
        if (currentToken.tokenCode == STR_TOKEN)
        {
            return true;
        }
        else
        {
            LigneError();
            TokenError(getKeywordString(STR_TOKEN));
            exit(1);
        }
    }
    return false;
}

bool function_call()
{
    if (currentToken.tokenCode == ID_TOKEN)
    {
        getToken();
        if (currentToken.tokenCode == OPPAR_TOKEN)
        {
            getToken();
            if (currentToken.tokenCode == ID_TOKEN)
            {
                return func_identifiers();
            }
            else if (currentToken.tokenCode == CLPAR_TOKEN)
            {
                return true;
            }
            else
            {
                LigneError();
                exit(1);
            }
        }
        else
        {
            LigneError();
            TokenError(getKeywordString(OPPAR_TOKEN));
            exit(1);
        }
    }
    return false;
}

bool func_identifiers()
{
    if (currentToken.tokenCode == ID_TOKEN)
    {
        getToken();
        if (currentToken.tokenCode == COMMA_TOKEN)
        {
            getToken();
            return func_identifiers();
        }
        else if (currentToken.tokenCode == CLPAR_TOKEN)
        {
            return true;
        }
        else
        {
            LigneError();
            exit(1);
        }
    }
    return false;
}

bool return_stmt()
{
    if (currentToken.tokenCode == RETURN_TOKEN)
    {
        ValidToken(getKeywordString(RETURN_TOKEN));
        getToken();
        if (value())
        {
            return true;
        }
        else
        {
            LigneError();
            exit(1);
        }
    }
    return false;
}

bool assign_expr()
{
    if (type())
    {
        getToken();
        if (currentToken.tokenCode == ID_TOKEN)
        {
            getToken();
            if (currentToken.tokenCode == AFF_TOKEN)
            {
                getToken();
                return value();
            }
            return true;
        }
        else
        {
            LigneError();
            TokenError(getKeywordString(ID_TOKEN));
            exit(1);
        }
    }

    if (currentToken.tokenCode == ID_TOKEN)
    {
        getToken();
        if (currentToken.tokenCode == AFF_TOKEN)
        {
            getToken();
            return value();
        }
        else
        {
            LigneError();
            TokenError(getKeywordString(AFF_TOKEN));
            exit(1);
        }
    }

    return false;
}

bool simple_stmt()
{
    if (assign_expr())
    {
        if (operation())
            ;
        if (value())
            ;
        // getToken();
        if (currentToken.tokenCode == SEMICOLON_TOKEN)
        {
            return true;
        }
        else
        {

            LigneError();
            TokenError(getKeywordString(SEMICOLON_TOKEN));
            exit(1);
        }
    }

    if (use_stmt())
    {
        getToken();
        if (currentToken.tokenCode == SEMICOLON_TOKEN)
        {
            return true;
        }
        else
        {
            LigneError();
            TokenError(getKeywordString(SEMICOLON_TOKEN));
            exit(1);
        }
    }

    if (print_stmt())
    {
        // getToken();
        if (currentToken.tokenCode == SEMICOLON_TOKEN)
        {
            return true;
        }
        else
        {
            LigneError();
            TokenError(getKeywordString(SEMICOLON_TOKEN));
            exit(1);
        }
    }

    if (return_stmt())
    {
        // getToken();
        if (currentToken.tokenCode == SEMICOLON_TOKEN)
        {
            return true;
        }
        else
        {
            LigneError();
            TokenError(getKeywordString(SEMICOLON_TOKEN));
            exit(1);
        }
    }

    if (function_call())
    {
        getToken();
        if (currentToken.tokenCode == SEMICOLON_TOKEN)
        {
            return true;
        }
        else
        {
            LigneError();
            TokenError(getKeywordString(SEMICOLON_TOKEN));
            exit(1);
        }
    }

    return false;
}

bool stmt()
{
    if (simple_stmt())
        return true;
    if (compound_stmt())
        return true;

    return false;
}

bool compound_stmt()
{
    if (if_stmt())
        return true;
    if (for_stmt())
        return true;
    if (while_stmt())
        return true;
    if (function_definition())
        return true;
    if (do_stmt())
        return true;
    return false;
}

bool function_definition()
{
    if (currentToken.tokenCode == FUNCTION_TOKEN)
    {
        ValidToken(getKeywordString(FUNCTION_TOKEN));
        getToken();
        if (currentToken.tokenCode == ID_TOKEN)
        {
            getToken();
            if (currentToken.tokenCode == OPPAR_TOKEN)
            {
                getToken();
                while (type())
                {
                    getToken();
                    if (currentToken.tokenCode == ID_TOKEN)
                    {
                        getToken();
                        if (currentToken.tokenCode == COMMA_TOKEN)
                        {
                            getToken();
                        }
                    }
                    else
                    {
                        return false;
                    }
                }

                if (currentToken.tokenCode == CLPAR_TOKEN)
                {
                    getToken();
                    return function_body();
                }
                else
                {
                    LigneError();
                    TokenError(getKeywordString(CLPAR_TOKEN));
                    exit(1);
                }
            }
            else
            {
                LigneError();
                TokenError(getKeywordString(OPPAR_TOKEN));
                exit(1);
            }
        }
        else
        {
            LigneError();
            TokenError(getKeywordString(ID_TOKEN));
            exit(1);
        }
    }
    return false;
}

bool function_body()
{
    if (currentToken.tokenCode == OPBR_TOKEN)
    {
        getToken();
        if (function_body_stmt())
        {
            do
            {
                getToken();
            } while (function_body_stmt());
            if (currentToken.tokenCode == CLBR_TOKEN)
                return true;
        }
    }
    LigneError();
    TokenError(getKeywordString(OPBR_TOKEN));
    exit(1);
}

bool function_body_stmt()
{
    if (simple_stmt())
        return true;

    if (if_stmt())
        return true;

    if (while_stmt())
        return true;

    if (for_stmt())
        return true;

    return false;
}

// if statment
bool if_stmt()
{
    if (currentToken.tokenCode == IF_TOKEN)
    {
        ValidToken(getKeywordString(IF_TOKEN));
        getToken();
        if (currentToken.tokenCode == OPPAR_TOKEN)
        {
            getToken();
            if (condition_expr())
            {
                if (currentToken.tokenCode == CLPAR_TOKEN)
                {
                    getToken();
                    if (currentToken.tokenCode == THEN_TOKEN)
                    {
                        ValidToken(getKeywordString(THEN_TOKEN));
                        getToken();
                        return if_body();
                    }
                    else
                    {
                        LigneError();
                        TokenError(getKeywordString(THEN_TOKEN));
                        exit(1);
                    }
                }
                else
                {
                    LigneError();
                    TokenError(getKeywordString(CLPAR_TOKEN));
                    exit(1);
                }
            }
            else
            {
                LigneError();
                exit(1);
            }
        }
        else
        {
            LigneError();
            TokenError(getKeywordString(OPPAR_TOKEN));
            exit(1);
        }
    }
    return false;
}

bool condition_expr()
{
    if (currentToken.tokenCode == ID_TOKEN ||
        currentToken.tokenCode == NUM_TOKEN ||
        currentToken.tokenCode == STR_TOKEN ||
        currentToken.tokenCode == TRUE_TOKEN ||
        currentToken.tokenCode == FALSE_TOKEN)
    {
        getToken();
        if (currentToken.tokenCode == CLPAR_TOKEN)
            return true;
        if (currentToken.tokenCode == EQ_TOKEN ||
            currentToken.tokenCode == NOTEQ_TOKEN ||
            currentToken.tokenCode == LT_TOKEN ||
            currentToken.tokenCode == LET_TOKEN ||
            currentToken.tokenCode == GT_TOKEN ||
            currentToken.tokenCode == GET_TOKEN)
        {
            getToken();
            if (currentToken.tokenCode == ID_TOKEN ||
                currentToken.tokenCode == NUM_TOKEN ||
                currentToken.tokenCode == STR_TOKEN ||
                currentToken.tokenCode == TRUE_TOKEN ||
                currentToken.tokenCode == FALSE_TOKEN)
            {
                getToken();
                if (currentToken.tokenCode == AND_TOKEN ||
                    currentToken.tokenCode == OR_TOKEN)
                {
                    getToken();
                    return condition_expr();
                }
                return true;
            }
        }
    }

    if (currentToken.tokenCode == DIFF_TOKEN)
    {
        getToken();
        return condition_expr();
    }

    LigneError();
    exit(1);
}

bool if_body()
{
    if (currentToken.tokenCode == OPBR_TOKEN)
    {
        getToken();
        while (simple_stmt() || while_stmt() || for_stmt() || if_stmt() || break_stmt())
        {
            getToken();
        }
        if (currentToken.tokenCode == CLBR_TOKEN)
        {
            getToken();
            if (currentToken.tokenCode == ELSE_TOKEN)
                return else_stmt();
            return true;
        }
        return false;
    }

    if (simple_stmt())
    {
        getToken();
        if (currentToken.tokenCode == ELSE_TOKEN)
            return else_stmt();
        return true;
    }

    if (break_stmt())
    {
        getToken();
        if (currentToken.tokenCode == ELSE_TOKEN)
            return else_stmt();
        return true;
    }
    LigneError();
    exit(1);
}

bool break_stmt()
{
    if (currentToken.tokenCode == BREAK_TOKEN)
    {
        ValidToken(getKeywordString(BREAK_TOKEN));
        getToken();
        if (currentToken.tokenCode == SEMICOLON_TOKEN)
        {
            return true;
        }
        else
        {
            LigneError();
            TokenError(getKeywordString(SEMICOLON_TOKEN));
            exit(1);
        }
    }
    return false;
}

bool else_stmt()
{
    if (currentToken.tokenCode == ELSE_TOKEN)
    {
        ValidToken(getKeywordString(ELSE_TOKEN));
        getToken();
        if (currentToken.tokenCode == OPBR_TOKEN)
        {
            getToken();
            while (simple_stmt() || while_stmt() || for_stmt() || if_stmt() || break_stmt())
            {
                getToken();
            }
            if (currentToken.tokenCode == CLBR_TOKEN)
            {
                return true;
            }
            else
            {
                LigneError();
                TokenError(getKeywordString(CLBR_TOKEN));
                exit(1);
            }
            return false;
        }

        if (simple_stmt())
        {
            return true;
        }

        if (break_stmt())
        {
            return true;
        }

        if (if_stmt())
            return true;
    }
    return false;
}

bool loop_body()
{
    if (currentToken.tokenCode == OPBR_TOKEN)
    {
        getToken();
        while (simple_stmt() || while_stmt() || for_stmt() || if_stmt() || break_stmt() || else_stmt())
        {
            getToken();
            if (currentToken.tokenCode == CLBR_TOKEN)
                break;
        }
        if (currentToken.tokenCode == CLBR_TOKEN)
        {
            return true;
        }
        else
        {
            LigneError();
            TokenError(getKeywordString(CLBR_TOKEN));
            exit(1);
        }
        return false;
    }

    if (simple_stmt())
    {
        return true;
    }

    if (break_stmt())
    {
        return true;
    }

    return false;
}

bool while_stmt()
{
    if (currentToken.tokenCode == WHILE_TOKEN)
    {
        ValidToken(getKeywordString(WHILE_TOKEN));
        getToken();
        if (currentToken.tokenCode == OPPAR_TOKEN)
        {
            getToken();
            if (condition_expr())
            {
                if (currentToken.tokenCode == CLPAR_TOKEN)
                {
                    getToken();
                    return loop_body();
                }
                else
                {
                    LigneError();
                    TokenError(getKeywordString(CLPAR_TOKEN));
                    exit(1);
                }
            }
            else
            {
                LigneError();
                exit(1);
            }
        }
        else
        {
            LigneError();
            TokenError(getKeywordString(OPPAR_TOKEN));
            exit(1);
        }
    }
    return false;
}

bool do_stmt()
{
    if (currentToken.tokenCode == DO_TOKEN)
    {
        ValidToken(getKeywordString(DO_TOKEN));
        getToken();
        bool result = loop_body();
        getToken();
        while (currentToken.tokenCode == CLBR_TOKEN)
        {
            getToken();
        };
        if (currentToken.tokenCode == WHILE_TOKEN)
        {
            ValidToken(getKeywordString(WHILE_TOKEN));
            getToken();
            if (currentToken.tokenCode == OPPAR_TOKEN)
            {
                getToken();
                if (condition_expr())
                {
                    if (currentToken.tokenCode == CLPAR_TOKEN)
                    {
                        getToken();
                        return result;
                    }
                    else
                    {
                        LigneError();
                        TokenError(getKeywordString(CLPAR_TOKEN));
                        exit(1);
                    }
                }
                else
                {
                    LigneError();
                    exit(1);
                }
            }
            else
            {
                LigneError();
                TokenError(getKeywordString(OPPAR_TOKEN));
                exit(1);
            }
        }
        else
        {
            LigneError();
            TokenError(getKeywordString(WHILE_TOKEN));
            exit(1);
        }
    }
    return false;
}

bool for_stmt()
{
    if (currentToken.tokenCode == FOR_TOKEN)
    {
        ValidToken(getKeywordString(FOR_TOKEN));
        getToken();
        if (currentToken.tokenCode == OPPAR_TOKEN)
        {
            getToken();
            if (currentToken.tokenCode == ID_TOKEN)
            {
                getToken();
                if (currentToken.tokenCode == BETWEEN_TOKEN)
                {
                    ValidToken(getKeywordString(BETWEEN_TOKEN));
                    getToken();

                    if (number())
                    {
                        getToken();
                        if (currentToken.tokenCode == COLON_TOKEN)
                        {
                            getToken();
                            if (number())
                            {
                                getToken();
                                if (currentToken.tokenCode == COLON_TOKEN)
                                {
                                    getToken();
                                    if (number())
                                    {
                                        getToken();
                                        if (currentToken.tokenCode == CLPAR_TOKEN)
                                        {
                                            getToken();
                                            return loop_body();
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

                if (currentToken.tokenCode == IN_TOKEN)
                {
                    getToken();
                    if (currentToken.tokenCode == ID_TOKEN)
                    {
                        getToken();
                        if (currentToken.tokenCode == CLPAR_TOKEN)
                        {
                            getToken();
                            return loop_body();
                        }
                    }
                }
            }
        }
        LigneError();
        TokenError(getKeywordString(OPPAR_TOKEN));
        exit(1);
    }

    return false;
}
