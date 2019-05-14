/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_doubletab_del.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jemagnie <jemagnie@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/23 01:55:47 by jemagnie     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/01 15:47:07 by jemagnie    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	ft_doubletab_del(void **map, size_t n)
{
	int		i;

	i = -1;
	if (map)
	{
		while (++i < (int)n)
			if (map[i])
				free(map[i]);
		free(map);
	}
}
