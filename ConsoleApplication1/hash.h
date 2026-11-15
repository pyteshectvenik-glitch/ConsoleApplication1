#pragma once

const int M = 10007;   
const int L = 32;      

typedef unsigned int (*HashFn)(const char*);

unsigned int hashDjb2(const char* s) {      
    unsigned int h = 5381;
    for (int i = 0; s[i]; i++) h = h * 33 + (unsigned char)s[i];
    return h;
}
unsigned int hashSum(const char* s) {      
    unsigned int h = 0;
    for (int i = 0; s[i]; i++) h += (unsigned char)s[i];
    return h;
}
unsigned int hashPoly(const char* s) {     
    unsigned int h = 0;
    for (int i = 0; s[i]; i++) h = h * 257 + (unsigned char)s[i];
    return h;
}
unsigned int hashRot(const char* s) {       
    unsigned int h = 12345;
    for (int i = 0; s[i]; i++) {
        h = (h << 5) | (h >> 27);
        h = h ^ (unsigned char)s[i];
        h = h * 2654435761u;
    }
    return h;
}