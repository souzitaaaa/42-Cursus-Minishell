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

#include "../../../../includes/minishell.h"

//* Vai meter na lista o certo
void    get_fd_out(t_main *main, int *i, t_type token, char *fd)
{
    int     start = 0;
    char    *aux;
    bool	run = true;
    
            printf("fd to insert: %s\n", fd);
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
    aux = ft_substr(main->input_prompt, start, (*i - start));
    fd = ft_strjoin(fd, " ");
    fd = ft_strjoin(fd, aux);
    add_token(main, token, i, fd);
    if (*i < main->tokens.str_len)
        main->flags.put_node_behind = true;
    //(*i)--;
}

//* Identifica qual o tipo de token do fd
void    fd_tokens(t_main *main, int *i, char *str)
{
    if (*i + 1 <= main->tokens.str_len && main->input_prompt[*i + 1] == OUT)
	{
		(*i)++;
		get_fd_out(main, i, APPEND, str);
	}
	else
	    get_fd_out(main, i, OUT, str);
}

//* Funcao principal para verificar se os numeros são um fd
int    get_fd_rdr(t_main *main, int *i)
{
    int     start = *i;
    char    *str;
    
                printf("\033[1;32m\t\t(Get_fd_rdr)\033[0m\n");
    while (main->input_prompt[*i])
    {
        printf("Char to compare: %c\n", main->input_prompt[*i]);
        if (main->input_prompt[*i] >= 48 && main->input_prompt[*i] <= 57)
            (*i)++;
        else
        {
            if (special_chr(main->input_prompt[*i]) == true)
            {
                if (ft_strncmp(main->input_prompt + *i, "|", 1) == 0)
                    return (*i - start);
                else
                {
                    str = ft_substr(main->input_prompt, start, (*i - start));
                    fd_tokens(main, i, str);
                    main->flags.rdr_treated = true;
                    printf("\033[1;32m\t\t(End get_fd_rdr special)\033[0m\n");
                    return (*i - start);
                }
            }
            else
                return (*i - start);
        }
    }
                printf("\033[1;32m\t\t(End get_fd_rdr)\033[0m\n");
    return (*i - start);
}

//* Funcao de ajuda para a get_rdr_out que verifica
bool    is_space(char c)
{
    if (ft_strchr(" ", c))
        return true;
    return false;
}

//* Aqui vai identificar para onde se vai mandar o output do caracter
void    get_rdr_out(t_main *main, int *i, t_type token, char *fd)
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
    add_token(main, token, i, str);
    //if (*i < main->tokens.str_len)
        //main->flags.put_node_behind = true;
    (*i)--;
}

//* Esta funcao identifica os caracteres de output, quer append quer redirect
void    search_output_tokens(t_main *main, int *i, char *str)
{
    if (*i + 1 <= main->tokens.str_len && main->input_prompt[*i + 1] == OUT)
	{
		(*i)++;
		get_rdr_out(main, i, APPEND, str);
	}
	else
	    get_rdr_out(main, i, OUT, str);
}