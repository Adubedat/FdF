/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubedat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 17:45:45 by adubedat          #+#    #+#             */
/*   Updated: 2016/01/18 22:29:00 by adubedat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	solve(char *argv)
{
	int		fd;
	char	*line;
	int		i;
	int		len;
	
	i = 0;
	len = 0;
	if ((fd = open(argv, O_RDONLY)) == -1)
	{
		ft_printf("Open() failed.\n");
		exit(1);
	}
	get_next_line(fd, &line);
//	if (check_error(line, len) == 1)
//	{
//		ft_printf("Input error.\n");
//		exit(1);
//	}
	while (line[i])
	{
		if (line[i] == ' ')
			len++;
		i++;
	}
	get_map(fd, line, len + 1);
}

void	get_map(int fd, char *line, int len)
{
	char	*str;
	int		height;

	height = 1;
	str = ft_strnew(0);
	str = ft_strjoin_free_s1(str, line);
	str = ft_strjoin_free_s1(str, " ");
	while (get_next_line(fd, &line) == 1)
	{
//		if (check_error(line, len) == 1)
//		{
//			ft_printf("Input error.\n");
//			exit(1);
//		}
		height++;
		str = ft_strjoin_free_s1(str, line);
		str = ft_strjoin_free_s1(str, " ");
	}
	get_coord(str, len, height);
}

void	get_coord(char *str, int len, int height)
{
	t_coord	**point;
	int		i;
	char	**split;

	i = 0;
	point = (t_coord**)malloc(sizeof(t_coord*) * height);
	split = ft_strsplit(str, ' ');
	while (i < height)
	{
		point[i] = (t_coord*)malloc(sizeof(t_coord) * len);
		point[i][0].z = ft_atoi(split[i * len]);
		if (i == 0)
			point[i][0].x = init_point(point[i][0].x, len, height);
		else
			point[i][0].x = point[0][0].x - (i * ((point[0][0].x - 50) / height)) / 2;
		if (height > len)
			point[i][0].y = (i * ((point[0][0].x - 50) / height)) + 50;
		else
			point[i][0].y = (i * ((point[0][0].x - 50) / len)) + 50;
		point[i][0] = get_color(point[i][0], point[i][0].z);
		i++;
	}
	point = get_coord2(split, point, len, height);
	free(split);
	print_image(point, height, len);
}

t_coord		**get_coord2(char **split, t_coord **point, int len, int height)
{
	int	i;
	int	j;
	double	mult;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < len)
		{
			if (j != 0)
			{
				point[i][j].z = ft_atoi(split[i * len + j]);
				point[i][j].x = point[i][0].x + j * ((1200 - point[0][0].x) / len);
				point[i][j].y = point[i][0].y + (j * ((1200 - point[0][0].x) / len) - point[i][j].z
						* (100 / (double)len)) / 2;
				point[i][j] = get_color(point[i][j], point[i][j].z);
			}
			j++;
		}
		i++;
	}
	return (point);
}

t_coord		get_color(t_coord point, int z)
{
	if (z < -10000)
		point = init_color(point, 0, 10, 57);
	else if (z >= -10000 && z <= -500)
		point = init_color(point, 0, 16, 94);
	else if (z > -500 && z <= -100)
		point = init_color(point, 4, 26, 141);
	else if (z > -100 && z <= -50)
		point = init_color(point, 31, 61, 206);
	else if (z > -50 && z < 0)
		point = init_color(point, 59, 79, 213);
	else if (z >= 0 && z <= 30)
		point = init_color(point, 83, 203, 83);
	else if (z > 30 && z <= 60)
		point = init_color(point, 22, 141, 22);
	else if (z > 60 && z <= 100)
		point = init_color(point, 244, 164, 96);
	else if (z > 100 && z <= 200)
		point = init_color(point, 139, 69, 19);
	else if (z > 200 && z <= 10000)
		point = init_color(point, 255, 255, 255);
	else if (z > 10000)
		point = init_color(point, 135, 206, 235);
	return (point);
}

t_coord		init_color(t_coord point, int r, int g, int b)
{
	point.rgb[0] = r;
	point.rgb[1] = g;
	point.rgb[2] = b;
	return (point);
}

double		init_point(double point, int len, int height)
{
	int	ratio;

	ratio = len / height;
	if (ratio >= 1)
		point = 600 / (double)ratio;
	else
	{
		ratio = height / len;
		point = 1200 - 600 / (double)ratio;
	}
	return (point);
}
