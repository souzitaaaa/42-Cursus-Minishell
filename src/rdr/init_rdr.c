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

//*Esta função chama as funções que executam os rdr guardados no token enviado
void	exec_rdr(t_token token, t_main *main, int hd)
{
	if(token.type == IN)
		rdr_in(token.arr, main);
	if(token.type == OUT)
		rdr_out(token.arr, main);
	if(token.type == APPEND)
		rdr_app(token.arr, main);
	if(token.type == HEREDOC)
		rdr_hd(token, main, hd);
}

void	find_exec_cmd_parent(t_lexer tokens, t_main *main)
{
	t_node *aux;
	int	counter;

	aux = tokens.head;
	counter = 0;
	while(counter++ < tokens.size)
	{

		if(aux->token.type == STRING)
		{
			print_arr(aux->token.arr);
			exec_cmd(aux->token.arr, main, false);
		}
		aux = aux->next;
	}
}

//*Esta função percorre a lista tokens e executa o comando
void	find_exec_cmd(t_lexer tokens, t_main *main)
{
	t_node *aux;
	int	counter;

	if(main->flags.rdr_err)
		exit_child(main, 1, true);
	aux = tokens.head;
	counter = 0;
	while(counter++ < tokens.size)
	{
		if(aux->token.type == STRING)
			exec_cmd(aux->token.arr, main, true);
		aux = aux->next;
	}
}

//*Esta função percorre a lista tokens, executa os here_doc, guarda o fd do último hd executado,
//*seta a bool hd a verdadeiro caso exista algum hd e o guarda o index do último hd executado
void	exec_hd(t_lexer tokens, t_main *main, bool *hd)
{
	t_node *aux;
	int	counter;

	aux = tokens.head;
	counter = 0;
	while(counter++ < tokens.size)
	{
		if(aux->token.type == HEREDOC)
		{
			if(!*hd)
				*hd = true;
			else
				close(main->hd.fd);
			if(aux->token.arr[1] == NULL)
				main->hd.fd = open_hd(aux->token.arr[0], aux->token.quotes, main);
			else
				main->hd.fd = open_hd(aux->token.arr[1], aux->token.quotes, main);
			main->hd.index = aux->index;
		}
		if (g_ex_status == 130)
			break ;
		aux = aux->next;
	}
}

//*Esta função percorre a lista tokens e faz todas as redireções in, out e app e a do ultimo hd
void	ft_redirect(t_lexer	tokens, t_main *main)
{
	t_node *aux;
	int	counter;

	aux = tokens.head;
	counter = 0;
	while(counter < tokens.size)
	{
		if(aux->token.type == STRING || (aux->token.type == HEREDOC && aux->index != main->hd.index))
		{
			counter++;
			if(counter < tokens.size)
				aux = aux->next;
		}
		exec_rdr(aux->token, main, main->hd.fd);
		aux = aux->next;
		counter++;
	}
}

int	check_cmd(t_lexer tokens)
{
	t_node	*aux;
	int counter;

	aux = tokens.head;
	counter = 0;
	while(counter++ < tokens.size)
	{
		if(aux->token.type == STRING)
		{
			if(!ft_strcmp(aux->token.arr[0], "cd") ||
				!ft_strcmp(aux->token.arr[0], "export") ||
					!ft_strcmp(aux->token.arr[0], "unset"))
						return(1);
		}
		aux = aux->next;
	}
	return(0);
}

//*Esta função percorre a lista tokens e executa os redirects, no final executa o comando
void	init_rdr(t_lexer tokens, t_main *main)
{
	int pid;
	bool hd;

	hd = false;
	exec_hd(tokens, main, &hd);
	if (g_ex_status == 130)
		return ;
	signals(1);
	pid = ft_fork(main);
	if (pid == 0)
	{
		ft_redirect(tokens, main);
		if(hd)
			close(main->hd.fd);
		find_exec_cmd(tokens, main);
		exit_child(main, 0, true);
	}
	else //!DESMECESSARIO
	{
		if(check_cmd(tokens))
		{
			main->flags.not_print = true;
			find_exec_cmd_parent(tokens, main);//uma função que chama versões do cd, unset e export, que não imprimem nada (servem para atualizar as variaveis de ambiente e o cd tem que fazer o chdir)
		}
		if(hd)
			close(main->hd.fd);
	}
	wait_estatus(pid, main);
}
