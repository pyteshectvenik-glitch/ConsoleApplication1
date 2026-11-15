#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "hash.h"
#include "table.h"

const int N = 10000;   
char data[N][L];       
int n;                 

void fillRandom() {
    n = N;
    for (int i = 0; i < n; i++) {
        int len = 5 + rand() % 8;
        for (int j = 0; j < len; j++) data[i][j] = 'a' + rand() % 26;
        data[i][len] = '\0';
    }
}
void fillNames() {
    n = 0;
    std::ifstream in("names.txt");
    while (n < N && in.getline(data[n], L)) {
        int len = (int)strlen(data[n]);
        if (len > 0 && data[n][len - 1] == '\r') data[n][len - 1] = '\0';
        if (strlen(data[n]) > 0) n++;
    }
}
void fillSequential() {
    n = N;
    for (int i = 0; i < n; i++) sprintf(data[i], "key%06d", i);
}

int main() {
    
    add("test", hashPoly);
    std::cout << "find: " << find("test", hashPoly) << std::endl;         
    removeKey("test", hashPoly);
    std::cout << "after remove: " << find("test", hashPoly) << std::endl; 
    clearTable();

    const char* setNames[3] = { "random", "names", "sequential" };
    const char* fnNames[4] = { "djb2", "Sum", "Poly257", "Rot" };
    HashFn fns[4] = { hashDjb2, hashSum, hashPoly, hashRot };

    std::ofstream csv("results.csv");
    csv << "dataset;function;collisions;max_chain\n";

    for (int d = 0; d < 3; d++) {
        if (d == 0) fillRandom();
        if (d == 1) fillNames();
        if (d == 2) fillSequential();

        for (int k = 0; k < 4; k++) {
            clearTable();
            for (int i = 0; i < n; i++) add(data[i], fns[k]);

            std::cout << setNames[d] << "\t" << fnNames[k] << "\t"
                << collisions << "\t" << maxChain() << std::endl;
            csv << setNames[d] << ";" << fnNames[k] << ";"
                << collisions << ";" << maxChain() << "\n";
        }
    }
    return 0;
}