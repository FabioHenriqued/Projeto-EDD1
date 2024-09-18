typedef struct{
    char email[80];
    char nome[50];
    double senha;
}Cadastro;
Cadastro* criacad();
void login(Cadastro *c);
void cadastrar(Cadastro *c);
int emailvalido(char c[]);
void editarcadastro(Cadastro *c); 
void listarusuarios(Cadastro *c);
void removerUsuario(Cadastro *c);