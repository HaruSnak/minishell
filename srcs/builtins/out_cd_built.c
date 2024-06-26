

#include "../../includes/minishell.h"

void	ft_handle_cd_home(t_parsing *parsing,
	char **envp)
{
	if (chdir(getenv("HOME")) == 0)
	{
		parsing->n_senv = "OLDPWD";
		parsing->v_senv = ft_strdup(getenv("PWD"));
		ft_setenv(envp, parsing);
		free(parsing->v_senv);
		parsing->n_senv = "PWD";
		parsing->v_senv = ft_strdup(getenv("HOME"));
		ft_setenv(envp, parsing);
		free(parsing->v_senv);
		parsing->exit_value = 0;
	}
	else
	{
		printf("minishell: cd: ~: No such file or directory\n");
		parsing->exit_value = 1;
	}
}

void	ft_handle_cd_previous(t_parsing *parsing,
	char **envp)
{
	char	*path;

	if (chdir("..") == 0)
	{
		parsing->v_senv = ft_strdup(getenv("PWD"));
		if (ft_strncmp(parsing->v_senv, "/", ft_strlen(parsing->v_senv)) == 0)
			path = ft_strdup("/");
		else
			path = ft_split_input(parsing->v_senv, "/");
		parsing->n_senv = "OLDPWD";
		ft_setenv(envp, parsing);
		free(parsing->v_senv);
		parsing->n_senv = "PWD";
		parsing->v_senv = ft_strdup(path);
		ft_setenv(envp, parsing);
		free(parsing->v_senv);
		free(path);
		parsing->exit_value = 0;
	}
	else
	{
		printf("minishell: cd: ..: No such file or directory\n");
		parsing->exit_value = 1;
	}
}

void	ft_handle_cd_root(t_parsing *parsing,
	char **envp)
{
	if (chdir("/") == 0)
	{
		parsing->n_senv = "OLDPWD";
		parsing->v_senv = getenv("PWD");
		ft_setenv(envp, parsing);
		parsing->n_senv = "PWD";
		parsing->v_senv = "/";
		ft_setenv(envp, parsing);
		parsing->exit_value = 0;
	}
	else
	{
		printf("minishell: cd: /: No such file or directory\n");
		parsing->exit_value = 1;
	}
}

void	ft_handle_cd_oldpwd(t_parsing *parsing,
	char **envp, char *path, char *oldpwd)
{
	if (chdir(getenv("OLDPWD")) == 0)
	{
		path = ft_strdup(getenv("OLDPWD"));
		oldpwd = ft_strdup(getenv("PWD"));
		parsing->pwd = path;
		parsing->n_senv = "OLDPWD";
		parsing->v_senv = oldpwd;
		ft_setenv(envp, parsing);
		parsing->n_senv = "PWD";
		parsing->v_senv = path;
		ft_setenv(envp, parsing);
		free(path);
		free(oldpwd);
		parsing->exit_value = 0;
	}
	else
	{
		printf("minishell: cd: %s: No such file or directory\n", oldpwd);
		parsing->exit_value = 1;
	}
}

void	ft_handle_cd_path(t_parsing *parsing, char **envp)
{
	if (chdir(parsing->tkn[1]) == 0)
	{
		parsing->n_senv = "OLDPWD";
		parsing->v_senv = parsing->pwd;
		ft_setenv(envp, parsing);
		parsing->n_senv = "PWD";
		parsing->v_senv = malloc(sizeof(char) * 1000);
		getcwd(parsing->v_senv, 1000);
		ft_setenv(envp, parsing);
		free(parsing->v_senv);
		parsing->exit_value = 0;
	}
	else
	{
		printf("minishell: cd: %s: No such file or directory\n",
			parsing->tkn[1]);
		parsing->exit_value = 1;
	}
}
