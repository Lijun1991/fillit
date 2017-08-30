/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnguyen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 11:51:07 by nnguyen           #+#    #+#             */
/*   Updated: 2016/11/24 11:51:09 by nnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fillit.h"

static int		check_char(char *s)
{
	int i;
	int hash;
	int point;
	int newline;

	i = 0;
	hash = 0;
	point = 0;
	newline = 0;
	while (s[i])
	{
		if (s[i] == '#')
			hash++;
		if (s[i] == '.')
			point++;
		if (s[i] == '\n')
			newline++;
		if (s[i] != '#' && s[i] != '.' && s[i] != '\n')
			return (0);
		i++;
	}
	if (hash % 4 == 0 && (point % 12 == 0 || newline % 4 == 0))
		return (1);
	return (0);
}

static int		check_line(char *s)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == '.' || s[i] == '#')
			j++;
		if (s[i] == '\n')
		{
			if (j % 4 != 0)
				return (0);
		}
		i++;
	}
	return (1);
}

static int		check_connect(char *s)
{
	int con;
	int i;

	con = 0;
	i = 0;
	while (i < 20)
	{
		if (s[i] == '#')
		{
			if ((i + 1) < 20 && s[i + 1] == '#')
				con++;
			if ((i - 1) >= 0 && s[i - 1] == '#')
				con++;
			if ((i + 5) < 20 && s[i + 5] == '#')
				con++;
			if ((i - 5) >= 0 && s[i - 5] == '#')
				con++;
		}
		i++;
	}
	if (con == 6 || con == 8)
		return (1);
	return (0);
}

/*
** open parameter file, Checking to ensure that the file contains valid information 
** (according to specifications in the fillit.en.pdf)  
*/

int				check_file(char *s)
{
	int		fd;
	int		ret;
	int		nb_read;
	char	buf[BUF_SIZE + 1];

	g_count = 0;
	nb_read = 0;
	fd = open(s, O_RDWR);
	while ((ret = read(fd, buf, BUF_SIZE)))
	{
		buf[ret] = '\0';
		if (!(check_char(buf) && check_line(buf) && check_connect(buf)))
			return (0);
		nb_read += ret;
		if (g_count++ >= 26)
			return (0);
	}
	if ((nb_read - 20) % 21)
		return (0);
	return (1);
}
