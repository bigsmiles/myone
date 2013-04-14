/*****************根据课后代码改编***********************************/
/* File: main.c                                     */
/* Main program for C- compiler                   */
/* Compiler Construction: Principles and Practice   */
/* xuchao                                         */
/****************************************************/

#ifndef _MYSCAN_H_
#define _MYSCAN_H_

/* MAXTOKENLEN is the maximum size of a token */
#define MAXTOKENLEN 40
#define false 0
#define true 1

#define MAXRESERVED 6
/* tokenString array stores the lexeme of each token */
extern char tokenString[MAXTOKENLEN+1];

extern FILE *source; /* source code text file */
extern FILE *target;

/* states in scanner DFA 状态的枚举*/
typedef enum
   { START,INNUM,INID,ENTERING_COMMENT,INCOMMENT,EXITING_COMMENT,
     INLE,INGE,INEQ,INNE,DONE }
   StateType;



/* lexeme of identifier or reserved word */
//暂时不知道什么用处   
char tokenString[MAXTOKENLEN+1];

/* BUFLEN = length of the input buffer for
   source code lines */
#define BUFLEN 256

static char lineBuf[BUFLEN]; /* holds the current line从文件中读入一行 */
static int linepos = 0; /* current position in LineBuf */
static int bufsize = 0; /* current size of buffer string  */
static int EOF_flag = false; /* corrects ungetNextChar behavior on EOF */
/* getNextChar fetches the next non-blank character
   from lineBuf, reading in a new line if lineBuf is
   exhausted */

typedef enum 
    /* book-keeping tokens */
   {ENDFILE = 0,ERROR,
    /* reserved words */
    ELSE,IF,INT,RETURN,VOID,WHILE,
    /* multicharacter tokens */
    ID,NUM,
    /* special symbols */
    /* = == != < > <= >= , + - * / ( ) ; [ ] { } */
    ASSIGN,EQ,NE,LT,GT,LE,GE,COMMAS,PLUS,MINUS,TIMES,OVER,LPAREN,RPAREN,SEMI,LBRACKET,RBRACKET,LBRACE,RBRACE  
    //COMMAS逗号，LPAREN左括号 SEMI分号 
   } TokenType;
   
   char *ansToken[] = {"ENDFILE ","ERROR ","ELSE ","IF ","INT ","RETURN ","VOID ","WHILE ","ID ","NUM ",
                    "ASSIGN ","EQ  == ","NE  !=","LT  < ","GT  > ","LE  <=","GE >=","COMMAS ,","PLUS ",
                    "MINUS ","TIMES ","OVER ","LPAREN ( ","RPAREN ) ","SEMI ; ",
                    "LBRACKET  [ ","RBRACKET  ] ","LBRACE  { ","RBRACE  } "};
/* function getToken returns the 
 * next token in source file
 */
TokenType getToken(void);

#endif
