#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

struct Node* createNode(int data) {
    struct Node* newNode = malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

void insertAtBeginning(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    if (*head != NULL) {
        newNode->next = *head;
        (*head)->prev = newNode;
    }
    *head = newNode;
}

void insertAtEnd(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
    } else {
        struct Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->prev = temp;
    }
}

void insertAtPosition(struct Node** head, int data, int position) {
    if (position <= 1) {
        insertAtBeginning(head, data);
    } else {
        struct Node* newNode = createNode(data);
        struct Node* temp = *head;
        for (int i = 1; i < position - 1 && temp != NULL; ++i) {
            temp = temp->next;
        }
        if (temp != NULL) {
            newNode->next = temp->next;
            newNode->prev = temp;
            if (temp->next != NULL) {
                temp->next->prev = newNode;
            }
            temp->next = newNode;
        } else {
            printf("Posição inválida.\n");
        }
    }
}

void deleteAtBeginning(struct Node** head) {
    if (*head != NULL) {
        struct Node* temp = *head;
        *head = (*head)->next;
        if (*head != NULL) {
            (*head)->prev = NULL;
        }
        free(temp);
    } else {
        printf("Lista vazia, não é possível excluir.\n");
    }
}

void deleteAtEnd(struct Node** head) {
    if (*head != NULL) {
        struct Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        if (temp->prev != NULL) {
            temp->prev->next = NULL;
        } else {
            *head = NULL;
        }
        free(temp);
    } else {
        printf("Lista vazia, não é possível excluir.\n");
    }
}

void deleteAtPosition(struct Node** head, int position) {
    if (*head != NULL && position >= 1) {
        struct Node* temp = *head;
        for (int i = 1; i < position && temp != NULL; ++i) {
            temp = temp->next;
        }
        if (temp != NULL) {
            if (temp->prev != NULL) {
                temp->prev->next = temp->next;
            } else {
                *head = temp->next;
            }
            if (temp->next != NULL) {
                temp->next->prev = temp->prev;
            }
            free(temp);
        } else {
            printf("Posição inválida, não é possível excluir.\n");
        }
    } else {
        printf("Lista vazia ou posição inválida, não é possível excluir.\n");
    }
}

struct Node* searchNode(struct Node* head, int data) {
    while (head != NULL) {
        if (head->data == data) {
            return head;
        }
        head = head->next;
    }
    return NULL;
}

void displayList(struct Node* head) {
    printf("Conteúdo da lista: ");
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

void freeList(struct Node** head) {
    while (*head != NULL) {
        struct Node* temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}

int main() {
    struct Node* head = NULL;
    int choice, data, position;

    do {
        printf("\n1. Inserir no início");
        printf("\n2. Inserir no final");
        printf("\n3. Inserir em uma posição específica");
        printf("\n4. Excluir do início");
        printf("\n5. Excluir do final");
        printf("\n6. Excluir de uma posição específica");
        printf("\n7. Pesquisar nó");
        printf("\n8. Exibir lista");
        printf("\n0. Sair");

        printf("\nEscolha uma opção: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Digite o valor a ser inserido: ");
                scanf("%d", &data);
                insertAtBeginning(&head, data);
                break;

            case 2:
                printf("Digite o valor a ser inserido: ");
                scanf("%d", &data);
                insertAtEnd(&head, data);
                break;

            case 3:
                printf("Digite o valor a ser inserido: ");
                scanf("%d", &data);
                printf("Digite a posição: ");
                scanf("%d", &position);
                insertAtPosition(&head, data, position);
                break;

            case 4:
                deleteAtBeginning(&head);
                break;

            case 5:
                deleteAtEnd(&head);
                break;

            case 6:
                printf("Digite a posição a ser excluída: ");
                scanf("%d", &position);
                deleteAtPosition(&head, position);
                break;

            case 7:
                printf("Digite o valor a ser pesquisado: ");
                scanf("%d", &data);
                struct Node* searchedNode = searchNode(head, data);
                if (searchedNode != NULL) {
                    printf("Nó encontrado com valor: %d\n", searchedNode->data);
                } else {
                    printf("Nó não encontrado.\n");
                }
                break;

            case 8:
                displayList(head);
                break;

            case 0:
                printf("Saindo do programa.\n");
                break;

            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (choice != 0);

    freeList(&head);

    return 0;
}
