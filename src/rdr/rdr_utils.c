/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdr_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 19:36:58 by rimarque          #+#    #+#             */
/*   Updated: 2023/08/30 19:36:58 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//*Esta função chama as funções que executam os rdr guardados no token enviado
void	exec_rdr(t_token token, t_main *main, int hd)
{
	if (token.type == IN)
		rdr_in(token.arr, main);
	if (token.type == OUT)
		rdr_out(token.arr, main);
	if (token.type == APPEND)
		rdr_app(token.arr, main);
	if (token.type == HEREDOC)
		rdr_hd(token, main, hd);
}

//parar os rdr exceto o here doc, ultima linha
void	rdr_error(char *str, t_main *main, int options)
{
	if (options == 0)
		error_msg_file(str, STDERR_FILENO, FILE_ERROR);
	if (options == 1)
		error_msg_fd(str, STDERR_FILENO);
	if (options == 2)
		error_msg_file(str, STDERR_FILENO, AMBIG);
	main->flags.rdr_err = true;
}

bool	ft_isexit(t_lexer tokens)
{
	t_node	*aux;
	int		counter;

	aux = tokens.head;
	counter = 0;
	while (counter++ < tokens.size)
	{
		if (aux->token.type == STRING && aux->token.arr)
		{
			if (!ft_strcmp(aux->token.arr[0], "exit"))
				return (true);
		}
		aux = aux->next;
	}
	return (false);
}

bool	check_cmd(t_lexer tokens)
{
	t_node	*aux;
	int		counter;

	aux = tokens.head;
	counter = 0;
	while (counter++ < tokens.size)
	{
		if (aux->token.type == STRING && aux->token.arr)
		{
			if (!ft_strcmp(aux->token.arr[0], "cd")
				|| !ft_strcmp(aux->token.arr[0], "export")
				|| !ft_strcmp(aux->token.arr[0], "unset"))
				return (true);
		}
		aux = aux->next;
	}
	return (false);
}

void	find_exec_cmd_parent(t_lexer tokens, t_main *main)
{
	t_node	*aux;
	int		counter;

	if (main->exit_code == 1)
		return ;
	aux = tokens.head;
	counter = 0;
	while (counter++ < tokens.size)
	{
		if (aux->token.type == STRING && aux->token.arr)
			exec_cmd(aux->token.arr, main, false);
		aux = aux->next;
	}
}