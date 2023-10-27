/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rdr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 11:02:50 by rimarque          #+#    #+#             */
/*   Updated: 2023/08/28 11:02:50 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_ex_status;

//*Esta função percorre a lista tokens, executa os
//* here_doc, guarda o fd do último hd executado,
//* seta a bool hd a verdadeiro caso exista algum hd
//* e o guarda o index do último hd executado
void	exec_hd(t_lexer tokens, t_main *main, bool *hd)
{
	t_node	*aux;
	int		counter;

	aux = tokens.head;
	counter = 0;
	while (counter++ < tokens.size)
	{
		if (aux->token.type == HEREDOC)
		{
			if (!*hd)
				*hd = true;
			else
				close(main->hd.fd);
			if (aux->token.arr[1] == NULL)
				main->hd.fd = open_hd(aux->token.arr[0],
						aux->token.quotes, main);
			else
				main->hd.fd = open_hd(aux->token.arr[1],
						aux->token.quotes, main);
			main->hd.index = aux->index;
		}
		if (g_ex_status == 130)
			break ;
		aux = aux->next;
	}
}

//*Esta função percorre a lista tokens e faz todas
//* as redireções in, out e app e a do ultimo hd
void	ft_redirect(t_lexer	tokens, t_main *main)
{
	t_node	*aux;
	int		counter;

	aux = tokens.head;
	counter = 0;
	while (counter < tokens.size)
	{
		if (aux->token.type == STRING
			|| (aux->token.type == HEREDOC
				&& aux->index != main->hd.index))
		{
			counter++;
			if (counter < tokens.size)
				aux = aux->next;
		}
		exec_rdr(aux->token, main, main->hd.fd);
		aux = aux->next;
		counter++;
	}
}

//*Esta função percorre a lista tokens e executa o comando
void	find_exec_cmd(t_lexer tokens, t_main *main)
{
	t_node	*aux;
	int		counter;

	if (main->flags.rdr_err)
		exit_child(main, 1, true);
	aux = tokens.head;
	counter = 0;
	while (counter++ < tokens.size)
	{
		if (aux->token.type == STRING && strcmp(aux->token.arr[0], "exit"))
			exec_cmd(aux->token.arr, main, true);
		aux = aux->next;
	}
}

void	check_execmd_parent(t_lexer tokens, t_main *main)
{
	if (ft_isexit(tokens))
		find_exec_cmd_parent(tokens, main);
	else if (check_cmd(tokens))
	{
		main->flags.not_print = true;
		find_exec_cmd_parent(tokens, main);
	}
}

//*Esta função percorre a lista tokens e executa
//* os redirects, no final executa o comando
void	init_rdr(t_lexer tokens, t_main *main)
{
	int		pid;
	bool	hd;

	hd = false;
	exec_hd(tokens, main, &hd);
	if (g_ex_status == 130)
		return ;
	signals(1);
	pid = ft_fork(main);
	if (pid == 0)
	{
		ft_redirect(tokens, main);
		if (hd)
			close(main->hd.fd);
		find_exec_cmd(tokens, main);
		exit_child(main, 0, true);
	}
	wait_estatus(pid, main);
	check_execmd_parent(tokens, main);
	if (hd)
		close(main->hd.fd);
}
