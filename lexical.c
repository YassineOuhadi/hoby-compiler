#include "includes.h"
#include "data.h"

int analyse_lexicale(FILE *file);
bool lexicale_program();

void printCurrentToken();
void getToken();
void LexError(char *message);
void clearWord();
void clearToken();
void ignoreWhiteSpaces();
void exitWithError();
char NextChar();
bool isCurrentCharEOF();
bool isDigit();
bool isChar();
bool isAlphaNum();
bool isSeparator();
bool isEOF();
bool isSpecial();
bool isNumber();
bool isString();
bool isWord();
bool hoby_program();

// La fonction principale
int analyse_lexicale(FILE *file)
{
    program = file;
    NextChar();
    lexicale_program();
    return 1;
}

// Les fonctions de l'analyseur lexical
bool lexicale_program()
{
    printf("[INFO] DEBUT Analyse Lexicale ===================================================\n");
    do
    {
        getToken();
        printCurrentToken();
        // printCurrentToken();
    } while (!isCurrentCharEOF());

    printf("[INFO] FIN Analyse Lexicale =====================================================\n");
    // go back to first of file :
    fseek(program, 0, SEEK_SET);
    ligneNumber = 1;
    return 1;
}

void printCurrentToken()
{
    printf("%s_TOKEN   ==>  %s\n", currentToken.tokenName, currentToken.tokenValue);
}

void LexError(char *message)
{
    printf("%s\n", message);
    exit(1);
}

void clearWord()
{
    memset(currentWord, '\0', sizeof(currentWord));
    lastIndex = 0;
}

void clearToken()
{
    memset(currentToken.tokenName, '\0', sizeof(currentToken.tokenName));
    memset(currentToken.tokenValue, '\0', sizeof(currentToken.tokenValue));
}

void ignoreWhiteSpaces()
{
    // Ignore blank space, tabulation, newline
    while (isSeparator())
    {
        NextChar();
    }
}

void getToken()
{
    clearToken();
    clearWord();

    // Ignore Whitespaces and Newlines and Comments
    ignoreWhiteSpaces();

    if (isEOF())
    {
    }
    else if (isNumber())
    {
    }
    else if (isString())
    {
    }
    else if (isWord())
    {
    }
    else if (isSpecial())
    {
    }
    else
    {
        LexError("Invalid Token");
    }
}

char NextChar()
{
    return currentChar = getc(program);
}

bool isDigit()
{
    if (currentChar >= '0' && currentChar <= '9')
        return true;
    else
        return false;
}

bool isChar()
{
    if (toupper(currentChar) >= 'A' && toupper(currentChar) <= 'Z')
        return true;
    else
        return false;
}

bool isAlphaNum()
{
    if ((toupper(currentChar) >= 'A' && toupper(currentChar) <= 'Z') || (currentChar >= '0' && currentChar <= '9'))
        return true;
    else
        return false;
}

bool isSeparator()
{
    // newLine = false;
    switch (currentChar)
    {
    case ' ':
        // nouvLigne = false;
        return true;
    case '\n':
        ligneNumber += 1;
        return true;
    case '\r':

        return true;
    case '\t':
        // nouvLigne = false;
        return true;
    default:
        // nouvLigne = false;
        return false;
    }
}

bool isSpecialChar()
{
    switch (currentChar)
    {
    case ';':
        return true;
    case '.':
        return true;
    case ',':
        return true;
    case '<':
        return true;
    case '-':
        return true;
    case '>':
        return true;
    case '=':
        return true;
    case '!':
        return true;
    case '{':
        return true;
    case '}':
        return true;
    case '(':
        return true;
    case ')':
        return true;
    case '[':
        return true;
    case ']':
        return true;
    case '#':
        return true;
    case '/':
        return true;
    case '+':
        return true;
    case '*':
        return true;
    case ':':
        return true;
    }
    return false;
}

bool isCurrentCharEOF()
{
    if (currentChar == EOF)
    {

        return true;
    }
    return false;
}

bool isEOF()
{
    if (currentChar == EOF)
    {

        strcpy(currentToken.tokenValue, "EOF");
        strcpy(currentToken.tokenName, "EOF");
        currentToken.tokenCode = EOF_TOKEN;

        return true;
    }
    return false;
}

