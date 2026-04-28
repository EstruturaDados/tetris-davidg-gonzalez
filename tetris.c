#include <stdio.h>
#include <stdlib.h>

// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha
// Este código inicial serve como base para o desenvolvimento do sistema de controle de peças.
// Use as instruções de cada nível para desenvolver o desafio.

#define TAM 5

// Struct da peça
typedef struct {
    char tipo;
    int id;
} Peca;

// Estrutura da fila circular
typedef struct {
    Peca itens[TAM];
    int inicio;
    int fim;
    int tamanho;
} Fila;

// Função para inicializar fila
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->tamanho = 0;
}

// Verifica se fila está cheia
int filaCheia(Fila *f) {
    return f->tamanho == TAM;
}

// Verifica se fila está vazia
int filaVazia(Fila *f) {
    return f->tamanho == 0;
}

// Gerar peça automaticamente
Peca gerarPeca() {
    static int contador = 1;
    char tipos[] = {'I', 'O', 'T', 'L'};

    Peca p;
    p.tipo = tipos[rand() % 4];
    p.id = contador++;

    return p;
}

// Inserir na fila (enqueue)
void enqueue(Fila *f, Peca p) {
    if (filaCheia(f)) {
        printf("Fila cheia!\n");
        return;
    }

    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % TAM;
    f->tamanho++;
}

// Remover da fila (dequeue)
Peca dequeue(Fila *f) {
    Peca p;

    if (filaVazia(f)) {
        printf("Fila vazia!\n");
        p.tipo = '-';
        p.id = -1;
        return p;
    }

    p = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % TAM;
    f->tamanho--;

    return p;
}

// Mostrar fila
void mostrarFila(Fila *f) {
    printf("\nFila de Peças: ");

    int i;
    int idx = f->inicio;

    for (i = 0; i < f->tamanho; i++) {
        printf("[%c %d] ", f->itens[idx].tipo, f->itens[idx].id);
        idx = (idx + 1) % TAM;
    }

    printf("\n");
}

int main() {

    // 🧩 Nível Novato: Fila de Peças Futuras
    //
    // - Crie uma struct Peca com os campos: tipo (char) e id (int).
    // - Implemente uma fila circular com capacidade para 5 peças.
    // - Crie funções como inicializarFila(), enqueue(), dequeue(), filaCheia(), filaVazia().
    // - Cada peça deve ser gerada automaticamente com um tipo aleatório e id sequencial.
    // - Exiba a fila após cada ação com uma função mostrarFila().
    // - Use um menu com opções como:
    //      1 - Jogar peça (remover da frente)
    //      0 - Sair
    // - A cada remoção, insira uma nova peça ao final da fila.

    Fila fila;
    int opcao;

    inicializarFila(&fila);

    // Preencher fila inicial com 5 peças
    for (int i = 0; i < TAM; i++) {
        enqueue(&fila, gerarPeca());
    }

    do {
        mostrarFila(&fila);

        printf("\n1 - Jogar Peça (dequeue)\n");
        printf("2 - Inserir Nova Peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                Peca removida = dequeue(&fila);
                if (removida.id != -1) {
                    printf("Voce jogou a peça [%c %d]\n", removida.tipo, removida.id);
                }
                break;
            }

            case 2:
                if (!filaCheia(&fila)) {
                    enqueue(&fila, gerarPeca());
                } else {
                    printf("Fila cheia! Não pode inserir.\n");
                }
                break;

            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Opção inválida!\n");
        }

    } while (opcao != 0);


    // 🧠 Nível Aventureiro: Adição da Pilha de Reserva
    // (não implementado neste nível)

    // 🔄 Nível Mestre: Integração Estratégica entre Fila e Pilha
    // (não implementado neste nível)

    return 0;
}