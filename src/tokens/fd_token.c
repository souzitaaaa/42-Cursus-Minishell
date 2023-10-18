/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 16:47:49 by dinoguei          #+#    #+#             */
/*   Updated: 2023/10/16 18:43:49 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    check_quotes_heredoc(t_lexer *lexer)
{
	int     count = 0;
	int     i = 0;
	int     j = 0;

	t_node  *aux = lexer->head;

	while (count++ < lexer->size)
		aux = aux->next;
	while (aux->token.arr[i])
		i++;
	i--;
	if (aux->token.arr[i][j] == '\'' && aux->token.arr[i][j + 1] != '\0')
	{
		j++;
		while (aux->token.arr[i][j] != '\0')
		{
			if (aux->token.arr[i][j] == '\'')
			{
				aux->token.quotes = true;
				return ;
			}
			j++;
		}

	}
	else if (aux->token.arr[i][j] == '\"' && aux->token.arr[i][j + 1] != '\0')
	{
		j++;
		while (aux->token.arr[i][j] != '\0')
		{
			if (aux->token.arr[i][j] == '\"')
			{
				aux->token.quotes = true;
				return ;
			}
			j++;
		}
	}
}

//* Vai meter na lista o certo
void    get_fd_out(t_main *main, int *i, t_type token, char *fd)
{
	int     start = 0;
	char    *aux;
	bool	run = true;

			//printf("fd to insert: %s\n", fd);
	/*while (special_chr(main->input_prompt[*i]) == true
        || is_space(main->input_prompt[*i]) == true)
        (*i)++;*/
    while (is_space(main->input_prompt[*i]) == true)
    {
        (*i)++;
    }
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
void    fd_tokens(t_main *main, int *i, char *fd, char token)
{
	if (token == OUT)
	{
		if (*i + 1 <= main->tokens.str_len && main->input_prompt[*i + 1] == OUT)
		{
			(*i) += 2;
			get_fd_out(main, i, APPEND, fd);
		}
		else
		{
			(*i)++;
			get_fd_out(main, i, OUT, fd);
		}
	}
	else
	{
		if (*i + 1 <= main->tokens.str_len && main->input_prompt[*i + 1] == IN)
		{
			(*i) += 2;
			get_fd_out(main, i, HEREDOC, fd);
		}
		else
		{
			(*i)++;
			get_fd_out(main, i, IN, fd);
		}
	}

}

bool	check_valid_fd(char *str)
{
	long int fd = ft_long_atol(str);

	if (fd > INT_MAX)
		return (false);
	return (true);
}

//* Funcao principal para verificar se os numeros são um fd
int    get_fd_rdr(t_main *main, int *i)
{
	int     start = *i;
	char    *str;

				//printf("\033[1;32m\t\t(Get_fd_rdr)\033[0m\n");
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
				}
			}
			else
				break ;
		}
	}
	return (*i - start);
}
