/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcruz-da <jcruz-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 22:44:59 by rimarque          #+#    #+#             */
/*   Updated: 2023/10/20 16:32:40 by jcruz-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/structs.h"

void	print_quotes(t_quotes *quotes)
{
	int					count;
	t_node_quotes		*aux;

	count = 0;
	aux = quotes->head;
	printf("\033[1;36m\t\t(Printing quotes)\033[0m\n");
	while (count++ < quotes->size)
	{
		printf("\033[1;34m[INDEX] \033[0m %i\n", aux->index);
		printf("\033[1;34m[TYPE]  \033[0m %c\n", aux->type);
		printf("\033[1;34m[START]  \033[0m %i\n", aux->start);
		printf("\033[1;34m[END]  \033[0m %i\n\n", aux->end);
		aux = aux->next;
	}
	printf("\033[1;36m\t\t(End printing quotes)\033[0m\n");
}

int	check_quotes_print(t_main *main, t_variables_quotes *s_var_quotes)
{
	main->input_prompt = remove_empty_quotes(main->input_prompt);
	main->tokens.str_len = ft_strlen(main->input_prompt);
	ini_variables_quotes(s_var_quotes);
	while (main->input_prompt[s_var_quotes->i] != '\0')
	{
		s_var_quotes->c = main->input_prompt[s_var_quotes->i];
		s_var_quotes->quotes_analises = check_quotes(s_var_quotes->c, s_var_quotes->quotes_analises);
		verify_quotes(main, s_var_quotes);
		s_var_quotes->i++;
	}
	if (update_erro_quotes(s_var_quotes->quotes_analises, main))
		return (2);
	print_quotes(&main->quotes);
	return (0);
}

void	verify_quotes(t_main *main, t_variables_quotes *s_var_quotes)
{
	printf("posicao: %i", s_var_quotes->i);
	printf("posicao: %i", s_var_quotes->open_quote_type);
	printf("posicao: %i", s_var_quotes->open_quote_type);

	if (s_var_quotes->c == SQUOTE || s_var_quotes->c == DQUOTE)
	{
		if ((s_var_quotes->quotes_analises == 1 \
		|| s_var_quotes->quotes_analises == 2) \
		&& s_var_quotes->open_quote_position == -1)
		{
			s_var_quotes->open_quote_position = s_var_quotes->i;
			s_var_quotes->open_quote_type = s_var_quotes->c;
		}
		else if (s_var_quotes->quotes_analises == 0 \
		&& s_var_quotes->open_quote_position != -1)
		{
			create_quotes_node(&main->quotes, s_var_quotes->open_quote_type, \
			s_var_quotes->open_quote_position, s_var_quotes->i);
			s_var_quotes->open_quote_position = -1;
			s_var_quotes->open_quote_type = '\0';
		}
		
	}
}
int	update_erro_quotes(int quotes_analises, t_main *main)
{
	if (quotes_analises == 1 || quotes_analises == 2)
	{
		error_syntax("newline");
		set_exit_code(main, 2);
		return (2);
	}
	return (0);
}
