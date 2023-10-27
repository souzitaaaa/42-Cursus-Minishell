/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenny <jenny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:53:46 by jenny             #+#    #+#             */
/*   Updated: 2023/10/18 15:53:46 by jenny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/structs.h"

void	create_quotes_node(t_quotes *quotes, int open_q_t, \
int open_q_p, int i)
{
	t_node_quotes	*new_node;

	new_node = malloc(sizeof(t_node_quotes));
	if (!new_node)
		return ;
	new_node->type = open_q_t;
	new_node->start = open_q_p;
	new_node->end = i;
	insert_last_quotes(quotes, new_node);
	shift_index_quotes(quotes);
}

int	check_quotes(char c, int quotes)
{
	if (c == DQUOTE)
	{
		if (!quotes)
			return (1);
		else if (quotes == 1)
			return (0);
	}
	else if (c == SQUOTE)
	{
		if (!quotes)
			return (2);
		else if (quotes == 2)
			return (0);
	}
	return (quotes);
}
