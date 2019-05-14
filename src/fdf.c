/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fdf.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jemagnie <jemagnie@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/28 18:38:43 by jemagnie     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/01 15:04:29 by jemagnie    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/fdf.h"

int		del(t_env **fdf)
{
	if ((*fdf)->line)
		ft_lstdel((&(*fdf)->line), &ft_del);
	if ((*fdf)->map)
		ft_doubletab_del((void *)(*fdf)->map, (*fdf)->i_max);
	if ((*fdf)->m_new)
		ft_doubletab_del((void *)(*fdf)->m_new, (*fdf)->i_max);
	if ((*fdf)->m_save)
		ft_doubletab_del((void *)(*fdf)->m_save, (*fdf)->i_max);
	if ((*fdf)->img_ptr)
		mlx_destroy_image((*fdf)->mlx_ptr, (*fdf)->img_ptr);
	if ((*fdf)->win_ptr)
		mlx_destroy_window((*fdf)->mlx_ptr, (*fdf)->win_ptr);
	if ((*fdf)->img)
		ft_memdelzero((void **)&(*fdf)->img, sizeof(t_img));
	ft_memdelzero((void **)fdf, sizeof(t_env));
	return (0);
}

int		looper(t_env *fdf)
{
	mlx_hook(fdf->win_ptr, 17, 1L << 17, exit_hook, fdf);
	mlx_hook(fdf->win_ptr, 2, 0, keydown_hook, fdf);
	mlx_hook(fdf->win_ptr, 3, 0, keyup_hook, fdf);
	mlx_hook(fdf->win_ptr, 5, 0, release_hook, fdf);
	mlx_hook(fdf->win_ptr, 4, 0, press_hook, fdf);
	mlx_hook(fdf->win_ptr, 6, 0, motion_hook, fdf);
	mlx_loop_hook(fdf->mlx_ptr, sleeper, fdf);
	mlx_loop(fdf->mlx_ptr);
	return (1);
}

int		init(t_env *fdf)
{
	t_img	*img;

	fdf->mlx_ptr = mlx_init();
	if (!(fdf->img = ft_memalloc(sizeof(t_img))))
		return (del(&fdf));
	img = fdf->img;
	fdf->height = 1;
	sizer(fdf);
	zoomer(fdf);
	maxer(fdf);
	img->x_img = round(fdf->max.x) + 1;
	img->y_img = round(fdf->max.y) + 1;
	img->x_zero = (WIN_X - img->x_img) / 2;
	img->y_zero = (WIN_Y - img->y_img) / 2;
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, WIN_X, WIN_Y, TITLE);
	fdf->img_ptr = mlx_new_image(fdf->mlx_ptr, img->x_img, img->y_img);
	img->ptr = (int *)mlx_get_data_addr(fdf->img_ptr, &img->bpp,
		&img->line, &img->endian);
	drawer(fdf);
	changer(fdf);
	looper(fdf);
	return (1);
}

int		main(int ac, char **av)
{
	t_env	*fdf;
	int		fd;

	if (ac != 2)
		return (ft_error("Usage : ./fdf [map]"));
	if ((fd = open(av[1], O_RDONLY)) < 0)
		return (ft_error("Fail open"));
	if (!(fdf = ft_memalloc(sizeof(t_env))))
		return (ft_error("Fail malloc"));
	if (!reader(fdf, fd))
		return (ft_error("Fail read"));
	if (!parser(fdf->line, fdf))
		return (ft_error("Fail parse"));
	if (!init(fdf))
		return (ft_error("Fail start"));
	return (del(&fdf));
}
