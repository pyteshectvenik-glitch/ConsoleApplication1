#pragma once

#include <cstring>
#include "hash.h"

struct Node {
    char key[L];
    Node* next;
};

Node* table[M];
int collisions = 0;

bool find(const char* key, HashFn f) {
    for (Node* p = table[f(key) % M]; p != NULL; p = p->next)
        if (strcmp(p->key, key) == 0) return true;
    return false;
}

void add(const char* key, HashFn f) {
    if (find(key, f)) return;
    int i = f(key) % M;
    if (table[i] != NULL) collisions++;
    Node* p = new Node;
    strcpy(p->key, key);
    p->next = table[i];
    table[i] = p;
}

void removeKey(const char* key, HashFn f) {
    int i = f(key) % M;
    Node* prev = NULL;
    for (Node* p = table[i]; p != NULL; p = p->next) {
        if (strcmp(p->key, key) == 0) {
            if (prev == NULL) table[i] = p->next;
            else prev->next = p->next;
            delete p;
            return;
        }
        prev = p;
    }
}

void clearTable() {
    for (int i = 0; i < M; i++) {
        while (table[i] != NULL) {
            Node* t = table[i];
            table[i] = t->next;
            delete t;
        }
    }
    collisions = 0;
}

int maxChain() {
    int mx = 0;
    for (int i = 0; i < M; i++) {
        int len = 0;
        for (Node* p = table[i]; p != NULL; p = p->next) len++;
        if (len > mx) mx = len;
    }
    return mx;
}