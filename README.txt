## HOBY COMPILER

Les fichiers nécessaires pour tester le compilateur:
 - includes.h
 - data.h
 - lexical.c
 - syntaxique.c
 - main.c
 - main.hoby   (le programme en langage HOBY)

Pour le compiler, utilisez la commande suivante:
 - gcc main.c -o main -w

Pour l'exécuter :
 - ./main



***La syntaxe :


//Import library :
use "library";


//Variables :

number x;
string a;
array<number> h;
array<string> g;
boolean b;


//affectation :
x := 0


//Print statement: 
print(x);


// If:
if (x<y) then {
    printt(x+y);
 }else if(x > y) then {
    print(y-x);
 }else {
    print(y);
 }


//For loop:
for(x between 1 : 10 : 2) {
    print(x);
}


array(number) h := [7,14,21];
for(x in h)
{
    print(x);
}


//While loop :
while(x < 10){
    print(x);
    x := x + 1;
    break;
}


//Functions :
function sub(number x, number y) {
    return x - y;
}



***La grammaire 

NT= <PROGRAM ;STMT ;SIMPLESTMT ;ASSEIGNEMENTSTMT ;TYPESPECIFIER ;VALUE ;STR ;NUM ;OPERATION ;BOOLEANVAL ;
ARRAYSTMT ;PRINTSTMT ; USESTMT ;FUNCTIONCALL ;COMPOUNDSTMT;FUNCDEFINITION ;FUNCBODY ;FUNCBODYSTMT ;
RETURNSTMT ;LOOPSTMT ;IFSTMT ;IFBODY ; ELSESTMT ;WHILESTMT ;LOOPBODY ;FORSTMT ;CONDITIONEXPR>

Terminaux = <string , number , array , if , then , else, while , for , break , print , use, function , return, in, and , or ,
 >= , <= , == , != , < , > , := , ! , :,  ( , ), { , } , + , . , [ , ] , ; , * , / , % , a...z , A...Z , 0...9>

Les règles de production : voir la tables des RPs.png 






