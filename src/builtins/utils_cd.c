/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jede-ara <jede-ara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:42:36 by jede-ara          #+#    #+#             */
/*   Updated: 2023/10/24 15:17:39 by jede-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*Essa funcao atualiza o pwd, toda vez que o pwd é mudado chamamos ela para
atualizar o path novo*/
void	refresh_pwd(t_main *main, char *str)
{
	char	*pwd;

	pwd = ft_strjoin("PWD=", str);
	if (modify_var(&main->export_list, pwd) == false)
		insert_var(&main->export_list, pwd);
	if (modify_var(&main->env_list, pwd) == false)
		insert_var(&main->env_list, pwd);
	ft_free_str(&pwd);
}

/*Essa funcao atualiza o oldpwd, toda vez que o oldpwd é mudado chamamos
ela para atualizar o path novo*/
void	refresh_oldpwd(t_main *main, char *str)
{
	char	*oldpwd;

	oldpwd = ft_strjoin("OLDPWD=", str);
	if (modify_var(&main->export_list, oldpwd) == false)
		insert_var(&main->export_list, oldpwd);
	if (modify_var(&main->env_list, oldpwd) == false)
		insert_var(&main->env_list, oldpwd);
	ft_free_str(&oldpwd);
}

/*Essa variavel é usada para mudar de diretorio, o chdir é usado para mudar
o diretório atual para o caminho especificado pelo parâmetro path*/
int	change_dir(char *path, t_main *main)
{
	if (chdir(path) != 0)
	{
		if (main->flags.not_print == false)
			error_msg_file(path, STDERR_FILENO);
		return (1);
	}
	return (0);
}

/*Essa função recebe uma str e procura uma variável de ambiente com o nome
especificado*/
char	*get_envvar(char *str, t_env *env_list)
{
	int		count;
	t_var	*aux;
	char	*out;

	count = 0;
	aux = env_list->head;
	while (count++ < env_list->size)
	{
		if (ft_strncmp(str, aux->var, ft_strlen(str)) == 0)
		{
			out = malloc(sizeof(char) * ft_strlen(aux->var) - ft_strlen(str));
			ft_strlcpy(out, aux->var + ft_strlen(str) + 1, ft_strlen(aux->var)
				- ft_strlen(str));
			return (out);
		}
		aux = aux->next;
	}
	return (NULL);
}

void	check_cd(char **command, t_main *main, bool child)
{
	char	*path;

	path = NULL;
	if (command[1] != NULL)
	{
		path = command[1];
		if (command[2] != NULL)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putendl_fd("cd: too many arguments", STDERR_FILENO);
			exit_child(main, 1, child);
			return ;
		}
	}
	cd(path, main, child);
}
