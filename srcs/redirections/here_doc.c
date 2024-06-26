
#include "../../includes/minishell.h"

void	ft_delete_file_heredoc(void)
{
	pid_t	pid;
	char	**envp;
	int		status;

	envp = NULL;
	pid = fork();
	if (pid == 0)
		execve("/bin/rm", (char *[]){"rm", "obj/srcs/redirections/heredoc.txt",
			NULL}, envp);
	waitpid(pid, &status, 0);
}

char	*ft_find_null(char *line, char *env_var, int *i)
{
	char	*tmp_after;
	char	*tmp_before;

	tmp_after = ft_substr(line, 0, (*i));// error handling
	tmp_before = ft_strjoin(tmp_after,
			line + ft_strlen(tmp_after) + ft_strlen(env_var) + 1);// error handling
	free(line);
	line = ft_strdup(tmp_before);// error handling
	free(tmp_after);
	free(tmp_before);
	(*i) -= 1;
	return (line);
}

// Find the environment variable in the input
// Replace the environment variable with the value in the input
char	*ft_find_var_env(char *line, char **envp, int *i, char *env_var)
{
	char	*tmp_after;
	char	*tmp_env;
	char	*tmp_before;
	int		p;

	p = -1;
	while (envp[++p] != NULL)
	{
		if (ft_strncmp(envp[p], env_var, ft_strlen(env_var)) == 0)
		{
			tmp_after = ft_substr(line, 0, (*i));// error handling
			tmp_env = ft_strjoin(tmp_after, envp[p] + ft_strlen(env_var) + 1);// error handling
			tmp_before = ft_strjoin(tmp_env, line + ft_strlen(tmp_env) + 1);// error handling
			free(line);
			line = ft_strdup(tmp_before);// error handling
			free(tmp_after);
			free(tmp_env);
			free(tmp_before);
			p = -1;
			break ;
		}
	}
	if (p != -1)
		line = ft_find_null(line, env_var, i);
	return (line);
}

char	*ft_var_env(char **envp, char *line)
{
	char	*env_var;
	int		i;

	i = -1;
	while (line[++i] != '\0')
	{
		if (line[i] == '$')
		{
			env_var = ft_substr(line, i + 1,
					ft_strlen_quote(line, ' ', i + 1));// error handling
			line = ft_find_var_env(line, envp, &i, env_var);
			free(env_var);
		}
	}
	return (line);
}

void	heredoc_handling(t_exec *data, char *eof, char **g_env)
{
	char	*line;
	int		heredoc;
	int		count;

	count = 0;
	heredoc = open("obj/srcs/redirections/heredoc.txt",
			O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (ft_error_cmd_ext(heredoc, "heredoc") == -1)
		return ;
	ft_init_signal_heredoc();
	while (1)
	{
		line = readline("> ");
		count++;
		if (ft_g_signal_exit(line, heredoc) == 1)
			return ;
		if (ft_line_null_msg(line, count) == 1)
			break ;
		if (ft_strncmp(line, eof, ft_strlen(eof)) == 0)
			break ;
		ft_write_heredoc(heredoc, line, g_env, data);
		free(line);
	}
	close(heredoc);
	ft_dup_heredoc(heredoc);
	data->parsing_ptr->exit_value = 0;
}
