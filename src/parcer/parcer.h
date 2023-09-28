/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joe <joe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 12:14:01 by joe               #+#    #+#             */
/*   Updated: 2023/09/28 12:14:45 by joe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARCER_H
# define PARCER_H

# include "minishell.h"
# include "defines.h"
# include "structs.h"

/*
!SYNTAX
*/
bool    syntax_analysis(t_main *main);

/*
!PARCER
*/
void	parcer(t_main *main);
void	test_ast(t_lexer tokens, t_ast *ast);
void	cmdcat(t_lexer *tokens);

#endif