#include "fast_trie.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <fast_trie.h>

const char *smoketest[] = {
        "hello", "there", "goodbye", "hells bells", "henry", "hell hath no fury", "xarg", "govna"
};

const char *heaptest[] = {
        "hellojlkdfssfdsddddddddfsddsfsagfdfgfadljdfsajlkfdsjklfdasjkfdsahjkhjkhjkjkhhjkjhkhjkhkjhkj",
        "therefdljfdsajklfdsjkldfsjkldfsjkldfs",
        "ljkdfsjlfdsjlkljkfsdlkjljkdfslkjjkldfsgoodbye", "hells bellskjndfsjklljkfdsjlk", "henryjklfdsljkjlkdfskljjklfds",
        "hell hath no jlkdfsjlljkdfskljlfjkdsljkdfsljklkjdfslkjdfs fury", "xargjkldfsjlkjlkdfslkjljkdfs", "govna"
};

int main(int argc, char *argv[]) {
    FastTrie small_wtrie;
    assert(!create_fast_trie(K_SMALL, 64, &small_wtrie));

    // basic test
    printf("Smoketest...\n");
    int smoketest_vids[sizeof(*smoketest)];
    for (int i = 0; i < sizeof(*smoketest); ++i) {
        int vid = add_fast_trie(&small_wtrie, (unsigned char*) smoketest[i], strlen(smoketest[i]));
        smoketest_vids[i] = vid;
    }
    print_fast_trie(&small_wtrie);
    for (int i = 0; i < sizeof(*smoketest); ++i) {
        int vid = add_fast_trie(&small_wtrie, (unsigned char*) smoketest[i], strlen(smoketest[i]));
//        printf("vid=%d test_vid=%d\n", vid, smoketest_vids[i]);
        assert(vid == smoketest_vids[i]);
    }
    // make sure partial vids are accounted for as well
    assert(add_fast_trie(&small_wtrie, (unsigned char*)"hell", 4) == 4);
    assert(add_fast_trie(&small_wtrie, (unsigned char*)"he", 2) == 6);

    // test string_for_vid
    for (int i = 0; i < sizeof(*smoketest); ++i) {
        unsigned char buff[1024];
        size_t buff_size = string_for_vid_fast_trie(&small_wtrie, smoketest_vids[i], buff, 1024);
//        printf("buff_size=%zd %s key='%.*s'\n", buff_size, smoketest[i], (int)buff_size, buff);
        assert(buff_size == strlen(smoketest[i]));
        assert(!memcmp(smoketest[i], buff, buff_size));
    }

    // make sure aggregate/migrated vids are accounted for
    assert(add_fast_trie(&small_wtrie, (unsigned char*)"hell hath no fury", 17) == 8);


    // test heap growth - the big strings should have doubled the heap's size twice (64 * 2) * 2 = 256
    FastTrie heap_wtrie;
    assert(!create_fast_trie(K_SMALL, 64, &heap_wtrie));
    printf("heaptest...\n");
    for (int i = 0; i < sizeof(*heaptest); ++i) {
//        printf("%s\n", heaptest[i]);
        add_fast_trie(&heap_wtrie, (unsigned char*) heaptest[i], strlen(heaptest[i]));
    }
    print_fast_trie(&heap_wtrie);
    assert(heap_wtrie.heap.capacity == 256);

    return 0;
}
