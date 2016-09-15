#ifndef FUNALLOC_H
# define FUNALLOC_H

# include <stdbool.h>

void *funalloc();
void free_fun(void *fun);
void ex_set(int v);

#endif
