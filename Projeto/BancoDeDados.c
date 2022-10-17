#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <sys/stat.h>
#include <ctype.h>
#include <time.h>


/* Structs das funções */
typedef struct{
    int numeroDaVenda;
    char dataDaVenda[13];
    int codigoDoCliente;
    int codigoDoProduto;
    int quantidadeDoProduto;
    float valorTotal;
} Venda;

// nome do arquivo = produtos.dat
// registro = produtosRegi.dat
typedef struct{
    int codigo;
    char nome[50];
    int quantidade;
    float valor;
} Produto;

// nome do arquivo = clientes.dat
// registro = clientesRegi.dat
typedef struct{
    int codigo;
    char nome[100];
    char telefone[13];
    char endereco[100];
} Cliente;
// nome do arquivo IndiceCliente.dat
typedef struct{
    int codigo;
    int posicao;
} Indice;
/* Fim dos Structs das funções */


/* Protótipos do menu principal */
int escolha_menu_principal(int *banco);

int menu_acoes(int *acao);
/* Fim dos protótipos do menu principal */

/* Protótipos das funções de Inclusão */
int GravarCliente();

int GravarProduto();

int GravarVendas();

int verificarIndice();

int incluirProduto(int codigo, char nome[], int quantidade, float valor);

int incluirCliente(int codigo, char nome[], char telefone[], char enderco[]);

int incluirVenda(Venda vendas);

int verificarCodigo(int codigo, char nomeDoArquivo[]);

int salvarRegistro(char nomeDoArquivo[], int codigo, int posicao);

int lerRegistro(char nomeDoArquivo[]);

int lerCliente();

int lerProduto();

int lerVenda();

char *retornarNome(int codigo);

char *retornarProduto(int codigo);

int retornarPosicao(char nomeDoArquivo[], int codigo);

int atualizarLinhaProdutos(Produto linha ,int posicao);

Produto retornarLinhaProdutos(int codigo);

int comparar(const void *p1, const void *p2);

int buscaBinaria(int codigo, long int n, Indice vetor[]);
/* Fim dos protótipos das funções de Inclusão */


/* Protótipos das funções de Alteração */
void alteraRegistro(FILE *cfPtr);

int inserirEscolha(void);

int searchClientPosByCode(FILE* ptrArquivo, int code);

int searchProdutoPosByCode(FILE* ptrArquivo, int code);

int searchVendasPosByCode(FILE* ptrArquivo, int code);
/* Fim dos protótipos das funções de alteração */


/* Protótipos das funções de Exclusão */
int exclusaoCliente(char nomeDoArquivo[15]);

int exclusaoProduto(char nomeDoArquivo[15]);

int exclusaoVenda(char nomeDoArquivo[15]);

int buscaCliente(FILE* ptrArquivo, int code);

int buscaProduto(FILE* ptrArquivo, int code);

int buscaVenda(FILE* ptrArquivo, int code);
/* Fim dos protótipos das funções de Exclusão */


/* Função principal */
int main(void)
{
    int banco;
    system("cls");
    printf("Bem vindo!\n");
    while(escolha_menu_principal(&banco) != EOF)
    {
        int acao;
        switch(banco)
        {
            case 1: // clientes.dat
                    system("cls");
                    printf("Em clientes.dat, voce deseja:\n");
                    while(menu_acoes(&acao) != EOF)
                    {
                        switch(acao)
                        {
                            case 1://incluir
                                GravarCliente();
                            break;
                            case 2://alterar
                                atualizarClientes("clientes.dat");
                            break;
                            case 3://excluir
                                exclusaoCliente("clientes.dat");
                            break;
                            case 4://consultar
                                printf("=====================Clientes=============================================\n");
                                printf("Codigo\tNome\tTelefone\tEndereço\n");
                                lerCliente();
                                printf("==================IndiceClientes==========================================\n");
                                printf("Codigo\tIndice\n");
                                lerRegistro("clientesRegi.dat");
                                printf("Digite 1 quando quiser sair do menu de consulta!\n");
                                int resposta;
                                scanf("%d", &resposta);
                                if(resposta != 1){
                                    do{
                                        printf("Comando errado!, digite novamente!\n");
                                        scanf("%d", &resposta);
                                    }while(resposta != 1);
                                }
                            break;
                            default:
                            printf("Opcao invalida.\n");
                            system("pause");
                        }
                        system("cls");
                        printf("Em clientes.dat, voce deseja:\n");
                    }
                    system("cls");
            break;
            case 2: //produtos.dat
                system("cls");
                printf("Em produtos.dat, voce deseja:\n");
                while(menu_acoes(&acao) != EOF)
                {
                    switch(acao)
                    {
                        case 1://incluir
                        GravarProduto();
                        break;
                        case 2://alterar
                            atualizarProduto("produtos.dat");
                        break;
                        case 3://excluir
                            exclusaoProduto("produtos.dat");
                        break;
                        case 4://consultar
                            printf("=====================Produtos=============================================\n");
                            printf("Codigo\tNome\tQuantidade\tValor\n");
                            lerProduto();
                            printf("==================IndiceProdutos==========================================\n");
                            printf("Codigo\tIndice\n");
                            lerRegistro("produtosRegi.dat");
                            printf("Digite 1 quando quiser sair do menu de consulta!\n");
                            int resposta;
                            scanf("%d", &resposta);
                            if(resposta != 1){
                                    do{
                                        printf("Comando errado!, digite novamente!\n");
                                        scanf("%d", &resposta);
                                    }while(resposta != 1);
                                }
                        break;
                        default:
                        printf("Opcao invalida.\n");
                        system("pause");
                    }
                    system("cls");
                    printf("Em produtos.dat, voce deseja:\n");
                }
                system("cls");
            break;
            case 3: //vendas.dat
                system("cls");
                printf("Em vendas.dat, voce deseja:\n");
                while(menu_acoes(&acao) != EOF)
                {
                    switch(acao)
                    {
                        case 1://incluir
                        GravarVendas();
                        break;
                        case 2://alterar
                            atualizarVendas("vendas.dat");
                        break;
                        case 3://excluir
                            exclusaoVenda("vendas.dat");
                        break;
                        case 4://consultar
                            printf("==============================Vendas=======================================\n");
                            printf("NumeroDaVenda\tData\t    CodigoCli  CodigoPro   Quantidade\tValorTotal\n");
                            lerVenda();
                            printf("==================IndiceVendas=============================================\n");
                            printf("Codigo\tIndice\n");
                            lerRegistro("vendasRegi.dat");
                            printf("===========================================================================\n");
                            printf("Digite 1 quando quiser sair do menu de consulta!\n");
                            int resposta;
                            scanf("%d", &resposta);
                            if(resposta != 1){
                                    do{
                                        printf("Comando errado!, digite novamente!\n");
                                        scanf("%d", &resposta);
                                    }while(resposta != 1);
                                }
                        default:
                        printf("Opcao invalida.\n");
                        system("pause");
                    }
                    system("cls");
                    printf("Em vendas.dat, voce deseja:\n");
                }
            system("cls");
            break;
            default:
            system("cls");
            printf("Opcao invalida, tente novamente.\n");
            system("pause");
            system("cls");
        }
    }
}
/* Fim da função principal */

