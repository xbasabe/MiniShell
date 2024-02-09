#include "minishell.h"

char	*active_dir(void)
{
	t_env	*env;

	env = g_shell.env;
	while (env)
	{
		if (str_cmp(env->name, "PWD") == 0)
			return (env->val);
		env = env->next;
	}
	return (env->val);
}

char	*home_dir(void)
{
	t_env	*env;

	env = g_shell.env;
	while (env)
	{
		if (str_cmp(env->name, "HOME") == 0)
		{
			printf("cd -ir a HOME- %s", env->val);
			return (env->val);
		}
		env = env->next;
	}
	return (env->val);
}

char	*old_dir(void)
{
	t_env	*env;

	env = g_shell.env;
	while (env)
	{
		if (str_cmp(env->name, "OLDPWD") == 0)
			return (env->val);
		env = env->next;
	}
	return (env->val);
}

int	init_cd(char *input, t_stack *node)
{
	(void) input;
	if (node->pipe.arg[0] == NULL)
		node->pipe.arg[0] = home_dir();
	else if (node->pipe.arg[0])
	{
		if (node->pipe.arg[0][0] == '.' && node->pipe.arg[0][1] == '/')
			expand_relative(node);
		if (node->pipe.arg[0][0] == '.' && node->pipe.arg[0][1] == '.' && node->pipe.arg[0][2] == '/')
			expand_relative2(node);
		if (strcmp(node->pipe.arg[0], "-") == 0 && !node->pipe.arg[1])
			node->pipe.arg[0] = old_dir();
	}
	else if (node->pipe.arg[2] != NULL)
	{
		fd_putstr_out("-Minishell: cd: too many arguments\n", node);
		g_shell.num_quit = 1;
		return (1);
	}
	return (0);
}

void	update_pwd(t_stack *node) //modifica en envi no pasa a sistema para los no built in
{
	t_env	*env;

	env = g_shell.env;
	if (access((const char *)node->pipe.arg[0], F_OK) == -1) //comprobar que hay acceso al directorio y si es archivo? mensaje de arg[0] no es un directorio
	{
		printf("-Minishell: cd: %s: No such file or directory\n", node->pipe.arg[0]);
		//printf("-Minishell: cd: %s: %s\n", node->pipe.arg[0], errno);
		g_shell.num_quit = 1;
		return ;
	}
	while (env)
	{
		if (str_cmp(env->name, "PWD") == 0)
		{
			env->val = node->pipe.arg[0];
			chdir((const char *)node->pipe.arg[0]);
			break ;
		}
		env = env->next;
	}
}

void	update_oldpwd(char *old_dir) //modifica en envi no pasa a sistema para los no built in
{
	t_env	*env;

	env = g_shell.env;
	while (env)
	{
		if (str_cmp(env->name, "OLDPWD") == 0)
		{
			env->val = old_dir;
			break ;
		}
		env = env->next;
	}
}

void	expand_relative(t_stack *node)
{
	char	*exp_dir;

	exp_dir = active_dir();
	node->pipe.arg[0]++;
	exp_dir = stradd(exp_dir, node->pipe.arg[0]);
	node->pipe.arg[0] = exp_dir;
}

void	expand_relative2(t_stack *node)
{
	char	*exp_dir;
	char	*tmp;
	int		i;

	exp_dir = active_dir();
	i = ft_strlen(exp_dir);
	while (exp_dir[i] != '/')
		i--;
	tmp = (char *)malloc(sizeof(char) * (i + 2));
	tmp[i + 1] = '\0';
	while (i >= 0)
	{
		tmp[i] = exp_dir[i];
		i--;
	}
	node->pipe.arg[0]++;
	node->pipe.arg[0]++;
	node->pipe.arg[0]++;
	exp_dir = tmp;
	exp_dir = stradd(exp_dir, node->pipe.arg[0]);
	node->pipe.arg[0] = exp_dir;
}

void	cd(char *input, t_stack *node)
{
	t_env	*env;
	char	*old_dir;

	env = g_shell.env;
	old_dir = NULL;
	while (env)
	{
		if (str_cmp(env->name, "PWD") == 0)
		{
			old_dir = ft_strdup(env->val);
			break ;
		}
		env = env->next;
	}
	if (init_cd(input, node) == 0)
		update_pwd(node);
	update_oldpwd(old_dir);
	if (old_dir)
		free(old_dir);
}
