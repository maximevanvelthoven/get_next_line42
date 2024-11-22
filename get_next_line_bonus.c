/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-vel <mvan-vel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 15:25:29 by mvan-vel          #+#    #+#             */
/*   Updated: 2024/06/14 17:15:01 by mvan-vel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	ft_free(char **dest)
{
	free(*dest);
	*dest = NULL;
}

static char	*trim_stach(char *stach)
{
	int		i;
	int		size;
	char	*newstach;

	i = 0;
	if (!stach)
		return (NULL);
	size = ft_strlen(stach);
	while (stach[i])
	{
		if (stach[i] == '\n')
		{
			newstach = (ft_substr(stach, i + 1, size - i));
			return (ft_free(&stach), newstach);
		}
		i++;
	}
	ft_free(&stach);
	return (stach);
}

static char	*fill_line(char *dest)
{
	int		i;
	char	*line;

	i = 0;
	if (!dest || dest[0] == '\0')
		return (NULL);
	while (dest[i] != '\n' && dest[i])
		i++;
	if (dest[i] == '\n')
		line = ft_substr(dest, 0, i + 1);
	else
		line = ft_substr(dest, 0, i);
	if (!line || !dest)
		return (NULL);
	if (dest[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	if (line[0] == '\0')
		return (ft_free(&line), NULL);
	return (line);
}

static char	*ft_fill_stach(int fd, char *stach)
{
	char	*buff;
	int		readcount;

	readcount = 1;
	while (ft_strchr(stach, '\n') == NULL)
	{
		if (readcount <= 0)
			break ;
		buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buff)
			return (ft_free(&stach), NULL);
		readcount = read(fd, buff, BUFFER_SIZE);
		buff[readcount] = '\0';
		stach = ft_strjoin(stach, buff);
		ft_free(&buff);
	}
	return (stach);
}

char	*get_next_line(int fd)
{
	static char	*stach[OPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0
		|| BUFFER_SIZE >= INT_MAX || fd >= OPEN_MAX)
		return (ft_free(&stach[fd]), NULL);
	if (!stach[fd])
	{
		stach[fd] = malloc(1);
		if (!stach[fd])
			return (NULL);
		stach[fd][0] = '\0';
	}
	stach[fd] = ft_fill_stach(fd, stach[fd]);
	line = fill_line(stach[fd]);
	stach[fd] = trim_stach(stach[fd]);
	if (!ft_strchr(line, '\n'))
		ft_free(&stach[fd]);
	return (line);
}
