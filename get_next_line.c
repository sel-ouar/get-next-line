/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-ouar <sel-ouar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 15:45:27 by sel-ouar          #+#    #+#             */
/*   Updated: 2022/12/19 21:32:47 by sel-ouar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int check_error(int fd)
{
    // char    c;
    
    if (fd < 0 || fd > OPEN_MAX)
        return (1);
    if (BUFFER_SIZE <= 0)
        return (1);
    // if (read(fd, &c, 0) < 0)
    //     return (1);
    return (0);
}
char    *readline(int fd, char *save)
{
    ssize_t ret;
    char    *buffer;
    char    *temp;
    
    ret = 0;
    buffer = malloc ((BUFFER_SIZE + 1) * sizeof(char));
    if (!buffer)
        return (NULL);
    if (!save)
        save = ft_strdup("");
    while (ft_strchr(save, '\n') == NULL)
    {
        if ((ret = read(fd, buffer, BUFFER_SIZE)) < 0)
        {
            free(buffer);
            free(save);
            save = NULL;
            return (NULL);
        }
        if (ret == 0 || buffer[0] == '\0')
            break;
        buffer[ret] = '\0';
        temp = save;
        save = ft_strjoin(save, buffer);
        free (temp);
    }
    free (buffer);
    return (save);
}
char    *get_next_line(int fd)
{
    static char *save;
    char        *line;
    char        *temp;
    size_t      len;
    
    if (check_error(fd))
        return (NULL);
    save = readline(fd, save);
    if (!save)
        return (NULL);
    if (!(ft_strchr(save, '\n')))
    {
        if (save[0] == '\0')
        {
            free(save);
            save = NULL;
            return (NULL);
        }
        if (!(line = ft_strdup(save)))
            return (NULL);
        free (save);
        save = NULL;
        return (line);
    }
    else
    {
        len = ft_strlen(save) - ft_strlen(ft_strchr(save, '\n') + 1);
        temp = save;
        line = ft_substr(save, 0, len);
        save = ft_strdup(save + len);
        free(temp);
        temp = NULL;
        return (line);                                                                                                                                
    }
    return (NULL);
}
