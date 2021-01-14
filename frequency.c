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

node *create_node();

void insert_node(node *head, char *word);

void print_words(node *head, int index, char* word);

void print_reverse_words(node* head, int index, char* word);

int main(int argc, char *argv[]) {
    node *head = create_node();
    char* word;
    word = (char*)calloc(1, sizeof (char));
    char letter;
    int i = 0;
    letter = getc(stdin);
    while (letter != EOF) {
        if (isalpha(letter)) {
            letter = tolower(letter);
            word = (char*)realloc(word, sizeof(char) * (i + 2));
            if (!word) {
                return 0;
            }
            word[i+1] ='\0';
            word[i] = letter;
            i++;
        } else if (letter == '\n' || letter == '\t' || letter == ' ') {
            insert_node(head, word);
            free(word);
            word = (char*)calloc(1, sizeof (char));
            if (!word) {
                return 0;
            }
            i = 0;
        }
        letter = getc(stdin);
    }
    free(word);
    char* word_print;
    word_print = (char*)calloc(2, sizeof (char));
    if (!word_print) {
        return 0;
    }
    word_print[1] = '\0';
    if (argc == 2 && *argv[1] == 'r') {
        print_reverse_words(head, 0, word_print);
    }
    else {
        print_words(head, 0, word_print);
    }
    free(word_print);
    free(head);

    return 0;
}

node* create_node() {
    node *new_node;
    new_node = (struct node*)calloc(2, sizeof(struct node));
    if (!new_node) {
        return NULL;
    }
    new_node->counter = 0;
    for (int i = 0; i < NUM_LETTERS; ++i) {
        new_node->children[i] = NULL;
    }
    return new_node;
}

void insert_node(node *head, char *word) {
    if (strlen(word) != 0) {
        char letter = *word;
        if (head->children[letter - 'a'] == NULL) {
            node *new_node = NULL;
            new_node = create_node();
            new_node->letter = letter;
            head->children[letter - 'a'] = new_node;
        }
        word++;
        insert_node(head->children[letter - 'a'], word);
    } else if(head->letter){
        head->counter++;
    }
}

void print_words(node* head, int index, char* word) {
    if (head == NULL) {
        return;
    }
    if (head->counter > 0) {
        char* tmp = (char*)calloc( strlen(word) + 2, sizeof (char));
        if (!tmp) {
            return;
        }
        strcpy(tmp,word);
        tmp[index] = '\0';
        printf("%s %lu\n", tmp, head->counter);
        free(tmp);
    }
    for (int i = 0; i < NUM_LETTERS; i++) {
        if (head->children[i]) {
            char* tmp = (char*)calloc( strlen(word) + 2, sizeof (char));
            if (!tmp) {
                return;
            }
            strcpy(tmp,word);
            tmp[index] = i + 'a';
            print_words(head->children[i], index + 1, tmp);
            free(head->children[i]);
            free(tmp);
        }
    }
}

void print_reverse_words(node* head, int index, char* word) {
    if (head == NULL) {
        return;
    }
    for (int i = NUM_LETTERS; i >= 0; i--) {
        if (head->children[i]) {
            char* tmp = (char*)calloc(strlen(word) + 2, sizeof (char));
            if (!tmp) {
                return;
            }
            strcpy(tmp, word);
            tmp[index] = i + 'a';
            print_reverse_words(head->children[i], index + 1, tmp);
            free(head->children[i]);
            free(tmp);
        }
    }
    if (head->counter > 0) {
        char* tmp = (char*)calloc( strlen(word) + 2, sizeof (char));
        if (!tmp) {
            return;
        }
        strcpy(tmp, word);
        tmp[index] = '\0';
        printf("%s %lu\n", tmp, head->counter);
        free(tmp);
    }
}