/* Funções do menu principal */
int escolha_menu_principal(int *banco) //int escolha_menu_principal(&variavel)
{
    /*TO DO: VERIFICAÇÃO DE ENTRADA!!!!!!!!!!!!!!!!!!*/
    int escolha;
    printf("Selecione o banco de dados que deseja manipular:\n");
    printf("1 - Clientes.dat, 2 - Produtos.dat, 3 - Vendas.dat, EOF - Encerrar programa.\n?");
    escolha = scanf("%d", banco);
    return escolha; //retorna o valor do scanf para comparar com EOF
}
int menu_acoes(int *acao)//int menu_acoes(&variavel)
{
    /*TO DO: VERIFICAÇÃO DE ENTRADA!!!!!!!!!!!!!!!!!!*/
    int escolha;
    printf("1 - Incluir, 2 - Alterar, 3 - Excluir, 4 - Consultar, EOF - Voltar.\n?");
    escolha = scanf("%d", acao);
    return escolha;
}
/* Fim das funções do menu principal */


/* Funções de Inclusão */
int incluirCliente(int codigo, char nome[], char telefone[], char endereco[]){
    FILE *cfPtr;
    long int tamanho;

    // obtém o tamanho do arquivo
    const char *filename = "clientes.dat";
    struct stat sb;
    stat(filename, &sb);
    tamanho = sb.st_size / sizeof(Cliente);

    // gravando os dados na estrutura clientes
    Cliente clientes;
    clientes.codigo = codigo;
    strcpy(clientes.nome, nome);
    strcpy(clientes.telefone, telefone);
    strcpy(clientes.endereco, endereco);

    if ((cfPtr = fopen("clientes.dat", "rb+")) == NULL){
        printf("Arquivo não pode ser aberto.\n");
        return 0;
    }

    fseek(cfPtr, (tamanho) * sizeof(Cliente), SEEK_SET);
    fwrite(&clientes, sizeof(Cliente), 1, cfPtr);

    fclose(cfPtr);

    // retorna a posição do registro atula no arquivo
    int posicao = tamanho;
    return posicao;
}

// inclui um produto no arquivo e retorna sua posição
int incluirProduto(int codigo, char nome[], int quantidade, float valor){
    FILE *cfPtr;
    long int tamanho;

    // obtém o tamanho do arquivo
    const char *filename = "produtos.dat";
    struct stat sb;
    stat(filename, &sb);
    tamanho = sb.st_size / sizeof(Produto);

    // gravando os dados na estrutura clientes
    Produto produtos;
    produtos.codigo = codigo;
    strcpy(produtos.nome, nome);
    produtos.quantidade = quantidade;
    produtos.valor = valor;

    if ((cfPtr = fopen("produtos.dat", "rb+")) == NULL){
        printf("Arquivo não pode ser aberto.\n");
        return 0;
    }

    fseek(cfPtr, (tamanho) * sizeof(Produto), SEEK_SET);
    fwrite(&produtos, sizeof(Produto), 1, cfPtr);

    fclose(cfPtr);

    // retorna a posição do registro atula no arquivo
    int posicao = tamanho;
    return posicao;
}

int incluirVenda(Venda vendas) {
    FILE *cfPtr;
    long int tamanho;

    // obtém o tamanho do arquivo
    const char *filename = "vendas.dat";
    struct stat sb;
    stat(filename, &sb);
    tamanho = sb.st_size / sizeof(Venda);

    // gravando os dados na estrutura clientes
    
    if ((cfPtr = fopen("vendas.dat", "rb+")) == NULL){
        printf("Arquivo não pode ser aberto.\n");
        return 0;
    }

    fseek(cfPtr, (tamanho) * sizeof(Venda), SEEK_SET);
    fwrite(&vendas, sizeof(Venda), 1, cfPtr);

    fclose(cfPtr);

    // retorna a posição do registro atula no arquivo
    int posicao = tamanho;
    return posicao;
}

