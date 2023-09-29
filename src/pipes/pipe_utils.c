/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 17:20:14 by rimarque          #+#    #+#             */
/*   Updated: 2023/09/22 17:20:14 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//*Esta função percorre a árvore (ast) e encontra o primeiro pipe
t_ast_node	*get_beg(t_ast *ast)
{
	t_ast_node	*aux;

	aux = ast->head;

	ast->counter = 0;
	while(ast->counter++ < ast->size - 1)
		aux = aux->left;
	return(aux);
}

//*Esta função redireciona o stdout para o writing end do pipe (fd[1]) e executa o comando
void	write_to_pipe(int *fd, char **cmd, t_main *main)
{
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	exec_cmd(cmd, main, true);
}

//*Esta função redireciona o stdin para o reading end do pipe anterior (fd[0])
//*Redireciona o stdout para o writing end do pipe seguinte (next_fd[1])
//*Executa o comando
void	pipe_read_and_write(int *fd, int *next_fd, char **cmd, t_main *main)
{
	close(next_fd[0]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	dup2(next_fd[1], STDOUT_FILENO);
	close(next_fd[1]);
	exec_cmd(cmd, main, true);
}

//*Esta função redireciona o stdin para o reading end do pipe (fd[0]) e executa o comando
void	read_from_pipe(int *fd, char **cmd, t_main *main)
{
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	exec_cmd(cmd, main, true);
}
