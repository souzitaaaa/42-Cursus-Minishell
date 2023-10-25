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

void	create_quotes_node(t_quotes *quotes, int open_quote_type, \
int open_quote_position, int i)
{
	t_node_quotes	*new_node;

	new_node = malloc(sizeof(t_node_quotes));
	if (!new_node)
		return ;
	new_node->type = open_quote_type;
	new_node->start = open_quote_position;
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

char	*remove_empty_quotes(char *prompt)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	result = ft_calloc(ft_strlen(prompt) + 1, sizeof(char));
	if (result == NULL)
		return (NULL);
	while (prompt[i] != '\0')
	{
		if ((prompt[i] == DQUOTE && prompt[i + 1] == DQUOTE)
			|| (prompt[i] == SQUOTE && prompt[i + 1] == SQUOTE))
			i += 2;
		else
		{
			result[j] = prompt[i];
			i++;
			j++;
		}
	}
	result[j] = '\0';
	ft_free_str(&prompt);
	return (result);
}
