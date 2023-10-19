/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinoguei <dinoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 16:47:49 by dinoguei          #+#    #+#             */
/*   Updated: 2023/10/18 18:00:14 by dinoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

//* Vai meter na lista o certo
void	get_fd_out(t_main *main, int *i, t_type token, char *fd)
{
	int		start;
	char	*aux;
	bool	run;

	run = true;
	while (is_space(main->input_prompt[*i]) == true)
		(*i)++;
	start = *i;
	while (*i <= main->tokens.str_len && run && main->input_prompt[*i])
	{
		if (special_chr(main->input_prompt[*i]) == true
			&& check_index_quotes(main, i) == false)
			break ;
		if (is_space(main->input_prompt[*i]) == false)
			(*i)++;
		else if (check_index_quotes(main, i) == false)
			run = false;
		else
			(*i)++;
	}
	aux = ft_substr(main->input_prompt, start, (*i - start));
	fd = ft_strjoinfree(fd, " ");
	fd = ft_strjoinfree(fd, aux);
	add_token(main, token, fd);
	free(aux);
	free(fd);
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

bool	check_valid_fd(char *str)
{
	long int	fd;

	fd = ft_long_atol(str);
	if (fd > INT_MAX)
		return (false);
	return (true);
}

//* Funcao principal para verificar se os numeros são um fd
int	get_fd_rdr(t_main *main, int *i)
{
	int		start;
	char	*str;

	start = *i;
	while (main->input_prompt[*i])
	{
		if (main->input_prompt[*i] >= 48 && main->input_prompt[*i] <= 57)
			(*i)++;
		else
		{
			if (special_chr(main->input_prompt[*i]) == true)
			{
				if (ft_strncmp(main->input_prompt + *i, "|", 1) == 0)
					break ;
				else
				{
					str = ft_substr(main->input_prompt, start, (*i - start));
					if (check_valid_fd(str) == false)
						break ;
					fd_tokens(main, i, str, main->input_prompt[*i]);
					main->flags.rdr_treated = true;
					break ;
				}
			}
			else
				break ;
		}
	}
	return (*i - start);
}
