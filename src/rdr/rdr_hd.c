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

t_main	*return_main(t_main	*main)
{
	static t_main *static_main;

	if (main)
		static_main = main;
	return (static_main);
}

int	get_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int	read_stdin_aux(char *str, char *lim, t_main *main, int *line)
{
	if(!str)
	{
		error_msg_hd(lim,  main->fd.stdout, main->line);
		return(-1);
	}
	(*line)++;
	if (!ft_strncmp(lim, str, get_max(ft_strlen(lim), ft_strclen(str, '\n'))))
	{
		ft_free_str(&str);
		return(-1);
	}
	return(0);
}

int	read_stdin(int fd, char *lim, bool quotes, t_main *main)
{
	int		line;
	char	*str;

	str = "\0";
	line = 0;
	while (1)
	{
		str = readline("> ");
		if (read_stdin_aux(str, lim, main, &line) == -1)
			break ;
		if(!quotes)
			str = check_expansion_str(main, str, true);
		if(str == NULL)
		{
			write(fd, "\n", 1);
			continue ;
		}
		else
			write(fd, str, ft_strlen(str));
		if(*str)
			ft_free_str(&str);
	}
	return(line);
}

int	open_hd(char *lim, bool quotes, t_main *main)
{
	int		heredoc_fd[2];
	int		pid;
	int		hd_line;

	error_fp(pipe(heredoc_fd), errno, main);
	signals(2);
	pid = fork();
	error_fp(pid, errno, main);
	return_main(main);
	if(pid == 0)
	{
		close(heredoc_fd[0]);
		hd_line = read_stdin(heredoc_fd[1], lim, quotes, main);
		close(heredoc_fd[1]);
		exit_child(main, hd_line, true);
	}
	signals(-1);
	close(heredoc_fd[1]);
	wait_set_line(pid, main);
	return(heredoc_fd[0]);
}

void	rdr_hd(t_token token, t_main *main, int fd)
{
	if(token.arr[1] == NULL)
		dup2(fd, STDIN_FILENO);
	else
	{
		if(dup2(fd, ft_atoi(token.arr[0])) == -1)
				rdr_error(token.arr[0], main, 1);
	}
	close(fd);
}

