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

bool	check_index_quotes(t_main *main, int *i)
{
	t_node_quotes	*aux;
	int				count;

	count = 0;
	aux = main->quotes.head;
	while (count++ < main->quotes.size)
	{
		if (aux->start < *i && aux->end > *i)
			return (true);
		aux = aux->next;
	}
	return (false);
}

void	init_vars(t_extra *a, int *i)
{
	a->start = *i;
	a->fd = true;
	a->extra = false;
	a->n_len = 0;
}

bool	extra_tokens_while(t_main *main, t_extra *a, int *i)
{
	if ((main->input_prompt[*i] >= 48
			&& main->input_prompt[*i] <= 57) && a->fd == true)
	{
		if (main->input_prompt[*i - 1] == '-'
			|| (ft_isalpha(main->input_prompt[*i - 1]) == 1
				&& special_chr(main->input_prompt[*i + 1]) == true))
			a->fd = false;
		else
		{
			a->n_len = get_fd_rdr(main, i);
			if (main->flags.rdr_treated == true)
				return (true);
			else
				a->n_len = 0;
		}
	}
	if (special_chr(main->input_prompt[*i]) == false)
		a->extra = true;
	else if (check_index_quotes(main, i) == false)
		return (true);
	return (false);
}

//* Esta funcao vai procurar pelo que nao for special char
	//* para guardar numa str e mandar para a struct
void	search_extra_tokens(t_main *main, int *i)
{
	char	*str;
	t_extra	a;

	init_vars(&a, i);
	while (*i <= main->tokens.str_len && main->input_prompt[*i])
	{
		if (extra_tokens_while(main, &a, i) == true)
			break ;
		else
			(*i)++;
	}
	if (main->flags.rdr_treated == true && a.extra == false)
	{
		main->flags.rdr_treated = false;
		return ;
	}
	main->flags.rdr_treated = false;
	str = ft_substr(main->input_prompt, a.start, (*i - a.start) - a.n_len);
	add_token(main, STRING, str);
	free(str);
	(*i)--;
}
