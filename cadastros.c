#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"cadastros.h"

Cadastro* criacad(){
    Cadastro *c = (Cadastro *)malloc(sizeof(Cadastro));
}

void login(Cadastro *c) {
    FILE *email = fopen("email.txt", "r");
    FILE *senha = fopen("senha.txt", "r");

    if (email == NULL || senha == NULL) {
        printf("Erro ao abrir arquivos.\n");
        return;
    }

    char emailt2[80], senhat2[80], emailt[80];
    int senha1, senhat;
    int loginrealizado = 0;

    printf("Por favor informe seu endereço de e-mail: ");
    scanf("%s", emailt2);
    printf("Informe a senha: ");
    scanf("%i", &senhat);

    while (getchar() != '\n');

    while (fgets(emailt, sizeof(emailt), email)) {
        emailt[strcspn(emailt, "\n")] = '\0';
        if (strcmp(emailt, emailt2) == 0) {
            loginrealizado = 1;
            break;
        }
    }

    fseek(senha, 0, SEEK_SET);

    while (fscanf(senha, "%i", &senha1)) {
        if (senha1 == senhat && loginrealizado == 1) {
            printf("Login realizado com sucesso!!!\n");
            fclose(email);
            fclose(senha);
            return;
        }
    }

    if (!loginrealizado) {
        printf("Email inválido.\n");
    } else {
        printf("Senha inválida.\n");
    }

    fclose(email);
    fclose(senha);
}

int emailvalido(char c[]){
    int cont = 0;
    for(int i = 0; i < strlen(c); i++){
        if(c[i] == '@'){
            cont++;
        }
    }
    if (cont == 1 && strlen(c) < 80){
        return 1;
    }else{
        return 0;
    }
}

void cadastrar(Lista *lista, Cadastro c){
    FILE *nome = fopen("nome.txt", "a");
    FILE *email = fopen("email.txt", "a");
    FILE *senha = fopen("senha.txt", "a");
    
    printf("Informe seu nome completo: \n");
    scanf(" %s", c.nome);
    
    printf("Informe seu email: \n");
    scanf(" %s", c.email);
    
    printf("Informe uma senha: \n");
    scanf(" %i", &c.senha);

    int emailv = emailvalido(c.email);
    
    if(emailv == 1){
        struct No *novo = (struct No*)malloc(sizeof(struct No));
        novo->dado = c;
        novo->prox = lista->inicio;
        lista->inicio = novo;
    }else if(emailv == 0){
        printf("Email invalido, digite novamente: ");
        scanf("%s", c.email);
        int emailv = emailvalido(c.email);
        while(emailv == 0){
            printf("Email invalido, digite novamente: ");
            scanf("%s", c.email);
            emailv = emailvalido(c.email);
        }
        struct No *novo = (struct No*)malloc(sizeof(struct No));
        novo->dado = c;
        novo->prox = lista->inicio;
        lista->inicio = novo;
    }

    struct No *pi;
    for(pi = lista->inicio; pi != NULL; pi = pi->prox){
        fprintf(nome, "%s\n", pi->dado.nome);
        fprintf(email, "%s\n", pi->dado.email);
        fprintf(senha, "%i\n", pi->dado.senha);
    }

    fclose(nome);
    fclose(email);
    fclose(senha);
}

