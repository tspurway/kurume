#ifndef _FAST_TRIE_H_
#define _FAST_TRIE_H_

#include "stdint.h"
#include "stddef.h"

#define MIN(x, y) (((x) < (y)) ? (x) : (y))

typedef struct {
    int             parent_index;
    size_t          kid_size;
    int             knodes[256];
    size_t          key_length;
    int             key;
} FastTrieNode;

typedef struct {
    size_t          capacity;
    int             free_index;
    unsigned char   *heap;
} StringHeap;


typedef enum {K_SMALL=8, K_MEDIUM=16, K_LARGE=32, K_XLARGE=64} TrieWidth;

typedef struct {
    FastTrieNode    *nodes;
    size_t          width;
    size_t          kid_space;
    size_t          size;           // current element in the heap
    size_t          rest;           //rest number of the slots available
    size_t          max_size;
    StringHeap      heap;
} FastTrie;

int create_fast_trie(const TrieWidth width, const size_t initial_size, FastTrie *trie);
int add_fast_trie(FastTrie *trie, unsigned char *key, size_t key_length);
void print_fast_trie(FastTrie *trie);
size_t string_for_vid_fast_trie(FastTrie *trie, int vid, unsigned char *key, size_t max_key_length);

#endif