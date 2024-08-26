#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <locale.h>

#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHTGRAY 7
#define DARKGRAY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTCYAN 11
#define LIGHTRED 12
#define LIGHTMAGENTA 13
#define YELLOW 14
#define WHITE 15
#define GREEK_CHARSET 16

// MS-DOS COLORS
void txtC(int color)
{
    // BLACK=0, BLUE=1; GREEN=2; CYAN=3; RED=4; MAGENTA=5; BROWN=6; LIGHTGRAY=7; DARKGRAY=8;
    // LIGHTBLUE=9; LIGHTGREEN=10; LIGHTCYAN=11, LIGHTRED=12; LIGHTMAGENTA=13; YELLOW=14; WHITE=15
    static int __BACKGROUND;
    HANDLE h = GetStdHandle ( STD_OUTPUT_HANDLE );
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    GetConsoleScreenBufferInfo(h, &csbiInfo);
    SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE),
                             color + (__BACKGROUND << 4));
}

void txtS(const char *str, unsigned int delay)
{
    while (*str)
    {
        putchar(*str++);
        fflush(stdout);
        usleep(delay);
    }
}

typedef struct
{
    int codigo;
    char descricao[50];
    float preco;
} tProd;

int mostra_menu()
{
    setlocale(LC_ALL, "Portuguese");

    int opcao;
    system("cls");
    txtC(11);
    txtS("Menu Principal\n", 10000);
    txtC(15);
    txtS("1 - Incluir\n", 1500);
    txtS("2 - Listar\n", 1500);
    txtS("3 - Pesquisar\n", 1500);
    txtS("4 - Gravar Arquivo\n", 1500);
    txtS("5 - Ler Arquivo\n", 1500);
    txtS("6 - Ordenar\n", 1500);
    txtS("7 - Editar\n", 1500);
    txtS("0 - Sair\n", 1500);
    txtS("Tecle op��o.: ", 1500);
    scanf("%d", &opcao);
    return opcao;
}

int ordenar_produtos(tProd* vProd, int qtd)
{
    float fTemp;
    int iTemp, i;
    char sTemp[50];

    int houve_troca = 1;
    while (houve_troca==1)
    {
        houve_troca = 0;
        for (i=0; i<qtd-1; i++)
        {
            // se as descricoes est�o fora de ordem
            if(strcmp(vProd[i].descricao,vProd[i+1].descricao)>0)
            {
                //efetua as trocas de valor

                houve_troca = 1;

                //primeiro troca o codigo
                iTemp = vProd[i].codigo;
                vProd[i].codigo = vProd[i+1].codigo;
                vProd[i+1].codigo = iTemp;

                // troca preco
                fTemp = vProd[i].preco;
                vProd[i].preco = vProd[i+1].preco;
                vProd[i+1].preco = fTemp;

                //troca descricao
                strcpy(sTemp,vProd[i].descricao);
                strcpy(vProd[i].descricao, vProd[i+1].descricao);
                strcpy(vProd[i+1].descricao, sTemp);
            }
        }
    }
   txtC(10);
   txtS("\nPRODUTO ORDENADOS COM SUCESSO!\n", 45000);
   txtC(15);
   system("pause");
}

int editar_arquivo(tProd* vProd, int qtd) {
   int numEsc;
   int alt;
   int produtoEncontrado = 0; //Vari�vel posicao/achou

   system("cls");

   txtS("Digite o n�mero do c�digo do produto: ", 10000); //User informa o n�mero do c�digo que ele deseja alterar
   scanf("%d", &numEsc); //N�mero armazenado

   for(int i=0; i<qtd; i++) {

      //Verificando se o n�mero � o mesmo
      if(numEsc == vProd[i].codigo){

        //Vari�vel posicao/achou = 1(true)
        produtoEncontrado = 1;

        //mostrando as informa��es atuais do Produto selecionado
         txtC(13);
         txtS("\n\nPRODUTO ENCONTRADO!", 45000);
         txtC(15);
         txtS("\nC�digo...: ", 19000); printf("%d", vProd[i].codigo);
         txtS("\nDescri��o: ", 19000); printf("%s", vProd[i].descricao);
         txtS("\nPre�o....: ", 19000); printf("%f\n\n", vProd[i].preco);

         //Alterando o produto
         txtC(11);
         txtS("ALTERANDO PRODUTO!", 45000);
         txtC(15);
         txtS("\ndescri��o.: ",22500);
         fflush(stdin);
         gets(vProd[i].descricao);
         txtS("pre�o.....: ",22500);
         scanf("%f", &vProd[i].preco);

         //Bon�s :)

         //Perguntando se o usu�rio deseja alterar o c�digo tamb�m
         txtS("\nDESEJA ALTERAR O C�DIGO TAMB�M?", 30000);
         txtS("\n(1 - sim)", 10000);
         txtS("\n(outro - n�o)\n\n: ", 10000);
         scanf("%d", &alt);

         //Se sim
         if(alt == 1){

            //Alterando c�digo
            txtC(11);
            txtS("ALTERANDO C�DIGO DO PRODUTO!", 45000);
            txtC(15);
            txtS("\n\nc�digo....: ",22500);
            scanf("%d", &vProd[i].codigo);

         }

        //Informando que as altera��es j� foram realizadas com sucesso
        txtC(14);
        txtS("\nALTERA��ES REALIZADAS!\n", 45000);
        txtC(15);

      }

   }

   //Se no final o produto n�o for encontrado
   if(produtoEncontrado == 0){

       //O Sistema avisa o usu�rio
       txtC(12);
       txtS("\nPRODUTO N�O ENCONTRADO!\n", 45000);
       txtC(15);
       system("pause");

   //se n�o
   }else{

        //Grava o arquivo que j� foi editado
        gravar_arquivo(vProd, qtd);

   }

}

