/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhasegaw <yhasegaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 11:15:38 by yhasegaw          #+#    #+#             */
/*   Updated: 2020/12/18 20:11:37 by yhasegaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char		*split_endl(char *str)
{
	int		num;
	char	*temp;

	if (!(temp = (char *)malloc(sizeof(char) * check_endl(str))))
		return (NULL);
	num = 0;
	while (num < check_endl(str) - 1)
	{
		temp[num] = str[num];
		num++;
	}
	temp[num] = '\0';
	return (temp);
}

char		*update_keeper(char *keeper)
{
	char	*ret;
	int		i;

	if (!(ret = (char *)malloc(sizeof(char) *
	(ft_strlen(keeper) - check_endl(keeper) + 1))))
		return (NULL);
	i = 0;
	while (keeper[check_endl(keeper) + i])
	{
		ret[i] = keeper[check_endl(keeper) + i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

int			create_ans(char **keeper, char **line)
{
	char *temp;

	if (!(*line = split_endl(*keeper)))
		return (safe_free(keeper, keeper, -1));
	if (!(temp = update_keeper(*keeper)))
		safe_free(line, keeper, -1);
	safe_free(keeper, keeper, 0);
	*keeper = temp;
	return (1);
}

ssize_t		read_section(int fd, char **keeper, char **line)
{
	char		*temp;
	ssize_t		read_ret;
	char		*buf;

	if (!(buf = (char *)malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1))))
		return (safe_free(line, keeper, -1));
	read_ret = 0;
	while (!(check_endl(*keeper))
	&& (read_ret = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[read_ret] = '\0';
		if (!(temp = ft_strjoin(*keeper, buf)))
		{
			safe_free(line, keeper, 0);
			return (safe_free(&buf, &buf, -1));
		}
		safe_free(keeper, keeper, 0);
		*keeper = temp;
	}
	safe_free(&buf, &buf, 0);
	return (read_ret);
}

int			get_next_line(int fd, char **line)
{
	static char		*keeper[256];
	ssize_t			read_ret;

	if (check_error(fd, line, &keeper[fd]))
		return (-1);
	if (check_endl(keeper[fd]))
		return (create_ans(&keeper[fd], line));
	else
		read_ret = read_section(fd, &keeper[fd], line);
	if (read_ret < 0)
		return (safe_free(line, &keeper[fd], -1));
	if (check_endl(keeper[fd]))
		return (create_ans(&keeper[fd], line));
	*line = keeper[fd];
	keeper[fd] = NULL;
	return (0);
}
