/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 19:05:06 by iksaiz-m          #+#    #+#             */
/*   Updated: 2024/04/20 17:38:30 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_get_one_line(char *save)
{
	int		i;

	i = 0;
	if (!save)
		return (NULL);
	while (save[i] && save[i] != '\n')
		i++;
	return (ft_substr(save, 0, i + 1));
}

static char	*ft_get_rest_line(char *save)
{
	int		i;
	char	*new_save;

	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (!save[i])
		return (free (save), NULL);
	i++;
	new_save = ft_substr(save, i, ft_strlen(save));
	if (new_save == NULL)
		return (free(save), NULL);
	free(save);
	return (new_save);
}

static char	*get_read_line(int fd, char *save)
{
	int		x;
	char	buffer[BUFFER_SIZE + 1];

	x = 1;
	while (x)
	{
		x = read(fd, buffer, BUFFER_SIZE);
		if (x == 0)
		{
			if (!ft_strlen(save))
				return (free(save), NULL);
			else if (ft_strlen(save))
				return (save);
		}
		if (x == -1)
			return (free(save), NULL);
		buffer[x] = '\0';
		save = gnl_join(save, buffer);
		if (!save)
			return (NULL);
		if (ft_strchr(save, '\n'))
			return (save);
	}
	return (save);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*save[FD_OPEN];

	if (fd < 0 || BUFFER_SIZE <= 0 || FD_OPEN < fd)
	{
		if (save[fd])
			free(save[fd]);
		return (NULL);
	}
	if (!save[fd])
	{
		save[fd] = malloc(sizeof(char));
		if (!save[fd])
			return (NULL);
		save[fd][0] = '\0';
	}
	save[fd] = get_read_line(fd, save[fd]);
	if (save[fd] == NULL)
		return (NULL);
	line = ft_get_one_line(save[fd]);
	save[fd] = ft_get_rest_line(save[fd]);
	return (line);
}
// int main()
// {
//     char *filename;
//     int fd;
// 		int fd2;

//     filename = "multiple_line_with_nl";
//     fd = open(filename, 0, O_RDONLY);
// 	fd2 = open("getnextlineprueba", 0, O_RDONLY);
//     if (fd == -1)
//     {
//         ft_printf("\nError Opening File\n");
//         exit(1);
//     }
// 	if (fd2 == -1)
// 	{
//         ft_printf("\nError Opening File\n");
//         exit(1);
//     }
//     else
//     {
//         ft_printf("\nFile %s opened sucessfully!\n", filename);
//     }
//     ft_printf("LINEA1:%s", get_next_line(fd));
// 	ft_printf("LINEA1:%s", get_next_line(fd2));
//     ft_printf("LINEA2:%s", get_next_line(fd));
// 	ft_printf("LINEA2:%s", get_next_line(fd2));
// 	ft_printf("LINEA3:%s", get_next_line(fd));
// 	ft_printf("LINEA3:%s", get_next_line(fd2));
//     ft_printf("LINEA4:%s", get_next_line(fd));
// 	ft_printf("LINEA4:%s", get_next_line(fd2));
//     ft_printf("LINEA5:%s", get_next_line(fd));
// 	ft_printf("LINEA5:%s", get_next_line(fd2));
//     ft_printf("LINEA6:%s", get_next_line(fd));
// 	ft_printf("LINEA6:%s", get_next_line(fd2));
// 	ft_printf("LINEA7:%s", get_next_line(fd));
// 	ft_printf("LINEA7:%s", get_next_line(fd2));
// 	ft_printf("LINEA8:%s", get_next_line(fd));
// 	ft_printf("LINEA8:%s", get_next_line(fd2));
//     return (0);
// }