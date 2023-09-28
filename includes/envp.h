/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimarque <rimarque>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:03:50 by rimarque          #+#    #+#             */
/*   Updated: 2023/09/28 15:03:50 by rimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVP_H
# define ENVP_H

# include "minishell.h"

//!ENV_ARR
void	set_env_arr(t_main *main);

//!ENV_LIST
t_var       *var_node(const char *var);
void        add_var(t_env *env, t_var *var_new);
void	    shift_index_env(t_env *stack);
void		set_env_list(t_main *main, char **envp);
void  		print_var(t_env env);

#endif
