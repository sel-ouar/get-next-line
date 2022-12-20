/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_get_next_line_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-ouar <sel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 13:20:22 by sel-ouar          #+#    #+#             */
/*   Updated: 2022/12/20 13:36:23 by sel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_free(char *save)
{
	free(save);
	return (NULL);
}

char	*ft_line(char **save)
{
	char	*line;

	if (!save[0][0])
	{
		*save = ft_free(*save);
		return (NULL);
	}
	line = ft_strdup(*save);
	if (!line)
		return (NULL);
	*save = ft_free(*save);
	return (line);
}

int	check_error(int fd)
{
	if (fd < 0 || fd > OPEN_MAX)
		return (1);
	if (BUFFER_SIZE <= 0)
		return (1);
	return (0);
}

char	*readline(int fd, char *save)
{
	ssize_t	ret;
	char	*buffer;
	char	*temp;

	ret = 0;
	buffer = malloc ((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	if (!save)
		save = ft_strdup("");
	while (ft_strchr(save, '\n') == NULL)
	{
		ret = read(fd, buffer, BUFFER_SIZE);
		if (ret < 0)
			return (ft_free(save), free(buffer), NULL);
		if (ret == 0 || buffer[0] == '\0')
			break ;
		buffer[ret] = '\0';
		temp = save;
		save = ft_strjoin(save, buffer);
		free (temp);
	}
	return (free(buffer), save);
}

char	*get_next_line(int fd)
{
	static char	*save[OPEN_MAX];
	char		*line;
	char		*temp;
	size_t		len;

	if (check_error(fd))
		return (NULL);
	save[fd] = readline(fd, save[fd]);
	if (!save[fd])
		return (NULL);
	if (!(ft_strchr(save[fd], '\n')))
	{
		line = ft_line(&save[fd]);
		return (line);
	}
		len = ft_strlen(save[fd]) - ft_strlen(ft_strchr(save[fd], '\n') + 1);
		temp = save[fd];
		line = ft_substr(save[fd], 0, len);
		save[fd] = ft_strdup(save[fd] + len);
		temp = ft_free(temp);
	return (line);
	return (NULL);
}
