#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Definição da estrutura da Peça
typedef struct {
    char nome; 
    int id;   
} Peca;

// Constantes da Fila
#define TAMANHO_MAX_FILA 5
#define TIPOS_DE_PECAS "IOTLJSZ" 

// Variáveis Globais da Fila Circular
Peca fila[TAMANHO_MAX_FILA]; // armazenar as peças
int frente = -1;             // frente da fila
int tras = -1;               // trás da fila
int contador_pecas = 0;      // Contador para gerar ID
int num_elementos = 0;       // Número atual de elementos 
/**
 * @brief Inicializa a fila de peças com um número fixo de elementos
 
 */
void inicializarFila() {
    // Inicializa o gerador de números 
    srand(time(NULL)); 

    // Preenche a fila inicialmente até o tamanho máximo
    for (int i = 0; i < TAMANHO_MAX_FILA; i++) {
        // Gera uma nova peça e insere. 
        
        // Chamada direta da função gerarPeca 
        
        Peca novaPeca = {
            .nome = TIPOS_DE_PECAS[rand() % 7], // tipo aleatório
            .id = contador_pecas++
        };
        
        // Inserção inicial
        if (frente == -1) {
            frente = 0;
            tras = 0;
        } else {
            tras = (tras + 1) % TAMANHO_MAX_FILA;
        }
        
        fila[tras] = novaPeca;
        num_elementos++;
    }
    
   
    printf("Fila de peças inicializada com %d elementos.\n", num_elementos);
}

/**
 * @brief Gera uma nova peça 
 * * @return 
 */
Peca gerarPeca() {
    Peca novaPeca;
    
    
    novaPeca.nome = TIPOS_DE_PECAS[rand() % 7]; 
    
    // Para atribuir o ID e incrementar ao contador global
    novaPeca.id = contador_pecas++; 
    
    printf("\nPeça gerada: [%c %d]\n", novaPeca.nome, novaPeca.id);
    return novaPeca;
}

/**
 * @brief Insere uma nova peça no final da fila 
 * * @param novaPeca 
 * @return 1 se puder inserir, 0 se a fila está cheia
 */
int enqueue(Peca novaPeca) {
    if (num_elementos == TAMANHO_MAX_FILA) {
        printf("\nErro: Fila de peças futuras está cheia! Não é possível inserir.\n");
        return 0; // Fila cheia
    }

    if (frente == -1) {
        // Se a fila estava vazia, aponta pra 0
        frente = 0;
        tras = 0;
    } else {
        
        tras = (tras + 1) % TAMANHO_MAX_FILA;
    }

    fila[tras] = novaPeca;
    num_elementos++;
    printf("Peça [%c %d] inserida no final da fila.\n", novaPeca.nome, novaPeca.id);
    return 1;
}

/**
 * @brief Remove a peça da frente da fila e retorna
 * * @return 
 */
Peca dequeue() {
    Peca pecaRemovida = {' ', -1}; // Peça vazia de retorno 

    if (num_elementos == 0) {
        printf("\nAviso: Fila de peças está vazia! Não tem peça para jogar.\n");
        return pecaRemovida; // Fila vazia
    }

    
    pecaRemovida = fila[frente];

    if (frente == tras) {
        // Se tinha um elemento, a fila fica vazia
        frente = -1;
        tras = -1;
    } else {
        
        frente = (frente + 1) % TAMANHO_MAX_FILA;
    }

    num_elementos--;
    printf("Peça [%c %d] jogada/removida da frente da fila.\n", pecaRemovida.nome, pecaRemovida.id);
    return pecaRemovida;
}

/**
 * @brief Estado atual da fila de peças
 */
void exibirFila() {
    printf("\n--Estado Atual da Fila de Peças--\n");
    if (num_elementos == 0) {
        printf("Fila vazia.\n");
        printf("-----------------------------\n");
        return;
    }
    
    
    printf("Fila de peças (Tamanho: %d/%d):\n", num_elementos, TAMANHO_MAX_FILA);

    int i = frente;
    int count = 0;

    
    while (count < num_elementos) {
        printf("[%c %d]", fila[i].nome, fila[i].id);
        
        // Adiciona um espaço
        if (count < num_elementos - 1) {
            printf(" ");
        }
        
        // Move para próxima posição 
        i = (i + 1) % TAMANHO_MAX_FILA;
        count++;
    }
    printf("\n--------------------------------\n");
}

/**
 * @brief Exibe o menu de opções 
 */
void exibirMenu() {
    printf("\n--Opções de Ação--\n");
    printf("Código - Ação\n");
    printf("-----------------------------------\n");
    printf("  1    - Jogar peça \n");
    printf("  2    - Inserir nova peça \n");
    printf("  0    - Sair\n");
    printf("-----------------------------------\n");
    printf("Escolha uma opção: ");
}

/**
 * @brief Função principal 
 */
int main() {
    int opcao;
    
    // Iniciar a fila
    inicializarFila();
    exibirFila(); 

    do {
        exibirMenu();
        if (scanf("%d", &opcao) != 1) {
            // Limpa a entrada em caso de erro 
            while (getchar() != '\n');
            opcao = -1; // Opção inválida
            printf("\nEntrada inválida. Por favor, digite um número.\n");
            continue;
        }

        switch (opcao) {
            case 1:
                // jogar peça 
                dequeue();
                break;
            case 2:
                // inserir nova peça 
                {
                    Peca novaPeca = gerarPeca();
                    enqueue(novaPeca);
                }
                break;
            case 0:
                // Sair
                printf("\nSaindo do Tetris Stack!\n");
                break;
            default:
                printf("\nOpção desconhecida. Por favor, tente novamente.\n");
                break;
        }

        // Exibe o estado da fila 
        if (opcao != 0) {
            exibirFila();
        }

    } while (opcao != 0);

    return 0;
}