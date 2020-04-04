%{
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "estrutura.h"
#define MAX 100
int id = 0;  //id pessoal apenas usado para conseguirmos distinguir os posts mais facilmente
int numberSpaces = 0; //numero de espaços, usado para facilitar no print da estrutura segundo a formatação necessaria. quando encontramos a marca <ol> aumentamos, quando encotnramos a marca </ol> diminuimos
                      
estrutura comment; //apontador para a cabeça da lista ligada
estrutura aux; //estrutura auxiliar que vai percorrendo e construindo todas as listas enquanto as vai juntando
int stack [MAX]; //estrutura usada para guardar os ids dos "pais comment" para conseguirmos contar o numero de replies que cada comentario vai ter
int sp = 0; //variavel usada que aponta para que elemento na stack estamos 
%}

%option noyywrap
%option stack

acentos ç|á|Á|à|À|ã|Ã|â|Â|é|É|è|È|ê|Ê|í|Í|ó|Ó|ô|O|ú|Ú
%x Comentario Resposta Intermedio Date Autor Texto Id 
%%

\<li                                           {
                                                if(id == 0) {comment = malloc(sizeof(struct estrutura)); aux = comment;}
                                                else {estrutura x = malloc(sizeof(struct estrutura)); aux -> next = x; aux = aux -> next;}
                                                aux -> idPessoal = ++id;
                                                aux -> numberOfReplies = 0;
                                                aux -> numberOfSpaces = numberSpaces;
                                                yy_push_state(Comentario);
                                               }
<Comentario>data-comment-id\=\"                {yy_push_state(Id);}
<Comentario>\<a[ ]*href\=\".*\"\>              {yy_push_state(Autor);}
<Comentario>\<a[ ]*class[^\/]*\>               {yy_push_state(Date);}
<Comentario>\<\/li\>                           {yy_pop_state();}
<Comentario>\<p>                               {yy_push_state(Texto);}
<Comentario>\<ol                               {stack[++sp] = id;
                                                numberSpaces++;
                                                yy_push_state(Intermedio);}
<Comentario>.|\n                               {;}
<Intermedio>\<li                               {yy_push_state(Resposta);}
<Intermedio><\/ol\>                            {sp--; numberSpaces--;
                                                yy_pop_state();}
<Intermedio>.|\n
<Id>\>                                         {yy_pop_state();}
<Id>[a-zA-Z0-9\-]*                             {addId(aux,yytext);}
<Id>.|\n                                       {;}
<Date>[^<]+                                    {addDate(aux,yytext);}
<Date>\<\/a\>                                  {yy_pop_state();}
<Date>.|\n                                     {;}     
<Autor>([^<]|acentos)+				           {addUser(aux,yytext);}
<Autor>\<\/a\>                                 {yy_pop_state();}
<Autor>.|\n                                    {;}
<Texto>([^<]|acentos)+					       {addText(aux,yytext);}
<Texto>\<\/p\>                                 {yy_pop_state();}
<Texto>.|\n
<Resposta>data-comment-id\=\"                  {estrutura x = malloc(sizeof(struct estrutura)); aux -> next = x; aux = aux -> next;
                                                aux -> idPessoal = ++id;
                                                addNReply(comment,stack[sp]);
                                                aux -> numberOfReplies = 0;
                                                aux -> numberOfSpaces = numberSpaces;
                                                yy_push_state(Id);}
<Resposta>\<a[ ]*href\=\".*\"\>                {
                                                yy_push_state(Autor);
                                               }
<Resposta>\<a[ ]*class[^\/]*\>                 {yy_push_state(Date);}
<Resposta>\<\/li\>                             {yy_pop_state();}
<Resposta>\<ol                                 {stack[++sp] = id; numberSpaces++;
                                                yy_push_state(Intermedio);}
<Resposta>\<p>                                 {yy_push_state(Texto);}
<Resposta>.|\n
.|\n                                           {;}
%%


int main()
{
    yylex();
    estrutura auxiliar = comment;
    printf("\"commenThread\": [ \n");
    
    while (auxiliar != NULL)
    {
        printEstrutura(auxiliar);
        auxiliar = auxiliar -> next;
    }
    
    printf("]\n");
    auxiliar = comment;
    estrutura tmp;
    while (auxiliar != NULL) 
    {
    	tmp = auxiliar;
    	auxiliar = auxiliar -> next;
    	freeE(tmp);
    }
    return 0;
}
