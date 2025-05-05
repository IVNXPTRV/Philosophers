/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:48:46 by ipetrov           #+#    #+#             */
/*   Updated: 2025/04/30 12:05:55 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/**
 * @brief Computes the length of the string.
 *
 * This function takes a constant character pointer as input and returns the
 * length of the string. If the input string is NULL, it returns 0.
 *
 * @param str The input string whose length is to be computed.
 * @return The length of the input string, or 0 if the input string is NULL.
 */
size_t	ft_strlen(const char *str)
{
	const char	*mem;

	if (!str)
		return (0);
	mem = str;
	while (*str)
		str++;
	return (str - mem);
}

/**
 * Allocates memory for an array of 'num' elements of 'size' bytes each and
 * initializes all bytes in the allocated storage to zero.
 *
 * @param num Number of elements.
 * @param size Size of each element.
 * @return A pointer to the allocated memory, or NULL if the allocation fails.
 */
void	*ft_calloc(size_t num, size_t size)
{
	size_t			total;
	unsigned char	*result;

	if (num == 0 || size == 0)
	{
		result = (void *)malloc(0);
		if (!result)
			puterr(PRNME"malloc: allocation failed\n");
		return (result);
	}
	if (num > SIZE_MAX / size)
		return (NULL);
	total = num * size;
	result = malloc(total);
	if (!result)
	{
		puterr(PRNME"malloc: allocation failed\n");
		return (NULL);
	}
	while (total--)
		*result++ = 0;
	return ((void *)(result - (num * size)));
}

/**
 * @brief Joins two strings into a new string.
 *
 * This function allocates memory and concatenates the strings s1 and s2.
 * The caller is responsible for freeing the allocated memory.
 * Protects ft_strlener(NULL) from segfault.
 *
 * @param s1 The first string.
 * @param s2 The second string.
 * @return A pointer to the newly allocated string, or NULL if allocation fails.
 */
char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*result;
	char	*mem;

	len = ft_strlen(s1) + ft_strlen(s2);
	result = ft_calloc(len + 1, sizeof(char));
	if (!result)
		return (NULL);
	mem = result;
	while (*s1)
		*result++ = *s1++;
	while (*s2)
		*result++ = *s2++;
	return (mem);
}

/**
 * Copies 'n' bytes from memory area 'src' to memory area 'dest'.
 * The memory areas must not overlap.
 *
 * @param dest The destination memory area.
 * @param src The source memory area.
 * @param n The number of bytes to copy.
 * @return A pointer to 'dest'.
 */
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	if (dest == NULL && src == NULL)
		return (NULL);
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	while (n--)
	{
		*d++ = *s++;
	}
	return (dest);
}

// t_time get_delay()
// {
// 	t_time start;
// 	t_time end;
// 	struct timeval tv;
// 	int i;
// 	int j;

// 	i = 0;
// 	j = 200;

// 	while (i < j)
// 	{
// 		gettimeofday(&tv, NULL);

// 		i++;
// 	}

// 	start = get_time();
// 	// smart_sleep(usec);
// 	usleep(usec);
// 	end = get_time();

// 	return (end - start - usec);
// }