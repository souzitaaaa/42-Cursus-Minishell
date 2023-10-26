/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinoguei <dinoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:45:44 by dinoguei          #+#    #+#             */
/*   Updated: 2023/08/22 15:45:44 by dinoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

//* Aqui vai identificar para onde se vai mandar o input do caracter
void	get_rdr_in(t_main *main, int *i, t_type token)
{
	int		start;
	char	*str;
	bool	run;

	start = 0;
	run = true;
	while (is_space(main->input[*i]) == true)
		(*i)++;
	start = *i;
	while (*i <= main->tokens.str_len && run && main->input[*i])
	{
		if (special_chr(main->input[*i]) == true
			&& check_index_quotes(main, i) == false)
			break ;
		if (is_space(main->input[*i]) == false)
			(*i)++;
		else if (check_index_quotes(main, i) == false)
			run = false;
		else
			(*i)++;
	}
	str = ft_substr(main->input, start, (*i - start));
	add_token(main, token, str);
	(*i)--;
	free(str);
}

//* Esta funcao identifica os caracteres de input, quer heredoc ou in
void	search_input_tokens(t_main *main, int *i)
{
	t_type	type;

	type = get_type(main, i, IN);
	if (type == HEREDOC)
		(*i) += 2;
	else
		(*i)++;
	get_rdr_in(main, i, type);
}
