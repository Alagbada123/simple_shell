#include "shell.h"

/**
 * _myhistory - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *str)
{
	char *d, a;
	int p;

	d = _strchr(str, '=');
	if (!d)
		return (1);
	a = *d;
	*d = 0;
	p = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*d = a;
	return (p);
}

/**
 * set_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *d;

	d = _strchr(str, '=');
	if (!d)
		return (1);
	if (!*++d)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *a = NULL, *d = NULL;

	if (node)
	{
		a = _strchr(node->str, '=');
		for (d = node->str; d <= a; d++)
			_putchar(*d);
		_putchar('\'');
		_puts(a + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myalias(info_t *info)
{
	int p = 0;
	char *d = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (p = 1; info->argv[p]; p++)
	{
		d = _strchr(info->argv[p], '=');
		if (d)
			set_alias(info, info->argv[p]);
		else
			print_alias(node_starts_with(info->alias, info->argv[p], '='));
	}

	return (0);
}
