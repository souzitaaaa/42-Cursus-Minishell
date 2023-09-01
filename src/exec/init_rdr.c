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

void	exec_rdr(t_token token, t_main *main)
{
	printf("entra aqui 2\n");
	if(token.type == IN)
		rdr_in(token.arr, main);
	if(token.type == OUT)
	{
		printf("entra aqui 3\n");
		rdr_out(token.arr, main);
	}
	if(token.type == APPEND)
		rdr_app(token.arr, main);
	if(token.type == HEREDOC)
		rdr_hd(token, main);
}

void	find_exec_cmd(t_lexer tokens, t_main *main)
{
	t_node *aux;
	int	counter;

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
}

//*Esta função percorre a lista tokens e executa os redirects, no final executa o comando
void	init_rdr(t_lexer tokens, t_main *main)
{
	t_node *aux;
	int	counter;
	int	pid;

	aux = tokens.head;
	counter = 0;
	//pid = fork();
	//if (pid == 0)
	{
		while(counter++ < tokens.size)
		{
			printf("entra aqui 1\n");
			if(aux->token.type == STRING)
				aux = aux->next;
			exec_rdr(aux->token, main);
			aux = aux->next;
		}
		find_exec_cmd(tokens, main);
	}
	//wait_estatus(pid, main);
}
