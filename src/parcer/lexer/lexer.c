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

#include "../../../includes/minishell.h"

void    get_iteration(t_main *main, int *i)
{
	int		start;
	char	*str;
	bool	run = true;

	while (*i <= main->tokens.str_len && main->input_prompt[*i]
		&& is_space(main->input_prompt[*i]) == true)
		(*i)++;
	start = *i;
	while (*i <= main->tokens.str_len && run && main->input_prompt[*i])
	{
		if (special_chr(main->input_prompt[*i]) == false)
			(*i)++;
		else
			run = false;
	}
	str = ft_substr(main->input_prompt, start, (*i - start));
	add_prev_token(main, i, str);
}

//* Cerebro da separacao de tokens, vai ver oque tem a string nesse index
	//* e posteriormente tratar de mandar, tudo tratado para a lista
void search_tokens(t_main *main, int *i)
{
	if (*i <= main->tokens.str_len && main->input_prompt[*i] == PIPE)
		add_token(main, PIPE, i, "|");
	else if (*i <= main->tokens.str_len && main->input_prompt[*i] == IN)
		search_input_tokens(main, i, "");
	else if (*i <= main->tokens.str_len && main->input_prompt[*i] == OUT)
		search_output_tokens(main, i, "");
	else if (*i <= main->tokens.str_len && main->input_prompt[*i] != ' ')
		search_extra_tokens(main, i);
}


//* Funcao main do lexer, vai simplesmente iniciar a lista e
	//* percorrer a str de input para fazer a divisao de tokens
void	lexer(t_main *main)
{
	int i;
				printf("\033[1;33m\t\t\t[Lexer function]\033[0m\n");
				printf("Input: %s Size: %i\n", main->input_prompt, main->tokens.str_len);
	i = 0;
	check_quotes_print(main);
	while(main->input_prompt[i] && i <= main->tokens.str_len)
	{
		search_tokens(main, &i);
		i++;
	}
	print_tokens(&main->tokens);
}
