/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jede-ai <jede-adi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 17:29:18 by dinoguei          #+#    #+#             */
/*   Updated: 2023/08/10 16:09:15 by jede-adi         ###   ########.fr       */
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

//* Esta funcao está muito má, eu depois melhoro-a mas por enquanto fica assim
char    *get_prompt_msg(t_main *main)
{
	char    *logname = NULL;
	char    *pwd = NULL;
	char    *at = NULL;
	char    *prompt = NULL;
	char    *blue = NULL;
	char    *green = NULL;
	char    *reset = NULL;
	char    *out = NULL;
	
	blue = "\033[1;36m";
	green = "\033[1;32m";
	reset = "\033[0m";
	logname = get_envvar("LOGNAME", &main->env_list);
	if (!logname)
		logname = get_envvar("USER", &main->env_list);
	pwd = get_envvar("PWD", &main->env_list);
	at = "\033[1;37m at \033[0m";
	prompt = "\n\033[1;31m|MINIHELL😈|--> \033[1;0m";
	
	logname = ft_strjoin("[", logname);
	logname = ft_strjoin(logname, "]");
	blue = ft_strjoin(blue, logname);
	blue = ft_strjoin(blue, reset);
	pwd = ft_strjoin("[", pwd);
	pwd = ft_strjoin(pwd, "]");
	green = ft_strjoin(green, pwd);
	green = ft_strjoin(green, reset);
	out = ft_strjoin(blue, at);
	out = ft_strjoin(out, green);
	out = ft_strjoin(out, prompt);
	
	return (out);
}

//* Vai iniciar o prompt para correr o programa
void	init_prompt(t_main	*main, char **envp)
{
	char		*input = NULL;

	init_env(&main->env_list);
	set_env_list(main, envp);
	while (1)
	{
		input = readline(get_prompt_msg(main));
		if (input == NULL)
			break;
		if (ft_strcmp(input, "exit") == 0)
		{
			free(input);
			printf("exit\n");
			break;
		}
		add_history(input);
		init_main(main, input);
		lexer(main);
		if (main->quotes.error == 0) 
			test_exec(main);
		free(input);
	}
}

//* Funcao main do nosso programa
int	main(int argc, char **argv, char **envp)
{
	t_main	main;

	(void)argc;
	(void)argv;
	init_prompt(&main, envp);
	//tratar aspas
	//lexer
	//se nao tiver carecteres expeciais vai logo para a exec_cmd;
	//analise sintatica --> se for falso da ERRO
	//AST
	//init_exec
}
