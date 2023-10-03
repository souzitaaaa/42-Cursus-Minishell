/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenny <jenny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:05:04 by jenny             #+#    #+#             */
/*   Updated: 2023/10/03 14:20:54 by jenny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_isnbr(const char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	if (*str == '\0')
		return(0);
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return(0);
		str++;
	}
	return(1);
}

int	unset_cd(t_main *main, char *str)
{
	int	index;

	print_var(main->env_list);
	index = unset_env(main, str);
	unset_exp(main, str);
	return (index);
}

void	refresh_pwd(t_main *main, char *str)
{
	char	*pwd;

	pwd = ft_strjoin("PWD=", str);
	if (modify_var_exp(main, pwd) == false)
		insert_var_exp(main, pwd);
	if (modify_var_env(main, pwd) == false)
		insert_var_env(main, pwd);
}
void	refresh_oldpwd(t_main *main, char *str)
{
	char	*oldpwd;

	oldpwd = ft_strjoin("OLDPWD=", str);
	if (modify_var_exp(main, oldpwd) == false)
		insert_var_exp(main, oldpwd);
	if (modify_var_env(main, oldpwd) == false)
		insert_var_env(main, oldpwd);
}
/*fazer uma funcao que dá erro em: - + * = % ? / | \ () e não adicionar
export -=jenny : bash: export: -=: invalid option: EXIT_CODE: 2
export: usage: export [-nf] [name[=value] ...] or export -p
export+=jenny : bash: export: `+=jenny': not a valid identifier EXIT_CODE: 1
export *=jenny: bash: export: `*=jenny': not a valid identifier EXIT_CODE: 1
export =jenny: bash: export: `=jenny': not a valid identifier(o nosso faz: minishell: zsh: bad assignment) EXIT_CODE: 1
export %=jenny: bash: export: `%=jenny': not a valid identifier EXIT_CODE: 1 
export ?=jenny: bash: export: `?=jenny': not a valid identifier EXIT_CODE: 1
export /=export: bash: export: `/=export': not a valid identifier EXIT_CODE: 1
export |=export: bash: =export: command not found EXIT_CODE: 127
export \=export: bash: export: `=export': not a valid identifier EXIT_CODE: 1
export (=export: bash: syntax error near unexpected token `=export' EXIT_CODE: 258
export )=export: bash: syntax error near unexpected token `)' EXIT_CODE: 258 */
void	validations_ch(t_main *main, char **str, int fd, bool child) 
{
    int i = 1;

    if (str[i][0] == '-')
	{
        ft_putstr_fd("minishell: ", fd);
        ft_putstr_fd(str[i], fd);
		ft_printf("entra aqui?\n");
        ft_putstr_fd(": invalid option\n", fd);
		if (child)
			exit(2);
		set_exit_code(main, 2);
    }
	else if (str[i][0] == '+' || str[i][0] == '*' || str[i][0] == '%' || str[i][0] == '?' || str[i][0] == '/' || str[i][0] == '\\')
	{
        ft_putstr_fd("minishell: ", fd);
        ft_putstr_fd(str[i], fd);
        ft_putstr_fd(": invalid option\n", fd);
		if (child)
			exit(1);
		set_exit_code(main, 1);
    }
	else if (str[i][0] == '|')
	{
        ft_putstr_fd("minishell: ", fd);
        ft_putstr_fd(str[i], fd);
        ft_putstr_fd(": invalid option\n", fd);
		if (child)
			exit(127);
		set_exit_code(main, 127);
    }
	else if (str[i][0] == '(' || str[i][0] == ')')
	{
        ft_putstr_fd("minishell: ", fd);
        ft_putstr_fd(str[i], fd);
        ft_putstr_fd(": syntax error near unexpected token '", fd);
        ft_putstr_fd(str[i], fd);
        ft_putstr_fd("'\n", fd);
		if (child)
			exit(258);
		set_exit_code(main, 258);
    }
}
