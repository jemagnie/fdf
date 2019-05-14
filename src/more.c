/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   more.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jemagnie <jemagnie@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/29 17:34:08 by jemagnie     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/01 15:51:51 by jemagnie    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/fdf.h"

t_angle	gon_to_rad(t_angle teta)
{
	t_angle		alpha;

	alpha.x = teta.x * M_PI / GON_2;
	alpha.y = teta.y * M_PI / GON_2;
	alpha.z = teta.z * M_PI / GON_2;
	return (alpha);
}

int		copier(t_env *fdf)
{
	int		i;
	int		j;

	i = -1;
	while (++i < fdf->i_max)
	{
		j = -1;
		while (++j < fdf->j_max)
			fdf->m_new[i][j] = fdf->m_save[i][j];
	}
	return (1);
}

int		finder(t_env *fdf)
{
	int		i;
	int		j;

	i = -1;
	fdf->min.x = fdf->m_new[0][0].x;
	fdf->min.y = fdf->m_new[0][0].y;
	fdf->max.x = fdf->m_new[0][0].x;
	fdf->max.y = fdf->m_new[0][0].y;
	while (++i < fdf->i_max)
	{
		j = -1;
		while (++j < fdf->j_max)
		{
			if (fdf->m_new[i][j].x < fdf->min.x)
				fdf->min.x = fdf->m_new[i][j].x;
			if (fdf->m_new[i][j].y < fdf->min.y)
				fdf->min.y = fdf->m_new[i][j].y;
			if (fdf->m_new[i][j].x > fdf->max.x)
				fdf->max.x = fdf->m_new[i][j].x;
			if (fdf->m_new[i][j].y > fdf->max.y)
				fdf->max.y = fdf->m_new[i][j].y;
		}
	}
	return (1);
}

int		miner(t_env *fdf)
{
	int		i;
	int		j;

	i = -1;
	fdf->min.x = fdf->m_new[0][0].x;
	fdf->min.y = fdf->m_new[0][0].y;
	while (++i < fdf->i_max)
	{
		j = -1;
		while (++j < fdf->j_max)
		{
			if (fdf->m_new[i][j].x < fdf->min.x)
				fdf->min.x = fdf->m_new[i][j].x;
			if (fdf->m_new[i][j].y < fdf->min.y)
				fdf->min.y = fdf->m_new[i][j].y;
		}
	}
	return (1);
}

int		maxer(t_env *fdf)
{
	int		i;
	int		j;

	i = -1;
	fdf->max.x = fdf->m_new[0][0].x;
	fdf->max.y = fdf->m_new[0][0].y;
	while (++i < fdf->i_max)
	{
		j = -1;
		while (++j < fdf->j_max)
		{
			if (fdf->m_new[i][j].x > fdf->max.x)
				fdf->max.x = fdf->m_new[i][j].x;
			if (fdf->m_new[i][j].y > fdf->max.y)
				fdf->max.y = fdf->m_new[i][j].y;
		}
	}
	return (1);
}
