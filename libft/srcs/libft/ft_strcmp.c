#include <stdint.h>

/**
 * @brief Lexicographically compare two strings.
 *
 * Walks `s1` and `s2` until the first differing character or the
 * null terminator.
 *
 * @param s1 First string to compare.
 * @param s2 Second string to compare.
 * @return Difference between the first differing characters
 *         (negative, zero, or positive).
 */
int	ft_strcmp(const char *s1, const char *s2) {
	while (*s1 != '\0' && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
