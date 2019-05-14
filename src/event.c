/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   event.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jemagnie <jemagnie@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/09 17:37:40 by jemagnie     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/01 18:09:54 by jemagnie    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/fdf.h"

int		exit_hook(t_env *fdf)
{
	del(&fdf);
	exit(1);
}

int		sleeper(t_env *fdf)
{
	if (fdf->mask & SLEEP)
	{
		fdf->mask |= CHANGE;
		fdf->teta.x += 2;
		fdf->teta.y += 2;
		fdf->teta.z += 2;
		changer(fdf);
	}
	return (1);
}

int		keydown_hook(int button, t_env *fdf)
{
	if (button == ESC_KEY)
		exit_hook(fdf);
	if (button == NKPL_KEY)
	{
		fdf->height += 0.05;
		fdf->mask |= CHANGE;
	}
	if (button == NKMN_KEY)
	{
		fdf->height -= 0.05;
		fdf->mask |= CHANGE;
	}
	if (button == SP_KEY)
		fdf->mask ^= SLEEP;
	if (button == R_KEY)
		reseter(fdf);
	changer(fdf);
	return (0);
}

int		keyup_hook(int button, t_env *fdf)
{
	(void)button;
	(void)fdf;
	return (0);
}
