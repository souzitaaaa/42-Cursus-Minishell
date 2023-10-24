/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenny <jenny@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 17:33:34 by jede-ara          #+#    #+#             */
/*   Updated: 2023/10/09 12:06:04 by jenny            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	only_cd(char *current, t_main *main)
{
	char	*new_path;
	int		dir;

	new_path = get_envvar("HOME", &main->env_list);
	if (new_path)
	{
		dir = change_dir(new_path, main);
		if (dir == 0)
		{
			main->path_pwd = ft_calloc(sizeof(char), 4096);
			getcwd(main->path_pwd, 4096);
			refresh_pwd(main, main->path_pwd);
			refresh_oldpwd(main, current);
			ft_free_str(&new_path);
			ft_free_str(&main->path_pwd);
			return (0);
		}
		ft_free_str(&new_path);
		return (1);
	}
	if (main->flags.not_print == false)
		error_cd(STDERR_FILENO, "HOME");
	return (1);
}

int	previous_path(char *current, t_main *main)
{
	int		dir;
	char	*prev;

	prev = get_envvar("OLDPWD", &main->env_list);
	if (prev)
	{
		dir = change_dir(prev, main);
		if (dir == 0)
		{
			if (main->flags.not_print == false)
				ft_printf("%s\n", prev);
			main->path_pwd = ft_calloc(sizeof(char), 4096);
			getcwd(main->path_pwd, 4096);
			refresh_pwd(main, main->path_pwd);
			refresh_oldpwd(main, current);
			ft_free_str(&prev);
			ft_free_str(&main->path_pwd);
			return (0);
		}
		ft_free_str(&prev);
		return (1);
	}
	if (main->flags.not_print == false)
		error_cd(STDERR_FILENO, "OLDPWD");
	return (1);
}

int	regular_cd(char *current, char *path, t_main *main)
{
	int		dir;

	dir = change_dir(path, main);
	if (dir == 0)
	{
		main->path_pwd = ft_calloc(sizeof(char), 4096);
		getcwd(main->path_pwd, 4096);
		refresh_pwd(main, main->path_pwd);
		refresh_oldpwd(main, current);
		ft_free_str(&main->path_pwd);
		return (0);
	}
	return (1);
}

void	cd(char *path, t_main *main, bool child)
{
	char	*current;

	current = ft_calloc(sizeof(char), 4096);
	getcwd(current, 4096);
	if (path == NULL || (path[0] == '~' && path[1] == '\0'))
		main->error = only_cd(current, main);
	else if (ft_strcmp(path, "-") == 0)
		main->error = previous_path(current, main);
	else
		main->error = regular_cd(current, path, main);
	free(current);
	exit_child(main, main->error, child);
}
