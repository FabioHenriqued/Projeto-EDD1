#include<stdio.h>
#include<locale.h>
#include<string.h>
#include<stdlib.h>

int rl = 0;
int et = 0;

typedef struct{
    int indice;
    char remedios[50];
    float valor;
}Produtos;

typedef struct{
    char email[80];
    char nome[50];
    double senha;
}Cadastro;

void adicionarprodutos(Produtos *p, FILE *produtos){
    produtos = fopen("produtos.txt", "a");

    printf("Por favor Informe o indice e o nome do produto: ");
    scanf("%i %s", &p->indice, p->remedios);

    printf("Agora informe o valor do seu produto: ");
    scanf("%f", &p->valor);

    fprintf(produtos, "%i %s %.2f", p->indice, p->remedios, p->valor);

    fclose(produtos);
}

void editarprodutos(Produtos *p){
    FILE *produtos = fopen("produtos.txt", "r");
    if(produtos == NULL){
        printf("erro ao abrir o arquivo");
    }

    int id;
    printf("Por favor, informe o indice do produto que deseja editar: ");
    scanf("%i", &id);
    int i = 0;
    char valor_s[10];

    while(fscanf(produtos, "%i %s %f", &p[i].indice, p[i].remedios, &p[i].valor) != EOF){
        if(p[i].indice == id){
            printf("Digite um novo valor: ");
            scanf("%f", &p[i].valor);
        }
        i++;
    }
    fclose(produtos);

    produtos = fopen("produtos.txt", "w");
    int j = 0;
    for (int j = 0; j < i; j++) {
        fprintf(produtos, "%i %s %.2f\n", p[j].indice, p[j].remedios, p[j].valor);
    }

    fclose(produtos);
}

void listarprodutos(Produtos *p, FILE *produtos){
    produtos = fopen("produtos.txt", "r");

    printf("===========Rémedios disponiveis===========\n");
    while(fscanf(produtos, "%i %s %f", &p->indice, p->remedios, &p->valor) != EOF){
        printf("Indice: %i | Produto: %s | Valor: %.2f\n", p->indice, p->remedios, p->valor);
    }

    fclose(produtos);
}

void removerprodutos(Produtos *p){
    FILE *produto = fopen("produtos.txt", "r");
    int id_temp, encontrado = 0;
    
    printf("Informe o ID do produto que deseja remover: ");
    scanf("%i", &id_temp);

    FILE *produto_temp = fopen("produtos_temp.txt", "w");
    while(fscanf(produto, "%i %s %f", &p->indice, p->remedios, &p->valor) != EOF){
        if(p->indice == id_temp){
            printf("Produto %s removido com sucesso!!", p->remedios);
            encontrado = 1;
        }else{
            fprintf(produto_temp, "%i %s %f", p->indice, p->remedios, p->valor);
        }
    }

    fclose(produto);
    fclose(produto_temp);

    if(!encontrado){
        printf("Produto não encontrado!");
        remove("produtos_temp.txt");
        return;
    }

    remove("produtos.txt");
    rename("produtos_temp.txt", "produtos.txt");
}

void verificarretiada(int rl){
    printf("=================================================");
    printf("Existem %i rémedios para serem retirados na loja!", rl);
    printf("=================================================");
}

