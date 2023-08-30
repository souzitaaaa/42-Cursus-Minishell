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

#include "../../../includes/minishell.h"

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

	while (*i <= main->tokens.str_len && run && main->input_prompt[*i])
	{
		if (special_chr(main->input_prompt[*i]) == false)
			(*i)++;
		else
			run = false;
	}
			//printf("start %i i(end) %i\n", start, *i);
	str = ft_substr(main->input_prompt, start, (*i - start));
			//printf("string: %s\n", str);
	add_token(main, STRING, i, str);
	(*i)--;
}