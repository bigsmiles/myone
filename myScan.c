/*****************根据课后代码改编***********************************/
/* File: main.c                                     */
/* Main program for C- compiler                   */
/* Compiler Construction: Principles and Practice   */
/* xuchao                                         */
/****************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "myScan.h"



static int getNextChar(void)
{ 
  if (!(linepos < bufsize)) //数组linebuf中无字符时 
   { 
                //lineno++;    
    //fgets(char *s, int n,FILE *)最多将 n-1字符读入 s，换行时换行符读入并结束 ，
    // 以'\0' 结尾，返回数组 s文件末尾是返回NULL 
    if (fgets(lineBuf,BUFLEN-1,source)) 
    { 
      //if (EchoSource) fprintf(listing,"%4d: %s",lineno,lineBuf);
      bufsize = strlen(lineBuf);
      linepos = 0;
      return lineBuf[linepos++];
    }
    else
    { EOF_flag = true;
      return EOF;
    }
  }
  else return lineBuf[linepos++];
}

/* ungetNextChar backtracks one character
   in lineBuf 
   getNextChar()中EOF_flag = true 时表明一个字符串横跨两行，下面要排除这个情况*/
static void ungetNextChar(void)
{ if (!EOF_flag) linepos-- ;}

/* lookup table of reserved words */
static struct
    { char* str;
      TokenType tok;
    } reservedWords[MAXRESERVED]
   = {{"else",ELSE},{"if",IF},{"int",INT},{"return",RETURN},
      {"void",VOID},{"while",WHILE}
      };
      
/* lookup an identifier to see if it is a reserved word */
/* uses linear search */
static TokenType reservedLookup (char * s)
{ int i;
  for (i=0;i<MAXRESERVED;i++)
    if (!strcmp(s,reservedWords[i].str))
      return reservedWords[i].tok;
  return ID;
}

/****************************************/
/* the primary function of the scanner  */
/****************************************/
/* function getToken returns the 
 * next token in source file
 */
TokenType getToken(void)
{  /* index for storing into tokenString */
   int tokenStringIndex = 0;
   /* holds current token to be returned */
   TokenType currentToken;
   /* current state - always begins at START */
   StateType state = START;
   /* flag to indicate save to tokenString */
   int save;
   while (state != DONE)
   { int c = getNextChar();
     save = true;  //...........
     switch (state)
     { case START:
         if (isdigit(c))
           state = INNUM;
         else if (isalpha(c))
           state = INID;
         //else if (c == ':')  //...............
           //state = INASSIGN;
         else if (c == '<')
           state = INLE;
         else if (c == '>')
           state = INGE;
         else if (c == '=')
           state = INEQ;
         else if (c == '!')
           state = INNE;
         else if ((c == ' ') || (c == '\t') || (c == '\n'))
           save = false;
         else if (c == '/')
         { //save = FALSE;
           state = ENTERING_COMMENT;
         } 
         else
         { state = DONE;
           switch (c)
           { case EOF:
               save = false;
               currentToken = ENDFILE;
               break;
             case '+':
               currentToken = PLUS;
               break;
             case '-':
               currentToken = MINUS;
               break;
             case '*':
               currentToken = TIMES;
               break;
             case '/':
               currentToken = ENTERING_COMMENT;
               break;
             case '(':
               currentToken = LPAREN;
               break;
             case ')':
               currentToken = RPAREN;
               break;
             case ';':
               currentToken = SEMI;
               break;
             case '[':
               currentToken = LBRACKET;
               break;
             case ']':
               currentToken = RBRACKET;
               break;
             case '{':
               currentToken = LBRACE;
               break;
             case '}':
               currentToken = RBRACE;
               break;
             default:
               currentToken = ERROR;
               break;
           }
         }
         break;
       /*case ENTERING_COMMENT:
         save = false;
         if (c == EOF)   //????????????????
         { state = DONE;
           currentToken = ENDFILE;
         }
         else if (c == '*') state = INCOMMENT;
         else { 
           currentToken = TIMES;
           save = true;
           state = DONE;
           }
         break; */
       case ENTERING_COMMENT:
            save = false;
            if(c == '*') state = INCOMMENT;
            else {
                 ungetNextChar();
                 currentToken = OVER;
                 state = DONE;
                 save = true;
                 }
            break;
       case INCOMMENT:
            save = false;
            if(c == '*') state = EXITING_COMMENT;
            break;
       case EXITING_COMMENT:
            save = false;
            if(c == '/') state = START;
            else if (c == '*') state = EXITING_COMMENT;
            else state = INCOMMENT;
            break;
                 
       case INLE:
         state = DONE;
         if (c == '=')
           currentToken = LE;
         else
         { /* backup in the input */
           ungetNextChar();
           //save = FALSE;
           currentToken = LT;
         }
         break;
         case INGE:
         state = DONE;
         if (c == '=')
           currentToken = GE;
         else
         { /* backup in the input */
           ungetNextChar();
           //save = FALSE;
           currentToken = GT;
         }
         break;
         case INEQ:
         state = DONE;
         if (c == '=')
           currentToken = EQ;
         else
         { /* backup in the input */
           ungetNextChar();
           //save = FALSE;
           currentToken = ASSIGN;
         }
         break;
         case INNE:       //不等号。。。。。。。。。。。。 
         state = DONE;
         if (c == '=')
           currentToken = NE;
         else
         { /* backup in the input */
           ungetNextChar();
           save = false;
           currentToken = ERROR;
         }
         break;
       case INNUM:
         if (!isdigit(c))
         { /* backup in the input */
           ungetNextChar();
           save = false;
           state = DONE;
           currentToken = NUM;
         }
         break;
       case INID:
         if (!isalpha(c))
         { /* backup in the input */
           ungetNextChar();
           save = false;
           state = DONE;
           currentToken = ID;
         }
         break;
       case DONE:
       default: /* should never happen */
         //fprintf(listing,"Scanner Bug: state= %d\n",state);
         state = DONE;
         currentToken = ERROR;
         break;
     }
     if ((save) && (tokenStringIndex <= MAXTOKENLEN))
     {
       tokenString[tokenStringIndex++] = (char) c;
       //tokenIndex[tokenStringIndex] = currentToken;
     }
       
     if (state == DONE)
     { tokenString[tokenStringIndex] = '\0';
       if (currentToken == ID) { 
         currentToken = reservedLookup(tokenString);
         }
     }
   }
  /* if (TraceScan) {
     fprintf(listing,"\t%d: ",lineno);
     printToken(currentToken,tokenString);
   }*/
   
   //printf("YES\n");
   //fputs(ansToken[currentToken],target);
    printf("%s\n",ansToken[currentToken]);
   return currentToken;
} /* end getToken */ 

/*


超神帅爆了！

 
*/







































