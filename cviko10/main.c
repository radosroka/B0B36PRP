
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#include "book.h"
#include "book_serializer.h"
 
BookList* get_example_list();
void test_list_contents();
int main() {
    printf("int: %ld\n", sizeof(int));
    printf("size_t: %ld\n", sizeof(size_t));
    printf("char: %ld\n", sizeof(char));
    printf("char*: %ld\n", sizeof(char*));
    printf("Book: %ld\n", sizeof(Book));
    test_list_contents();
    return 0;
}
 
BookList* get_example_list() {
    BookList* pl = create_book_list();
    Book* p1 = create_book(2005, "Programming in C", "Programming in C will teach you how to write programs in the C programming language.");
    Book* p2 = create_book(161, "Meditations", NULL);
    Book* p3 = create_book(-1500, "Poor Man of Nipur", "");
    add_book(pl, p1);
    add_book(pl, p2);
    add_book(pl, p3);
    return pl;
}
 
void test_list_contents() {
    BookList* pl = get_example_list();
    print_book_list(pl);
    
    {
        printf("Writing\n");
        FILE* f = fopen(OUTPUT_FILE, "wb");
        serialize_book_list(f, pl);
        destroy_book_list(pl);
        fclose(f);
    }
    
    {
        printf("Reading\n");
        FILE* f = fopen(OUTPUT_FILE, "rb");
        pl = deserialize_book_list(f);
        print_book_list(pl);
        destroy_book_list(pl);
        fclose(f);
    }
    

}
