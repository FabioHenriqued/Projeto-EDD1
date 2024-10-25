#include<stdio.h>
#include<locale.h>
#include<stdlib.h>
#include"cadastros.h"
#include"produtos.h"

int rl = 0;
int et = 0;

void menucomum(){
    printf("===========Farmacia===========\n");
    printf("1 - Comprar Rémedio.\n");
    printf("2 - Listar Produtos.\n");
    printf("3 - Buscar Produto.\n");
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
    printf("11 - Buscar Produto\n");
    printf("12 - Ordenar Produtos\n");
    printf("13 - Sair\n");
}

int main(){
    Lista lista;
    lista.inicio = NULL;
    int id;
    int n;
    Produtos *p;
    Cadastro c;
    setlocale(LC_ALL, "Portuguese");
    int tp, op, op2;
    printf("===========Olá, seja bem vindo a farmacia===========\n");
    printf("1 - Usuario Novo.\n");
    printf("2 - Usuario Existente\n");
    scanf("%i", &op);
    if(op == 1){
        cadastrar(&lista, c);
    }else if(op == 2){
        login(c);
        printf("Deseja fazer login como adm[1], ou como cliente[2]? ");
        scanf("%i", &tp);

        if(tp == 1){
            do{
                menuadm();
                printf("Escolha uma opção: ");
                scanf("%i", &op2);
                
                switch(op2){
                    case 1:
                        adicionarprodutos(p);

                        break;
                    case 2:
                        editarprodutos(p);
                        break;
                    case 3:
                        removerprodutos(p);
                        break;
                    case 4:
                        listarprodutos(p);
                        break;
                    case 5:
                        editarcadastro(&lista, c);
                        break;
                    case 6:
                        removerUsuario(&lista, c);
                        break;
                    case 7:
                        listarusuarios(&lista, c);
                        break;
                    case 8:
                        verificarentrega(et);
                        break;
                    case 9:
                        verificarretiada(rl);
                        break;
                    case 10:
                        comprarremedio(p, &rl, &et);
                        break;
                    case 11:
                        printf("Informe o Indice do produto: ");
                        int id;
                        scanf("%i", &id);
                        int idx = buscabinaria(p, id);
                        printf("==========Produto Disponivel!!!==========\n");
                        printf("ID: %i | Nome: %s | Valor: %.2f\n", p[idx].indice, p[idx].remedios, p[idx].valor);
                        printf("=========================================\n");
                        break;
                    case 12:
                        n = lerarquivo(&p);
                        if (n == -1) {
                            return 1;
                        }
                        quicksort(p, 0, n - 1);
                        escreverarquivo(p, n);
                        break;
                    case 13:
                        printf("Saindoo...");
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
                        comprarremedio(p, &rl, &et);
                        break;
                    case 2:
                        listarprodutos(p);
                        break;
                    case 3:
                        printf("Informe o Indice do produto: ");
                        int id;
                        scanf("%i", &id);
                        int idx = buscabinaria(p, id);
                        printf("==========Produto Disponivel!!!==========");
                        printf("ID: %i | Nome: %s | Valor: %f", p[idx].indice, p[idx].remedios, p[idx].valor);
                        printf("=========================================");
                        break;
                }
            }while(op != 3);
        }
    }
    return(0);
}