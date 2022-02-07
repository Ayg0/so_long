/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 14:58:10 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/02/07 20:07:28 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "get_next_line.h"
# include <mlx.h>

typedef struct s_ig
{
	void	*ig;
	char	*ad;
	int		bp;
	int		l_s;
	int		en;
}	t_xml_ig;
typedef struct s_enemy_info
{
	int	x;
	int	y;
	int	d;
}	t_e_info;

typedef struct s_player_info
{
	int		moves;
	int		x;
	int		y;
	int		r_l;
	int		coins;
}	t_p_info;

typedef struct s_numbers
{
	int	w;
	int	h;
	int	c;
	int	player;
	int	en_num;
	int	frames;
	int	ene_less;
	int	ex;
	int	ps;
	int	work;
}	t_num;

typedef struct s_sprites
{
	t_xml_ig	p1;
	t_xml_ig	p2;
	t_xml_ig	e;
	t_xml_ig	c;
	t_xml_ig	c1;
	t_xml_ig	c2;
	t_xml_ig	c3;
	t_xml_ig	c4;
	t_xml_ig	c5;
	t_xml_ig	win;
	t_xml_ig	b;
	t_xml_ig	e1;
	t_xml_ig	e2;
	t_xml_ig	m;
}	t_sp;

typedef struct all_in_one
{
	void		*mlx;
	void		*window;
	char		**map;
	char		*(*k)(void *ig, int *b, int *sl, int *e);
	void		*(*b)(void *mlx, char *file, int *w, int *h);
	t_p_info	player;
	t_sp		s;
	t_e_info	*bad;
	t_num		nu;
}	t_data;

void	render_it(t_data *game_info, int flag);
int		add_life(int keycode, t_data *game_info);
void	init_data(t_data *game_info);
void	init_elements(t_data *game_info);
int		close_window(void);
int		load_map(char *name, t_data *game_info);
int		final_check(t_data *game_info);
int		check_map(char *name, t_data *game_info);
void	*the_one(t_data *game_info, char c, int i, int j);
void	render_map(t_data *game_info);
char	*ft_strstr(char *haystack, char *needle, size_t len);
char	*ft_itoa(int n);
int		ft_strchr(char *s, int c, int f1, int f2);
void	arr_swap(char *s);
void	ft_sleep(unsigned int time);
void	coin_changes(t_data	*gl);
void	render_mods(t_data	*gl);
void	check_places_of_bads(t_data *gl);
int		close_window(void);
#endif