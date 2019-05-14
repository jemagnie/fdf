/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memdelzero.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jemagnie <jemagnie@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/23 08:04:16 by jemagnie     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/01 15:45:37 by jemagnie    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	ft_memdelzero(void **ap, size_t n)
{
	if (!ap)
		return ;
	ft_bzero(*ap, n);
	free(*ap);
	*ap = NULL;
}
