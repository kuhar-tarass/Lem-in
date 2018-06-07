/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuhar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 20:17:17 by tkuhar            #+#    #+#             */
/*   Updated: 2018/05/16 16:54:01 by tkuhar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

static t_ls		*fnd(t_ls **ls, int fd)
{
	t_ls	*new;
	t_ls	*tmp;

	tmp = *ls;
	while (tmp)
	{
		if (tmp->fd == fd)
			return (tmp);
		if (tmp->next == 0)
			break ;
		tmp = tmp->next;
	}
	new = malloc(sizeof(t_ls));
	if (*ls != 0)
		(tmp)->next = new;
	else
		*ls = new;
	new->fd = fd;
	new->dt = 0;
	new->next = 0;
	return (new);
}

static void		rewrite(char **dest, char *s0, char *s2)
{
	char		*tmp;

	tmp = ft_strjoin(s0, s2);
	if (!*tmp)
	{
		free(tmp);
		tmp = 0;
	}
	if (*dest)
		free(*dest);
	*dest = tmp;
}

static int		ret(char **f, char **line, char **buf)
{
	free(*buf);
	if (*f)
	{
		*line = ft_strdup(*f);
		free(*f);
		*f = 0;
		return (1);
	}
	return (0);
}

int				get_next_line(const int fd, char **line)
{
	static t_ls	*ls = 0;
	t_ls		*f;
	char		*buf;

	if (fd < 0 || !line || read(fd, 0, 0) < 0)
		return (-1);
	f = fnd(&ls, fd);
	buf = malloc(sizeof(char) * (BUFF_SIZE + 1));
	while (1)
	{
		if (f->dt && ft_strchr(f->dt, '\n'))
		{
			*line = ft_strsub(f->dt, 0, ft_strchr(f->dt, '\n') - f->dt);
			rewrite(&f->dt, 0, ft_strchr(f->dt, '\n') + 1);
			free(buf);
			return (1);
		}
		ft_memset(buf, 0, BUFF_SIZE + 1);
		read(fd, buf, BUFF_SIZE);
		if (!(*buf))
			return (ret(&f->dt, line, &buf));
		rewrite(&f->dt, f->dt, buf);
	}
}
