/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joe <joe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 11:43:46 by joe               #+#    #+#             */
/*   Updated: 2023/09/28 12:24:04 by joe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"
# include "defines.h"
# include "structs.h"

/*
!BUILTINS
*/
void    echo(char **command, t_main *main, bool child);
void    pwd(t_main *main, bool child);
void    env(t_env *env, t_main *main, bool child, char **command);
void	unset_exp(t_main *main, char *str);
int		unset_env(t_main *main, char *str);
void	unset(t_main *main, char **array, bool child);
void	ft_export(t_env *exp);
void    export(t_main *main, char **array, bool child);
void    insert_var_exp(t_main *main, char *str);
void    insert_var_env(t_main *main, char *str);
bool    modify_var_exp(t_main *main, char *str);
bool    modify_var_env(t_main *main, char *str);
void	copy_exp(t_main *main);
void    remove_var(t_env *env, int index);
void    cd(char *path, t_main *main, bool child);
void	refresh_pwd(t_main *main, char *str);
void	refresh_oldpwd(t_main *main, char *str);
void	ft_exit(char **command, bool child, t_main main);
int		ft_isnbr(const char *str);


/*
!ENVP
*/
t_var       *var_node(const char *var);
void		add_var(t_env *env, t_var *var_new, int index);
void	    shift_index_env(t_env *stack);
void		set_env_list(t_main *main, char **envp);
void  		print_var(t_env env);
void		set_env_arr(t_main *main);


#endif
