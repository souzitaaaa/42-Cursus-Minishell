/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdr_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 00:14:27 by rimarque          #+#    #+#             */
/*   Updated: 2023/08/31 00:14:27 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*read_stdin(char *lim, bool quotes)
{
	char	*str;
	char	*buff;

	str = "\0";
	buff = "\0";
	while (1)
	{
		ft_printf("> ");
		str = get_next_line(STDIN_FILENO, false);
		//!str = expand_line(str, quotes);
		if (!strncmp(lim, str, strlen(lim)))
		{
			ft_free_str(&str);
			break ;
		}
		buff = ft_strjoinfree(buff, str);
		ft_free_str(&str);
	}
	return (buff);
}

int	open_hd(char *lim, bool quotes, t_main *main)
{
	int		heredoc_fd[2];
	char	*buff;

	if (pipe(heredoc_fd) == -1)
	{
		//!error_management(NULL, 0, errno); //*errno -> number of last error
	}
	buff = read_stdin(lim, quotes);
	write(heredoc_fd[1], buff, strlen(buff));
	close(heredoc_fd[1]);
	if (*buff)
		ft_free_str(&buff);
	return (heredoc_fd[0]);
}

void	rdr_hd(t_token token, t_main *main)
{
	int	fd;

	if(token.arr[1] == NULL)
	{
		fd = open_hd(token.arr[0], token.quotes, main);
		dup2(fd, STDIN_FILENO);
	}
	else
	{
		fd = open_hd(token.arr[1], token.quotes, main);
		if(dup2(fd, ft_atoi(token.arr[0])) == -1)
		{
			//!std_err
		}
	}
	close(fd);
}
