#pragma once
#include <cstring>
#include "hash.h"

char keys[M][L];
char state[M];          
int collisions = 0;     
int maxProbes = 0;      


int stepOf(const char* key) {
    return 1 + hashFnv(key) % (M - 1);
}

bool find(const char* key, HashFn f) {
    int idx = f(key) % M;
    int step = stepOf(key);
    for (int i = 0; i < M; i++) {
        if (state[idx] == 0) return false;
        if (state[idx] == 1 && strcmp(keys[idx], key) == 0) return true;
        idx = (idx + step) % M;
    }
    return false;
}

void add(const char* key, HashFn f) {
    if (find(key, f)) return;
    int idx = f(key) % M;
    int step = stepOf(key);
    int probes = 0;
    while (state[idx] == 1) {       
        collisions++;
        probes++;
        idx = (idx + step) % M;
    }
    strcpy(keys[idx], key);
    state[idx] = 1;
    if (probes > maxProbes) maxProbes = probes;
}

void removeKey(const char* key, HashFn f) {
    int idx = f(key) % M;
    int step = stepOf(key);
    for (int i = 0; i < M; i++) {
        if (state[idx] == 0) return;
        if (state[idx] == 1 && strcmp(keys[idx], key) == 0) {
            state[idx] = 2;         
            return;
        }
        idx = (idx + step) % M;
    }
}

void clearTable() {
    memset(state, 0, sizeof(state));
    collisions = 0;
    maxProbes = 0;
}