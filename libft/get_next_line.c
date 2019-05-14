/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jemagnie <jemagnie@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/25 21:16:40 by jemagnie     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/17 19:23:05 by jemagnie    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static int		ft_memchr_int(const char *mem, const unsigned char c, size_t n)
{
	unsigned long	mask;
	unsigned long	*l;
	unsigned char	*s;
	int				a;
	int				b;

	a = 0;
	s = (unsigned char *)mem;
	while (((n - a) % 8) && (n - a))
		if (s[a++] == c)
			return (--a);
	mask = ft_mask((int)c);
	l = (unsigned long *)(s + a);
	while (a < (int)n)
	{
		if ((((*l++ ^ mask) - MASK_0X01L) & MASK_0X80L) && (b = -1))
		{
			s = (unsigned char *)(l - 1);
			while (++b < 8)
				if (s[b] == c)
					return (a + b);
		}
		a += 8;
	}
	return (a);
}

static char		*ft_strjoin_free(char *s1, char *s2, int lens2)
{
	char	*str;
	int		lens1;

	if (!s1 || !s2)
		return (NULL);
	lens1 = ft_strlen(s1);
	if (!(str = ft_strnew(lens1 + lens2)))
		return (NULL);
	ft_memcpy(str, s1, lens1);
	ft_memcpy(str + lens1, s2, lens2);
	free(s1);
	return (str);
}

int				get_next_line(const int fd, char **line)
{
	static t_gnl gnl;

	if (fd < 0 || !line || !(*line = ft_strnew(0)))
		return (-1);
	while ("z4 > z*")
	{
		if ((gnl.ret) <= 0 && !(gnl.start = 0) &&
				((gnl.ret = read(fd, gnl.buff, BUFF_SIZE)) < 0))
			return (-1);
		if (!(gnl.ret))
			return (**line ? 1 : 0);
		gnl.len = ft_memchr_int(&((gnl.buff)[gnl.start]), '\n', gnl.ret);
		*line = ft_strjoin_free(*line, &((gnl.buff)[gnl.start]), gnl.len);
		if ((gnl.ret -= gnl.len) &&
				((gnl.buff[gnl.start += gnl.len] == '\n') || !gnl.len))
		{
			gnl.ret--;
			gnl.start++;
			return (1);
		}
	}
}
