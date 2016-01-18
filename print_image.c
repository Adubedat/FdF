/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_image.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubedat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 17:00:31 by adubedat          #+#    #+#             */
/*   Updated: 2016/01/18 22:32:20 by adubedat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

void	print_image(t_coord **point, int height, int len)
{
	void	*mlx[2];
	int		i;
	int		j;

	i = 0;
	mlx[0] = mlx_init();
	mlx[1] = mlx_new_window(mlx[0], 1400, 1000, "FDF");
	while (i < height)
	{
		j = 0;
		while (j < len)
		{
			if (i > 0)
				get_index(mlx, point[i][j], point[i - 1][j]);
			if (j > 0)
				get_index(mlx, point[i][j], point[i][j - 1]);
			j++;
		}
		i++;
	}
	mlx_loop(mlx[0]);
}

void	get_index(void **mlx, t_coord point, t_coord point2)
{
	if (point.x > point2.x && point.y > point2.y)
		rely_points_tl(mlx, point, point2);
	else if (point.x > point2.x && point.y < point2.y)
		rely_points_dl(mlx, point, point2);
	else if (point.x < point2.x && point.y > point2.y)
		rely_points_tr(mlx, point, point2);
	else if (point.x < point2.x && point.y < point2.y)
		rely_points_dr(mlx, point, point2);
	else if (point.x > point2.x && point.y == point2.y)
		rely_points_tl(mlx, point, point2);
	else if (point.x < point2.x && point.y == point2.y)
		rely_points_dr(mlx, point, point2);
	else if (point.x == point2.x && point.y > point2.y)
		rely_points_tr(mlx, point, point2);
	else if (point.x == point2.x && point.y < point2.y)
		rely_points_dl(mlx, point, point2);

}

void	rely_points_tl(void **mlx, t_coord p, t_coord p2)
{
	double	index;
	double	indey;

	index = p.x / p2.x;
	indey = (p.y - p2.y) / ((p.x - p2.x) / index);
	while (index >= 1 || indey >= 1)
	{
		index /= 2;
		indey /= 2;
	}
	while (p.x > p2.x)
	{
		mlx_pixel_put(mlx[0], mlx[1], (int)p.x, (int)p.y, p.rgb[0] * 65536 + p.rgb[1] * 256 + p.rgb[2] - 1);
		p.x -= index;
		if (p.y > p2.y)
			p.y -= indey;
	}
}

void	rely_points_tr(void **mlx, t_coord p, t_coord p2)
{
	double	index;
	double	indey;

	indey = p.y / p2.y;
	index = (p2.x - p.x) / ((p.y - p2.y) / indey);
	while (index >= 1 || indey >= 1)
	{
		index /= 2;
		indey /= 2;
	}
	while (p.y > p2.y)
	{
		mlx_pixel_put(mlx[0], mlx[1], (int)p.x, (int)p.y, p.rgb[0] * 65536 + p.rgb[1] * 256 + p.rgb[2] - 1);
		if (p.x < p2.x)
			p.x += index;
		p.y -= indey;
	}
}

void	rely_points_dl(void **mlx, t_coord p, t_coord p2)
{
	double	index;
	double	indey;

	indey = p2.y / p.y;
	index = (p.x - p2.x) / ((p2.y - p.y) / indey);
	while (index >= 1 || indey >= 1)
	{
		index /= 2;
		indey /= 2;
	}
	while (p.y < p2.y)
	{
		mlx_pixel_put(mlx[0], mlx[1], (int)p.x, (int)p.y, p.rgb[0] * 65536 + p.rgb[1] * 256 + p.rgb[2] - 1);
		if (p.x > p2.x)
			p.x -= index;
		p.y += indey;
	}
}

void	rely_points_dr(void **mlx, t_coord p, t_coord p2)
{
	double	index;
	double	indey;

	index = p2.x / p.x;
	indey = (p2.y - p.y) / ((p2.x - p.x) / index);
	while (index >= 1 || indey >= 1)
	{
		index /= 2;
		indey /= 2;
	}
	while (p.x < p2.x)
	{
		mlx_pixel_put(mlx[0], mlx[1], (int)p.x, (int)p.y, p.rgb[0] * 65536 + p.rgb[1] * 256 + p.rgb[2] - 1);
		p.x += index;
		if (p.y < p2.y)
			p.y += indey;
	}
}
