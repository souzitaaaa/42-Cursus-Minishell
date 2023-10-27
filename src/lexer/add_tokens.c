/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinoguei <dinoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 16:00:15 by dinoguei          #+#    #+#             */
/*   Updated: 2023/09/21 16:00:15 by dinoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	head_null(t_main *main, char *str, char ***result, t_type token)
{
	*result = ft_split_tab(str);
	check_expansion_arr(main, result);
	if (is_rdr(token))
	{
		if (result == NULL)
		{
			ft_free_array(result);
			*result = str_to_arr(str, false);
		}
	}
}

//* Esta função vai tratar da separação do conteudo da array dependendo
//*  se a mesma têm aspas ou não, caso não as tenha, simplesmente faz um split
//*  e vai verificar se os argumentos precisam de ser expandidos, caso tenha
//*  aspas vai para uma outra função mais complexa para o tratamento das mesmas
char	**quotes_split(char *str, t_main *main, t_type token, bool *quote_hd)
{
	char		**result;
	t_quotes	quotes;

	init_quotes(&quotes);
	quotes_substr(&quotes, str);
	if (token == HEREDOC)
		main->flags.hd = true;
	if (quotes.head == NULL)
		head_null(main, str, &result, token);
	else
	{
		*quote_hd = true;
		result = quotes_treatment(quotes, str, main);
		free_quotes(&quotes);
	}
	main->flags.hd = false;
	return (result);
}

//* Esta função trata de inserir os elementos do token em cada nó,
//*  ou seja, o tipo do token, e uma array com o conteudo dele
t_node	*create_n(t_main *main, t_type token, char *str)
{
	t_node	*new;
	char	**arr;
	bool	quote_hd;

	arr = NULL;
	quote_hd = false;
	new = malloc(sizeof(t_node));
	if (!new)
		return (NULL);
	new->token.type = token;
	if (*str)
		arr = quotes_split(str, main, token, &quote_hd);
	if (!arr)
		new->token.arr = NULL;
	else
	{
		new->token.arr = ft_calloc(ft_arrlen(arr) + 1, sizeof(char *));
		ft_arrlcpy(new->token.arr, arr, ft_arrlen(arr) + 1);
	}
	if (str)
		free(arr);
	new->token.quotes = quote_hd;
	return (new);
}

//* Esta função trata de criar um novo node e de o inserir na lista do Lexer
//* Recebe como argumentos, o main para ter acesso a tudo do projeto,
//*  ao tipo do token e uma string que vai ser o conteudo do token
int	add_token(t_main *main, t_type token, char *str)
{
	t_node	*new;

	new = create_n(main, token, str);
	if (!new)
		return (1);
	insert_last(&main->tokens, new);
	return (0);
}
