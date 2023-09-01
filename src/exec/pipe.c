/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 18:19:10 by rimarque          #+#    #+#             */
/*   Updated: 2023/09/01 15:18:49 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pipe_read_and_write(int *fd, int *next_fd, char **cmd, t_main *main)
{
	close(next_fd[0]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	dup2(next_fd[1], STDOUT_FILENO);
	close(next_fd[1]);
	exec_cmd(cmd, main, true);
}
void	read_from_pipe(int *fd, char **cmd, t_main *main)
{
	dup2(fd[0], STDIN_FILENO); //*redireciona o stdin para o pipe
	close(fd[0]);
	exec_cmd(cmd, main, true);
}

void	write_to_pipe(int *fd, char **cmd, t_main *main)
{
	//printf("cmd: %s\n", cmd[0]);
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO); //*redireciona o stdout para o pipe
	//dup2(main->fd.stdin , STDIN_FILENO); //*redireciona o stdin de volta ao stdin
	close(fd[1]);
	exec_cmd(cmd, main, true);
	//exit(0);
}

void	mltp_pipes(int	*fd, t_ast ast, t_ast_node *node, t_main *main)
{
	int	next_fd[2];
	int pid;
	int exit_status;

	while (node->index < ast.size - 1) //*quando o index é igual ao size - 1, estamos no ultimo pipe a ser executado
	{
		close(fd[1]);
		if (pipe(next_fd) == -1)
		{
			//!error_management(NULL, 0, errno);
		}
		pid = fork();
		//!if (pid == -1)
			//!	error_management(NULL, 0, errno);
		if (pid == 0)
			pipe_read_and_write(fd, next_fd, node->right->token.arr, main);
		waitpid(pid, &exit_status, WNOHANG); //!WNOHANG perceber para que serve esta flag e quando
		if (WEXITSTATUS(exit_status) != 0)
			set_exit_code(main, WEXITSTATUS(exit_status));
		else
			set_exit_code(main, 0);
		dup2(next_fd[0], fd[0]);
		dup2(next_fd[1], fd[1]);
		close(next_fd[1]);
		close(next_fd[0]);
		node = node->prev;
	}
	pid = fork();
	//!if (pid == -1)
		//!	error_management(NULL, 0, errno);
	if (pid == 0)
	{
		read_from_pipe(fd, node->right->token.arr, main);
	}
	waitpid(pid, NULL, 0);
}

void	pipex(t_ast ast, t_ast_node *node, t_main *main)
{
	int	fd[2];
	int	pid;
	int	exit_status;
	//int	next_fd[2];

	//printf("pipex\n");
	//printf("pipex\n");
	if (pipe(fd) == -1)
	{
		//!error_management(NULL, 0, errno); //!
	}
	pid = fork();
	//!if (pid == -1)
		//!	error_management(NULL, 0, errno);
	if (pid == 0)
		write_to_pipe(fd, node->left->token.arr, main);
	waitpid(pid, &exit_status, WNOHANG);
	if (WEXITSTATUS(exit_status) != 0)
		set_exit_code(main, WEXITSTATUS(exit_status));
	else
		set_exit_code(main, 0);
	if(ast.size > 1)
		mltp_pipes(fd, ast, node, main);
	else
	{
		close(fd[1]);
		pid = fork();
		//!if (pid == -1)
			//!	error_management(NULL, 0, errno);
		if (pid == 0)
		{
			read_from_pipe(fd, node->right->token.arr, main);
		}
		waitpid(pid, &exit_status, 0);
		if (WEXITSTATUS(exit_status) != 0)
			set_exit_code(main, WEXITSTATUS(exit_status));
		else
			set_exit_code(main, 0);
	}
	close(fd[0]);
}
t_ast_node	*get_beg(t_ast ast)
{
	t_ast_node	*aux;

	aux = ast.head;

	ast.counter = 0;
	while(ast.counter++ < ast.size - 1)
		aux = aux->left;
	return(aux);
}

void	init_exec_ast(t_ast ast, t_main *main)
{
	t_ast_node	*aux;

	aux = get_beg(ast);
	printf("first_node: %s\n", aux->token.arr[0]);
	pipex(ast, aux, main);
}
