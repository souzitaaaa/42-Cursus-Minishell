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

#include "../../../includes/minishell.h"

void	exec_rdr(t_token token, t_main *main, int hd_fd)
{
	if(token.type == IN)
		rdr_in(token.arr, main);
	if(token.type == OUT)
		rdr_out(token.arr, main);
	if(token.type == APPEND)
		rdr_app(token.arr, main);
	if(token.type == HEREDOC)
		rdr_hd(token, main, hd_fd);
}

void	find_exec_cmd(t_lexer tokens, t_main *main)
{
	t_node *aux;
	int	counter;

	if(main->flags.rdr_err)
		exit(1);
	aux = tokens.head;
	counter = 0;
	if(main->flags.rdr_err)
		exit(main->exit_code);
	while(counter++ < tokens.size)
	{
		if(aux->token.type == STRING)
			exec_cmd(aux->token.arr, main, true);
		aux = aux->next;
	}
	exit(0);
}

//*Esta função percorre a lista tokens e executa os redirects, no final executa o comando
void	init_rdr(t_lexer tokens, t_main *main)
{
	t_node *aux;
	int	counter;
	int	pid;
	bool hd;
	int index;
	int hd_fd;

	aux = tokens.head;
	counter = 0;
	while(counter++ < tokens.size)
	{
		if(aux->token.type == HEREDOC)
		{
			if(!hd)
				hd = true;
			else
				close(hd_fd);
			if(aux->token.arr[1] == NULL)
				hd_fd = open_hd(aux->token.arr[0], aux->token.quotes, main);
			else
				hd_fd = open_hd(aux->token.arr[1], aux->token.quotes, main);
		}
		aux = aux->next;
	}
	signals(1);
	pid = fork();
	//error_pipe();
	aux = tokens.head;
	counter = 0;
	if (pid == 0)
	{
		index = find_last_hd(tokens);
		while(counter < tokens.size)
		{
			if(aux->token.type == STRING || (aux->token.type == HEREDOC && aux->index != index))
			{
				counter++;
				if(counter < tokens.size)
					aux = aux->next;
			}
			exec_rdr(aux->token, main, hd_fd);
			aux = aux->next;
			counter++;
		}
		find_exec_cmd(tokens, main);
	}
	if(hd)
		close(hd_fd);
	wait_estatus(pid, main);
}
