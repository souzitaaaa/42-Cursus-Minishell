/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinoguei <dinoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 16:11:20 by dinoguei          #+#    #+#             */
/*   Updated: 2023/08/18 04:01:31 by dinoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//* Cerebro da separacao de tokens, vai ver oque tem a string nesse index
//*  e posteriormente tratar de mandar, tudo tratado para a lista
void	search_tokens(t_main *main, int *i)
{
	if (*i <= main->tokens.str_len && main->input[*i] == PIPE)
		add_token(main, PIPE, "|", NULL);
	else if (*i <= main->tokens.str_len && main->input[*i] == IN)
		search_input_tokens(main, i);
	else if (*i <= main->tokens.str_len && main->input[*i] == OUT)
		search_output_tokens(main, i);
	else if (*i <= main->tokens.str_len
		&& is_space(main->input[*i]) == false)
		search_extra_tokens(main, i);
}

//* Funcao main do lexer, vai simplesmente iniciar a lista e
//*  percorrer a str de input para fazer a divisao de tokens
void	lexer(t_main *main)
{
	int	i;

	i = 0;
	main->tokens.str_len = ft_strlen(main->input);
	while (i < main->tokens.str_len)
	{
		search_tokens(main, &i);
		i++;
	}
}
