/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnguyen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 13:57:56 by nnguyen           #+#    #+#             */
/*   Updated: 2016/11/24 13:57:57 by nnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

t_point	*get_point(char **map, int i)
{
	int		x;
	int		y;
	t_point *point;

	point = (t_point*)malloc(sizeof(t_point) * 1);
	y = 0;
	while (y < map_size(map))
	{
		x = 0;
		while (x < map_size(map))
		{
			if (map[y][x] == 'A' + i)
			{
				point->y = y;
				point->x = x;
				return (point);
			}
			x++;
		}
		y++;
	}
	return (NULL);
}

int		norm_check(int *yx, int len, char **map, int i)
{
	if (yx[0] < len && yx[1] < len && yx[2] < len && yx[3] < len && \
		yx[4] < len && yx[5] < len && yx[6] < len && yx[7] < len && \
		yx[0] >= 0 && yx[1] >= 0 && yx[2] >= 0 && yx[3] >= 0 && \
		yx[4] >= 0 && yx[5] >= 0 && yx[6] >= 0 && yx[7] >= 0 && \
		map[yx[0]][yx[1]] == '.' && map[yx[2]][yx[3]] == '.' && \
		map[yx[4]][yx[5]] == '.' && map[yx[6]][yx[7]] == '.')
	{
		map[yx[0]][yx[1]] = 'A' + i;
		map[yx[2]][yx[3]] = 'A' + i;
		map[yx[4]][yx[5]] = 'A' + i;
		map[yx[6]][yx[7]] = 'A' + i;
		return (1);
	}
	return (0);
}

int		check_fitput(char **map, int *yx, int i, t_point *point)
{
	int len;

	len = map_size(map);
	while (!(point->x == map_size(map) - 1 && point->y == map_size(map) - 1))
	{
		if (point->x < map_size(map) - 1)
			point->x++;
		else if (point->x == map_size(map) - 1 && point->y < map_size(map) - 1)
		{
			point->y++;
			point->x = 0;
		}
		else
			return (0);
		adjust_pos(point->y, point->x, yx);
		if (norm_check(yx, len, map, i))
			return (1);
	}
	return (0);
}

void	remove_tetri(char **map, int i, t_point *point)
{
	int y;
	int x;

	point = get_point(map, i);
	y = 0;
	while (y < map_size(map))
	{
		x = 0;
		while (x < map_size(map))
		{
			if (map[y][x] == 'A' + i)
			{
				map[y][x] = '.';
			}
			x++;
		}
		y++;
	}
}
