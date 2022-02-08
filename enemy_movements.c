/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_movements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 08:53:03 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/02/08 08:54:49 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// bads == enemies
void	check_places_of_bads(t_data *gl)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	if (gl->nu.en_num == 0)
		return ;
	gl->bad = (t_e_info *)malloc(sizeof(t_e_info) * gl->nu.en_num);
	while (i < gl->nu.h)
	{
		j = 0;
		while (j < gl->nu.w)
		{
			if (gl->map[i][j] == 'N')
			{
				gl->bad[k].x = i;
				gl->bad[k].y = j;
				gl->bad[k].d = 1;
				k++;
			}
			j++;
		}
		i++;
	}
}

void	condition_of_moves(t_data *gl, int i)
{
	if (ft_strchr("CE1N",
			gl->map[gl->bad[i].x][gl->bad[i].y + gl->bad[i].d], 0, 0) >= 0)
		gl->bad[i].d *= -1;
	else if (gl->map[gl->bad[i].x][gl->bad[i].y + gl->bad[i].d] == 'P'
		&& gl->nu.work == 0)
		gl->nu.work = 2;
	else
	{
		gl->map[gl->bad[i].x][gl->bad[i].y] = '0';
		gl->bad[i].y += gl->bad[i].d;
		gl->map[gl->bad[i].x][gl->bad[i].y] = 'N';
	}	
}

void	enemy_logic(t_data *gl)
{
	int	i;

	i = 0;
	if (gl->nu.en_num == 0)
		return ;
	gl->nu.ene_less++;
	if (gl->nu.ene_less < 20)
		return ;
	else if (gl->nu.ene_less == 20)
		gl->nu.ene_less = 0;
	while (i < gl->nu.en_num)
	{
		condition_of_moves(gl, i);
		i++;
	}
}