/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   mouse.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jemagnie <jemagnie@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/01 15:49:55 by jemagnie     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/01 17:48:39 by jemagnie    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/fdf.h"

int		press_hook(int button, int x, int y, t_env *fdf)
{
	fdf->m_pos.x = x;
	fdf->m_pos.y = y;
	if (button == SCROLLUP_KEY)
	{
		fdf->zoom -= 1;
		fdf->mask |= CHANGE;
		changer(fdf);
	}
	if (button == SCROLLDOWN_KEY)
	{
		fdf->zoom += 1;
		fdf->mask |= CHANGE;
		changer(fdf);
	}
	fdf->mask |= (1 << button);
	return (0);
}

int		release_hook(int button, int x, int y, t_env *fdf)
{
	t_pos a;

	a.x = x;
	a.y = y;
	(void)button;
	if (fdf->mask & SLEEP)
		fdf->mask = SLEEP;
	else
		fdf->mask = 0;
	return (0);
}

int		motion_hook(int x, int y, t_env *fdf)
{
	if (fdf->mask & RIGHT)
	{
		fdf->mask |= CHANGE;
		fdf->teta.x += (y - fdf->m_pos.y);
		fdf->teta.z += (x - fdf->m_pos.x);
		changer(fdf);
	}
	if (fdf->mask & LEFT)
	{
		fdf->s_pos.x += fdf->m_pos.x - x;
		fdf->s_pos.y += fdf->m_pos.y - y;
		changer(fdf);
	}
	if (fdf->mask & SCROLL)
	{
		fdf->mask |= CHANGE;
		fdf->teta.x += (y - fdf->m_pos.y);
		fdf->teta.y += (x - fdf->m_pos.x);
		changer(fdf);
	}
	fdf->m_pos.x = x;
	fdf->m_pos.y = y;
	return (0);
}
