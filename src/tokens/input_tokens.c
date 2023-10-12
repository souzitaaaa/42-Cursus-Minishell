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

#include "../../includes/minishell.h"

//* Aqui vai identificar para onde se vai mandar o input do caracter
void    get_rdr_in(t_main *main, int *i, t_type token, char *fd)
{
    int     start = 0;
    char    *str;
    bool	run = true;

    while (special_chr(main->input_prompt[*i]) == true
        || is_space(main->input_prompt[*i]) == true)
        (*i)++;
    start = *i;
	while (*i <= main->tokens.str_len && run && main->input_prompt[*i])
	{
		if (is_space(main->input_prompt[*i]) == false)
			(*i)++;
		else
			run = false;
	}
    str = ft_substr(main->input_prompt, start, (*i - start));
    add_token(main, token, str);
    //if (*i < main->tokens.str_len)
        //main->flags.put_node_behind = true;
    (*i)--;
}

//* Esta funcao identifica os caracteres de input, quer heredoc ou in
void    search_input_tokens(t_main *main, int *i, char *str)
{
    if (*i + 1 <= main->tokens.str_len && main->input_prompt[*i + 1] == IN)
	{
		(*i)++;
		get_rdr_in(main, i, HEREDOC, str);
	}
	else
	    get_rdr_in(main, i, IN, str);
}
