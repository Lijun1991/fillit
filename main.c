/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnguyen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 14:03:34 by nnguyen           #+#    #+#             */
/*   Updated: 2016/11/24 14:03:35 by nnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int	main(int argc, char **argv)
{
	int n;
	int **yxarray;
	int fd;

	if (argc == 2)
	{
		if (!(check_file(argv[1])) || g_count == 0)
		{
			ft_putstr("error\n");
			return (0);
		}
		n = count_tetri(argv[1]);
		fd = open(argv[1], O_RDWR);
		yxarray = all_hashyx_array(n, 0, fd);
		smallest_square_map(0, n, yxarray, 0);
		free(yxarray);
	}
	else
		ft_putstr("usage: ./fillit filename\n");
	return (0);
}
