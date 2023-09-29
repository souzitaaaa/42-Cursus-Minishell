/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 12:05:20 by rimarque          #+#    #+#             */
/*   Updated: 2023/08/28 12:05:20 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//*Esta função espera pelo processo identificado pelo pid (process id) e seta o exit status
void	wait_estatus(int pid, t_main *main)
{
	int	exit_status;

	waitpid(pid, &exit_status, 0);
	if (WEXITSTATUS(exit_status) != 0)
		set_exit_code(main, WEXITSTATUS(exit_status));
	else
		set_exit_code(main, 0);
}

void	wait_set_line(int pid, t_main *main)
{
	int	exit_status;

	waitpid(pid, &exit_status, 0);
	if (WEXITSTATUS(exit_status) != 0)
		main->line += WEXITSTATUS(exit_status);
}

//*Esta função faz o handle do erro das funções fork e pipe
//*Se o resultado for -1, imprime o erro respetivo e sai com o exit code respetivo
//*O exit_code que recebe corresponde ao errno
void	error_fp(int result, int exit_code, t_main *main)
{
	if (result == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putendl_fd(strerror(exit_code), STDERR_FILENO);
		set_exit_code(main, exit_code);
		ft_exit(NULL, false, *main);
	}
}

//*Esta função usa a função fork() para abrir um processo child,
//*Chama a função que lida com erro e devolve o pid do child process
int	ft_fork(t_main *main)
{
	int	pid;

	pid = fork();
	error_fp(pid, errno, main);
	return (pid);
}

//*Esta função espera pelos processos child no final dos pipes serem todos executados e seta o exit code respetivo
//*Por ordem de abertura dos processos!
void	wait_estatus_p(t_main *main, t_ast ast)
{
	t_ast_node *node;
	bool first_time;

	node = get_beg(&ast);
	while(node != NULL)
	{
		if(node->left)
		{
			wait_estatus(node->left->pid, main);
			wait_estatus(node->right->pid, main);
			first_time = false;
		}
		else
			wait_estatus(node->right->pid, main);
		node = node->prev;
	}
}
