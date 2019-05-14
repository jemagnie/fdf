/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lstadd_end.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jemagnie <jemagnie@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/03 16:34:47 by jemagnie     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/11 19:32:07 by jemagnie    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_end(t_list **alst, t_list *new)
{
	t_list	*begin;

	if (alst && new)
	{
		if (*alst)
			begin = *alst;
		while (*alst)
		{
			if ((*alst)->next == NULL)
			{
				(*alst)->next = new;
				*alst = begin;
				return ;
			}
			*alst = (*alst)->next;
		}
		*alst = new;
	}
}
