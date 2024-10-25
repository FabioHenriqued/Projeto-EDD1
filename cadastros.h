typedef struct{
    char email[80];
    char nome[50];
    double senha;
}Cadastro;

struct No{
    Cadastro dado;
    struct No *prox;
};

typedef struct{
    struct No *inicio;
}Lista;

Cadastro* criacad();
void login(Cadastro c);
void cadastrar(Lista *lista, Cadastro c);
int emailvalido(char c[]);
void editarcadastro(Lista *lista, Cadastro c); 
void listarusuarios(Lista *lista, Cadastro c);
void removerUsuario(Lista *lista, Cadastro c);