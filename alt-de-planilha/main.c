#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <mshtmlc.h>

#define tamanho_max 100

typedef struct {
    char nome[50];
    char tamanho[10];
    int quantidade;
    double preco;
} Confeccao;

void apresentarIntrucao() {
    setlocale(LC_ALL, "Portuguese");

    wprintf(L"-------------------------------------------------------\n\n");
    wprintf(L"Instruções:\n");
    wprintf(L"Para execução correta deste programa de gerenciamento de peças de roupa para confecção\n");
    wprintf(L"Siga a estrutura de planilha apresentada abaixo\n\n");
}

void leituraCSV(const char *confeccao) {
    FILE *file;
    file = fopen(confeccao, "r");

    if (file == NULL) {
        wprintf(L"Erro abrindo o arquivo, por favor verifique e tente novamente...(Cód:1)\n");
        return;
    }

    char line[tamanho_max];
    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%s", line);
    }

    fclose(file);
}

void escreverCSV(const char *confeccao, const Confeccao *nova_Confeccao) {
    FILE *file;
    file = fopen(confeccao, "a");

    if (file == NULL) {
        wprintf(L"Erro abrindo o arquivo para escrita, por favor verifique e tente novamente...(Cód:3)\n");
        return;
    }

    fprintf(file, "%s;%s;%d;%.2f\n", nova_Confeccao->nome, nova_Confeccao->tamanho, nova_Confeccao->quantidade, nova_Confeccao->preco);

    fclose(file);
}

void excluirCSV(const char *confeccao, const char *nomeParaExcluir) {
    FILE *file;
    file = fopen(confeccao, "r");

    if (file == NULL) {
        wprintf(L"Erro abrindo o arquivo para leitura ou escrita, por favor verifique e tente novamente...(Cód:4)\n");
        return;
    }

    char line[tamanho_max];

    while (fgets(line, sizeof(line), file) != NULL){
        char nomeparaexcluir[50];
        sscanf(line, "%49[^;]", nomeparaexcluir);
    }
    fclose(file);
    remove(confeccao);
}

void alterarCSV(const char *confeccao, const char *nomeParaAlterar, const Confeccao *novosDados) {
    FILE *file = fopen(confeccao, "r+");

    if (file == NULL) {
        wprintf(L"Erro abrindo o arquivo para leitura ou escrita, por favor verifique e tente novamente...(Cód:5)\n");
        return;
    }

    char line[tamanho_max];

    while (fgets(line, sizeof(line), file) != NULL) {
        char currentNome[50];
        sscanf(line, "%49[^;]", currentNome);

        if (strcmp(currentNome, nomeParaAlterar) == 0) {
            fseek(file, -strlen(line) - 1, SEEK_CUR);
            fprintf(file, "%s;%s;%d;%.2f\n", novosDados->nome, novosDados->tamanho, novosDados->quantidade, novosDados->preco);
        }
    }
    fclose(file);
}

int main(void) {
    int escolha_menu;
    Confeccao nova_Confeccao;
    Confeccao novosDados;
    char nomeParaExcluir[50];
    apresentarIntrucao();
    const char *arquivo = "C:\\Users\\luizf\\ClionProjects\\untitled4\\confeccao.csv";
    leituraCSV(arquivo);
    setlocale(LC_ALL, "Portuguese");


    while(escolha_menu != 0) {
        wprintf(L"------------------------Menu---------------------------");
        wprintf(L"\n1. Visualizar planilha\n");
        wprintf(L"2. Adicionar item \n");
        wprintf(L"3. Alterar item na planilha\n");
        wprintf(L"4. Excluir item na planilha\n");
        wprintf(L"Para encerrar o programa, digite 0 \n");
        wscanf(L"\n\n%d", &escolha_menu);
        wprintf(L"-------------------------------------------------------");
        
        switch (escolha_menu) {
            case 1:
                leituraCSV(arquivo);
                break;

            case 2:
                escreverCSV(arquivo, &nova_Confeccao);
                wprintf(L"Informe o nome da confecção, tamanho, quantidade e o preço de venda separados por ponto e virgula:\n");
                wscanf(L"%s %s %d %lf", nova_Confeccao.nome, nova_Confeccao.tamanho, &nova_Confeccao.quantidade,
                       &nova_Confeccao.preco);
                break;
            case 3:
                wprintf(L"Informe o nome da confecção para alterar:\n");
                wscanf(L"%s", nomeParaExcluir);
               wprintf(L"Informe os novos dados (nome tamanho quantidade preco):\n");
                wscanf(L"%s %s %d %lf", novosDados.nome, novosDados.tamanho, &novosDados.quantidade, &novosDados.preco);
                alterarCSV(arquivo, nomeParaExcluir, &novosDados);
                break;
            case 4:
                wprintf(L"Informe o nome da confecção para excluir:\n");
                wscanf(L"%s", nomeParaExcluir);
                excluirCSV(arquivo, nomeParaExcluir);
                break;
            default:
               break;
        }
        if(escolha_menu == 0){
            break;
        }
    }
    wprintf(L"Obrigado por utilizar o programa!");

//    Confeccao nova_Confeccao;
//  wprintf(L"Informe o nome da confecção, tamanho, quantidade e o preço de venda separados por ponto e virgula:\n");
//    wscanf(L"%s %s %d %lf", nova_Confeccao.nome, nova_Confeccao.tamanho, &nova_Confeccao.quantidade, &nova_Confeccao.preco);
//    fflush(stdin);
//
//    //escreverCSV(arquivo, &nova_Confeccao);
//    //leituraCSV(arquivo);
//    char nomeParaExcluir[50];
//    wprintf(L"Informe o nome da confecção para excluir:\n");
//    wscanf(L"%s", nomeParaExcluir);
//    excluirCSV(arquivo,nomeParaExcluir);
//
//    Confeccao novosDados;
//    wprintf(L"Informe o nome da confecção para alterar:\n");
//    wscanf(L"%s", nomeParaExcluir);  // Reusing the variable for simplicity
//    wprintf(L"Informe os novos dados (nome tamanho quantidade preco):\n");
//    wscanf(L"%s %s %d %lf", novosDados.nome, novosDados.tamanho, &novosDados.quantidade, &novosDados.preco);
//
//    alterarCSV(arquivo, nomeParaExcluir, &novosDados);
//    leituraCSV(arquivo);


    return 0;
}
