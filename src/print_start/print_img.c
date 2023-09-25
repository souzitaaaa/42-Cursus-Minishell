/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_img.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joe <joe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 11:12:39 by joe               #+#    #+#             */
/*   Updated: 2023/09/22 12:02:23 by joe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_intro(void)
{
	int		fd;
	char	buff[1];

	fd = open("src/print_start/intro.txt", O_RDONLY);
	if (fd == -1)
		return ;
	while (read(fd, buff, 1))
	{
		if (buff[0] == '1')
			printf(RGB_PINK_2 "█" COL_RESET);
		else if (buff[0] == '2')
			printf(PURPLE "█" COL_RESET);
		else if (buff[0] == '3')
			printf(RGB_PINK "█" COL_RESET);
		else if (buff[0] == '4')
			printf(RGB_PURPLE_2 "█" COL_RESET);
		else if (buff[0] == 'y')
			printf(LYELLOWB " " COLOUR_RESET);
		else if (buff[0] == 'r')
			printf(REDB " " COLOUR_RESET);
		else
			printf("%c", buff[0]);
	}
	close(fd);
	return ;
}