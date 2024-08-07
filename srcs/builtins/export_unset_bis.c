/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset_bis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmoreno <shmoreno@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:37:33 by shmoreno          #+#    #+#             */
/*   Updated: 2024/07/25 18:29:57 by shmoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Set the environment variable if the value is not empty
void	ft_setenv_if_v_env(t_parsing *parsing, int j)
{
	char	*tmp_equal;

	tmp_equal = NULL;
	if (parsing->v_senv != NULL)
	{
		tmp_equal = ft_strjoin(parsing->n_senv, "=");
		malloc_error_ptr(tmp_equal, "malloc : ft_setenv_last");
		parsing->tmp_setenv[j] = ft_strjoin(tmp_equal, parsing->v_senv);
		malloc_error_ptr(parsing->tmp_setenv[j], "malloc : ft_setenv_last");
		free(tmp_equal);
	}
	else
	{
		parsing->tmp_setenv[j] = ft_strdup(parsing->n_senv);
		malloc_error_ptr(parsing->tmp_setenv[j], "malloc : ft_setenv_last");
	}
}

// Add an environment variable if it doesn't exist
// So it basically does envp + 1 and adds the variable
void	ft_setenv_last(char **envp, t_parsing *parsing, int i)
{
	static int	j;

	if (parsing->tmp_setenv == NULL)
	{
		parsing->tmp_setenv = malloc(sizeof(char *)
				* (parsing->count_envp + 2));
		malloc_error_dbl_ptr(parsing->tmp_setenv, "malloc : ft_setenv_last");
	}
	ft_setenv_if_v_env(parsing, j);
	parsing->tmp_setenv[j + 1] = NULL;
	envp[i + 1] = parsing->tmp_setenv[j];
	envp[i + 2] = NULL;
	j++;
}

void	ft_envp_external(t_parsing *parsing, char **envp, int i)
{
	char	*tmp_equal;
	char	*tmp;
	int		j;

	j = 0;
	while (parsing->tmp_setenv[j] != NULL)
	{
		if (ft_strncmp(envp[i], parsing->tmp_setenv[j],
				ft_strlen(parsing->tmp_setenv[j])) == 0)
		{
			tmp_equal = ft_strjoin(parsing->n_senv, "=");
			tmp = ft_strjoin(tmp_equal, parsing->v_senv);
			free(tmp_equal);
			free(parsing->tmp_setenv[j]);
			parsing->tmp_setenv[j] = ft_strdup(tmp);
			free(tmp);
			envp[i] = parsing->tmp_setenv[j];
			break ;
		}
		j++;
	}
}

void	ft_setenv_bis(t_parsing *parsing, char **envp, int i, char *tmp_equal)
{
	char	*tmp_last;

	tmp_last = NULL;
	if (parsing->v_senv != NULL)
	{
		if (i < parsing->count_envp)
		{
			tmp_equal = ft_strjoin(parsing->n_senv, "=");
			malloc_error_ptr(tmp_equal, "malloc : ft_setenv_bis");
			tmp_last = ft_strjoin(tmp_equal, parsing->v_senv);
			malloc_error_ptr(tmp_last, "malloc : ft_setenv_bis");
			ft_strlcpy(envp[i], tmp_last, ft_strlen(tmp_last) + 1);
			free(tmp_last);
			free(tmp_equal);
		}
		else
		{
			ft_envp_external(parsing, envp, i);
		}
	}
	else
		ft_strlcpy(envp[i], parsing->n_senv, ft_strlen(parsing->n_senv) + 1);
}

// Base function that groups the different cases of setenv
// If the variable already exists, modify it
// If the variable doesn't exist, create it
int	ft_setenv(char **envp, t_parsing *parsing)
{
	char	*tmp;
	int		i;

	i = -1;
	tmp = NULL;
	while (envp[++i] != NULL)
	{
		if (!ft_strncmp(envp[i], parsing->n_senv, ft_strlen(parsing->n_senv)))
		{
			tmp = ft_strnstr(envp[i], "\n", ft_strlen(envp[i]));
			if (tmp != NULL)
				ft_memmove(envp[i], tmp + 1, ft_strlen(tmp) - 1);
			ft_setenv_bis(parsing, envp, i, tmp);
			parsing->exit_value = 0;
			return (0);
		}
		else if (envp[i + 1] == NULL)
			return (parsing->exit_value = 0,
				ft_setenv_last(envp, parsing, i), 0);
	}
	return (-1);
}
