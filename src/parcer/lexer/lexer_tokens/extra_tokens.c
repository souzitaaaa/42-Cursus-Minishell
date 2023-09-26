/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinoguei <dinoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 14:35:10 by dinoguei          #+#    #+#             */
/*   Updated: 2023/08/22 17:04:12 by dinoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

//* Funcao de ajuda para a search_extra_tokens para verificar se encontrou
	//* um caracter delimitador de token
bool	special_chr(char c)
{
	if (ft_strchr("|<>", c))
		return true;
	return false;
}

//* Esta funcao vai procurar pelo que nao for special char
	//* para guardar numa str e mandar para a struct
void	search_extra_tokens(t_main *main, int *i)
{
	int		start = *i;
	char	*str;
	bool	run = true;
	bool    extra = false;
	int     n_len = 0;

	while (*i <= main->tokens.str_len && run && main->input_prompt[*i])
	{
		if (main->input_prompt[*i] >= 48 && main->input_prompt[*i] <= 57)
		{
			n_len = get_fd_rdr(main, i);
			if (main->flags.rdr_treated == true)
				break ;
			else
				n_len = 0;
		}
		if (main->input_prompt[*i] == '\'' || main->input_prompt[*i] == '\"')
		{
			//quotes_treatment(main, i, start);
			return ;
		}
		if (special_chr(main->input_prompt[*i]) == false)
		{
			(*i)++;
			extra = true;
		}
		else
			run = false;
	}
	if (main->flags.rdr_treated == true && extra == false)
		return ;
	str = ft_substr(main->input_prompt, start, (*i - start) - n_len);
	add_token(main, STRING, i, str);
	free(str);
	(*i)--;
}