void verificarentrega(int et){
    printf("=========================================\n");
    printf("Existem %i rémedios para serem entregues!\n", et);
    printf("=========================================\n");
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

void menucomum(){
    printf("===========Farmacia===========\n");
    printf("1 - Comprar Rémedio.\n");
    printf("2 - Listar Produtos.\n");
}

void comprarremedio(Produtos *p, FILE *produtos, int *rl, int *et){
    produtos = fopen("produtos.txt", "r");
    int n, id;

    printf("===========Comprar Rémedio===========");
    while(fscanf(produtos, "%i %s %f", &p->indice, p->remedios, &p->valor) != EOF){
        printf("\nIndice: %i | Produto: %s | Valor: %.2f", p->indice, p->remedios, p->valor);
    }

    printf("\nInforme o indice do rémedio que deseja comprar: ");
    scanf("%i", &id);

    rewind(produtos);

    while(fscanf(produtos, "%i %s %f", &p->indice, p->remedios, &p->valor) != EOF){
        if(p->indice == id){
            printf("%s %.2f\n", p->remedios, p->valor);
            break;
        }
    }

    printf("1 - Retirada na loja.\n");
    printf("2 - Entrega\n");
    scanf("%i", &n);

    if(n == 1){
        (*rl) += 1;
    }else if(n == 2){
        (*et) += 1;
    }else{
        printf("Operador invalido");
    }

    fclose(produtos);
}

void menuadm(){
    printf("===========ADM===========\n");
    printf("1 - Adicionar Produto.\n");
    printf("2 - Editar Produto.\n");
    printf("3 - Excluir Produto.\n");
    printf("4 - Listar Produtos Disponiveis.\n");
    printf("5 - Editar Cadastro.\n");
    printf("6 - Excluir Cadastro.\n");
    printf("7 - Listar Usuarios.\n");
    printf("8 - Verificar Entregas.\n");
    printf("9 - Verificar Retirada na Loja.\n");
    printf("10 - Comprar Rémedios.\n");
    printf("11 - Sair\n");
}

void login(Cadastro *c, FILE *email, FILE *senha) {
    email = fopen("email.txt", "r");
    senha = fopen("senha.txt", "r");

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

void cadastrar(Cadastro *c, FILE *email, FILE *nome, FILE *senha){
    nome = fopen("nome.txt", "a");
    email = fopen("email.txt", "a");
    senha = fopen("senha.txt", "a");
    
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

void editarcadastro(Cadastro *c, FILE *nomeFile, FILE *emailFile, FILE *senhaFile) {
    int i = 0, encontrado = 0;
    char nome_ex[50];

    nomeFile = fopen("nome.txt", "r");
    emailFile = fopen("email.txt", "r");
    senhaFile = fopen("senha.txt", "r");

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

void listarusuarios(Cadastro *c, FILE *nomeFile){
    nomeFile = fopen("nome.txt", "r");

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

int main(){
    setlocale(LC_ALL, "Portuguese");
    FILE *nome, *email, *senha, *produtos;
    Cadastro *c = (Cadastro *)malloc(sizeof(Cadastro));
    Produtos *p = (Produtos *)malloc(sizeof(Produtos));
    int rl1, et2, tp, op, op2;
    nome = fopen("nome.txt", "r");
    email = fopen("email.txt", "r");
    senha = fopen("senha.txt", "r");
    printf("===========Olá, seja bem vindo a farmacia===========\n");
    printf("1 - Usuario Novo.\n");
    printf("2 - Usuario Existente\n");
    scanf("%i", &op);
    if(op == 1){
        cadastrar(c, email, nome, senha);
    }else if(op == 2){
        login(c, email, senha);
        printf("Deseja fazer login como adm[1], ou como cliente[2]? ");
        scanf("%i", &tp);

        if(tp == 1){
            do{
                menuadm();
                printf("Escolha uma opção: ");
                scanf("%i", &op2);
                
                switch(op2){
                    case 1:
                        adicionarprodutos(p, produtos);

                        break;
                    case 2:
                        editarprodutos(p);
                        break;
                    case 3:
                        removerprodutos(p);
                        break;
                    case 4:
                        listarprodutos(p, produtos);
                        break;
                    case 5:
                        editarcadastro(c, nome, email, senha);
                        break;
                    case 6:
                        removerUsuario(c);
                        break;
                    case 7:
                        listarusuarios(c, nome);
                        break;
                    case 8:
                        verificarentrega(et);
                        break;
                    case 9:
                        verificarretiada(rl);
                        break;
                    case 10:
                        comprarremedio(p, produtos, &rl, &et);
                        break;
                    case 11:
                        printf("Saindo...");
                        break;
                    default:
                        printf("Opção Invalida.");
                        break;
                }
            }while(op2 != 11);
        }else if(tp == 2){
            do{
                menucomum();
                printf("Escolha uma opção: ");
                scanf("%i", &op2);
                switch(op2){
                    case 1:
                        comprarremedio(p, produtos, &rl, &et);
                        break;
                    case 2:
                        listarprodutos(p, produtos);
                        break;
                }
            }while(op != 3);
        }
    }
    return(0);
}