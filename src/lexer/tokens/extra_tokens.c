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

//* Esta funcao vai procurar pelo que nao for special char
	//* para guardar numa str e mandar para a struct
void	search_extra_tokens(t_main *main, int *i)
{
	int		start;
	char	*str;
	bool	fd;
	bool	run;
	bool	extra;
	int		n_len;

	start = *i;
	fd = true;
	run = true;
	extra = false;
	n_len = 0;
	while (*i <= main->tokens.str_len && run && main->input_prompt[*i])
	{
		if ((main->input_prompt[*i] >= 48
				&& main->input_prompt[*i] <= 57) && fd == true)
		{
			if (main->input_prompt[*i - 1] == '-')
				fd = false;
			else
			{
				n_len = get_fd_rdr(main, i);
				if (main->flags.rdr_treated == true)
					break ;
				else
					n_len = 0;
			}
		}
		if (special_chr(main->input_prompt[*i]) == false)
		{
			(*i)++;
			extra = true;
		}
		else if (check_index_quotes(main, i) == false)
			run = false;
		else
			(*i)++;
	}
	if (main->flags.rdr_treated == true && extra == false)
	{
		main->flags.rdr_treated = false;
		return ;
	}
	main->flags.rdr_treated = false;
	str = ft_substr(main->input_prompt, start, (*i - start) - n_len);
	add_token(main, STRING, str);
	free(str);
	(*i)--;
}

/*
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


void	init_extra(t_extra *a, int i)
{
	a->start = i;
	a->fd = true;
	a->run = true;
	a->extra = false;
	a->n_len = 0;
}

bool	fd_extra_tokens(t_main *main, t_extra *a, int *i)
{
	if (main->input_prompt[*i - 1] == '-')
		a->fd = false;
	else
	{
		a->n_len = get_fd_rdr(main, i);
		if (main->flags.rdr_treated == true)
			return (true);
		else
			a->n_len = 0;
	}
	return (false);
}

bool	extra_tokens_while(t_main *main, t_extra *a, int *i)
{
	if ((main->input_prompt[*i] >= 48 && main->input_prompt[*i] <= 57)
		&& a->fd == true)
	{
		if (fd_extra_tokens(main, a, i) == true)
			return (true);
	}
	if (special_chr(main->input_prompt[*i]) == false)
		a->extra = true;
	else if (check_index_quotes(main, i) == false)
	{
		a->run = false;
		return (true);
	}
	return (false);
}

void	search_extra_tokens(t_main *main, int *i)
{
	char	*str;
	t_extra	a;

	init_extra(&a, (int)*i);
	while (*i <= main->tokens.str_len && a.run && main->input_prompt[*i])
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
}*/