int salvarRegistro(char nomeDoArquivo[], int codigo, int posicao){
    FILE *cfPtr;
    long int tamanho;

    // obetem o tamanho do arquivo
    const char *filename = nomeDoArquivo;
    struct stat sb;
    stat(filename, &sb);
    tamanho = sb.st_size / sizeof(Indice);

    Indice sort[tamanho + 1];
    // salvar os valores autuais
    sort[tamanho].codigo = codigo;
    sort[tamanho].posicao = posicao;

    if ((cfPtr = fopen(nomeDoArquivo, "rb+")) == NULL){
        printf("Arquivo não pode ser aberto.\n");
        return 0;
    }

    // concertar!
    // Ordenar antes de salvar!

    fread(&sort, sizeof(Indice), tamanho + 1, cfPtr);
    qsort(sort, tamanho + 1, sizeof(Indice), comparar);
    // fseek retorna o ponteiro para o inici do arquivo
    fseek(cfPtr, 0, SEEK_SET);
    fwrite(&sort, sizeof(Indice), tamanho + 1, cfPtr);

    // fseek e fwirte salvam os dados em sequencia
    //********************************************
    // fseek(cfPtr,(tamanho) *sizeof(Indice), SEEK_SET);
    // fwrite(&indices,sizeof(Indice),1, cfPtr);

    // fecha o arquivo
    fclose(cfPtr);
}

int lerRegistro(char nomeDoArquivo[]){
    FILE *cfPtr;
    long int tamanho;
    int i;

    // obetem o tamanho do arquivo
    const char *filename = nomeDoArquivo;
    struct stat sb;
    stat(filename, &sb);
    tamanho = sb.st_size / sizeof(Indice);

    // dados do registro
    Indice indices[tamanho];

    if ((cfPtr = fopen(nomeDoArquivo, "rb+")) == NULL){
        printf("Arquivo não pode ser aberto.\n");
        return 0;
    }

    // Carrega os dados de um arquivo em memoria
    fread(&indices, sizeof(Indice), tamanho, cfPtr);

    for (i = 0; i < tamanho; i++){
        printf("%d\t%d\n", indices[i].codigo, indices[i].posicao);
    }

    fclose(cfPtr);
}

int lerCliente(){
    FILE *cfPtr;
    int i;
    long int tamanho;

    // obetem o tamanho do arquivo
    const char *filename = "clientes.dat";
    struct stat sb;
    stat(filename, &sb);
    tamanho = sb.st_size / sizeof(Cliente);

    Cliente ler[tamanho];

    if ((cfPtr = fopen("clientes.dat", "rb+")) == NULL){
        printf("Arquivo não pode ser aberto.\n");
        return 0;
    }

    fread(&ler, sizeof(Cliente), tamanho, cfPtr);

    for (i = 0; i < tamanho; i++){
        printf("%d\t%s\t%s\t%s\n", ler[i].codigo, ler[i].nome, ler[i].telefone,
               ler[i].endereco);
    }

    fclose(cfPtr);
}

int lerProduto(){
    FILE *cfPtr;
    int i;
    long int tamanho;

    // obtém o tamanho do arquivo
    const char *filename = "produtos.dat";
    struct stat sb;
    stat(filename, &sb);
    tamanho = sb.st_size / sizeof(Produto);

    Produto ler[tamanho];

    if ((cfPtr = fopen("produtos.dat", "rb+")) == NULL){
        printf("Arquivo não pode ser aberto.\n");
        return 0;
    }

    fread(&ler, sizeof(Produto), tamanho, cfPtr);

    for (i = 0; i < tamanho; i++){
        printf("%d\t%s\t%d\t\tR$ %.2f\n", ler[i].codigo, ler[i].nome, ler[i].quantidade,
               ler[i].valor);
    }

    fclose(cfPtr);
}

int lerVenda() {
  FILE *cfPtr;
  int i;
  long int tamanho;

  // obetem o tamanho do arquivo
  const char *filename = "vendas.dat";
  struct stat sb;
  stat(filename, &sb);
  tamanho = sb.st_size / sizeof(Venda);

  Venda ler[tamanho];

  if ((cfPtr = fopen("vendas.dat", "rb+")) == NULL){
      printf("Arquivo não pode ser aberto.\n");
      return 0;
  }

  fread(&ler, sizeof(Venda), tamanho, cfPtr);

  //nomes

  char nome[100];
  char produto[100];
  for (i = 0; i < tamanho; i++){
    strcpy(nome,retornarNome(ler[i].codigoDoCliente));
    strcpy(produto,retornarProduto(ler[i].codigoDoProduto));


      printf("%d\t\t%s\t%s\t%s\t\t%d\tR$ %.2f\n", ler[i].numeroDaVenda, ler[i].dataDaVenda, 
            nome, produto,ler[i].quantidadeDoProduto,
            ler[i].valorTotal);
  }

  fclose(cfPtr);

}

int verificarCodigo(int codigo, char nomeDoArquivo[]){

    long int tamanho;

    // obetem o tamanho do arquivo
    const char *filename = nomeDoArquivo;
    struct stat sb;
    stat(filename, &sb);
    tamanho = sb.st_size / sizeof(Indice);

    //****
    Indice Indices[tamanho];
    FILE *cfPtr;

    if ((cfPtr = fopen(nomeDoArquivo, "rb+")) == NULL){
        printf("Arquivo não pode ser aberto.\n");
        return 0;
    }

    // Carrega os dados de um arquivo em memoria
    fread(&Indices, sizeof(Indice), tamanho, cfPtr);
    // realiza busca binaria e compara o codigo
    if (buscaBinaria(codigo, tamanho, Indices) == 1){
        // retorna 1 se encontrar o valor e -1 se não encontra
        return 1;
    }
    else{
        return -1;
    }

    fclose(cfPtr);
}