int inclusao(tProd* vProd, int qtd)
{
    setlocale(LC_ALL, "Portuguese");

    system("cls");
    txtC(10);
    printf("Inclus�o\n");

    txtC(15);
    //codigo manual
    txtS("c�digo....: ",22500);
    scanf("%d", &vProd[qtd].codigo);
    //codigo automatico
    //vProd[qtd].codigo = qtd + 1;
    txtS("descri��o.: ",22500);
    fflush(stdin);
    gets(vProd[qtd].descricao);
    txtS("pre�o.....: ",22500);
    scanf("%f", &vProd[qtd].preco);
    txtC(11);
    txtS("Registro Incluido!\n",25000);
    txtC(15);
    system("pause");
    return qtd+1;
}

int listar(tProd* vProd, int qtd)
{
    int i;
    system("cls");
    printf("+-------------------------------------------------+\n");
    printf("|              Listagem de Produtos               |\n");
    printf("+-------------------------------------------------+\n");
    for (i=0; i<qtd; i++)
    {
        printf("| %3d | %-30s | %8.2f |\n", vProd[i].codigo, vProd[i].descricao, vProd[i].preco);
    }
    printf("+-------------------------------------------------+\n");
    printf("| Total de Registros: %3d                         |\n", qtd);
    printf("+-------------------------------------------------+\n");
    system("pause");
}

void print_spaces(int n)
{
    int i;
    for (i=0; i<n; i++)
    {
        printf(" ");
    }
}

int pesquisar(tProd* vProd, int qtd)
{
    int i, cont=0;;
    char buscar[50];
    system("cls");
    printf("Informe a Expressao de Busca: ");
    fflush(stdin);
    gets(buscar);

    printf("+-------------------------------------------------+\n");
    printf("| Pesquisando Produto '%s'",buscar);
    print_spaces(26-strlen(buscar));
    printf("|\n");
    printf("+-------------------------------------------------+\n");
    for (i=0; i<qtd; i++)
    {
        if (strstr(strlwr(vProd[i].descricao), strlwr(buscar))!=NULL)
        {
            printf("| %3d | %-30s | %8.2f |\n", vProd[i].codigo, vProd[i].descricao, vProd[i].preco);
            cont++;
        }
    }
    printf("+-------------------------------------------------+\n");
    printf("| %3d Registros Encontrados                       |\n", cont);
    printf("+-------------------------------------------------+\n");
    system("pause");
}

int gravar_arquivo(tProd* vProd, int qtd)
{

    int i;
    char nomearquivo[] = "produtos.csv";
    FILE* file = fopen (nomearquivo, "w");
    if (file == NULL)
    {
        printf("Erro ao tentar gravar o arquivo\n");
    }
    else
    {
        for (i=0; i<qtd; i++)
        {
            fprintf(file, "%d;%s;%f\r\n", vProd[i].codigo, vProd[i].descricao, vProd[i].preco);
        }
        txtC(11);
        printf("\nARQUIVO GRAVADO COM SUCESSO!\n");
        txtC(15);
        system("pause");
    }
    fclose(file);
}

int ler_arquivo(tProd* vProd)
{
    int cont = 0;
    char linha[256] = "";
    char* token;
    char nomearquivo[] = "produtos.csv";
    FILE* file = fopen(nomearquivo, "r");
    if (file == NULL)
    {
      txtC(12);
      txtS("Erro ao tentar ler o arquivo\n", 25000);
    }
    else
    {
        // ler linhas
        while (fgets(linha,256,file))
        {
            printf("%s", linha);

            token = strtok(linha, ";\r\n");
            vProd[cont].codigo = atoi(token);

            token = strtok(NULL, ";\r\n");
            strcpy(vProd[cont].descricao, token);

            token = strtok(NULL, ";\r\n");
            vProd[cont].preco = atof(token);

            cont++;
        }

        txtC(11);
        printf("\n%d registros lidos!\n", cont);
    }
    txtC(15);
    fclose(file);
    system("pause");
    return cont;
}

int main()
{
    tProd vProd[100];
    int qtd = 0;
    int opcao;

    setlocale(LC_ALL, "Portuguese");

    do
    {
        opcao = mostra_menu();

        switch (opcao)
        {
        case 1:
            qtd = inclusao(vProd, qtd); break;
        case 2:
            listar(vProd, qtd); break;
        case 3:
            pesquisar(vProd, qtd); break;
        case 4:
            gravar_arquivo(vProd, qtd); break;
        case 5:
            qtd = ler_arquivo(vProd); break;
        case 6:
            ordenar_produtos(vProd, qtd); break;
        case 7:
            editar_arquivo(vProd, qtd); break;
        case 0:
            printf("Encerrando...\n"); break;
        default:
            printf("Opcao invalida\n");
            system("pause");
        }

    }
    while (opcao != 0);
}






