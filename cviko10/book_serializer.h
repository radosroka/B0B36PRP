#ifndef __BOOK_SERIALIZER_H__
#define __BOOK_SERIALIZER_H__

#include <stdio.h>
#include "book.h"

#define OUTPUT_FILE "serialized.file"

void serialize_book(FILE* f, Book* p);
Book* deserialize_book(FILE* f);

void serialize_book_list(FILE* f, BookList* pl);
BookList* deserialize_book_list(FILE* f);

#endif
