/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinoguei <dinoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 17:30:54 by dinoguei          #+#    #+#             */
/*   Updated: 2023/08/19 17:31:05 by dinoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

//* Esta função pode ser útil para mais funções, ela recebe uma str e procura
	//* uma variavel de ambiente com esse nome
char    *get_envvar(char *str, t_env *env_list)
{
	int count = 0;
	t_var *aux = env_list->head;
	char *out = NULL;

	while(count++ < env_list->size)
	{
		if (ft_strncmp(str, aux->var, ft_strlen(str)) == 0)
		{
			out = malloc(sizeof(char) * ft_strlen(aux->var) - ft_strlen(str));
			ft_strlcpy(out, aux->var + ft_strlen(str) + 1, ft_strlen(aux->var) - ft_strlen(str));
			return(out);
		}
		aux = aux->next;
	}
	return(NULL);
}

//*Inicia a struct para o tratamento do prompt
void	init_struct_prompt(t_main *main)
{
	main->prompt_list.logname = NULL;
	main->prompt_list.pwd = NULL;
	main->prompt_list.out = NULL;
	main->prompt_list.logname = get_envvar("LOGNAME", &main->env_list);
	if (!main->prompt_list.logname)
		main->prompt_list.logname = get_envvar("USER", &main->env_list);
	main->prompt_list.pwd = get_envvar("PWD", &main->env_list);
}

//* Esta funcao está muito má, eu depois melhoro-a mas por enquanto fica assim
char    *get_prompt_msg(t_main *main)
{
	init_struct_prompt(main);

	if (ft_strcmp(main->prompt_list.logname, "dinoguei") == 0)
		prompt_diogo(&main->prompt_list);
	else if (ft_strcmp(main->prompt_list.logname, "rita") == 0
		|| ft_strcmp(main->prompt_list.logname, "rimarque") == 0)
		prompt_rita(&main->prompt_list);
	//else if (ft_strcmp(main->prompt_list.logname, "jede-ara"))
	//	prompt_jenny(main->prompt_list);
	//else if (ft_strcmp(main->prompt_list.logname, "jcruz-da"))
	//	prompt_jo(main->prompt_list);
	//else
	//	prompt_default(main->prompt_list);
	return (main->prompt_list.out);
}

//* Vai iniciar o prompt para correr o programa
//! Ver uma forma de ter sempre o prompt quando se da unset ou se muda as variaveis
void	init_prompt(t_main	*main)
{
	char	*input = NULL;
	char	*prompt = NULL;

	while (1)
	{
		prompt = get_prompt_msg(main);
		input = readline(prompt);
		if (input == NULL)
			break;
		if (ft_strcmp(input, "exit") == 0)
		{
			free(input);
			printf("exit\n");
			break;
		}
		add_history(input);
		init_input(main, input);
		lexer(main);
		if (main->quotes.error == 0)
			test_exec(main);
		free(input);
		free(prompt);
	}
}

//* Funcao main do nosso programa
int	main(int argc, char **argv, char **envp)
{
	t_main	main;

	(void)argc;
	(void)argv;
	init_main(&main, envp);
	init_prompt(&main);
	//tratar aspas
	//lexer
	//se nao tiver carecteres expeciais vai logo para a exec_cmd;
	//analise sintatica --> se for falso da ERRO
	//AST
	//init_exec
}
