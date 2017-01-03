/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnguyen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/27 19:39:28 by nnguyen           #+#    #+#             */
/*   Updated: 2016/10/30 14:18:56 by nnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include "./libft/libft.h"
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# define BUF_SIZE 21

int				g_count;

typedef struct	s_point
{
	int x;
	int y;
}				t_point;

int				check_file(char *s);
int				*hash_xy_array(char *s, int len, int i, int t);
int				**all_hashyx_array(int n, int y, int fd);
int				count_tetri(char *file);
void			adjust_pos(int y, int x, int *yx);
t_point			*get_point(char **map, int i);
int				norm_check(int *yx, int len, char **map, int i);
int				check_fitput(char **map, int *yx, int i, t_point *point);
void			remove_tetri(char **map, int i, t_point *point);
int				min_len(int n);
int				map_size(char **map);
void			print_map(char **map, int len);
int				solve(char **map, int i, int **hashyx, int n);
void			smallest_square_map(int length, int n, int **hashyx, int y);

#endif
