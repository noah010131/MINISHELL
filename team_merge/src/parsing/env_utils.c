#include "../../include/minishell.h"

t_envp	**add_envplast(t_envp **ret, char *str)
{
	t_envp	*current;
	t_envp	*new;

	if (!ret || !str)
		return (NULL);
	new = malloc(sizeof(t_envp));
	if (!new)
		return (NULL);
	new->name = ft_strlimdup(str, ft_pos_c(str, '='));
	new->value = ft_strdup(str + ft_pos_c(str, '=') + 1);
	new->next = NULL;
	new->prev = NULL;
	if (!*ret)
	{
		*ret = new;
		return (ret);
	}
	current = *ret;
	while (current->next)
		current = current->next;
	current->next = new;
	new->prev = current;
	return (ret);
}

t_envp	**add_envplast_null(t_envp **ret, char *str)
{
	t_envp	*current;
	t_envp	*new;

	if (!ret || !str)
		return (NULL);
	new = malloc(sizeof(t_envp));
	if (!new)
		return (NULL);
	new->name = ft_strdup(str);
	new->value = NULL;
	new->next = NULL;
	new->prev = NULL;
	if (!*ret)
	{
		*ret = new;
		return (ret);
	}
	current = *ret;
	while (current->next)
		current = current->next;
	current->next = new;
	new->prev = current;
	return (ret);
}

int	ft_pos_c(char *str, char c)
{
	int	i;

	i = 0;
	if (!str)
		return (-2);
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	nb_expand_hd(char *str)
{
	if (!str)
		return (-1);
	if (ft_pos_c(str, '$') > -1 && exp_exception_hd(str) > 0)
		return (1);
	return (0);
}

int	nb_expand(t_cmds *cmd)
{
	if (!cmd)
		return (-1);
	if (cmd->code_id == 20)
		return (0);
	if (ft_pos_c(cmd->name, '$') == -1)
		return (0);
	return (exp_exception(cmd->name));
}