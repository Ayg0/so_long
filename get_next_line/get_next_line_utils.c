/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 20:30:46 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/02/05 13:33:05 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*b;
	int		i;

	i = count * size;
	b = malloc(i);
	if (b == 0)
		return (0);
	while (i)
		((char *)b)[--i] = 0;
	return (b);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*player;
	size_t	i;
	size_t	c;

	i = 0;
	if (!s)
		return (NULL);
	c = ft_strlen(s + start);
	if (len > c)
		len = c;
	player = (char *)ft_calloc((len + 1), sizeof(char));
	if (!player)
		return (NULL);
	while (*(s + start) && len)
	{
		player[i] = *(s + start);
		i++;
		s++;
		len--;
	}
	return (player);
}

char	*ft_strdup(const char *s1)
{
	size_t		i;
	char		*bo;

	if (!s1)
		return (ft_strdup(""));
	i = ft_strlen(s1);
	bo = (char *)ft_calloc(i + 1, sizeof(char));
	if (bo == 0)
		return (0);
	i = 0;
	while (s1[i])
	{
		bo[i] = s1[i];
		i++;
	}
	return (bo);
}

char	*ft_strjoin(char **s1, char *s2)
{
	char		*s3;
	size_t		i;
	size_t		j;

	if (!(*s1))
		return (ft_strdup(s2));
	i = 0;
	j = 0;
	s3 = (char *)ft_calloc(ft_strlen(*s1) + ft_strlen(s2) + 1, sizeof(char));
	if (!s3)
		return (NULL);
	while (s1[0][i])
		s3[j++] = s1[0][i++];
	i = 0;
	my_free(s1, NULL, 0);
	while (s2[i])
		s3[j++] = s2[i++];
	return (s3);
}

int	ft_newlchr(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}