bool isSpecial()
{
    if (!isSpecialChar(currentChar))
        return false;

    currentWord[lastIndex] = currentChar;
    lastIndex += 1;

    currentChar = NextChar();
    currentWord[lastIndex] = currentChar;
    if (isSpecialChar(currentChar))
    {
        currentWord[lastIndex + 1] = '\0';
    }
    else
    {
        currentWord[lastIndex] = '\0';
    }

    int sizeSpecialTokens = sizeof(specialTokens_symb) / sizeof(specialTokens_symb[0]);
    int sizeMultiCharsSpecialTokens = sizeof(multiCharsSpecialTokens_symb) / sizeof(multiCharsSpecialTokens_symb[0]);

    if (strlen(currentWord) == 2)
    {
        for (int i = 0; i < sizeMultiCharsSpecialTokens; i++)
        {
            if ((strcmp(currentWord, multiCharsSpecialTokens_symb[i]) == 0))
            {
                strcpy(currentToken.tokenName, multiCharsSpecialTokens_list[i]);
                strcpy(currentToken.tokenValue, multiCharsSpecialTokens_symb[i]);
                currentToken.tokenCode = multiCharsSpecialTokens_code[i];
                currentChar = NextChar();
                return true;
            }
        }
    }

    currentWord[lastIndex] = '\0';

    for (int i = 0; i < sizeSpecialTokens; i++)
    {
        if (strcmp(currentWord, specialTokens_symb[i]) == 0)
        {
            strcpy(currentToken.tokenName, specialTokens_list[i]);
            strcpy(currentToken.tokenValue, specialTokens_symb[i]);
            currentToken.tokenCode = specialTokens_code[i];
            return true;
        }
    }

    LexError("Invalid Token");
}

bool isNumber()
{
    if (!isdigit(currentChar))
        return false;

    currentWord[lastIndex] = currentChar;

    while (++lastIndex <= MAX_SIZE && isdigit(currentWord[lastIndex] = currentChar = NextChar()))
        ;

    if (lastIndex > MAX_SIZE)
        LexError("Word exceeded the maximum");

    currentWord[lastIndex] = '\0';

    strcpy(currentToken.tokenName, "NUM");
    strcpy(currentToken.tokenValue, currentWord);
    currentToken.tokenCode = NUM_TOKEN;

    return true;
}

bool isString()
{
    if (currentChar != '"')
        return false;

    currentWord[lastIndex] = currentChar;

    while (++lastIndex <= MAX_SIZE && (currentWord[lastIndex] = currentChar = NextChar()) != '"')
        ;

    if (lastIndex == MAX_SIZE)
        LexError("there is many characters in this word");

    currentWord[lastIndex + 1] = '\0';

    if (currentWord[0] == '"' && currentWord[lastIndex] == '"')
    {
        strcpy(currentToken.tokenValue, currentWord);
        strcpy(currentToken.tokenName, "STR");
        currentToken.tokenCode = STR_TOKEN;
    }
    else
    {
        LexError("String not closed properly!!");
    }

    currentChar = NextChar();

    return true;
}

bool isWord()
{

    if (!isChar(currentChar))
        return false;

    int i = 0, j = 0, cmp = 0;
    currentWord[lastIndex] = toupper(currentChar);

    while (++lastIndex <= MAX_SIZE && (isAlphaNum(currentWord[lastIndex] = currentChar = toupper(NextChar())) || currentChar == '_'))
        ;

    if (lastIndex == MAX_SIZE)
        LexError("there is many characters in this word");

    currentWord[lastIndex] = '\0';

    int keywordsSize = sizeof(keywords_code) / sizeof(keywords_code[0]);

    // Verify this word match a keyword in the list of keywords
    while ((cmp = strcmp(currentWord, keywords_list[j++])) != 0 && j < keywordsSize)
        ;

    if (cmp == 0)
    { // is keyword
        strcpy(currentToken.tokenName, keywords_list[j - 1]);
        strcpy(currentToken.tokenValue, currentWord);
        currentToken.tokenCode = keywords_code[j - 1];
    }

    else
    { // If not keyword, so it's an ID
        strcpy(currentToken.tokenName, "ID");
        strcpy(currentToken.tokenValue, currentWord);
        currentToken.tokenCode = ID_TOKEN;
    }

    return true;
}