//retornar a posição de um registro qualquer
int retornarPosicao(char nomeDoArquivo[], int codigo){
    long int tamanho;

    // obetem o tamanho do arquivo
    const char *filename = nomeDoArquivo;
    struct stat sb;
    stat(filename, &sb);
    tamanho = sb.st_size / sizeof(Indice);

    //****
    Indice Indices[tamanho];
    FILE *cfPtr;

    if ((cfPtr = fopen(nomeDoArquivo, "rb+")) == NULL){
        printf("Arquivo não pode ser aberto.\n");
        return 0;
    }

    // Carrega os dados de um arquivo em memoria
    fread(&Indices, sizeof(Indice), tamanho, cfPtr);
    // realiza busca binaria e compara o codigo
    
    //busca binarias
    int esquerda = -1;
    int direita = tamanho;

    while (esquerda < direita - 1){
        int meio = (esquerda + direita) / 2;
        if (Indices[meio].codigo < codigo)
            esquerda = meio;
        else
            direita = meio;
        }

    return Indices[direita].posicao;

    fclose(cfPtr);
}
// retorna uma linha do arquivo
Produto retornarLinhaProdutos(int codigo){
    long int tamanho;
    int posicao;

    // obetem o tamanho do arquivo
    const char *filename = "produtos.dat";
    struct stat sb;
    stat(filename, &sb);
    tamanho = sb.st_size / sizeof(Produto);
    
    posicao = retornarPosicao("produtosRegi.dat",codigo);
    Produto linha;
    FILE *cfPtr;

    if ((cfPtr = fopen("produtos.dat", "rb+")) == NULL){
        printf("Arquivo não pode ser aberto.\n");
    }
    fseek(cfPtr, posicao * sizeof(Produto), SEEK_SET);
    fread(&linha,sizeof(Produto),1,cfPtr);

    fclose(cfPtr);

    return linha;
}

int atualizarLinhaProdutos(Produto linha ,int posicao) {
    long int tamanho;

    // obetem o tamanho do arquivo
    const char *filename = "produtos.dat";
    struct stat sb;
    stat(filename, &sb);
    tamanho = sb.st_size / sizeof(Produto);
    
    FILE *cfPtr;

    if ((cfPtr = fopen("produtos.dat", "rb+")) == NULL){
        printf("Arquivo não pode ser aberto.\n");
    }
    fseek(cfPtr, (posicao * sizeof(Produto)), SEEK_SET);
    fwrite(&linha, sizeof(Produto),1, cfPtr);
    
    fclose(cfPtr);

    return 0;

}

// apenas para o Qsort
int comparar(const void *p1, const void *p2){
    if ((*(Indice *)p1).codigo == (*(Indice *)p2).codigo){
        return 0;
    }
    else if ((*(Indice *)p1).codigo < (*(Indice *)p2).codigo){
        return -1;
    }
    else{
        return 1;
    }
}
// retorna a posição do valor
int buscaBinaria(int codigo, long int n, Indice vetor[]){

    int esquerda = -1;
    int direita = n;

    while (esquerda < direita - 1){
        int meio = (esquerda + direita) / 2;
        if (vetor[meio].codigo < codigo)
            esquerda = meio;
        else
            direita = meio;
        }

    if (vetor[direita].codigo == codigo){
        // caso encontre o valor
        return 1;
    }
    else{
        // caso nao encontre
        return -1;
    }
}

int GravarCliente() { //codigo para salvar o novo registro
    char NomeDoArquivo[20];
    strcpy(NomeDoArquivo,"clientesRegi.dat");
    int codigo = verificarIndice(NomeDoArquivo);
    int posica; 

    // cadastra o cliente;

    char nome[100];
    char telefone[13];
    char endereco[100];

    // validação telefone! O errro tá aqui!!!
    printf("Digite o telefone: ");
    scanf("%s",telefone);
    printf("\n");

    printf("digite o seu endereço (Use '_' para o 'espaço'):");
    scanf("%s", endereco);
    printf("\n");

    printf("Digite O nome do cliente: ");
    scanf("%s", nome);

    // salva os dados seus registros
    posica = incluirCliente(codigo, nome, telefone, endereco);
    salvarRegistro("clientesRegi.dat", codigo, posica);
}

int GravarProduto() {
    char NomeDoArquivo[20];
    strcpy(NomeDoArquivo,"produtosRegi.dat");
    int codigo = verificarIndice(NomeDoArquivo);
    int posica;

    // cadastra o produto;
    int posicao;

    char nome[100];
    int quantidade;
    float valor;
    // Atenção !!!!
    // está faltando as funções de verificação de campo
    printf("Digite O nome do Produto: ");
    scanf("%s", nome);

    // valida a quantidade do produto
    printf("digite a quantidade do produto :");
    scanf("%d",&quantidade);
    printf("\n");

    // validar o valor do produto
    printf("digite o valor do produto :");
    scanf("%f",&valor);
    printf("\n");
    

    // salva os dados seus registros
    posicao = incluirProduto(codigo, nome, quantidade, valor);
    salvarRegistro("produtosRegi.dat", codigo, posicao);
}

int GravarVendas() {
    char NomeDoArquivo[20];
    strcpy(NomeDoArquivo,"vendasRegi.dat");
    int codigo = verificarIndice(NomeDoArquivo);
    int posica;
    int posicao;
    //venda

    int posicaoVendas;

    char dataDaVenda[13];
    int codigoDoCliente;
    int codigoDoProduto;
    int quantidadeDoProduto;
    float valorTotal;

    printf("Digite o codigo do Cliente: ");
    scanf("%d",&codigoDoCliente);
    printf("\n");

    // verificando a existencia dos codigos;
    if (verificarCodigo(codigoDoCliente, "clientesRegi.dat") == -1){
        printf("O Cliente não existe!\nTente novamente!\n");
        return 0;
    }

    printf("Digite o codigo do Produto: ");
    scanf("%d",&codigoDoProduto);
    printf("\n");

    if (verificarCodigo(codigoDoProduto, "produtosRegi.dat") == -1){
        printf("O Produto não existe!\nTente novamente!\n");
        return 0;
    }

    // pega a data do sistema
    struct tm tempo;
    time_t dia;

    time(&dia);
    tempo = *localtime(&dia);

    sprintf(dataDaVenda, "%.2d/%.2d/%d",
    tempo.tm_mday, tempo.tm_mon + 1, tempo.tm_year + 1900);

    // quantidade do produto
    Produto linha = retornarLinhaProdutos(codigoDoProduto);
    if (linha.quantidade == 0){
        printf("O estoque de %s está zerado... =( :\n", linha.nome);
        printf("Tente outro produto!\n");
        return 0;
    }

    // valida a quantidade do produto
    printf("Digite A quantidade do produto: ");
    scanf("%d",&quantidadeDoProduto);
    printf("\n");

    while ((quantidadeDoProduto < 0) ||
          (quantidadeDoProduto > linha.quantidade)){
        printf("Apenas '%d' unidades de '%s' no estoque!\nDigite um valor condizente! :", linha.quantidade, linha.nome);
        scanf("%d", &quantidadeDoProduto);
        printf("\n");
    }

    // calculo do valor total
    valorTotal = quantidadeDoProduto * linha.valor;

    // atualizar o a quantidade de intens na tabela produtos
    linha.quantidade -= quantidadeDoProduto;
    // função atualizar
    posicao = retornarPosicao("produtosRegi.dat", codigoDoProduto);
    atualizarLinhaProdutos(linha, posicao);
    // salva os valores!
    Venda vendas;
    vendas.numeroDaVenda = codigo;
    strcpy(vendas.dataDaVenda, dataDaVenda);
    vendas.codigoDoCliente = codigoDoCliente;
    vendas.codigoDoProduto = codigoDoProduto;
    vendas.quantidadeDoProduto = quantidadeDoProduto;
    vendas.valorTotal = valorTotal;

    // salva tudo
    posicaoVendas = incluirVenda(vendas);
    salvarRegistro(NomeDoArquivo, codigo, posicaoVendas);

}

