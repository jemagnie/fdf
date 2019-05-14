/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jemagnie <jemagnie@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/10 14:24:35 by jemagnie     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/01 15:50:56 by jemagnie    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/fdf.h"

int		create_new(t_env *fdf)
{
	int		i;

	i = -1;
	if (!(fdf->m_new = malloc(sizeof(t_3dpos *) * fdf->i_max)))
		return (del(&fdf));
	while (++i < fdf->i_max)
		if (!(fdf->m_new[i] = malloc(sizeof(t_3dpos) * fdf->j_max)))
			return (del(&fdf));
	return (copier(fdf));
}

int		convert(t_env *fdf)
{
	int		i;
	int		j;

	if (!(fdf->m_save = malloc(sizeof(t_3dpos *) * fdf->i_max)))
		return (del(&fdf));
	i = -1;
	while (++i < fdf->i_max && (j = -1))
	{
		if (!(fdf->m_save[i] = malloc(sizeof(t_3dpos) * fdf->j_max)))
			return (del(&fdf));
		while (++j < fdf->j_max)
		{
			fdf->m_save[i][j].x = (double)fdf->map[i][j].x;
			fdf->m_save[i][j].y = (double)fdf->map[i][j].y;
			fdf->m_save[i][j].z = (double)fdf->map[i][j].z;
			fdf->m_save[i][j].color = fdf->map[i][j].color;
		}
	}
	return (create_new(fdf));
}

int		parser(t_list *lst, t_env *fdf)
{
	int		i;
	int		j;
	char	*tmp;

	if (!lst || !(fdf->map = malloc(sizeof(t_3dpos *) * fdf->i_max)))
		return (del(&fdf));
	i = -1;
	while (++i < fdf->i_max)
	{
		if (!(fdf->map[i] = malloc(sizeof(t_3dpos) * fdf->j_max)))
			return (del(&fdf));
		tmp = (char *)lst->content;
		j = -1;
		while (++j < fdf->j_max)
		{
			fdf->map[i][j].x = j;
			fdf->map[i][j].y = i;
			fdf->map[i][j].z = ft_atoi_ptr(&tmp);
			tmp = *tmp == ',' ? tmp + 1 : tmp;
			fdf->map[i][j].color = *(tmp - 1) == ',' ?
				ft_atoi_more_ptr(&tmp) : 0xFFFFFF;
		}
		lst = lst->next;
	}
	return (convert(fdf));
}

int		checker(char *line, t_env *fdf)
{
	int		n;

	n = 0;
	while (*line)
	{
		if ((*line == '-' || *line == '+') && (ft_isdigit(*(line + 1))))
			line++;
		if (ft_isdigit(*line) && ++n)
		{
			line = ft_strwhile(line, &ft_isdigit);
			if (*line == ',' && *(line + 1) == '0' &&
				(*(line + 2) == 'x' || *(line + 2) == 'X'))
				line = ft_strwhile(line + 3, &ft_ishexa);
		}
		if (*line && !(ft_isblank(*line)))
			return (0);
		line = ft_strwhile(line, &ft_isblank);
	}
	fdf->j_max = (fdf->j_max ? fdf->j_max : n);
	return (n == fdf->j_max && n > 1 ? 1 : 0);
}

int		reader(t_env *fdf, int fd)
{
	int		len;
	char	*line;
	t_list	*tmp;

	while ((len = (int)get_next_len(fd, &line)) > -1)
	{
		if (!checker(line, fdf))
			return (del(&fdf));
		if (!(tmp = ft_lstnew(line, (size_t)len + 1)))
			return (del(&fdf));
		ft_lstadd_end(&(fdf->line), tmp);
		fdf->i_max += 1;
		free(line);
	}
	free(line);
	close(fd);
	return (fdf->i_max > 1 ? 1 : del(&fdf));
}
