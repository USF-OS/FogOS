#include "shuf.h"
#include "user.h"

void malloc_error(char* error) 
{
  printf("shuf malloc error: %s\n", error);
  exit(-1);
}

void vec_init(vec_t* vec, int n) 
{
  vec->strings = malloc(n * sizeof(char*));
  if (!vec->strings) malloc_error("Vec init failed");
  vec->len = 0;
  vec->cap = n;
  int i;
  for (i = 0; i < n; i++) {
    vec->strings[i] = NULL;
  }
}

void vec_push(vec_t* vec, char* string) 
{
  // if we are about to go over capacity
  if (vec->len == vec->cap) {
    vec->cap *= 2;
    char** new_buf = malloc(vec->cap * sizeof(char*));
    if (!new_buf) malloc_error("Vec realloc failed");
    // clear new_buf
    int i;
    for (i = vec->len; i < vec->cap; i++) {
      new_buf[i] = NULL;
    }
    // realloc
    memcpy(new_buf, vec->strings, vec->len * sizeof(char*));
    free(vec->strings);
    vec->strings = new_buf;
  }
  // essentially strdup
  int string_len = strlen(string);
  vec->strings[vec->len] = malloc(string_len + 1);
  if (!vec->strings[vec->len]) malloc_error("Vec push failed");
  strcpy(vec->strings[vec->len], string);

  (vec->len)++;
}