int verificarIndice (char NomeDoArquivo[]){
    int codigo;
    printf("digite O codigo: ");
    scanf("%d",&codigo);

    // verificar**
    while (verificarCodigo(codigo, NomeDoArquivo) == 1)
    {
        // se o codigo já estiver cadastrado
        printf("Codigo já CADASTRADO!\nPor favor insira um não cadastrado: ");
        scanf("%d",&codigo);
    }
    return codigo;
}

char *retornarNome(int codigo){
    FILE *cfPtr;
    int i;
    long int tamanho;
    int posicao;

    // obetem o tamanho do arquivo
    const char *filename = "clientes.dat";
    struct stat sb;
    stat(filename, &sb);
    tamanho = sb.st_size / sizeof(Cliente);

    Cliente produtos;

    posicao = retornarPosicao("clientesRegi.dat",codigo);

    if ((cfPtr = fopen("clientes.dat", "rb+")) == NULL){
        printf("Arquivo não pode ser aberto.\n");
        return 0;
    }

    fseek(cfPtr, posicao*sizeof(Cliente),SEEK_SET);
    fread(&produtos,sizeof(Cliente),1,cfPtr);

    fclose(cfPtr);
    char produto[100];
    char *produtoPtr;
    strcpy(produto,produtos.nome);
    produtoPtr = produto;

    return produtoPtr;

}

char *retornarProduto(int codigo){
    FILE *cfPtr;
    int i;
    long int tamanho;
    int posicao;

    // obetem o tamanho do arquivo
    const char *filename = "produtos.dat";
    struct stat sb;
    stat(filename, &sb);
    tamanho = sb.st_size / sizeof(Produto);

    Produto cliente;

    posicao = retornarPosicao("produtosRegi.dat",codigo);

    if ((cfPtr = fopen("produtos.dat", "rb+")) == NULL){
        printf("Arquivo não pode ser aberto.\n");
        return 0;
    }

    fseek(cfPtr, posicao*sizeof(Produto),SEEK_SET);
    fread(&cliente,sizeof(Produto),1,cfPtr);

    fclose(cfPtr);
    char nome[100];
    char *nomePtr;
    strcpy(nome,cliente.nome);
    nomePtr = nome;

    return nomePtr;

}
/* Fim das funções de Inclusão */


/* Funções de Alteração */
int inserirEscolha(void){
    int escolha;
    printf("Digite sua escolha\n1 - Incluir\n2 - Excluir\n3 - Alterar\n");
    scanf("%d", &escolha);
    return escolha;
}

int escolherCampo(void){
    int campo;
    printf("1 - Nome\n2 - Telefone\n3 - Endereço\n0 - Encerrar\n");
    scanf("%d", &campo);
    return campo;
}
int escolherCampoProduto(void){
    int campo;
    printf("1 - Nome\n2 - Quantidade\n3 - Valor\n0 - Encerrar\n");
    scanf("%d", &campo);
    return campo;
}

int escolherCampoVenda(void){
    int campo;
    printf("\n1 - Data da Venda\n2 - Valor Total\n3 - Quantidade de produtos vendidos\n0 - Encerrar\n");
    scanf("%d", &campo);
    return campo;
}

int searchClientPosByCode(FILE* ptrArquivo, int code){
    Cliente clientes = {0, "", "", ""};
    for(int i = 0; !feof(ptrArquivo); i++) {
        fseek(ptrArquivo, i * sizeof(Cliente), SEEK_SET);
        fread(&clientes, sizeof(Cliente), 1, ptrArquivo);
        if(clientes.codigo == code) {
            return i;
        }
    }
    //retorna -1 se não encontrar nenhuma conta registrada com o numero descrito.
    return -1;
}

int searchProdutoPosByCode(FILE* ptrArquivo, int code) {
    Produto produtos = {0, "", 0, 0.0};
    for(int i = 0; !feof(ptrArquivo); i++) {
        fseek(ptrArquivo, i * sizeof(Produto), SEEK_SET);
        fread(&produtos, sizeof(Produto), 1, ptrArquivo);
        if(produtos.codigo == code) {
            return i;
        }
    }
    //retorna -1 se não encontrar nenhuma conta registrada com o numero descrito.
    return -1;
}

int searchVendasPosByCode(FILE* ptrArquivo, int code) {
    Venda vendas = {0, "", 0, 0.0};
    for(int i = 0; !feof(ptrArquivo); i++) {
        fseek(ptrArquivo, i * sizeof(Venda), SEEK_SET);
        fread(&vendas, sizeof(Venda), 1, ptrArquivo);
        if(vendas.numeroDaVenda == code) {
            return i;
        }
    }
    //retorna -1 se não encontrar nenhuma conta registrada com o numero descrito.
    return -1;
}

