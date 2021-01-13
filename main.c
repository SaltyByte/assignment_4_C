#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define NUM_LETTERS 26

typedef struct node {
    char letter;
    long unsigned int counter;
    struct node *children[NUM_LETTERS];
} node;

char *get_word();

node *create_node();

void insert_node(node *head, char *word);

void print_words(node *head);

int main(int argc, char* argv[]) {
//    if (argc == 'r'){
//        reverse
//    }
//    else {
//        regular
//    }


    node *head = create_node();
    char *word = get_word();
    printf("%s", word);

//    while (strlen(word) > 0) {
//        printf("%s", word);
//        insert_node(head, word);
//        word = get_word();
//    }
    return 0;
}

char *get_word() {
    char letter = '\0';
    char *word = (char *) malloc(sizeof(char));
    if (!word) {
        return NULL;
    }
    while (letter != EOF) {
        scanf("%c", &letter);
        if (letter >= 'A' && letter <= 'Z') {
            word = (char *) realloc(word, sizeof(char) * strlen(word) + 1);
            if (!word) {
                return NULL;
            }
            letter = tolower(letter);
            strncat(word, &letter, 1);
        } else if (letter == '\n' || letter == '\t' || letter == '\r' || letter == ' ') {
            break;
        } else if (letter >= 'a' && letter <= 'z') {
            word = (char *) realloc(word, sizeof(char) * strlen(word) + 1);
            if (!word) {
                return NULL;
            }
            strncat(word, &letter, 1);
        }
    }
    return word;
}

node *create_node() {
    node *new_node;
    new_node = malloc(sizeof(node));
    new_node->counter = 0;
    for (int i = 0; i < NUM_LETTERS; ++i) {
        new_node->children[i] = NULL;
    }
    return new_node;
}

void insert_node(node *head, char *word) {
    if (head == NULL || word == NULL) {
        return;
    }
    if (strlen(word) - 1 != 0) {
        char letter = *word;
        if (head->children[letter - 'a'] == NULL) {
            node *new_node = NULL;
            new_node = create_node();
            new_node->letter = letter;
            head->children[letter - 'a'] = new_node;
        }
        word++;
        insert_node(head->children[letter - 'a'], word);
    } else {
        head->counter++;
    }
}

void print_words(node *head) {
    if (head == NULL) {
        return;
    }

}



