LD_PRELOAD=./libft_malloc.so ./a.out


valgrind \
  --leak-check=full \
  --track-origins=yes \
  --show-leak-kinds=all \
  --soname-synonyms=somalloc=nouserintercepts \
  env LD_PRELOAD="$PWD/libft_malloc.so" ./test_malloc
