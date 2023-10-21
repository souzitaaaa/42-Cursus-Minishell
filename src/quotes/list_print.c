/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joe <joe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 22:44:59 by rimarque          #+#    #+#             */
/*   Updated: 2023/10/21 12:43:26 by joe              ###   ########.fr       */
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

int start_with_quotes(t_main *main, int fd)
{
    int i;

	i = 0;
    while (main->input_prompt[i] == ' ')
        i++;
	if (main->input_prompt[i] == SQUOTE || main->input_prompt[i] == DQUOTE)
	{
    	char quote = main->input_prompt[i]; 
		i++;
		if(main->input_prompt[i] != quote)
			return 1;
		while (main->input_prompt[i] != '\0' && main->input_prompt[i] != quote)
			i++;
		if (main->input_prompt[i] == '\0')
			return 1;
 		return(0);
	}	
	else 
		return 1;
}

int	check_quotes_print(t_main *main, t_variables_quotes *s_var_quotes)
{
	if (!start_with_quotes(main, 1))
		return(0);
	main->input_prompt = remove_empty_quotes(main->input_prompt);
	main->tokens.str_len = ft_strlen(main->input_prompt);
	ini_variables_quotes(s_var_quotes);
	
	while (main->input_prompt[s_var_quotes->i] != '\0')
	{
		s_var_quotes->c = main->input_prompt[s_var_quotes->i];
		s_var_quotes->quotes_analises = check_quotes(s_var_quotes->c, \
		s_var_quotes->quotes_analises);
		verify_quotes(main, s_var_quotes);
		s_var_quotes->i++;
	}
	if (update_erro_quotes(s_var_quotes->quotes_analises, main))
		return (2);
	return (0);
}

void	verify_quotes(t_main *main, t_variables_quotes *s_var_quotes)
{
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
// int start_with_quotes(t_main *main, int fd)
// {
// 	int i;

// 	i = 0;
// 	while (main->input_prompt[i] == ' ')
// 		i++;
// 	if ((!check_quotes(main->input_prompt[i], main->input_prompt[i] == SQUOTE)) \
// 	|| (!check_quotes(main->input_prompt[i], main->input_prompt[i] == DQUOTE)))
// 	{
// 		error_msg_cmd(main->input_prompt, fd);
// 		return(0);
// 	}
// 	return (1);
// }

// #include <stdbool.h>
// #include <stdio.h>


