#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"produtos.h"

Produtos* criaprod(){
    Produtos* p = (Produtos *)malloc(sizeof(Produtos));
}

void adicionarprodutos(Produtos *p){
    FILE *produtos = fopen("produtos.txt", "a");

    printf("Por favor Informe o indice e o nome do produto: ");
    scanf("%i %s", &p->indice, p->remedios);

    printf("Agora informe o valor do seu produto: ");
    scanf("%f", &p->valor);

    fprintf(produtos, "%i %s %.2f", p->indice, p->remedios, p->valor);

    fclose(produtos);
}

int buscabinaria(Produtos *p, int id){
    FILE *produtos = fopen("produtos.txt", "r");
    int j = 0;
    while(fscanf(produtos, "%i %s %f", &p[j].indice, p[j].remedios, &p[j].valor) != EOF){
        j++;
    }
    int i = 0;
    int f = j - 1;
    while(i <= f){
        int meio = (i + f)/2;
        if(p[meio].indice == id){
            return meio;
        }else if(p[meio].indice < id){
            i = meio + 1;
        }else{
            f = meio - 1;
        }
    }
    return -1;
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

void listarprodutos(Produtos *p){
    FILE *produtos = fopen("produtos.txt", "r");
    
    if (produtos == NULL) {
        printf("Erro ao abrir o arquivo produtos.txt.\n");
        return;
    }

    printf("===========Rémedios disponiveis===========\n");
    
    while (fscanf(produtos, "%i %49s %f", &p->indice, p->remedios, &p->valor) != EOF) {
        printf("Indice: %i | Produto: %s | Valor: %.2f\n", p->indice, p->remedios, p->valor);
    }

    fclose(produtos);
}

void swap(Produtos *a, Produtos *b) {
    Produtos temp = *a;
    *a = *b;
    *b = temp;
}

int particao(Produtos array[], int low, int high) {
    int pivot = array[high].indice;
    int i = (low - 1);

    for (int j = low; j < high; j++) {
        if (array[j].indice < pivot) {
            i++;
            swap(&array[i], &array[j]);
        }
    }
    swap(&array[i + 1], &array[high]);
    return (i + 1);
}

void quicksort(Produtos array[], int low, int high) {
    if (low < high) {
        int pi = particao(array, low, high);

        quicksort(array, low, pi - 1);
        quicksort(array, pi + 1, high);
    }
}

int lerarquivo(Produtos **medicamentos) {
    FILE *file = fopen("produtos.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return -1;
    }

    int count = 0, size = 10;
    *medicamentos = (Produtos *)malloc(size * sizeof(Produtos));

    while (fscanf(file, "%d %s %f", &(*medicamentos)[count].indice, 
                  (*medicamentos)[count].remedios, 
                  &(*medicamentos)[count].valor) != EOF) {
        count++;
        if (count >= size) {
            size *= 2;
            *medicamentos = (Produtos *)realloc(*medicamentos, size * sizeof(Produtos));
        }
    }

    fclose(file);
    return count;
}

void escreverarquivo(Produtos medicamentos[], int size) {
    FILE *prod = fopen("produtos.txt", "w");
    if (prod == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    for (int i = 0; i < size; i++) {
        fprintf(prod, "%d %s %.2f\n", medicamentos[i].indice, medicamentos[i].remedios, medicamentos[i].valor);
    }

    fclose(prod);
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

void comprarremedio(Produtos *p, int *rl, int *et){
    FILE *produtos = fopen("produtos.txt", "r");
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