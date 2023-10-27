/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdcat_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 21:57:13 by rimarque          #+#    #+#             */
/*   Updated: 2023/10/27 19:42:19 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//*encontra o primeiro comando e devolve o seu index
int	find_first_cmd(t_node *aux, int size)
{
	while (1)
	{
		if (aux->token.type == STRING && aux->token.arr)
			return (aux->index);
		if (aux->index == size - 1)
			break ;
		aux = aux->next;
	}
	return (-1);
}

char	**copy_first_cmd(t_lexer tokens, int index)
{
	int		counter;
	t_node	*aux;

	counter = 0;
	aux = tokens.head;
	while (counter++ < index)
		aux = aux->next;
	return (ft_arrdup(aux->token.arr));
}

t_node	*create_n_cmd(char **temp)
{
	t_node	*new;

	new = malloc(sizeof(t_node));
	if (!new)
		return (NULL);
	new->token.arr = ft_arrdup(temp);
	ft_free_array(&temp);
	new->token.type = STRING;
	return (new);
}

void	insert_temp(t_lexer *tokens, int index, char **temp)
{
	t_node	*new;

	remove_node(tokens, index, true);
	new = create_n_cmd(temp);
	insert_node(tokens, new, index);
}
