/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 00:46:15 by rimarque          #+#    #+#             */
/*   Updated: 2023/08/19 00:46:15 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/structs.h"

void	error_msg_cmd(char	*str, int fd)
{
	ft_putstr_fd(str, fd);
	ft_putstr_fd(": ", fd);
	ft_putendl_fd(CMD_ERROR, fd);
}

void	error_msg_file(char *str, int fd)
{
	ft_putstr_fd("minishell: ", fd);
	ft_putstr_fd(str, fd);
	ft_putstr_fd(": ", fd);
	ft_putendl_fd(FILE_ERROR, fd);
}

void	error_msg_fd(char *str, int fd)
{
	ft_putstr_fd("minishell: ", fd);
	ft_putstr_fd(str, fd);
	ft_putstr_fd(": ", fd);
	ft_putendl_fd(FD_ERROR, fd);
}

void	error_msg_hd(char *str, int fd, int line)
{
	ft_putstr_fd("minishell: warning: ", fd);
	ft_putstr_fd("here-document at line ", fd);
	ft_putnbr_fd(line, fd);
	ft_putstr_fd(" delimited by end-of-file", fd);
	ft_putstr_fd(" (wanted `", fd);
	ft_putstr_fd(str, fd);
	ft_putendl_fd("')", fd);
}

void	error_cd(int fd, char *str)
{
	ft_putstr_fd("minishell: ", fd);
	ft_putstr_fd("cd: ", fd);
	ft_putstr_fd(str, fd);
	ft_putendl_fd(" not set", fd);
}

void	error_export(int fd)
{
	ft_putstr_fd("minishell: ", fd);
	ft_putendl_fd("bad assignment", fd);
}

void	error_env(int fd)
{
	ft_putstr_fd("minishell: ", fd);
	ft_putendl_fd("env: No such file or directory", fd);
}

void	error_with_arg(int fd, char *str)
{
	ft_putstr_fd("env: ", fd);
	ft_putstr_fd(str, fd);
	ft_putendl_fd(": No such file or directory", fd);
}

//void	error_quotes(int fd)
void	error_syntax(char *token)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(SYNTAX_ERROR, STDERR_FILENO);
	ft_putstr_fd(token, STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
}

