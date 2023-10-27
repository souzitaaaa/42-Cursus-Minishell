/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 16:47:49 by dinoguei          #+#    #+#             */
/*   Updated: 2023/10/27 18:13:12 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

//* Vai meter na lista o certo
void	get_fd_out(t_main *main, int *i, t_type token, char *fd)
{
	int		start;
	bool	run;
	char	*str;

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
	add_token(main, token, str, fd);
	free(fd);
	free(str);
}

//* Identifica qual o tipo de token do fd
void	fd_tokens(t_main *main, int *i, char *fd, char token)
{
	t_type	type;

	if (token == OUT)
	{
		type = get_type(main, i, OUT);
		if (type == APPEND)
			(*i) += 2;
		else
			(*i)++;
		get_fd_out(main, i, type, fd);
	}
	else
	{
		type = get_type(main, i, IN);
		if (type == HEREDOC)
			(*i) += 2;
		else
			(*i)++;
		get_fd_out(main, i, type, fd);
	}
}

int	get_fd_file_name(t_main *main, int start, int *i)
{
	char	*str;

	str = ft_substr(main->input, start, (*i - start));
	if (check_valid_fd(str) == false)
	{
		ft_free_str(&str);
		return (*i - start);
	}
	fd_tokens(main, i, str, main->input[*i]);
	main->flags.rdr_treated = true;
	return (*i - start);
}

void	stop_beeing_fd(t_main *main, int *i)
{
	int		index;

	index = *i + 1;
	if (main->input[index] >= 48 && main->input[index] <= 57)
		index++;
	if (special_chr(main->input[*i]) == true)
	{
		if (ft_strncmp(main->input + *i, "|", 1) == 0)
			return ;
	}
	*i = index;
}

//* Funcao principal para verificar se os numeros são um fd
int	get_fd_rdr(t_main *main, int *i)
{
	int		start;

	start = *i;
	while (main->input[*i])
	{
		if (main->input[*i] >= 48 && main->input[*i] <= 57)
			(*i)++;
		else
		{
			if (special_chr(main->input[*i]) == true)
			{
				if (ft_strncmp(main->input + *i, "|", 1) == 0)
					break ;
				else
					return (get_fd_file_name(main, start, i));
			}
			else
			{
				stop_beeing_fd(main, i);
				break ;
			}
		}
	}
	return (*i - start);
}
