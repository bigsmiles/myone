/*****************根据课后代码改编***********************************/
/* File: main.c                                     */
/* Main program for C- compiler                   */
/* Compiler Construction: Principles and Practice   */
/* xuchao                                         */
/****************************************************/


#include <stdio.h>
#include <stdlib.h>
#include "myScan.h"


FILE *source;   /* source code text file */
FILE *target;   /*token写进这个文件*/ 

int main(int argc, char *argv[])
{
    //freopen("F:\\School\\Compiler\\myC\\in.txt","r",stdin);
    freopen("F:\\School\\Compiler\\myC\\out.txt","w",stdout);
    
    source = fopen("F:\\School\\Compiler\\myC\\in.txt","r");
    target = fopen("F:\\School\\Compiler\\myC\\out.txt","w+");
    while(getToken() != ENDFILE)
    ;
    
    fclose(source);
    fclose(stdout);
    //system("pause");
  
	
  return 0;
}
