#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estrutura.h"

//funcao que liberta a memoria que foi alocada para guardar informaao na lista passada
void freeE(estrutura l)
{
    free (l -> hasReplies);
    free (l -> commentText);
    free (l -> date);
    free (l -> user);
    free(l -> identificador);
}

//funcao que adiciona um ser à estrutura passada
void addUser (estrutura l, char* user)
{
    l -> user = malloc (strlen(user) * sizeof(char*));
    strcpy (l -> user, user);
}

//funcao que adiciona uma data à estrutura passada
void addDate (estrutura l, char* date)
{
    l -> date = malloc (strlen(date) * sizeof(char*));
    strcpy (l -> date, date);
}

//funcao que adiciona o texto à estrutura passada
void addText (estrutura l, char* text)
{
    l -> commentText = malloc (strlen(text) * sizeof(char*));
    strcpy (l -> commentText, text);
}

//funcao que adiciona se o comentario guardado nesta lista tem replies ou nao
void addHasReply (estrutura l, char* has)
{
    l -> hasReplies = malloc (strlen(has) * sizeof(char*));
    strcpy (l -> hasReplies, has);
}

//funcao que adiciona um id à estrutura passada
void addId (estrutura l, char* id)
{
    l -> identificador = malloc (strlen(id) * sizeof(char*));
    strcpy (l -> identificador,id);
}

//funcao que adiciona o numero de replies
void addNReply (estrutura l, int id)
{
    estrutura aux = l;
    while (aux != NULL)
    {
        if ((aux -> idPessoal) == id)
        {
            (aux -> numberOfReplies)++;
            break;
        }
        
        else aux = aux -> next;
    }
}

//funcao que apenas adiciona um numero de tabs para auxiliar com a formataçao
void addTabs (int times)
{
    for (int i = 0; i < times; i++)
        printf("     ");
}

//funcao que da print a uma lista
void printEstrutura (estrutura l)
{
    if((l -> numberOfReplies) > 0) addHasReply(l,"TRUE");
    else addHasReply(l,"FALSE");
    
   
    addTabs(l -> numberOfSpaces);
    printf("{\n");
    addTabs(l -> numberOfSpaces);
    if((l -> identificador) == NULL) printf("\"id\": \"N/A\"\n");
    else printf("\"id\": \"%s\"\n",(l -> identificador));
    
    addTabs(l -> numberOfSpaces);
    if((l -> user) == NULL) printf("\"user\": \"N/A\"\n");
    else printf("\"user\": \"%s\"\n",(l -> user));
    
    addTabs(l -> numberOfSpaces);
    if((l -> date) == NULL) printf("\"user\": \"N/A\"\n");
    else printf("\"date\": \"%s\"\n",(l -> date));
    
    addTabs(l -> numberOfSpaces);
    printf("\"likes\": \"%d\"\n",0);
    
    addTabs(l -> numberOfSpaces);
    printf("\"hasReplies\": \"%s\"\n",(l -> hasReplies));
    
    addTabs(l -> numberOfSpaces);
    printf("\"numberOfReplies\": \"%d\"\n",(l -> numberOfReplies));
    
    addTabs(l -> numberOfSpaces);
    if ((l -> commentText) == NULL) printf("\"user\": \"N/A\"\n");
    printf("\"commentTest\": \"%s\"\n",(l -> commentText));
    
    if ((l -> numberOfReplies) == 0)
    {
        addTabs(l -> numberOfSpaces);
        printf("\"replies\": []\n");
        addTabs(l -> numberOfSpaces);
        printf("}\n");
        
        if ((l -> next) != NULL)
        {
            if (((l -> next) -> numberOfSpaces) < l -> numberOfSpaces)
            {
                addTabs((l -> numberOfSpaces));
                printf("]\n");
                addTabs((l -> next) -> numberOfSpaces);
                printf("}\n");
            }
               
        } else
        {
            for (int i = 0; i < (l -> numberOfSpaces); i++)
            {
                addTabs((l -> numberOfSpaces) - i);
                printf("]\n");
                addTabs((l -> numberOfSpaces) - i - 1);
                printf("}\n");
            }
                
        }
    }
    
    else
    {
        addTabs(l -> numberOfSpaces);
        printf("\"replies\": [\n");
    }
    
}
        
    
    
    
    
    
    
    
    
    
    

