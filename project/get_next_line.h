/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhasegaw <yhasegaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 16:41:21 by yhasegaw          #+#    #+#             */
/*   Updated: 2020/12/18 20:10:50 by yhasegaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

int		safe_free(char **s1, char **s2, int num);
int		get_next_line(int fd, char **line);
int		check_error(int fd, char **line, char **keeper);
int		ft_strlen(char *s);
char	*ft_strjoin(char *s1, char *s2);
int		check_endl(char *s);

#endif
