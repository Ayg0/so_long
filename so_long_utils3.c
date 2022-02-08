/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 19:08:52 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/02/07 16:01:18 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*ft_strstr(char *haystack, char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!haystack)
		return (NULL);
	if (*needle == '\0')
		return ((char *)haystack);
	while (haystack[i])
	{
		j = 0;
		while (haystack[i + j] == needle[j] && j + i < len)
		{
			if (needle[j + 1] == '\0')
				return ((char *)(haystack + i));
			j++;
		}
		i++;
	}
	return (0);
}

static int	how_long(int c)
{
	int	i;

	i = 0;
	if (c == 0)
		return (1);
	while (c)
	{
		c /= 10;
		i++;
	}
	return (i);
}

static int	plas_wn(int n)
{
	if (n < 0)
		return (1);
	return (0);
}

char	*ft_itoa(int n)
{
	int				c;
	char			*player;
	int				i;

	c = how_long(n) + plas_wn(n);
	i = 0;
	player = (char *)ft_calloc((size_t)(c + 1), sizeof(char));
	if (player == 0)
		return (0);
	if (plas_wn(n))
	{
		player[i] = '-';
		n *= -1;
	}
	while (n || i == 0)
	{
		player[c - i - 1] = n % 10 + '0';
		n /= 10;
		i++;
	}
	return (player);
}

int	ft_strchr(char *s, int c, int f1, int f2)
{
	int	i;

	i = 0;
	if (f1 || f2)
		s = "1";
	while (s[i])
	{
		if (s[i] == (char )c)
			return (i);
		i++;
	}
	return (-1);
}
