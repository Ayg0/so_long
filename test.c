#include <mlx.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "get_next_line.h"

typedef struct s_vect
{
	int	x;
	int	y;
	int i;
	int	b;
	int	a;
}	t_vect;

typedef struct s_data
{
	void	*img;
	char	*add;
	int		b_per_p;
	int		line_lenght;
	int		endian;
}	t_data;
typedef struct s_vars
{
	void	*mlx;
	void	*window;
	t_vect	*bam;
	t_data	image;
	char	**k;
	int		h;
	int		w;
}	t_vars;

int	ft_strcmp(char *q1, char *q2)
{
	size_t			i;

	i = 0;
	while (q1[i] == q2[i] && q1[i] && q2[i])
		i++;
	return (q1[i] - q2[i]);
}
char	*check_for_me(int i, int j, t_vars *vars, int flag)
{
	if(vars->k[i][j] == '1')
		return ("b.xpm");
	else if(vars->k[i][j] == '0')
		return ("b.xpm");
	else if(vars->k[i][j] == 'P' && flag == 1)
	{
		vars->bam->i = j;
		vars->bam->b = i;
		return ("p.xpm");
	}
	else if(vars->k[i][j] == 'E')
		return ("b.xpm");
	else if(vars->k[i][j] == 'C')
		return ("coin.xpm");
	else
		return (NULL);
}

char	*draw(t_vars *vars, int flag)
{
	int		i;
	int		j;
	char	*m;

	i = 0;
	while(i < vars->w)
	{
		j = 0;
		while(j < vars->h)
		{
			m = check_for_me(i, j, vars, flag);
			if(!m)
				return (NULL);
			if(!(flag == 1 && ft_strcmp(m, "player")))
			{
				vars->image.img = mlx_new_image(vars->mlx, 32, 32);
				vars->image.img = mlx_xpm_file_to_image(vars->mlx, m, &vars->bam->x, &vars->bam->y);			
				vars->image.add = mlx_get_data_addr(vars->image.img,&vars->image.b_per_p, &vars->image.line_lenght, &vars->image.endian);
				mlx_put_image_to_window(vars->mlx, vars->window, vars->image.img, vars->bam->x * j, vars->bam->y * i);
			}
			j++;
		}
		i++;
	}
	return ("OKAY");
}

int	number_of_moves(int keycode, t_vars *vars)
{
	if (keycode == 13)
		vars->bam->b -= 1;
	else if (keycode == 2)
		vars->bam->i += 1;
	else if (keycode == 1)
		vars->bam->b += 1;
	else if (keycode == 0)
		vars->bam->i -= 1;
	vars->bam->a++;
	vars->image.img = mlx_new_image(vars->mlx, 32, 32);
	vars->image.img = mlx_xpm_file_to_image(vars->mlx, "p.xpm", &vars->bam->x, &vars->bam->y);
	vars->image.add = mlx_get_data_addr(vars->image.img,&vars->image.b_per_p, &vars->image.line_lenght, &vars->image.endian);
	mlx_clear_window(vars->mlx, vars->window);
	draw(vars, 0);
	mlx_put_image_to_window(vars->mlx, vars->window, vars->image.img, vars->bam->x * vars->bam->i, vars->bam->y * vars->bam->b);
	return(printf("%d\n", vars->bam->a));
}

void	map_size(char *name, t_vars *wow)
{
	int	fd;

	fd = open(name, O_RDWR);
	wow->h = ft_strlen(get_next_line(fd, 1)) - 1;
	wow->w += 1;
	while(get_next_line(fd, 1))
		wow->w += 1;
	close(fd);
}

void fill_it(char *name, t_vars *wow)
{
	int	fd;
	int	a;
	int	b;

	fd = open(name, O_RDWR);
	a = 0;
	wow->k = (char **)ft_calloc(wow->w , sizeof(char *));
	while (a < wow->w)
	{
		wow->k[a] = get_next_line(fd, 1);
		a++;
	}
	close(fd);
}

int	main(int ac, char **av)
{
	t_vars	wow;
	void	*window;
	char	*b;

	wow.bam = (t_vect *)malloc(sizeof(t_vect) * 1);
	if (!wow.bam)
		return (0);
	wow.bam->x = 32;
	wow.bam->y = 32;
	wow.bam->i = 0;
	wow.bam->b = 0;
	wow.bam->a = 0;
	wow.mlx = mlx_init();
	map_size("map.ber", &wow);
	fill_it("map.ber", &wow);
	wow.window = mlx_new_window(wow.mlx, wow.h * 32, wow.w * 32, "new ");
	b = draw(&wow, 1);
	if (!b)
		return(write(1, "error", 5));
	mlx_key_hook(wow.window, number_of_moves, &wow);
	mlx_loop(wow.mlx);
	free(wow.bam);
}
//gcc -Imlx -lmlx -framework OpenGl -framework Appkit *.c -D BUFFER_SIZE=1 -fsanitize=address -g && ./a.out "map.ber"