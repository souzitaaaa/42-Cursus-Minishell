/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jede-ara <jede-ara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 12:47:14 by rimarque          #+#    #+#             */
/*   Updated: 2023/10/24 15:09:18 by jede-ara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVP_H
# define ENVP_H

# include "minishell.h"

/*
!ENVP
*/
t_var		*var_node(char *var);
void		add_var(t_env *env, t_var *var_new, int index);
void		shift_index_env(t_env *stack);
void		set_env_list(t_main *main, char **envp);
void		print_var(t_env env);
void		set_env_arr(t_main *main);

#endif
