/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 18:19:10 by rimarque          #+#    #+#             */
/*   Updated: 2023/10/01 17:50:40 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	check_hd(t_node *head)
{
	t_node	*aux;

	aux = head;
	while (aux != NULL)
	{
		if (aux->token.type == HEREDOC)
			return (true);
		aux = aux->next;
	}
	return (false);
}

//*Abre um processo filho
//*Executa o primeiro comando dentro de um processo filho
//(redirecionando o output para o writing end do pipe (fd[1]))
//*Guarda o id do processo filho, no processo pai
void	first_fork(int *fd, t_leaf *leaf, t_main *main)
{
	int	pid;

	pid = ft_fork(main);
	if (pid == 0)
		write_to_pipe(fd, leaf, main);
	else
	{
		if (leaf->hd.flag)
			close(leaf->hd.fd);
		leaf->pid = pid;
	}
	close(fd[1]);
}

void	fork_btwn_pipes(int *fd, int *next_fd, t_leaf *leaf, t_main *main)
{
	int	pid;

	pid = ft_fork(main);
	if (pid == 0)
		pipe_read_and_write(fd, next_fd, leaf, main);
	else
	{
		if (leaf->hd.flag)
			close(leaf->hd.fd);
		leaf->pid = pid;
	}
	close(fd[0]);
	close(next_fd[1]);
}

//*Executa o último comando dentro de um processo filho
//*Executa o último comando dentro de um processo filho
//(redirecionando o input para o reading end do pipe (fd[0]))
//*Guarda o id do processo filho, no processo pai
//*Fecha os fd do pipe no processo pai
//*Espera pelos processos filhos e guarda o exit status
void	last_fork(int *fd, t_leaf *leaf, t_main *main, t_ast ast)
{
	int	pid;

	pid = ft_fork(main);
	if (pid == 0)
		read_from_pipe(fd, leaf, main);
	else
	{
		if (leaf->hd.flag)
			close(leaf->hd.fd);
		leaf->pid = pid;
	}
	close(fd[0]);
	wait_estatus_p(main, ast);
}

void	mltp_pipes(int	*fd, t_ast *ast, t_ast_node *node, t_main *main)
{
	int	next_fd[2];

	while (node->prev)
	{
		error_fp(pipe(next_fd), errno, main);
		fork_btwn_pipes(fd, next_fd, node->right, main);
		error_fp(pipe(fd), errno, main);
		close(fd[1]);
		dup2(next_fd[0], fd[0]);
		close(next_fd[0]);
		node = node->prev;
	}
	last_fork(fd, node->right, main, *ast);
}

//*Esta função organiza a execução dos pipes
//*Encontra o 1º pipe, abre um pipe
//*Modifica o handle do ctrl C
//*Executa o primeiro comando dentro de um processo filho
//(redirecionando o output para o writing end do pipe (fd[1]))
//*Se houver mais que um pipe, chama a função mltp_pipes
//*Se houver apenas um pipe, executa o segundo e ultimo comando
//* dentro de outro processo filho
//(redirecionando o input para o reading end do pipe (fd[0]))
void	pipex(t_ast *ast, t_main *main)
{
	int			fd[2];
	t_ast_node	*node;

	node = get_beg(ast);
	error_fp(pipe(fd), errno, main);
	signals(1);
	first_fork(fd, node->left, main);
	if (ast->size > 1)
		mltp_pipes(fd, ast, node, main);
	else
		last_fork(fd, node->right, main, *ast);
}
