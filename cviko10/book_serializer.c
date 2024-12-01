#include <stdlib.h>
#include <string.h>

#include "book_serializer.h"

void serialize_book(FILE* f, Book* b) {
    if (!f || !b) {
        fprintf(stderr, "Error: got NULL");
        return;
    }

    if (fwrite(&b->year, sizeof(int), 1, f) != 1) {
        perror("Error: writing to file1");
        return;
    }

    if (fwrite(b->title, sizeof(char) * MAX_NAME_SIZE, 1, f) != 1) {
        perror("Error: writing to file2");
        return;
    }

    if (fwrite(&b->abstract, sizeof(char*) , 1, f) != 1) {
        perror("Error: writing to file3");
        return;
    }

    size_t len = 0; 
    if (b->abstract)
        len = strlen(b->abstract);
    
    if (fwrite(&len, sizeof(size_t), 1, f) != 1) {
        perror("Error: writing file4");
        return;
    }

    if (b->abstract && len > 0)
        if (fwrite(b->abstract, sizeof(char) * len, 1, f) != 1) {
            perror("Error: writing to file5");
            return;
        }
}

Book* deserialize_book(FILE* f) {
    if (!f) {
        fprintf(stderr, "Error: got NULL");
        return NULL;
    }

    Book* book = create_book(0, "", "");
    if (!book) {
        fprintf(stderr, "Error: malloc failed");
        return NULL;
    }
    
    if (fread(&book->year, sizeof(int), 1, f) != 1) {
        if (!feof(f))
            perror("Error: reading file1");
        goto error;
    }

    if (fread(book->title, sizeof(char) * MAX_NAME_SIZE, 1, f) != 1) {
        perror("Error: reading file2");
        goto error;
    }

    char* abstract = NULL;
    if (fread(&abstract, sizeof(char*), 1, f) != 1) {
        perror("Error: reading file3");
        goto error;
    }

    size_t len = 0;
    if (fread(&len, sizeof(size_t), 1, f) != 1) {
        perror("Error: reading file4");
        goto error;
    }

    if (!abstract) {
        free(book->abstract);
        book->abstract = NULL;
        return book;
    }

    // handle empty string
    if (abstract && len == 0) {
        return book;
    }

    char * str = malloc(sizeof(char) * len);
    if (!str) {
        fprintf(stderr, "Error: malloc failed");
        goto error;
    }

    if (fread(str, sizeof(char) * len, 1, f) != 1) {
        perror("Error: reading file5");
        free(str);
        goto error;
    }

    free(book->abstract);
    book->abstract = str;

    return book;

error:
    destroy_book(book);
    return NULL;
}


void serialize_book_list(FILE* f, BookList* p1) {
    if (!f || !p1) {
        fprintf(stderr, "Error: got NULL");
        return;
    }

    for (size_t i = 0; i < p1->size; i++) {
        serialize_book(f, p1->books[i]);
    }
}

BookList* deserialize_book_list(FILE* f) {
    if (!f) {
        fprintf(stderr, "Error: got NULL");
        return NULL;
    }

    BookList* bl = create_book_list();
    Book* b = NULL;
    while ((b = deserialize_book(f))) {
        add_book(bl, b);
    }
    
    return bl;
}

