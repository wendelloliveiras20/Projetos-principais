#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LIVROS 50
#define MAX_EMPRESTIMOS 100 
#define TAM_STRING 100

struct Livro {
    char nome[TAM_STRING];
    char autor[TAM_STRING];
    char editora[TAM_STRING];
    int edicao;
    int disponivel; // 1 para SIM, 0 para NÃO.
};

//struct para armazenar informações do empréstimo.
struct Emprestimo{
    int indiceLivro;
    char nomeUsuario[TAM_STRING];
};

//Função para limpar o buffer de entrada.
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
};

int main() {
    struct Livro *biblioteca;
    struct Emprestimo *emprestimos;

    //Utilizar calloc para inicializar a memoria com 0.
    biblioteca = (struct Livro *) calloc(MAX_LIVROS, sizeof(struct Livro));

    emprestimos = (struct Emprestimo *) malloc(MAX_EMPRESTIMOS * sizeof(struct Emprestimo));

    //VERIFICAÇÃO
    if (biblioteca == NULL || emprestimos == NULL) {
        printf("Erro : Falha ao colocar memoria.\n");
        return 1; //retornar 1 para idicar um erro.
    }

    int totalLivros = 0;
    int totalEmprestimos = 0;
    int opcao;

    do {
        printf("===============================\n");
        printf("  BIBLIOTECA - PARTE 2\n");
        printf("===============================\n");
        printf("1 - Cadastrar novo livro\n");
        printf("2 - Listar todos os livros\n");
        printf("3 - Realizar emprestimos\n");
        printf("4 - Listar emprestimos\n");
        printf("0 - Sair\n");
        printf("-------------------------------\n");
        printf("Escolha uma opção: \n");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1: //CADASTRO DE LIVROS  
                printf("--- Cadastro de Novo livro ---\n\n");
                if (totalLivros < MAX_LIVROS) {
                    printf("Digite o nome do livro: ");
                    fgets(biblioteca[totalLivros].nome, TAM_STRING, stdin);

                    printf("Digite o autor: ");
                fgets(biblioteca[totalLivros].autor, TAM_STRING, stdin);

                printf("Digite a editora: ");
                fgets(biblioteca[totalLivros].editora, TAM_STRING, stdin);

                biblioteca[totalLivros].nome[strcspn(biblioteca[totalLivros].nome, "\n")];
                biblioteca[totalLivros].autor[strcspn(biblioteca[totalLivros].autor, "\n")];
                biblioteca[totalLivros].editora[strcspn(biblioteca[totalLivros].editora, "\n")];

                printf("Digite a edição: ");
                scanf("%d", &biblioteca[totalLivros].edicao, TAM_STRING, stdin);
                limparBuffer();

                biblioteca[totalLivros].disponivel = 1;
                totalLivros++;
                printf("\nLivro cadastrado com sucesso!\n");
                } else {
                    printf("Biblioteca cheia!\n");
                }
                printf("\nPrecione Enter para continuar...");
                getchar();
                break;

            case 2: // LISTAGEM DE LIVROS. 
                printf("--- Lista de Livros Cadastrados ---\n\n");
                if (totalLivros == 0)
                {
                printf("Nenhum livro casdastradado ainda.\n");
                }   
                else
                {
                for (int i = 0; i < totalLivros; i++){
                
                    printf("-----------------------\n");
                    printf("LIVRO %d\n", i + 1);
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

            case 3: //EPRÉSTIMO 
                printf("--- Realizar empréstimo ---\n");

                if (totalEmprestimos >= MAX_EMPRESTIMOS) {
                    printf("Limite de emprétimos atingido!\n");
                } else {
                    printf("Livros disponiveis:\n");
                    int disponiveis = 0;
                    for (int i = 0; i < totalLivros; i++){
                        if (biblioteca[i].disponivel) {
                            printf("%d - %s\n" , i + 1, biblioteca[i].nome);
                            disponiveis++;
                        }
                    }

                    if (disponiveis == 0) {
                        printf("Nenhum livro disponivel para empréstimos.\n");
                    } else {
                        printf("\nDigite o número do livro que deseja retirar: ");
                        int numLivro;
                        scanf("%d", &numLivro);
                        limparBuffer();

                        int indice = numLivro - 1;
                        
                        // Validação de escolha do usuário.
                        if (indice >= 0 && indice <totalLivros && biblioteca[indice].disponivel) {
                            printf("Digite o nome do usuario que esta pegando o livro: ");
                            fgets(emprestimos[totalEmprestimos].nomeUsuario, TAM_STRING, stdin);
                            emprestimos[totalEmprestimos].nomeUsuario[strcspn(emprestimos[totalEmprestimos].nomeUsuario, "\n")] = '\0';

                            //Registra o empréstimo.
                            emprestimos[totalEmprestimos].indiceLivro = indice;

                            //Atualiza o status do livro para disponivel.
                            biblioteca[indice].disponivel = 0;

                            totalEmprestimos++;
                            printf("\nEmpréstimo realizado com sucesso!\n");
                        } else {
                            printf("\nNúmero do livro invalido ou livro indiponivel.\n");
                        }
                    }
                }
                printf("\nPrecione Enter para continuar...");
                getchar();
                break;
            
            case 4: // LISTAR EMPÉSTIMOS.
                printf("--- Lista de Empréstimos ---\n");
                if (totalEmprestimos == 0) {
                    printf("Nenhum empréstimo realizado.\n");
                } else {
                    for (int i = 0; i < totalEmprestimos; i++) {
                        int indiceLivro = emprestimos[i].indiceLivro;
                        printf("------------------------------\n");
                        printf("EMPRESTIMO %d\n", i + 1);
                        printf("Livro: %s\n", biblioteca[indiceLivro].nome);
                        printf("Usuário: %s\n", emprestimos[i].nomeUsuario);
                    }
                    printf("------------------------------\n");
                }
                printf("\nPressione Enter para continuar...");
                getchar();
                break;
            
            case 0:
                printf("\nSaindo do sistema...\n");
                break;
            default:
                printf("\nOpção invalida\n");
                printf("\nPressione Enter para continuar...");
                break;
        }
    } while (opcao != 0);

    //LIBERAÇÃO DA MEMORIA

    free(biblioteca);
    free(emprestimos);

    printf("memoria liberada.\n");

    return 0;
}