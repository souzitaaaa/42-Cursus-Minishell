/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jennifera <jennifera@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 14:04:00 by rimarque          #+#    #+#             */
/*   Updated: 2023/08/14 17:46:26 by jennifera        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

#include "minishell.h"

typedef struct s_var
{
    struct s_var    *prev;
    char            *var;
    int             index;
    struct s_var    *next;
} t_var;

typedef struct s_env
{
    t_var   *head;
    int     size;
    int     i;
} t_env;

#endif
