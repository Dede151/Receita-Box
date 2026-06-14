#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    const int TAM = 1024;
    int op;
    char sn[5];
    char linha[TAM],nomeBusca[100],nome[100];
    FILE *file;

    printf("\nReceita BOX\nO livro de reicetas virtual\n\n");
    printf("Deseja acessar o livro de receitas? s/n: ");
    scanf("%s", sn);

    if (sn[0] == 's' || sn[0] == 'S') {
        while (sn[0] == 's' || sn[0] == 'S') {

            printf("\n\t===== MENU =====");
            printf("\n1. Receitas");
            printf("\n2. Nova Receita");
            printf("\n3. Sair\n");
            printf("\nEscolha uma opcao: ");
            scanf("%d", &op);

            switch (op) {

                case 1:
                    file = fopen("receitas.txt", "r");
                    if (file == NULL) {
                        printf("\nNenhuma receita encontrada ainda.\n");
                        break;
                    }

                    printf("\n=== Receitas disponiveis ===\n");
                    while (fgets(linha, 1024, file) != NULL) {
                        linha[strcspn(linha, "\n")] = '\0';
                        if (strncmp(linha, "[", 1) == 0 && strcmp(linha, "[FIM]") != 0) {
                            linha[strlen(linha) - 1] = '\0';
                            printf("- %s\n", linha + 1);
                        }
                    }
                    fclose(file);
                    
                    printf("\nDigite o nome da receita que deseja ver: ");
                    scanf(" ");
                    fgets(nomeBusca, 100, stdin);
                    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

                    file = fopen("receitas.txt", "r");
                    int encontrou = 0;
                    int exibindo = 0;

                    while (fgets(linha, 1024, file) != NULL) {
                        linha[strcspn(linha, "\n")] = '\0';

                        if (strncmp(linha, "[", 1) == 0 && strstr(linha, nomeBusca) != NULL) {
                            encontrou = 1;
                            exibindo = 1;
                            printf("\n\n=== %s ===\n", nomeBusca);
                            continue;
                        }

                        if (exibindo && strcmp(linha, "[FIM]") == 0) {
                            exibindo = 0;
                            break;
                        }

                        if (exibindo) printf("%s\n", linha);
                    }

                    fclose(file);

                    if (!encontrou)
                        printf("\nReceita \"%s\" nao encontrada.\n", nomeBusca);

                    break;

                case 2:
                    printf("\nDigite o nome da nova receita: ");
                    scanf(" ");
                    fgets(nome, 100, stdin);
                    nome[strcspn(nome, "\n")] = '\0';

                    file = fopen("receitas.txt", "a");
                    if (file == NULL) {
                        printf("\nERRO ao abrir o arquivo.\n");
                        break;
                    }

                    fprintf(file, "[%s]\n", nome);

                    printf("\nDigite a receita. Quando terminar, escreva FIM numa linha sozinha:\n\n");
                    scanf(" ");
                    while (fgets(linha, 1024, stdin) != NULL) {
                        if (strncmp(linha, "FIM", 3) == 0) break;
                        fprintf(file, "%s", linha);
                    }

                    fprintf(file, "[FIM]\n\n");
                    fclose(file);
                    printf("\nReceita \"%s\" salva com sucesso!\n", nome);
                    break;

                case 3:
                    sn[0] = 'n';
                    break;

                default:
                    printf("\nOpcao invalida!\n");
                    break;
            }

            if (sn[0] == 'n') break;

            printf("\n\nDeseja voltar ao menu? s/n: ");
            scanf("%s", sn);
        }

        printf("\n\tFECHANDO O LIVRO...\n...\n");
    }

    return 0;
}
