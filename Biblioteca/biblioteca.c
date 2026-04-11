#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constantes
#define MAX_LIVROS 50
#define TAM_STRING 100

// Definicição de estruturas

struct Livro
{
    char nome[TAM_STRING];
    char autor[TAM_STRING];
    char editora[TAM_STRING];
    int edicao;
};

// Função para limpar o buffer
void limparBufferEntrada()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

// Função principal

int main()
{
    struct Livro biblioteca[MAX_LIVROS];
    int totalLivros = 0;
    int opcao;

    do
    {

        printf("================\n");
        printf("   BIBLIOTECA \n");
        printf("================\n");
        printf("1 - Cadastrar livros\n");
        printf("2 - Listar todos os livros\n");
        printf("0 - Sair\n");
        printf("----------------------\n");
        printf("Escolha uma opção: \n");

        // Lê a opção do usuário.
        scanf("%d", &opcao);
        limparBufferEntrada();

        // ------ Processamneto da Opção ------
        switch (opcao)
        {
        case 1: // CADASTRO DE LIVROS
            printf("----- Cadastro de novo livro -----\n\n");

            if (totalLivros < MAX_LIVROS)
            {
                printf("Digite o nome do livro: ");
                fgets(biblioteca[totalLivros].nome, TAM_STRING, stdin);

                printf("Digite o autor: ");
                fgets(biblioteca[totalLivros].autor, TAM_STRING, stdin);

                printf("Digite a editora: ");
                fgets(biblioteca[totalLivros].editora, TAM_STRING, stdin);

                biblioteca[totalLivros].nome[strcspn(biblioteca[totalLivros].nome, "\n")] = '\0';
                biblioteca[totalLivros].autor[strcspn(biblioteca[totalLivros].autor, "\n")] = '\0';
                biblioteca[totalLivros].editora[strcspn(biblioteca[totalLivros].editora, "\n")] = '\0';

                printf("Digite a edição: ");
                scanf("%d", &biblioteca[totalLivros].edicao, TAM_STRING, stdin);
                limparBufferEntrada();

                totalLivros++;

                printf("\nLivro cadastrado com sucesso!!\n");
            }
            else
            {
                printf("Biblioteca cheia ! Não foi possivel cadastrar mais livros.\n");
            }

            printf("\nPressione Enter para continuar...");
            getchar(); // Pausa para o usúario ler a menssagem antes de voltar poara o menu.
            break;

        case 2: // LISTAGEM DE LIVROS
            printf("--- Lista de Livros Cadastrados ---\n\n");

            if (totalLivros == 0)
            {
                printf("Nenhum livro casdastradado ainda.\n");
            }
            else
            {
                for (int i = 0; i < totalLivros; i++)
                {
                    printf("-----------------------\n");
                    printf("LIVRO: %d\n", i + 1);
                    printf("Nome: %s\n", biblioteca[i].nome);
                    printf("Autor: %s\n", biblioteca[i].autor);
                    printf("Editora: %s\n", biblioteca[i].editora);
                    printf("Edição: %d\n", biblioteca[i].edicao);
                }
                printf("---------------------------\n");
            }
            printf("\nPressione Enter para continuar...\n");
            getchar();
            break;

        case 0: // SAIDA DO SISTEMA
            printf("\nSaindo do sistema...\n");
            break;

        default:
            printf("\nOpção invalida! Tente novamente.\n");
            printf("\nPressione Enter para continuar...");
            getchar();
            break;
        }

    } while (opcao != 0);
    return 0;
}
