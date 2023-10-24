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

int	find_last_hd(t_lexer tokens)
{
	int		counter;
	t_node	*aux;
	t_node	*result;

	counter = 0;
	aux = tokens.head;
	while (counter++ < tokens.size)
	{
		if (aux->token.type == HEREDOC)
			result = aux;
		aux = aux->next;
	}
	return (result->index);
}

void	set_rdr_err(t_main *main)
{
	main->flags.rdr_err = true;
}

//parar os rdr exceto o here doc, ultima linha
void	rdr_error(char *str, t_main *main, int options)
{
	if (options == 0)
		error_msg_file(str, STDERR_FILENO, FILE_ERROR);
	if (options == 1)
		error_msg_fd(str, STDERR_FILENO);
	set_rdr_err(main);
}
