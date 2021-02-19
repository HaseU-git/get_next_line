/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhasegaw <yhasegaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:39:44 by yhasegaw          #+#    #+#             */
/*   Updated: 2020/12/18 20:14:02 by yhasegaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int		check_error(int fd, char **line, char **keeper)
{
	if ((read(fd, *keeper, 0) < 0) || line == NULL || BUFFER_SIZE <= 0)
		return (-1);
	if (*keeper == NULL)
	{
		if (!(*keeper = (char *)malloc(1 * sizeof(char))))
			return (-1);
		*keeper[0] = '\0';
	}
	return (0);
}

int		ft_strlen(char *s)
{
	int i;

	if (s == NULL)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		len1;
	int		len2;
	char	*ret;
	int		i;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (!(ret = (char *)malloc(sizeof(char) * (len1 + len2 + 1))))
		return (NULL);
	i = 0;
	while (i < len1)
		ret[i++] = *s1++;
	while (i < len1 + len2)
		ret[i++] = *s2++;
	ret[i] = '\0';
	return (ret);
}

int		check_endl(char *s)
{
	int num;

	num = 0;
	while (s[num] != '\0')
	{
		if (s[num] == '\n')
			return (num + 1);
		num++;
	}
	return (0);
}

int		safe_free(char **s1, char **s2, int ret)
{
	if (*s1)
	{
		free(*s1);
		*s1 = NULL;
	}
	if (*s2)
	{
		free(*s2);
		*s2 = NULL;
	}
	return (ret);
}
