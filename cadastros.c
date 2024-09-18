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

void cadastrar(Cadastro *c){
    FILE *nome = fopen("nome.txt", "a");
    FILE *email = fopen("email.txt", "a");
    FILE *senha = fopen("senha.txt", "a");
    
    printf("Informe seu nome completo: \n");
    scanf(" %s", c->nome);
    
    printf("Informe seu email: \n");
    scanf(" %s", c->email);
    
    printf("Informe uma senha: \n");
    scanf(" %i", &c->senha);

    int emailv = emailvalido(c->email);
    
    if(emailv == 1){
        fprintf(nome, "%s\n", c->nome);
        fprintf(email, "%s\n", c->email);
        fprintf(senha, "%i\n", c->senha);
    }else if(emailv == 0){
        printf("Email invalido, digite novamente: ");
        scanf("%s", c->email);
        int emailv = emailvalido(c->email);
        while(emailv == 0){
            printf("entrou");
            printf("Email invalido, digite novamente: ");
            scanf("%s", c->email);
            emailv = emailvalido(c->email);
        }
        fprintf(nome, "%s\n", c->nome);
        fprintf(email, "%s\n", c->email);
        fprintf(senha, "%i\n", c->senha);
    }

    fclose(nome);
    fclose(email);
    fclose(senha);
}

void editarcadastro(Cadastro *c) {
    int i = 0, encontrado = 0;
    char nome_ex[50];

    FILE *nomeFile = fopen("nome.txt", "r");
    FILE *emailFile = fopen("email.txt", "r");
    FILE *senhaFile = fopen("senha.txt", "r");

    printf("Digite o nome do usuario que deseja excluir: ");
    scanf("%s", nome_ex);

    while(fscanf(nomeFile, "%s", c[i].nome) && fscanf(emailFile, "%s", c[i].email) && fscanf(senhaFile, "%i", &c[i].senha) != EOF){

        if(strcmp(nome_ex, c[i].nome) == 0){
            printf("Digite um novo nome: ");
            scanf("%s", c[i].nome);

            printf("Digite um novo e-mail: ");
            scanf("%s", c[i].email);

            printf("Digite uma nova senha: ");
            scanf("%i", &c[i].senha);
        }
        i++;
    }
    fclose(nomeFile);
    fclose(emailFile);
    fclose(senhaFile);

    nomeFile = fopen("nome.txt", "w");
    emailFile = fopen("email.txt", "w");
    senhaFile = fopen("senha.txt", "w");

    for(int j = 0; j < i; j++){
        fprintf(nomeFile, "%s\n", c[j].nome);
        fprintf(emailFile, "%s\n", c[j].email);
        fprintf(senhaFile, "%i\n", c[j].senha);
    }
    fclose(nomeFile);
    fclose(emailFile);
    fclose(senhaFile);
}

void listarusuarios(Cadastro *c){
    FILE *nomeFile = fopen("nome.txt", "r");

    printf("===========Usuarios Disponiveis===========\n");
    while(fscanf(nomeFile, "%s", c->nome) != EOF){
        printf("%s\n", c->nome);
    }

    fclose(nomeFile);
}

void removerUsuario(Cadastro *c){
    int i = 0, encontrado = 0;
    char nome_ex[50];
    FILE *email, *nome, *senha;

    email = fopen("email.txt", "r");
    nome = fopen("nome.txt", "r");
    senha = fopen("senha.txt", "r");

    printf("Digite o nome do usuario que deseja remover: ");
    scanf("%s", nome_ex);

    while(fscanf(nome, "%s", c[i].nome ) && fscanf(email, "%s", c[i].email) && fscanf(senha, "%i", &c[i].senha) != EOF){
            if(strcmp(nome_ex, c[i].nome) == 0){
                printf("Usuario Removido!!");
                encontrado = 1;
                continue;
            }
            i++;
    }

    fclose(email);
    fclose(nome);
    fclose(senha);

    email = fopen("email.txt", "w");
    nome = fopen("nome.txt", "w");
    senha = fopen("senha.txt", "w");
    int j = 0;

    for(j = 0; j < i; j++){
        fprintf(nome, "%s\n", c[j].nome);
        fprintf(email, "%s\n", c[j].email);
        fprintf(senha, "%i\n", c[j].senha);
    }

    fclose(email);
    fclose(nome);
    fclose(senha);
}