void atualizarClientes(char nomeDoArquivo[15]){
    FILE *cfPtr;
    //Abre o arquivo escolhido.
    if ( ( cfPtr = fopen(nomeDoArquivo, "rb+" ) ) == NULL ) {
        printf( "Arquivo não pode ser aberto.\n" );
    }
    //Inicialização do struct clientes.
    Cliente clientes = {0,"","",""};

    unsigned int atualizarcodigo;

    printf("Digite o codigo para atualizar: ");

    scanf("%d", &atualizarcodigo);

    //chama a função de pegar a posição do código no arquivo pelo número descrito.
    atualizarcodigo = searchClientPosByCode(cfPtr, atualizarcodigo);

    //direciona o ponteiro para a posição do código descrito no arquivo.
    fseek(cfPtr ,atualizarcodigo*sizeof(Cliente),SEEK_SET);

    //faz a leitura do tamanho do valores de clientes.
    fread(&clientes, sizeof(Cliente),1, cfPtr);
    
    //Se não existir nenhuma conta com o código descrito, retorna -1.
    if(atualizarcodigo == -1){
        printf("Cliente não existe\n!");
    }
    else{
        int escolha;
        int novoCodigo;
        char novoNome[100];
        char novoTelefone[13];
        char novoEndereco[100];

        printf("Antes da atualização\n");

        printf("%-0d %-3s %-10s %8s\n", clientes.codigo,clientes.nome, clientes.telefone, clientes.endereco);

        //menu de escolha de ações disponíveis para o usuário.
        while((escolha = escolherCampo()) != 0){

            switch(escolha){

                //alteração do nome.
                case 1:
                    printf("Digite um novo nome: \n");

                    scanf("%s",novoNome);

                    //copia o nome novo digitado substituindo o antigo no arquivo.
                    strcpy(clientes.nome, novoNome);

                    fseek(cfPtr, atualizarcodigo*sizeof(Cliente),SEEK_SET);

                    fwrite( &clientes, sizeof(Cliente), 1, cfPtr);

                    break;

                //alteração de telefone.
                case 2:
                    printf("Digite o novo telefone: \n");

                    scanf("%s", novoTelefone);
                    
                    //copia o nome novo digitado substituindo o antigo no arquivo.
                    strcpy(clientes.telefone, novoTelefone);

                    fseek(cfPtr, atualizarcodigo*sizeof(Cliente),SEEK_SET);

                    fwrite(&clientes, sizeof(Cliente), 1, cfPtr);

                    break;
                
                //alteração de endereço.
                case 3:

                    printf("Digite o novo endereço: \n");

                    scanf("%s", novoEndereco);
                    
                    //copia o novo endereço digitado para o clientes.endereço.
                    strcpy(clientes.endereco, novoEndereco);
                    
                    //faz a procura do local onde a mudança vai ser feita.
                    fseek(cfPtr, atualizarcodigo*sizeof(Cliente),SEEK_SET);
                    
                    //escreve a mudança feita no arquivo.
                    fwrite( &clientes, sizeof(Cliente), 1, cfPtr);

                    break;

                default:
                    printf("Valor Inválido\n");
            }
        };

        printf("Após a atualizacao: \n");

        fseek(cfPtr,(atualizarcodigo) * sizeof(Cliente), SEEK_SET);

        fread(&clientes, sizeof(Cliente),1, cfPtr);

        lerCliente("clientes.dat");

        printf("Atualizacao realizada com SUCESSO.\n");
    }
}
void atualizarProduto(char nomeDoArquivo[15]){
    FILE *cfPtr;

    //Abre o arquivo escolhido.
    if ( ( cfPtr = fopen(nomeDoArquivo, "rb+" ) ) == NULL ) {
        printf( "Arquivo não pode ser aberto.\n" );
    }
    Produto produtos = {0,"", 0, 0.0};

    unsigned int atualizarcodigo;

    printf("Digite o codigo para atualizar: ");

    scanf("%d", &atualizarcodigo);

    //chama a função de pegar a posição do código no arquivo pelo número descrito.
    atualizarcodigo = searchProdutoPosByCode(cfPtr, atualizarcodigo);

    //direciona o ponteiro para a posição do código descrito no arquivo.
    fseek(cfPtr , atualizarcodigo * sizeof(Produto),SEEK_SET);

    //faz a leitura do tamanho do valores de produtos;
    fread(&produtos, sizeof(Produto),1, cfPtr);
    
    //Se não existir nenhuma conta com o código descrito, retorna -1.
    if(atualizarcodigo == -1){
        printf("Produto não existe\n!");
    }else{
        int escolha;
        int novoCodigo;
        char novoNomeProduto[50];
        int novoQuantidade;
        float novoValor;

        printf("Antes da atualização\n");

        printf("%-6d  %-16s %-11d %10.2f\n", produtos.codigo, produtos.nome, produtos.quantidade, produtos.valor);

        //menu de escolha de ações disponíveis para o usuário.
        while((escolha = escolherCampoProduto()) != 0){

            switch(escolha){

                //alteração do nome do produto.
                case 1:
                    printf("Digite um novo nome do produto: \n");

                    scanf("%s", novoNomeProduto);

                    //copia o nome novo digitado substituindo o antigo no arquivo.
                    strcpy(produtos.nome, novoNomeProduto);

                    fseek(cfPtr, atualizarcodigo*sizeof(Produto),SEEK_SET);

                    fwrite( &produtos, sizeof(Produto), 1, cfPtr);

                    break;

                //alteração da quantidade de produtos.
                case 2:
                    printf("Digite a nova quantidade de produtos: \n");

                    scanf("%d", &novoQuantidade);

                    //produtos.quantidade recebe a nova quantidade.
                    produtos.quantidade = novoQuantidade;

                    fseek(cfPtr, atualizarcodigo*sizeof(Produto),SEEK_SET);

                    fwrite(&produtos, sizeof(Produto), 1, cfPtr);

                    break;
                
                //alteração do valor do produto.
                case 3:

                    printf("Digite um novo valor do produto: \n");

                    scanf("%f", &novoValor);
                    
                    //copia o novo valor digitado para o produtos.valor.
                    produtos.valor = novoValor;
                    
                    //faz a procura do local onde a mudança vai ser feita.
                    fseek(cfPtr, atualizarcodigo*sizeof(Produto), SEEK_SET);
                    
                    //escreve a mudança feita no arquivo.
                    fwrite(&produtos, sizeof(Produto), 1, cfPtr);

                    break;

                default:
                    printf("Valor Inválido\n");
            }
        };

        printf("Após a atualizacao: \n");

        fseek(cfPtr,(atualizarcodigo) * sizeof(Produto), SEEK_SET);

        fread(&produtos, sizeof(Produto),1, cfPtr);

        lerProduto();

        printf("Atualizacao realizada com SUCESSO.\n");
    }
}

