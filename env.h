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
} t_env;

#endif