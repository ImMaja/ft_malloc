
A faire avant re rendre:
	Virer tous les ft_print et write de test


LD_PRELOAD=./libft_malloc.so ./a.out


valgrind \
  --leak-check=full \
  --track-origins=yes \
  --show-leak-kinds=all \
  --soname-synonyms=somalloc=nouserintercepts \
  env LD_PRELOAD="$PWD/libft_malloc.so" ./test_malloc
