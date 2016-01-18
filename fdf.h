/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubedat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/04 16:05:33 by adubedat          #+#    #+#             */
/*   Updated: 2016/01/18 22:32:23 by adubedat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H

# define FDF_H
# define C_MAX	16777215
# define C_MIN	255
# include "libft/libft.h"
# include "minilibx/mlx.h"

typedef struct	s_coord
{
	double			x;
	double			y;
	double			z;
	int				rgb[3];
}				t_coord;

void			print_image(t_coord **point, int height, int len);
void			solve(char *argv);
void			get_map(int fd, char *line, int len);
void			get_coord(char *str, int len, int height);
void			get_index(void **mlx, t_coord point, t_coord point2);
void			rely_points_tl(void **mlx, t_coord point, t_coord point2);
void			rely_points_dl(void **mlx, t_coord point, t_coord point2);
void			rely_points_tr(void **mlx, t_coord point, t_coord point2);
void			rely_points_dr(void **mlx, t_coord point, t_coord point2);
double			*init_tmp(t_coord point, t_coord point2);
t_coord			get_color(t_coord point, int z);
t_coord			init_color(t_coord point, int r, int g, int b);
double			init_point(double point, int len, int height);
t_coord			**get_coord2(char **split, t_coord **point, int len, int height);

#endif
