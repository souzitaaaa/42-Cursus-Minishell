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


char	**quotes_split_expand(char *str, t_main *main, t_type token)
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

	(void)main;
	new = malloc(sizeof(t_node));
	if (!new)
		return (NULL);
	new->token.type = token;
	arr = quotes_split_expand(str, main, token);
	new->token.arr = ft_calloc(ft_arrlen(arr) + 1, sizeof(char *));
	ft_arrlcpy(new->token.arr, arr, ft_arrlen(arr) + 1);
	free(arr);
	new->token.quotes = false;
	return (new);
}

/*t_node	*create_n_quotes(t_main *main, t_type token, int *i, char **result, bool expand)
{
	t_node	*new;

	(void)main;
	new = malloc(sizeof(t_node));
	if (!new)
		return (NULL);
	new->token.type = token;
	new->token.arr = ft_calloc(ft_arrlen(result) + 1, sizeof(char *));
	ft_arrlcpy(new->token.arr, result, ft_arrlen(result) + 1);
	new->token.quotes = false;
	//! falta o free da arr
	return (new);
}*/
