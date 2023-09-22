/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 18:19:10 by rimarque          #+#    #+#             */
/*   Updated: 2023/09/22 17:36:19 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_ast_node	*get_beg(t_ast *ast)
{
	t_ast_node	*aux;

	aux = ast->head;

	ast->counter = 0;
	while(ast->counter++ < ast->size - 1)
		aux = aux->left;
	return(aux);
}

void	wait_estatus_p(t_main *main, t_ast ast)
{
	int exit_status;
	t_ast_node *node;
	bool first_time;
	int counter;

	first_time = true;
	node = get_beg(&ast);
	counter = 0;
	while(counter < ast.size)
	{
		if(first_time)
		{
			waitpid(node->left->pid, &exit_status, 0);
			first_time = false;
		}
		else
		{
			waitpid(node->right->pid, &exit_status, 0);
			counter++;
			node = node->prev;
		}
	}
	if (WEXITSTATUS(exit_status) != 0)
	{
		set_exit_code(main, WEXITSTATUS(exit_status));
	}
	else
		set_exit_code(main, 0);
}

void	pipe_read_and_write(int *fd, int *next_fd, char **cmd, t_main *main)
{
	close(fd[1]);
	close(next_fd[0]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	dup2(next_fd[1], STDOUT_FILENO);
	close(next_fd[1]);
	exec_cmd(cmd, main, true);
}

void	read_from_pipe(int *fd, char **cmd, t_main *main)
{
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO); //*redireciona o stdin para o pipe
	close(fd[0]);
	exec_cmd(cmd, main, true);
}

void	write_to_pipe(int *fd, char **cmd, t_main *main)
{
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO); //*redireciona o stdout para o pipe
	close(fd[1]);
	exec_cmd(cmd, main, true);
}

void	mltp_pipes(int	*fd, t_ast *ast, t_ast_node *node, t_main *main)
{
	int	next_fd[2];
	int pid;

	while (node->index < ast->size - 1) //*quando o index é igual ao size - 1, estamos no ultimo pipe a ser executado
	{
		error_fp(pipe(next_fd) , errno, main);
		pid = fork();
		error_fp(pid, errno, main);
		if (pid == 0)
		{
			node->right->pid = getpid();
			pipe_read_and_write(fd, next_fd, node->right->token.arr, main);
		}
		else
			node->right->pid = pid;
		close(fd[0]);
		close(fd[1]);
		error_fp(pipe(fd), errno, main);
		dup2(next_fd[0], fd[0]);
		dup2(next_fd[1], fd[1]);
		close(next_fd[0]);
		close(next_fd[1]);
		node = node->prev;
	}
	pid = fork();
	error_fp(pid, errno, main);
	if (pid == 0)
		read_from_pipe(fd, node->right->token.arr, main);
	else
		node->right->pid = pid;
	close(fd[0]);
	close(fd[1]);
	wait_estatus_p(main, *ast);
}

void	pipex(t_ast *ast, t_main *main)
{
	int	fd[2];
	int	pid;
	t_ast_node	*node;

	signals(1);
	node = get_beg(ast);
	error_fp(pipe(fd), errno, main);
	pid = fork();
	error_fp(pid, errno, main);
	if (pid == 0)
	{
		write_to_pipe(fd, node->left->token.arr, main);
	}
	else
	{
		node->left->pid = pid;
	}
	if(ast->size > 1)
	{
		mltp_pipes(fd, ast, node, main);
	}
	else
	{
		pid = fork();
		error_fp(pid, errno, main);
		if (pid == 0)
		{
			read_from_pipe(fd, node->right->token.arr, main);
		}
		else
		{
			node->right->pid = pid;
		}
		close(fd[0]);
		close(fd[1]);
		wait_estatus_p(main, *ast);
	}
}
