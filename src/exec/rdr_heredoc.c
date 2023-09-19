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

extern int	g_ex_status;

int	get_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

void	read_stdin(int fd, char *lim, bool quotes, t_main main)
{
	char	*str;
	char	*buff;
	int		pid;

	str = "\0";
	buff = "\0";

	while (1)
	{
		write(main.fd.stdout, "> ", 2);
		str = get_next_line(STDIN_FILENO, false);
		if(!str)
		{
			ft_putstr_fd("minishell:  warning: here-document at line 1 delimited by end-of-file (wanted `", main.fd.stdout);
			ft_putstr_fd(lim, main.fd.stdout);
			ft_putendl_fd("')", main.fd.stdout);
			break ;
		}
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
}

int	open_hd(char *lim, bool quotes, t_main *main)
{
	int		heredoc_fd[2];
	char	*buff;
	int pid;
	int exit_status;

	if (pipe(heredoc_fd) == -1)
	{
		//!error_management(NULL, 0, errno); //*errno -> number of last error
	}
	signals(2);
	pid = fork();
	if(pid == 0)
	{
		close(heredoc_fd[0]);
		read_stdin(heredoc_fd[1], lim, quotes, *main);
		close(heredoc_fd[1]);
		exit(0);
	}
	signals(-1);
	close(heredoc_fd[1]);
	waitpid(pid, &exit_status, 0);
	return(heredoc_fd[0]);
}

void	rdr_hd(t_token token, t_main *main, int fd)
{
	if(token.arr[1] == NULL)
	{
		dup2(fd, STDIN_FILENO) == -1;
	}
	else
	{
		if(dup2(fd, ft_atoi(token.arr[0])) == -1)
		{
			//!std_err
		}
	}
	close(fd);
}

