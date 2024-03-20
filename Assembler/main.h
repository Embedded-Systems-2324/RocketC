#ifndef _ASSEMBLER_MAIN_H_
#define _ASSEMBLER_MAIN_H_

#include <stdio.h>
#include <stdlib.h>

void get_source_file(FILE** file);

size_t get_line_number();
size_t increment_line_number(size_t n);

#endif