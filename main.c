#include "includes/minishell.h"

int	g_ex_status = 0;


//* Vai iniciar o prompt para correr o programa
//! Ver uma forma de ter sempre o prompt quando se da unset ou se muda as variaveis
void	init_prompt(t_main	*main, t_variables_quotes *s_var_quotes)
{
	char	*input;
	

	while (1)
	{
		signals(0);
		input = readline("minishell -> ");
		if (!input)
			ft_exit(NULL, false, main, false);
		main->line++;
		add_history(input);
		init_input(main, input);
		if(g_ex_status != 0)
		{
			set_exit_code(main, g_ex_status);
			g_ex_status = 0;
		}
		if (check_quotes_print(main,s_var_quotes))
			continue ;
		lexer(main);
		parser(main);
		destroy_input(main);
	}
}

//* Funcao main do nosso programa
int	main(int argc, char **argv, char **envp)
{
	t_main	main;
	t_variables_quotes s_var_quotes;

	(void)argc;
	(void)argv;
	//print_intro();
	init_main(&main, envp);
	init_prompt(&main, &s_var_quotes);
}