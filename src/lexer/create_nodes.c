/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_nodes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinoguei <dinoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 16:06:55 by dinoguei          #+#    #+#             */
/*   Updated: 2023/09/21 16:06:55 by dinoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


char	**quotes_split_expand(char *str, t_main *main, t_type token, bool *quote_hd)
{
	char		**result;
	t_quotes	quotes;

	ini_quotes(&quotes);
	quotes_substr(&quotes, str);
	if(token == HEREDOC)
		main->flags.hd = true;
	if (quotes.head == NULL)
	{
		result = ft_split(str, ' ');
		if(token != HEREDOC)
			check_expansion_arr(main, result);
	}
	else
	{
		*quote_hd = true;
		result = quotes_treatment(quotes, str, main);
		//free_quotes();
	}
	main->flags.hd = false;
	return (result);
}

t_node	*create_n(t_main *main, t_type token, char *str)
{
	t_node	*new;
	char	**arr;
	bool    quote_hd;

	(void)main;
	quote_hd = false;
	new = malloc(sizeof(t_node));
	if (!new)
		return (NULL);
	new->token.type = token;
	arr = quotes_split_expand(str, main, token, &quote_hd);
	new->token.arr = ft_calloc(ft_arrlen(arr) + 1, sizeof(char *));
	ft_arrlcpy(new->token.arr, arr, ft_arrlen(arr) + 1);
	free(arr);
	new->token.quotes = quote_hd;
	return (new);
}
