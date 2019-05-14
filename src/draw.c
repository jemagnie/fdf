/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   draw.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jemagnie <jemagnie@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/08 17:36:20 by jemagnie     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/01 18:09:21 by jemagnie    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/fdf.h"

t_cpos	convertpos(t_3dpos src)
{
	t_cpos	dst;

	dst.x = round(src.x);
	dst.y = round(src.y);
	dst.color = src.color;
	return (dst);
}

int		drawer(t_env *fdf)
{
	int		i;
	int		j;
	t_cpos	a;
	t_cpos	b;
	t_cpos	c;

	i = -1;
	while (++i < fdf->i_max && (j = -1))
		while (++j < fdf->j_max)
		{
			a = convertpos(fdf->m_new[i][j]);
			if (j < fdf->j_max - 1)
			{
				b = convertpos(fdf->m_new[i][j + 1]);
				bresenham(fdf, a, b);
			}
			if (i < fdf->i_max - 1)
			{
				c = convertpos(fdf->m_new[i + 1][j]);
				bresenham(fdf, a, c);
			}
		}
	return (1);
}

int		imager(t_env *fdf)
{
	t_img	*img;

	img = fdf->img;
	mlx_destroy_image(fdf->mlx_ptr, fdf->img_ptr);
	maxer(fdf);
	img->x_img = round(fdf->max.x) + 1;
	img->y_img = round(fdf->max.y) + 1;
	img->y_zero = (WIN_Y - img->y_img) / 2;
	img->x_zero = (WIN_X - img->x_img) / 2;
	fdf->img_ptr = mlx_new_image(fdf->mlx_ptr, img->x_img, img->y_img);
	img->ptr = (int *)mlx_get_data_addr(fdf->img_ptr, &img->bpp,
		&img->line, &img->endian);
	drawer(fdf);
	return (1);
}

int		reseter(t_env *fdf)
{
	fdf->s_pos.x = 0;
	fdf->s_pos.y = 0;
	fdf->teta.x = 0;
	fdf->teta.y = 0;
	fdf->teta.z = 0;
	fdf->height = 1;
	fdf->mask = 0;
	sizer(fdf);
	copier(fdf);
	zoomer(fdf);
	imager(fdf);
	return (1);
}

int		changer(t_env *fdf)
{
	if (fdf->mask & CHANGE)
	{
		copier(fdf);
		taller(fdf);
		rotater(fdf);
		zoomer(fdf);
		imager(fdf);
	}
	mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr,
		fdf->img_ptr, fdf->img->x_zero - fdf->s_pos.x,
			fdf->img->y_zero - fdf->s_pos.y);
	return (1);
}
