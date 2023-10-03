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
	while(aux->left_n)
		aux = aux->left_n;
	return(aux);
}

//*Esta função redireciona o stdout para o writing end do pipe (fd[1]) e executa o comando
void	write_to_pipe(int *fd, t_leaf *cmd, t_main *main)
{
	close(fd[0]);
	if(cmd->left)
		ft_redirect_in(cmd->left, main, cmd->hd);
	if(cmd->right)
		ft_redirect_out(cmd->right, main);
	else
		dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	if (cmd->token.type == STRING && !main->flags.rdr_err)
		exec_cmd(cmd->token.arr, main, true);
	else
		exit(0);
}

//*Esta função redireciona o stdin para o reading end do pipe anterior (fd[0])
//*Redireciona o stdout para o writing end do pipe seguinte (next_fd[1])
//*Executa o comando
void	pipe_read_and_write(int *fd, int *next_fd, t_leaf *cmd, t_main *main)
{
	close(next_fd[0]);
	if(cmd->left)
		ft_redirect_in(cmd->left, main, cmd->hd);
	else
		dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	if(cmd->right)
		ft_redirect_out(cmd->right, main);
	else
		dup2(next_fd[1], STDOUT_FILENO);
	close(next_fd[1]);
	if (cmd->token.type == STRING && !main->flags.rdr_err)
		exec_cmd(cmd->token.arr, main, true);
	else
		exit(0);
}

//*Esta função redireciona o stdin para o reading end do pipe (fd[0]) e executa o comando
void	read_from_pipe(int *fd, t_leaf *cmd, t_main *main)
{
	if(cmd->left)
		ft_redirect_in(cmd->left, main, cmd->hd);
	else
		dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	if(cmd->right)
		ft_redirect_out(cmd->right, main);
	if (cmd->token.type == STRING && !main->flags.rdr_err)
		exec_cmd(cmd->token.arr, main, true);
	else
		exit(0);
}
