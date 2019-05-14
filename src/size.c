/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   size.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jemagnie <jemagnie@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/30 15:18:00 by jemagnie     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/01 17:54:13 by jemagnie    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/fdf.h"

int		sizer(t_env *fdf)
{
	double	zoom;
	int		x;
	int		y;

	x = fdf->j_max - 1;
	y = fdf->i_max - 1;
	zoom = 1.0;
	while (1)
	{
		if (zoom * x > WIN_X / 2 || zoom * y > WIN_Y)
			break ;
		zoom += 1;
	}
	fdf->zoom = zoom;
	return (1);
}

int		taller(t_env *fdf)
{
	int		i;
	int		j;

	i = -1;
	while (++i < fdf->i_max)
	{
		j = -1;
		while (++j < fdf->j_max)
			fdf->m_new[i][j].z *= fdf->height;
	}
	return (1);
}

int		zoomer(t_env *fdf)
{
	int		i;
	int		j;

	i = -1;
	if (fdf->zoom < 0.5)
		fdf->zoom = 0.5;
	while (++i < fdf->i_max)
	{
		j = -1;
		while (++j < fdf->j_max)
		{
			fdf->m_new[i][j].x *= fdf->zoom;
			fdf->m_new[i][j].y *= fdf->zoom;
			fdf->m_new[i][j].z *= fdf->zoom;
		}
	}
	return (1);
}
