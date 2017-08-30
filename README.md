# fillit
A bin-packing program to fit between 1  and 26 tetromino pieces into the smallest possible square. A tetromino is a shape created from four square cells as is found in the game Tetris:

![alt text](https://github.com/robertnowell/fillit/blob/master/tetriminos.png "Tetromino")

This program takes a file as parameter which contains a list of Tetriminos and arranges them to create the smallest square possible. The main goal is to find this smallest square in the minimal amount of time, despite a exponentially growing number of possibilities each time a piece is added. The most significant challenge of the implementation was being careful about data structures and our solving algorithm in order to solve the packing problem efficiently.

See fillit.en.pdf for additional project information.

## Implementation

This project was implemented in C through an iterative backtracking algorithm. Allowed functions: malloc, write, and free.

## Detail and Code Examples

Our implementation start with validating file first, then store Tetrimino data to two-dimensional array, calculate smallest reasonable current map size (this is the square filled with tetromino pieces) base on tetromino total pieces. The following is the main function for our program:

```
int	main(int argc, char **argv)
{
	int tetri_total;
	int **yxarray;
	int fd;

	if (argc == 2)
	{
		if (!(check_file(argv[1])) || g_count == 0)
		{
			ft_putstr("error\n");
			return (0);
		}
		tetri_total = count_tetri(argv[1]);
		fd = open(argv[1], O_RDWR);
		yxarray = all_hashyx_array(tetri_total, 0, fd);
		smallest_square_map(0, tetri_total, yxarray, 0);
		free(yxarray);
	}
	else
		ft_putstr("usage: ./fillit filename\n");
	return (0);
}
```

### Retrieving and Formatting Tetrimino Data

Our implementation start with validating the file. Checking to ensure that the file contains valid information (according to specifications in the fillit.en.pdf), we all check_file() from the main function:

```
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
```

Then open the file and read in data about our tetromino pieces. We store the data read from file into two dimensional (int \*\*\*) array. We call all_hashyx_array() from the main function:

```
int		**all_hashyx_array(int tetri_total, int y, int fd)
{
	int		ret;
	int		**hashyx;
	char	buf[22];

	if (fd == -1)
	{
		ft_putstr("open() error");
		return (NULL);
	}
	hashyx = (int**)malloc(sizeof(int*) * (tetri_total + 1));
	while ((ret = read(fd, buf, BUF_SIZE)))
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
```
all_hashyx_array() is our central function for:  
1. Accessing data stored in the file given to the program as a parameter
2. Filling our two-dimensional array with formatted data about the tetrominos contained in the file. Each element of the two-dimensional array is a tetrimino, four arrays of four characters (essentially a 2-d matrix) with "." for empty spaces and "#" for tetrimino spaces.


### The Solving Algorithm

Again in the main function, we will call smallest_square_map() to initialize a two dimensional array of map_size elements (to start, calculate smallest reasonable current map size (this is the square filled with tetromino pieces) base on tetromino total pieces.), then keep enlarging until big enough.

```
void	smallest_square_map(int length, int tetri_total, int **hashyx, int y)
{
	char	**map;
	int		x;

	if (length == 0)
		length = min_len(tetri_total);
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
	if (!solve(map, 0, hashyx, tetri_total))
	{
		free(map);
		smallest_square_map(++length, tetri_total, hashyx, 0);
	}
	else
		print_map(map, length);
}
```

Core backtracking algorithm solve() returns zero if there is no possible way to fit the tetrominos in the current map size. In this case, we increase the map size, recreate the map, and again call the solver function:

```
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
```

Within our solver() function, we reset our map x and y variables, then proceed to our attempt to fit all tetrominos within the current square map. We do this one tetromino at a time. The process is as follows:  
  
1.  Check if our current tetromino will fit starting from our current position in the map (i.e. map[x_point][y_point]).
2.  If the piece will fit:
    1. Edit the map to reflect this positioning of the tetromino (put the piece on the map)
    2. If that was the final tetromino, return 1 to indicate success.
    3. If that was not the final tetromino, find the next open spot on the map and return to the start of the loop to try to fit.
3. If the piece will not fit:
    1. Check if there is another open space on the map. If not, a bigger map is needed, so return 0.
    2. If there is another open space, then that means there is more space on the map but our piece won't fit, so we need to backtrack. Delete the most recent tetromino, and return to the start of the map to try to place it in the next available location.  
  
  
This algorithm will run until either:

1.  All pieces are successfully placed in the current map. In this case solver() returns 1 and the successfully filled-in map is printed.  
2.  No more backtracking is possible (the program is attempting to place the first tetromino), and there are no more additional open spaces on the current map (the program is attempting to place the tetromino in the final possible map location, i.e. the bottom right position of the map). In this case solver() returns 0, a bigger map is created, and solver() tries again on the bigger map.  
  
  
The program continues until a map is found that will contain all of the tetrominos. This is quite quick for collections of less than ten pieces (less than one one hundredth of a second), and has been tested for collections of tetrominos as high as twenty pieces, and twenty pieces takes a good amount of time.  

## Authors

* **Lijun Wang** (https://github.com/robertnowell)
* **Ngan Kim Nguyen**
## Acknowledgments

* This project was completed at School 42, Fremont
