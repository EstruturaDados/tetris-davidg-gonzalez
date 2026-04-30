#include <stdio.h>
#include <stdlib.h>

#define TAM 5
#define TAM_PILHA 3

// Struct da peça
typedef struct {
    char tipo;
    int id;
} Peca;

// ================= FILA =================
typedef struct {
    Peca itens[TAM];
    int inicio;
    int fim;
    int tamanho;
} Fila;

void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->tamanho = 0;
}

int filaCheia(Fila *f) {
    return f->tamanho == TAM;
}

int filaVazia(Fila *f) {
    return f->tamanho == 0;
}

void enqueue(Fila *f, Peca p) {
    if (filaCheia(f)) return;

    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % TAM;
    f->tamanho++;
}

Peca dequeue(Fila *f) {
    Peca p;

    if (filaVazia(f)) {
        p.id = -1;
        return p;
    }

    p = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % TAM;
    f->tamanho--;

    return p;
}

// ================= PILHA =================
typedef struct {
    Peca itens[TAM_PILHA];
    int topo;
} Pilha;

void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

int pilhaCheia(Pilha *p) {
    return p->topo == TAM_PILHA - 1;
}

int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

void push(Pilha *p, Peca x) {
    if (pilhaCheia(p)) {
        printf("Pilha cheia!\n");
        return;
    }

    p->itens[++p->topo] = x;
}

Peca pop(Pilha *p) {
    Peca x;

    if (pilhaVazia(p)) {
        x.id = -1;
        return x;
    }

    return p->itens[p->topo--];
}

// ================= GERAÇÃO =================
Peca gerarPeca() {
    static int contador = 0;
    char tipos[] = {'I', 'O', 'T', 'L'};

    Peca p;
    p.tipo = tipos[rand() % 4];
    p.id = contador++;

    return p;
}

// ================= MOSTRAR =================
void mostrarFila(Fila *f) {
    printf("\nFila de Peças: ");

    int idx = f->inicio;

    for (int i = 0; i < f->tamanho; i++) {
        printf("[%c %d] ", f->itens[idx].tipo, f->itens[idx].id);
        idx = (idx + 1) % TAM;
    }

    printf("\n");
}

void mostrarPilha(Pilha *p) {
    printf("Pilha de Reserva (Topo -> Base): ");

    for (int i = p->topo; i >= 0; i--) {
        printf("[%c %d] ", p->itens[i].tipo, p->itens[i].id);
    }

    printf("\n");
}

int main() {

    // 🧩 Nível Novato: Fila de Peças Futuras
    // (já implementado)

    // 🧠 Nível Aventureiro: (já implementado)

    Fila fila;
    Pilha pilha;
    int opcao;

    inicializarFila(&fila);
    inicializarPilha(&pilha);

    // Preencher fila inicial
    for (int i = 0; i < TAM; i++) {
        enqueue(&fila, gerarPeca());
    }

    do {
        printf("\n=== Estado Atual ===\n");
        mostrarFila(&fila);
        mostrarPilha(&pilha);

        printf("\nOpções:\n");
        printf("1 - Jogar peça da frente da fila\n");
        printf("2 - Enviar peça da fila para reserva (pilha)\n");
        printf("3 - Usar peça da reserva (pilha)\n");
        printf("4 - Trocar peça da frente da fila com o topo da pilha\n");
        printf("5 - Trocar os 3 primeiros da fila com as 3 peças da pilha\n");
        printf("0 - Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao);

        switch (opcao) {

            case 1: {
                Peca removida = dequeue(&fila);
                if (removida.id != -1) {
                    printf("Você jogou [%c %d]\n", removida.tipo, removida.id);
                    enqueue(&fila, gerarPeca());
                }
                break;
            }

            case 2: {
                if (pilhaCheia(&pilha)) {
                    printf("Pilha cheia!\n");
                    break;
                }

                Peca removida = dequeue(&fila);
                if (removida.id != -1) {
                    push(&pilha, removida);
                    printf("Peça [%c %d] enviada para reserva\n", removida.tipo, removida.id);
                    enqueue(&fila, gerarPeca());
                }
                break;
            }

            case 3: {
                Peca usada = pop(&pilha);
                if (usada.id != -1) {
                    printf("Você usou [%c %d] da reserva\n", usada.tipo, usada.id);
                    enqueue(&fila, gerarPeca());
                } else {
                    printf("Pilha vazia!\n");
                }
                break;
            }

            case 4: {
                if (filaVazia(&fila) || pilhaVazia(&pilha)) {
                    printf("Não é possível realizar a troca!\n");
                    break;
                }
            
                int idx = fila.inicio;
            
                Peca temp = fila.itens[idx];
                fila.itens[idx] = pilha.itens[pilha.topo];
                pilha.itens[pilha.topo] = temp;
            
                printf("Troca realizada entre a frente da fila e o topo da pilha.\n");
                break;
            }

            case 5: {
                if (fila.tamanho < 3 || pilha.topo < 2) {
                    printf("Não há peças suficientes para troca!\n");
                    break;
                }
            
                Peca tempFila[3];
                Peca tempPilha[3];
            
                for (int i = 0; i < 3; i++) {
                    int idx = (fila.inicio + i) % TAM;
                    tempFila[i] = fila.itens[idx];
                }
            
                for (int i = 0; i < 3; i++) {
                    tempPilha[i] = pilha.itens[pilha.topo - i];
                }
            
                for (int i = 0; i < 3; i++) {
                    int idx = (fila.inicio + i) % TAM;
                    fila.itens[idx] = tempPilha[i];
                }
            
                for (int i = 0; i < 3; i++) {
                    pilha.itens[pilha.topo - i] = tempFila[2 - i];
                }
            
                printf("Troca realizada entre os 3 primeiros da fila e os 3 da pilha.\n");
            
                printf("\n=== Novo Estado ===\n");
                mostrarFila(&fila);
                mostrarPilha(&pilha);
            
                break;
            }

            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Opção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}