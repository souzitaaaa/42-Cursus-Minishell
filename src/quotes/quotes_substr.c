/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_substr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 11:22:13 by rimarque          #+#    #+#             */
/*   Updated: 2023/10/04 11:22:13 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	verify_quotes_str(t_quotes *quotes, t_variables_quotes *s_var_quotes)
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
			create_quotes_node(quotes, s_var_quotes->open_quote_type, \
			s_var_quotes->open_quote_position, s_var_quotes->i);
			s_var_quotes->open_quote_position = -1;
			s_var_quotes->open_quote_type = '\0';
		}
	}
}

void	quotes_substr(t_quotes *quotes, char *str)
{
	t_variables_quotes s_var_quotes;

	ini_variables_quotes(&s_var_quotes);
	while (str[s_var_quotes.i] != '\0')
	{
		s_var_quotes.c = str[s_var_quotes.i];
		s_var_quotes.quotes_analises = check_quotes(s_var_quotes.c, s_var_quotes.quotes_analises);
		verify_quotes_str(quotes, &s_var_quotes);
		s_var_quotes.i++;
	}
}