void atualizarVendas(char nomeDoArquivo[15]){

    FILE *cfPtr;
    FILE *cfPtr2;

    //Abre o arquivo escolhido.
    if ( ( cfPtr = fopen(nomeDoArquivo, "rb+" ) ) == NULL ) {
        printf( "Arquivo não pode ser aberto.\n" );
    }
    Venda vendas = {0,"",0 ,0 , 0.0};

    unsigned int atualizarcodigo;

    printf("Digite o codigo da venda para atualizar: ");

    scanf("%d", &atualizarcodigo);

    //chama a função de pegar a posição do código no arquivo pelo número descrito.
    atualizarcodigo = searchVendasPosByCode(cfPtr, atualizarcodigo);

    //direciona o ponteiro para a posição do código descrito no arquivo.
    fseek(cfPtr ,atualizarcodigo*sizeof(Venda),SEEK_SET);

    //faz a leitura do tamanho do valores de vendas;
    fread(&vendas, sizeof(Venda),1, cfPtr);

    //Se não existir nenhuma conta com o código descrito, retorna -1.
    if(atualizarcodigo == -1){
        printf("Cliente não existe\n!");
    }else{
        int escolha;
        char novadataVenda[10];
        float novoValorVenda;
        int novoValorQuantidadeVenda;
        int novaQuantidade;
        int posicaoCodigoProduto;

        printf("Antes da atualização\n");

        printf("%-0d %-3s %-5d %-5d %-10d %-10.2f\n", vendas.numeroDaVenda, vendas.dataDaVenda, vendas.codigoDoCliente, vendas.codigoDoProduto,
                vendas.quantidadeDoProduto,vendas.valorTotal);

        //menu de escolha de ações disponí­veis para o usuário.
        while((escolha = escolherCampoVenda()) != 0){

            switch(escolha){

                //alteração da data de venda.
                case 1:
                    printf("Digite uma nova data da venda: \n");

                    scanf("%s",novadataVenda);

                    //copia o nome novo digitado substituindo o antigo no arquivo.
                    strcpy(vendas.dataDaVenda, novadataVenda);

                    fseek(cfPtr, atualizarcodigo*sizeof(Venda),SEEK_SET);

                    fwrite( &vendas, sizeof(Venda), 1, cfPtr);

                    break;

                //alteração do valor da venda
                case 2:
                    printf("Digite um novo valor da venda: \n");

                    scanf("%f", &novoValorVenda);
                    //copia o nome novo digitado substituindo o antigo no arquivo.

                    vendas.valorTotal = novoValorVenda;

                    fseek(cfPtr, atualizarcodigo*sizeof(Venda),SEEK_SET);

                    fwrite(&vendas, sizeof(Venda), 1, cfPtr);

                    break;

                case 3:
                    //Abre o arquivo produtos.dat e faz a verificação.
                    if ( ( cfPtr2 = fopen("produtos.dat", "rb+" ) ) == NULL ) {
                        printf( "Arquivo de produtos não pode ser aberto.\n" );
                    }
                    //faz a verificação se existe a conta com o índice descrito(atualizarcodigo) no arquivo produtos.dat.
                    else{
                        Produto produtos = {0,"", 0, 0.0};

                        posicaoCodigoProduto = searchProdutoPosByCode (cfPtr2, vendas.codigoDoProduto);

                        if(posicaoCodigoProduto == -1){
                            printf("Produto nao existe, cadastre seu produto primeiro!\n");
                        }
                        //se existir a conta, faz a alteração no valor dos arquivos de produto, e venda.
                        else{
                            printf("Digite a quantidade do produto vendidos: \n");
                            scanf("%d", &novoValorQuantidadeVenda);
                            
                            vendas.quantidadeDoProduto = novoValorQuantidadeVenda;
                            
                            fseek(cfPtr, atualizarcodigo*sizeof(Venda),SEEK_SET);

                            fwrite(&vendas, sizeof(Venda), 1, cfPtr);

                            // Agora atualizar no arquivo de produtos  

                            posicaoCodigoProduto = searchProdutoPosByCode (cfPtr2, vendas.codigoDoProduto);

                            fseek(cfPtr2, posicaoCodigoProduto*sizeof(Produto), SEEK_SET);
                            
                            fread(&produtos, sizeof(Produto),1, cfPtr2);
                            
                            produtos.quantidade -= novoValorQuantidadeVenda;

                            fseek(cfPtr2, posicaoCodigoProduto*sizeof(Produto), SEEK_SET);

                            fwrite(&produtos, sizeof(Produto), 1, cfPtr2);
                        }
                    }
                    fclose(cfPtr2);

                    break;

                default:
                    printf("Valor Inválido\n");
            }
        };

        printf("Após a atualizacao: \n");

        fseek(cfPtr,(atualizarcodigo) * sizeof(Venda), SEEK_SET);

        fread(&vendas, sizeof(Venda),1, cfPtr);

        lerVenda();
        printf("\n");
        lerProduto();

        printf("Atualizacao realizada com SUCESSO.\n");
    }
}
/* Fim das funções de Alteração */


