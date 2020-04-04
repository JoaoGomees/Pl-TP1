
typedef struct estrutura
{
    char* identificador; //id do comment que aparece no html
    int idPessoal; //id pessoal criado por nos para facilitar a gestao dos comments
    char* user; // string que representa o username
    char* date; // string da data
    char* commentText; // texto do comentario
    char* hasReplies; // se tem replies ou nao, pode ser TRUE ou FALSE
    int numberOfReplies; // numero de replies que este post tem. Apenas conta as replies diretas e nao as replies das replies
    int numberOfSpaces; // numero de espaçso para melhor facilitar a formataçao do testo final
    struct estrutura* next; // apontar para a proxima lista
}*estrutura;

void freeE(estrutura l);
void addUser (estrutura l, char* user);
void addDate (estrutura l, char* date);
void addText (estrutura l, char* text);
void addHasReply (estrutura l, char* has);
void addId (estrutura l, char* id);
void addNReply (estrutura l, int id);
void printEstrutura (estrutura l);
void addTabs (int times);

