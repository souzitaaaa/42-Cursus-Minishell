/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jede-ara <jede-ara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 14:38:26 by rimarque          #+#    #+#             */
/*   Updated: 2023/10/26 20:05:27 by jede-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/structs.h"

void	init_std(t_std *fd)
{
	fd->stdin = dup(STDIN_FILENO);
	fd->stdout = dup(STDOUT_FILENO);
	fd->stderr = dup(STDERR_FILENO);
}

void	init_bool(t_bool *flags)
{
	flags->rdr_treated = false;
	flags->rdr_err = false;
	flags->signal = false;
	flags->not_print = false;
	flags->hd = false;
}

//! Dar free sempre que se inicia novamente
void	init_input(t_main *main, char *input)
{
	main->input_prompt = input;
	init_bool(&main->flags);
	init_quotes(&main->quotes);
	init_lexer(&main->tokens);
	init_ast(&main->ast);
	main->hd.fd = 0;
	main->hd.index = 0;
	main->hd.str = NULL;
}

void	init_main(t_main *main, char **envp)
{
	init_env(&main->env_list);
	init_env(&main->export_list);
	set_env_list(main, envp);
	copy_exp(main);
	main->env_arr = NULL;
	main->path_pwd = NULL;
	main->exit_code = 0;
	main->line = 0;
	main->error = 0;
	init_std(&main->fd);
	main->flags.signal = false;
}