/* Funções de Exclusão */
int exclusaoCliente(char nomeDoArquivo[15]){

    FILE *cfPtr;
    //Abre o arquivo escolhido.
    if ( ( cfPtr = fopen(nomeDoArquivo, "rb+" ) ) == NULL ) {
        printf( "Arquivo nao pode ser aberto.\n" );
    }
    int codigo;
    int escolha;

    printf("Digite o codigo do cliente para excluir: ");
    scanf("%d", &codigo);

    printf("\n1 - Para excluir\n2 - Nao excluir\n");
    printf("Opção: ");
    scanf("%d", &escolha);

    if(escolha == 2){
        return 0;
    }
    else{
        int ind = buscaCliente(cfPtr, codigo);
    }
    fclose(cfPtr);
}


//EXCLUSÃO DE PRODUTOS///
int exclusaoProduto(char nomeDoArquivo[15]){


    FILE *cfPtr;
    //Abre o arquivo escolhido.
    if ( ( cfPtr = fopen(nomeDoArquivo, "rb+" ) ) == NULL ) {
        printf( "Arquivo nao pode ser aberto.\n" );
    }
    int codigo;
    int escolha;

    printf("Digite o codigo do produto para excluir: ");
    scanf("%d", &codigo);

    printf("\n1 - Para excluir\n2 - Nao excluir\n");
    printf("Opcao: ");
    scanf("%d", &escolha);

    if(escolha == 2){
        return 0;
    }
    else{
        int ind = buscaProduto(cfPtr, codigo);
    }
    fclose(cfPtr);
}

//EXCLUSÃO DE VENDAS////
int exclusaoVenda(char nomeDoArquivo[15]){
    FILE *cfPtr;
    //Abre o arquivo escolhido.
    if ( ( cfPtr = fopen(nomeDoArquivo, "rb+" ) ) == NULL ) {
        printf( "Arquivo nao pode ser aberto.\n" );
    }

    int codigo;
    int escolha;

    printf("Digite o numero da venda para excluir: ");
    scanf("%d", &codigo);

    printf("\n1 - Para excluir\n2 - Nao excluir\n");
    printf("Opcao: ");
    scanf("%d", &escolha);

    if(escolha == 2){
        return 0;
    }
    else{
        int ind = buscaVenda(cfPtr, codigo);

    }
    fclose(cfPtr);
}


//FUNÇÕES USADAS PARA EXCLUIR CLIENTE, PRODUTO E VENDA///

int buscaCliente(FILE* ptrArquivo, int code){
    Cliente clientes = {0, "", "", ""};
    int temCliente=0;
    int cont=0;
    FILE *f1;
    f1= fopen("copy.dat", "wb+");
    for(int i = 0; !feof(ptrArquivo); i++) {
        fseek(ptrArquivo, i * sizeof(Cliente), SEEK_SET);
        fread(&clientes, sizeof(Cliente), 1, ptrArquivo);
        cont++;

        if(clientes.codigo == code) {
                temCliente = 1;
                printf("Codigo encontrado.");
          }
        else{
            fwrite(&clientes, sizeof(Cliente), 1, f1);

        }
     }
    fclose(f1);
    fclose(ptrArquivo);

    int res = remove("clientes.dat");
    int result = rename("copy.dat", "clientes.dat");

    if(temCliente == 1){
        return cont++;
    }
     printf("Codigo nao encontrado.");
    //retorna -1 se não encontrar nenhuma conta registrada com o numero descrito.
    return -1;
}
int buscaProduto(FILE* ptrArquivo, int code){
    Produto produtos = {0, "", 0, 0};
    int temProduto=0;
    int cont=0;
    FILE *f1;
    f1= fopen("copy.dat", "wb+");
    for(int i = 0; !feof(ptrArquivo); i++) {
        fseek(ptrArquivo, i * sizeof(Produto), SEEK_SET);
        fread(&produtos, sizeof(Produto), 1, ptrArquivo);
        cont++;

        if(produtos.codigo == code) {
                temProduto = 1;
                printf("Codigo do produto encontrado.\n");
          }
        else{
            fwrite(&produtos, sizeof(Produto), 1, f1);

        }
     }
    fclose(f1);
    fclose(ptrArquivo);

    int res = remove("produtos.dat");
    int result = rename("copy.dat", "produtos.dat");

    if(temProduto == 1){
        return cont++;
    }
     printf("Codigo do produto nao encontrado.");
    //retorna -1 se não encontrar nenhuma conta registrada com o numero descrito.
    return -1;
}
int buscaVenda(FILE* ptrArquivo, int code){
    Venda vendas = {0,"",0,0,0,0};
    int temVenda=0;
    int cont=0;
    FILE *f1;
    f1= fopen("copy.dat", "wb+");
    for(int i = 0; !feof(ptrArquivo); i++) {
        fseek(ptrArquivo, i * sizeof(Venda), SEEK_SET);
        fread(&vendas, sizeof(Venda), 1, ptrArquivo);
        cont++;

        if(vendas.numeroDaVenda == code) {
                temVenda = 1;
                printf("Numero de venda encontrado.");
          }
        else{
            fwrite(&vendas, sizeof(Venda), 1, f1);

        }
     }
    fclose(f1);
    fclose(ptrArquivo);

    int res = remove("vendas.dat");
    int result = rename("copy.dat", "vendas.dat");

    if(temVenda == 1){
        return cont++;
    }
    printf("Numero de venda nao encontrado.");
    //retorna -1 se não encontrar nenhuma conta registrada com o numero descrito.
    return -1;
}
/* Fim das funções de Exclusão */