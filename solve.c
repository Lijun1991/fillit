/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnguyen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 14:02:37 by nnguyen           #+#    #+#             */
/*   Updated: 2016/11/24 14:02:38 by nnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		min_len(int n)
{
	int i;

	i = 0;
	while ((i * i) < (n * 4))
		i++;
	return (i);
}

int		map_size(char **map)
{
	int i;

	i = 0;
	while (map[i] != 0)
		i++;
	return (i);
}

void	print_map(char **map, int len)
{
	int y;
	int x;

	y = 0;
	while (y < len)
	{
		x = 0;
		while (x < len)
		{
			ft_putchar(map[y][x]);
			x++;
		}
		ft_putchar('\n');
		y++;
	}
}

int		solve(char **map, int i, int **hashyx, int n)
{
	int		len;
	t_point *point;

	point = (t_point*)malloc(sizeof(t_point) * 1);
	point->x = -1;
	point->y = 0;
	len = map_size(map);
	if (i == n)
		return (1);
	while (check_fitput(map, hashyx[i], i, point))
	{
		if (solve(map, ++i, hashyx, n))
			return (1);
		else
			remove_tetri(map, --i, point);
	}
	return (0);
}

void	smallest_square_map(int length, int n, int **hashyx, int y)
{
	char	**map;
	int		x;

	if (length == 0)
		length = min_len(n);
	map = (char **)malloc(sizeof(char *) * (length + 1));
	while (y < length)
	{
		map[y] = (char *)malloc(sizeof(char) * (length + 1));
		x = 0;
		while (x < length)
		{
			map[y][x++] = '.';
		}
		y++;
	}
	map[y] = 0;
	if (!solve(map, 0, hashyx, n))
	{
		free(map);
		smallest_square_map(++length, n, hashyx, 0);
	}
	else
		print_map(map, length);
}
