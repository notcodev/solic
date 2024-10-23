#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define CARD_WIDTH 60
#define CARD_HEIGHT 60
#define COLUMNS_GAP 20

#define NELEMS(x)  (sizeof(x) / sizeof(x[0]))

typedef enum {
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING,
    ACE,
} Rank;

typedef enum {
    HEARTS,
    DIAMONDS,
    CLUBS,
    SPADES,
} Suit;

typedef struct {
    Rank rank;
    Suit suit;
} Card;

typedef struct LinkedListNode {
    void *data;
    struct LinkedListNode *prev;
    struct LinkedListNode *next;
} LinkedListNode;

typedef struct {
    struct LinkedListNode *head;
    struct LinkedListNode *tail;
} LinkedList;

static void shuffle(void *array, size_t n, size_t size) {
    char tmp[size];
    char *arr = array;
    size_t stride = size * sizeof(char);

    if (n > 1) {
        size_t i;
        for (i = 0; i < n - 1; ++i) {
            size_t rnd = (size_t) rand();
            size_t j = i + rnd / (RAND_MAX / (n - i) + 1);

            memcpy(tmp, arr + j * stride, size);
            memcpy(arr + j * stride, arr + i * stride, size);
            memcpy(arr + i * stride, tmp, size);
        }
    }
}


void fillCards(Card **array) {
    int index = 0;
    for (int rank = TWO; rank <= ACE; rank++) {
        for (int suit = HEARTS; suit <= SPADES; suit++) {
            Card *card = (Card*)(malloc(sizeof(Card)));
            card->suit = suit;
            card->rank = rank;

            array[index] = card;
            index++;
        }
    }
}

void drawCardText(Card *card, int posX, int posY, int fontSize, Color color) {
    switch (card->rank) {
        case TWO:
            DrawText("2", posX, posY, fontSize, color);
            break;
        case THREE:
            DrawText("3", posX, posY, fontSize, color);
            break;
        case FOUR:
            DrawText("4", posX, posY, fontSize, color);
            break;
        case FIVE:
            DrawText("5", posX, posY, fontSize, color);
            break;
        case SIX:
            DrawText("6", posX, posY, fontSize, color);
            break;
        case SEVEN:
            DrawText("7", posX, posY, fontSize, color);
            break;
        case EIGHT:
            DrawText("8", posX, posY, fontSize, color);
            break;
        case NINE:
            DrawText("9", posX, posY, fontSize, color);
            break;
        case TEN:
            DrawText("10", posX, posY, fontSize, color);
            break;
        case JACK:
            DrawText("J", posX, posY, fontSize, color);
            break;
        case QUEEN:
            DrawText("Q", posX, posY, fontSize, color);
            break;
        case KING:
            DrawText("K", posX, posY, fontSize, color);
            break;
        case ACE:
            DrawText("A", posX, posY, fontSize, color);
            break;
    }
}

void fillSlots(LinkedList** slots, Card** cards) {
    int index = 0;

    for (int i = 0; i < 7; i++) {
        LinkedList* column = (LinkedList*)malloc(sizeof(LinkedList));
        column->head = NULL;
        column->tail = NULL;
        LinkedListNode* lastNode = NULL;

        for (int j = 0; j < i + 1; j++) {
            LinkedListNode* node = (LinkedListNode*)malloc(sizeof(LinkedListNode));
            node->data = cards[index];
            node->prev = NULL;
            node->next = NULL;

            if (j == 0) {
                column->head = node;
            } else {
                lastNode->next = node;
                node->prev = lastNode;
            }

            if (j == i) {
                column->tail = node;
            }

            lastNode = node;
            index++;
        }

        slots[i] = column;
    }
}

int main(void) {
    srand(time(NULL));

    Card* cards[52];
    LinkedList* slots[7];

    fillCards(cards);
    shuffle(cards, NELEMS(cards), sizeof(Card*));
    fillSlots(slots, cards);

    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Raylib basic window");
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(WHITE);

        for (int i = 0; i < 7; i++) {
            LinkedList* column = slots[i];
            LinkedListNode* lastNode = column->head;

            int y = 20;

            while (lastNode != NULL) {
                int rectX = 20 + (CARD_WIDTH + COLUMNS_GAP) * i;
                int rectY = y;

                Rectangle rect = {
                    .height = CARD_HEIGHT,
                    .width = CARD_WIDTH,
                    .x = rectX,
                    .y = rectY
                };

                DrawRectangleRec(rect, BLACK);
                drawCardText((Card*)lastNode->data, rect.x + 4, rect.y + 4, 12, WHITE);

                y += 20;
                lastNode = lastNode->next;
            }
        }

        // if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) ClearBackground(BLACK);
        // else ClearBackground(WHITE);

        // DrawText("It works!", 20, 20, 20, BLACK);
        EndDrawing();
    }
    CloseWindow();

    return 0;
}
