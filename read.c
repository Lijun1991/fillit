/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnguyen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 13:55:37 by nnguyen           #+#    #+#             */
/*   Updated: 2016/11/24 13:55:38 by nnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		*hash_xy_array(char *s, int len, int i, int t)
{
	int	x;
	int y;
	int *dst;

	y = 0;
	dst = (int *)malloc(sizeof(int) * 8);
	while (i < len)
	{
		while (y++ < 4)
		{
			x = 0;
			while (x++ < 5)
			{
				if (s[i] == '#')
				{
					dst[++t] = y;
					dst[++t] = x;
				}
				i++;
			}
		}
		i++;
	}
	return (dst);
}

int		**all_hashyx_array(int n, int y, int fd)
{
	int		ret;
	int		**hashyx;
	char	buf[22];

	if (fd == -1)
	{
		ft_putstr("open() error");
		return (NULL);
	}
	hashyx = (int**)malloc(sizeof(int*) * (n + 1));
	while ((ret = read(fd, buf, 21)))
	{
		hashyx[y++] = hash_xy_array(buf, ret, 0, -1);
	}
	if (close(fd) == -1)
	{
		ft_putstr("close() error");
		return (NULL);
	}
	return (hashyx);
}

int		count_tetri(char *file)
{
	int		fd;
	int		ret;
	int		count;
	char	buf[BUF_SIZE + 1];

	count = 0;
	fd = open(file, O_RDWR);
	while ((ret = read(fd, buf, BUF_SIZE)))
		count++;
	return (count);
}

void	adjust_pos(int y, int x, int *yx)
{
	int dy;
	int dx;

	dy = yx[0] - y;
	dx = yx[1] - x;
	yx[0] = yx[0] - dy;
	yx[1] = yx[1] - dx;
	yx[2] = yx[2] - dy;
	yx[3] = yx[3] - dx;
	yx[4] = yx[4] - dy;
	yx[5] = yx[5] - dx;
	yx[6] = yx[6] - dy;
	yx[7] = yx[7] - dx;
}
