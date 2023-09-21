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

#include "../../../includes/minishell.h"

extern int	g_ex_status;

int	get_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int	read_stdin(int fd, char *lim, bool quotes, t_main *main)
{
	char	*str;
	char	*buff;
	int		pid;
	int		hd_line;

	str = "\0";
	buff = "\0";

	hd_line = 0;
	while (1)
	{
		write(main->fd.stdout, "> ", 2);
		str = get_next_line(STDIN_FILENO, false);
		if(!str)
		{
			error_msg_hd(lim,  main->fd.stdout, main->line);
			break ;
		}
		hd_line++;
		if(!quotes)
		{
			//!str = expand_line(str, quotes);
		}
		if (!ft_strncmp(lim, str, get_max(ft_strlen(lim), ft_strclen(str, '\n'))))
		{
			ft_free_str(&str);
			break ;
		}
		write(fd, str, strlen(str));
		ft_free_str(&str);
	}
	return(hd_line);
}

int	open_hd(char *lim, bool quotes, t_main *main)
{
	int		heredoc_fd[2];
	char	*buff;
	int pid;
	int exit_status;
	int	hd_line;

	pipe(heredoc_fd);
	signals(2);
	pid = fork();
	if(pid == 0)
	{
		close(heredoc_fd[0]);
		hd_line = read_stdin(heredoc_fd[1], lim, quotes, main);
		close(heredoc_fd[1]);
		exit(hd_line);
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

