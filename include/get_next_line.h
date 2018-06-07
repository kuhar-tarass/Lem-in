/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuhar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 20:17:44 by tkuhar            #+#    #+#             */
/*   Updated: 2018/04/19 14:40:38 by tkuhar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H
# define BUFF_SIZE 1000
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct		s_ls
{
	struct s_ls		*next;
	char			*dt;
	int				fd;
}					t_ls;
int					get_next_line(const int fd, char **line);

#endif
