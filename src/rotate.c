/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   rotate.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jemagnie <jemagnie@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/08 17:45:07 by jemagnie     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/01 15:57:19 by jemagnie    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/fdf.h"

int		replacer(t_env *fdf)
{
	int		i;
	int		j;

	i = -1;
	miner(fdf);
	while (++i < fdf->i_max)
	{
		j = -1;
		while (++j < fdf->j_max)
		{
			fdf->m_new[i][j].x -= fdf->min.x;
			fdf->m_new[i][j].y -= fdf->min.y;
		}
	}
	return (1);
}

void	rotate_x(t_3dpos *pos, double y, double z, double teta)
{
	pos->y = y * cosf(teta) + z * sinf(teta);
	pos->z = y * -sinf(teta) + z * cosf(teta);
}

void	rotate_y(t_3dpos *pos, double x, double z, double teta)
{
	pos->x = z * sinf(teta) + x * cosf(teta);
	pos->z = z * cosf(teta) - x * sinf(teta);
}

void	rotate_z(t_3dpos *pos, double x, double y, double teta)
{
	pos->x = x * cosf(teta) + y * sinf(teta);
	pos->y = -x * sinf(teta) + y * cosf(teta);
}

int		rotater(t_env *fdf)
{
	int		i;
	int		j;
	t_3dpos	*pos;
	t_angle	rad;

	rad = gon_to_rad(fdf->teta);
	i = -1;
	while (++i < fdf->i_max)
	{
		j = -1;
		while (++j < fdf->j_max)
		{
			pos = &(fdf->m_new[i][j]);
			rotate_x(pos, pos->y, pos->z, rad.x);
			rotate_y(pos, pos->x, pos->z, rad.y);
			rotate_z(pos, pos->x, pos->y, rad.z);
		}
	}
	return (miner(fdf) && replacer(fdf));
}
