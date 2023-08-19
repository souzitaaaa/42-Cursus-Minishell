/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 18:19:10 by rimarque          #+#    #+#             */
/*   Updated: 2023/08/19 18:30:07 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pipe_read_and_write(int *fd, int *next_fd, char *cmd, char **envp)
{
	int	stdout_copy;

	close(next_fd[0]);
	stdout_copy = dup(1);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	dup2(next_fd[1], STDOUT_FILENO);
	close(next_fd[1]);
	exec_cmd(stdout_copy, cmd, envp);
}

int	mltp_pipes(int	*fd, int argc, char	**argv, char	**envp)
{
	int	pid;
	int	next_fd[2];
	int	index;

	index = get_index(argv[1]);
	while (index <= argc - 3)
	{
		close(fd[1]);
		if (pipe(next_fd) == -1)
			error_management(NULL, 0, errno);
		pid = fork();
		if (pid == -1)
			error_management(NULL, 0, errno);
		if (pid == 0)
			pipe_read_and_write(fd, next_fd, argv[index], envp);
		waitpid(pid, NULL, WNOHANG);
		dup2(next_fd[0], fd[0]);
		dup2(next_fd[1], fd[1]);
		close(next_fd[1]);
		close(next_fd[0]);
		index++;
	}
	return (pid);
}

int	ft_pipex(int argc, char	**argv, char	**envp)
{
	int		pid;
	int		fd[2];
	int		index;

	if (pipe(fd) == -1)
		error_management(NULL, 0, errno);
	pid = first_fork(fd, argc, argv, envp);
	waitpid(pid, NULL, WNOHANG);
	index = get_index(argv[1]);
	if (argc - (index + 1) > 1)
		pid = mltp_pipes(fd, argc, argv, envp);
	waitpid(pid, NULL, WNOHANG);
	pid = last_fork(fd, argc, argv, envp);
	close(fd[0]);
	close(fd[1]);
	return (pid);
}
