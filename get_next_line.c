/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akloster <akloster@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:53:40 by akloster          #+#    #+#             */
/*   Updated: 2023/12/05 12:53:40 by akloster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	int	clean(t_list **head)
{
	t_list	*current;
	t_list	*prev;
	t_list	*temp;

	temp = *head;
	current = *head;
	while (current->next != NULL && current->nl == NULL
	&& current->i_nl + 1 == BUFFER_SIZE)
	{
		prev = current;
		current = current->next;
	}
	if (current != *head)
	{
		prev->next = NULL;
		*head = current;
		ft_lstclear(&temp);
	}
	free(current->content);
	if (current->nl != NULL && current->nl[1] != '\0')
		current->content = ft_strdup(current->nl + 1, 0);
	if (!current->content)
		return (1);
	current->nl += find_next_line(current->content) + 1;
	return (0);
}

static char	*gnl(t_list **head)
{
	t_list	*temp;
	char	*str;

	temp = *head;
	str = ft_strdup(temp->content, temp->i_nl);
	if (!str)
		return (ft_lstclear(head), NULL);
	temp = temp->next;
	while (temp->i_nl > 0 && temp != NULL)
	{
		str = ft_strjoin(str, temp->content, temp->i_nl);
		if (!str)
			return (ft_lstclear(head), NULL);
		temp = temp->next;
	}
	if (clean(head))
		return (ft_lstclear(head), NULL);
	return (str);
}

char	*get_next_line(int fd)
{
	static t_list	*head;
	t_list			*temp;
	char			*buf;
	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(BUFFER_SIZE));
	if (!buf)
		return (NULL);
	buf[BUFFER_SIZE] = '\0';
	head = ft_lstnew(buf, fd);
	free(buf);
	if (!head)
		return (NULL);
	temp = head;
	while (temp->cnt > 0)
	{
		if (ft_lstadd_back(&head, fd))
			return (ft_lstclear(&head), NULL);
		temp = temp->next;
		printf("temp->cnt: |%d|", temp->cnt);
	}
	// printf("test\n");
	return (gnl(&head));
}

int	ft_strlen(char const *s)
{
	int	i;

	i = 0;
	while(s[i] != '\0')
		++i;
	return (i);
}

int	find_next_line(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\n' && s[i] != '\0' && s[i] != EOF)
		++i;
	if (s[i] == '\0' || s[i] == EOF)
		return (-1);
	return (i);
}
