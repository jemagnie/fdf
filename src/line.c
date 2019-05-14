/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   line.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jemagnie <jemagnie@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/01 15:49:02 by jemagnie     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/01 15:49:03 by jemagnie    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/fdf.h"

int		img_pixel_put(t_img *img, int x, int y, int color)
{
	*(img->ptr + (y * (img->x_img) + x)) = color;
	return (1);
}

void	bresenham(t_env *fdf, t_cpos a, t_cpos b)
{
	t_bresenham	l;

	l.dx = (int)fabs((double)(b.x - a.x));
	l.dy = (int)fabs((double)(b.y - a.y));
	l.sx = (a.x < b.x) ? 1 : -1;
	l.sy = (a.y < b.y) ? 1 : -1;
	l.err = ((l.dx > l.dy) ? l.dx : -l.dy) / 2;
	while (1)
	{
		img_pixel_put(fdf->img, a.x, a.y, 0xffffff);
		if (a.x == b.x && a.y == b.y)
			break ;
		l.err2 = l.err;
		if (l.err2 > -l.dx)
		{
			l.err -= l.dy;
			a.x += l.sx;
		}
		if (l.err2 < l.dy)
		{
			l.err += l.dx;
			a.y += l.sy;
		}
	}
}
