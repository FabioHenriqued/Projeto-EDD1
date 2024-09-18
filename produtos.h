typedef struct{
    int indice;
    char remedios[50];
    float valor;
}Produtos;
Produtos* criaprod();
int buscabinaria(Produtos *p, int id);
void adicionarprodutos(Produtos *p);
void editarprodutos(Produtos *p);
void listarprodutos(Produtos *p);
int lerarquivo(Produtos **medicamentos);
void swap(Produtos *a, Produtos *b);
int particao(Produtos array[], int low, int high);
void quicksort(Produtos array[], int low, int high);
void escreverarquivo(Produtos medicamentos[], int size);
void removerprodutos(Produtos *p);
void verificarretiada(int rl);
void verificarentrega(int et);
void comprarremedio(Produtos *p, int *rl, int *et);