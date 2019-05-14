/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fdf.h                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jemagnie <jemagnie@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/05/15 21:05:48 by jemagnie     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/01 17:53:46 by jemagnie    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../minilibx_macos/mlx.h"
# include "../libft/libft.h"
# include <limits.h>
# include <math.h>

# define TITLE "FDF - jemagnie"

# define WIN_X 2560
# define WIN_Y 1395

# define LEFT		(1 << 1)
# define RIGHT 		(1 << 2)
# define SCROLL		(1 << 3)
# define SLEEP		(1 << 4)
# define CHANGE		(1 << 5)

# define GON		400
# define GON_2		200

/*
**	struct fdf
*/

typedef struct		s_cpos
{
	int				x;
	int				y;
	int				color;
}					t_cpos;

typedef struct		s_fpos
{
	double			x;
	double			y;
}					t_fpos;

typedef struct		s_bresenham
{
	int				dx;
	int				dy;
	int				sx;
	int				sy;
	int				err;
	int				err2;
}					t_bresenham;

typedef struct		s_3dpos
{
	double			x;
	double			y;
	double			z;
	int				color;
}					t_3dpos;

typedef struct		s_angle
{
	double			x;
	double			y;
	double			z;
}					t_angle;

typedef struct		s_map
{
	int				x;
	int				y;
	int				z;
	int				color;
}					t_map;

typedef	struct		s_img
{
	int				*ptr;
	int				endian;
	int				bpp;
	int				line;
	int				x_img;
	int				y_img;
	int				x_zero;
	int				y_zero;
}					t_img;

typedef struct		s_env
{
	t_list			*line;
	t_map			**map;
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	t_img			*img;
	t_3dpos			**m_save;
	t_3dpos			**m_new;
	t_angle			teta;
	t_fpos			min;
	t_fpos			max;
	double			zoom;
	double			height;
	int				i_max;
	int				j_max;
	int				mask;
	t_pos			m_pos;
	t_pos			s_pos;
}					t_env;

/*
** event functions
*/

int					keyup_hook(int button, t_env *param);
int					exit_hook(t_env *fdf);
int					press_hook(int button, int x, int y, t_env *param);
int					release_hook(int button, int x, int y, t_env *param);
int					motion_hook(int x, int y, t_env *param);
int					keydown_hook(int button, t_env *param);
int					sleeper(t_env *fdf);

/*
** main functions
*/

int					reader(t_env *fdf, int fd);
int					parser(t_list *lst, t_env *fdf);
int					checker(char *line, t_env *fdf);
int					convert(t_env *fdf);
int					creater(t_env *fdf);

/*
** tools functions
*/

int					sizer(t_env *fdf);
int					miner(t_env *fdf);
int					maxer(t_env *fdf);
int					finder(t_env *fdf);
int					copier(t_env *fdf);

/*
**	graphic functions
*/

int					reseter(t_env *fdf);
int					changer(t_env *fdf);
int					drawer(t_env *fdf);
int					img_pixel_put(t_img *img, int x, int y, int color);
void				bresenham(t_env *fdf, t_cpos a, t_cpos b);
int					rotater(t_env *fdf);
int					zoomer(t_env *fdf);
int					replacer(t_env *fdf);
int					taller(t_env *fdf);

/*
** init & del functions
*/

int					looper(t_env *fdf);
int					del(t_env **fdf);
int					init(t_env *fdf);

/*
** math functions
*/

t_angle				gon_to_rad(t_angle teta);

#endif