void editarcadastro(Lista *lista, Cadastro c) {
    int i = 0, encontrado = 0;
    char nome_ex[50];

    FILE *nome = fopen("nome.txt", "r");
    FILE *email = fopen("email.txt", "r");
    FILE *senha = fopen("senha.txt", "r");

    printf("Digite o nome do usuario que deseja editar: ");
    scanf("%s", nome_ex);

    while(fscanf(nome, "%s", c.nome ) && fscanf(email, "%s", c.email) && fscanf(senha, "%i", &c.senha) != EOF){
        struct No *novo = (struct No*)malloc(sizeof(struct No));
        novo->dado = c;
        novo->prox = lista->inicio;
        lista->inicio = novo;
    }
    fclose(nome);
    fclose(email);
    fclose(senha);

    struct No *pi;
    for(pi = lista->inicio; pi != NULL && strcmp(nome_ex, pi->dado.nome) != 0; pi = pi->prox);
    if(pi == NULL){
        printf("Usuario não existe.");
    }
    else{
        char nome_novo[50];
        char email_novo[50];
        int senha_novo;

        printf("Informe o novo nome: ");
        scanf("%s", nome_novo);
        printf("informe o novo email: ");
        scanf("%s", email_novo);
        printf("Informe a nova senha:");
        scanf("%i", &senha_novo);

        strcpy(pi->dado.nome, nome_novo);
        strcpy(pi->dado.email, email_novo);
        pi->dado.senha = senha_novo;
    }

    nome = fopen("nome.txt", "w");
    email = fopen("email.txt", "w");
    senha = fopen("senha.txt", "w");

    struct No *pi2;
    for(pi2 = lista->inicio; pi2 != NULL; pi2 = pi2->prox){
        fprintf(nome, "%s\n", pi2->dado.nome);
        fprintf(email, "%s\n", pi2->dado.email);
        fprintf(senha, "%i\n", pi2->dado.senha);
    }

    fclose(nome);
    fclose(email);
    fclose(senha);
}

void listarusuarios(Lista *lista, Cadastro c){
    FILE *nomeFile = fopen("nome.txt", "r");
    FILE *emailFile = fopen("email.txt", "r");
    FILE *senhaFile = fopen("senha.txt", "r");
    printf("===========Usuarios Disponiveis===========\n");
    while(fscanf(nomeFile, "%s", c.nome) && fscanf(emailFile, "%s", c.email) && fscanf(senhaFile, "%i", &c.senha) != EOF){
        struct No *novo = (struct No*)malloc(sizeof(struct No));
        novo->dado = c;
        novo->prox = lista->inicio;
        lista->inicio = novo;
    }

    struct No *pi = lista->inicio;
    while(pi != NULL){
        printf("%s\n", pi->dado.nome);
        pi = pi->prox;
    }

    fclose(nomeFile);
    fclose(emailFile);
    fclose(senhaFile);
}

void removerUsuario(Lista *lista, Cadastro c){
    int i = 0, encontrado = 0;
    char nome_ex[50];
    FILE *email, *nome, *senha;

    email = fopen("email.txt", "r");
    nome = fopen("nome.txt", "r");
    senha = fopen("senha.txt", "r");

    printf("Digite o nome do usuario que deseja remover: ");
    scanf("%s", nome_ex);

    while(fscanf(nome, "%s", c.nome ) && fscanf(email, "%s", c.email) && fscanf(senha, "%i", &c.senha) != EOF){
        struct No *novo = (struct No*)malloc(sizeof(struct No));
        novo->dado = c;
        novo->prox = lista->inicio;
        lista->inicio = novo;
    }

    fclose(email);
    fclose(nome);
    fclose(senha);

    if(lista->inicio == NULL){
        printf("A lista esta vazia.\n");
    }
    else if(strcmp(nome_ex, lista->inicio->dado.nome) == 0){
        struct No *pi = lista->inicio;
        lista->inicio = pi->prox;
        free (pi);
    }
    else if(lista->inicio->prox == NULL){
        if(strcmp(nome_ex, lista->inicio->dado.nome) != 0){
            printf("Usuario não pode ser removido");
        }
    }
    else{
        struct No *pa;
        struct No *pi;
        for(pi = lista->inicio; pi != NULL && strcmp(nome_ex, pi->dado.nome) != 0; pi = pi->prox){
            pa = pi;
        }
        if(pi == NULL){
            printf("O usuario não pode ser removido.");
        }else{
            pa->prox = pi->prox;
            free(pi);
        }
    }

    email = fopen("email.txt", "w");
    nome = fopen("nome.txt", "w");
    senha = fopen("senha.txt", "w");
    
    struct No *pi;
    for(pi = lista->inicio; pi != NULL; pi = pi->prox){
        fprintf(nome, "%s\n", pi->dado.nome);
        fprintf(email, "%s\n", pi->dado.email);
        fprintf(senha, "%i\n", pi->dado.senha);
    }

    fclose(email);
    fclose(nome);
    fclose(senha);
}