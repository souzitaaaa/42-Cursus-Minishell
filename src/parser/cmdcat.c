/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdcat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinoguei <dinoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:57:47 by dinoguei          #+#    #+#             */
/*   Updated: 2023/09/19 17:57:47 by dinoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	cmdarrcat(t_lexer *tokens, t_node *aux, char ***temp, bool *cmdcat)
{
	int	index;

	*cmdcat = true;
	index = aux->index;
	*temp = ft_arrjoin_free(*temp, aux->token.arr);
	remove_node(tokens, aux->index, false);
	return (index);
}

//*concatenar os tipo S até ao próximo pipe ou até ao fim da lista
void	cmdpipecat(t_lexer *tokens, t_node *aux, int index)
{
	char	**temp;
	int		aux_index;
	bool	cmdcat;

	cmdcat = false;
	temp = ft_arrdup(aux->token.arr);
	aux = aux->next;
	while (aux->token.type != PIPE && aux != tokens->head)
	{
		if (aux->token.type == STRING && aux->token.arr)
		{
			aux_index = cmdarrcat(tokens, aux, &temp, &cmdcat);
			aux = get_node(*tokens, aux_index);
			if (aux == NULL)
				break ;
		}
		else
			aux = aux->next;
	}
	if (cmdcat)
		insert_temp(tokens, index, temp);
	else
		ft_free_array(&temp);
}

//*Esta função junta os tipos S todos no mesmo nó,
//para que entre pipes só haja um tipo S (comando)
void	cmdcat(t_lexer *tokens)
{
	t_node	*aux;
	int		cmd_index;

	aux = tokens->head;
	while (aux->next != tokens->head)
	{
		cmd_index = find_first_cmd(aux, tokens->size);
		if (cmd_index == -1)
			return ;
		aux = get_node(*tokens, cmd_index);
		cmdpipecat(tokens, aux, cmd_index);
		aux = get_node(*tokens, cmd_index);
		while (aux->token.type != PIPE && aux->next != tokens->head)
			aux = aux->next;
		if (aux->next == tokens->head)
			break ;
		aux = aux->next;
	}
}
