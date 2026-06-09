#include "../../libft.h"

/**
 * @brief Compute the length of a C-string up to a maximum.
 * 		Scans at most `maxlen` bytes starting at `s` and returns the number of
 * 		non-`'\0'` bytes found before the first null terminator. If no null is found
 * 		within the first `maxlen` bytes, returns `maxlen`.
 * @param s Pointer to the string to measure. If `NULL`, the function returns 0
 *		(non‑standard behavior).
 * @param maxlen Maximum number of bytes to examine.
 * @return Length of the string, clamped to `maxlen`.
 *
 * @note Implementation uses `ft_memchr` to locate the null byte efficiently.
 */
size_t	ft_strnlen(const char *s, const size_t maxlen) {
	if (!s)
		return (0);

	const char	*found = ft_memchr(s, '\0', maxlen);
	return ( found ? (size_t) (found - s) : (maxlen) );
}
