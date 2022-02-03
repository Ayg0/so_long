/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 20:31:20 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/02/02 20:13:28 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>

char	*ft_strjoin(char **s1, char *s2);
int		ft_newlchr(const char *s);
size_t	ft_strlen(const char *s);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(const char *s1);
char	*get_next_line(int fd, int BUFFER_SIZE);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*my_free(char **buff, char **temp, int flag);
#endif
