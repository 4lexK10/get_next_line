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
	while (current->next && !current->nl)
	{
		prev = current;
		current = current->next;
	}
	if (current != *head)
		prev->next = NULL;
	else
	{
		*head = current;
		ft_lstclear(&temp);
	}
	free(current->content);
	current->content = ft_strdup(current->nl + 1, 0);
	if (!current->content)
		return (1);
	return (0);
}

char	*get_next_line(int fd)
{
	static t_list	*head;
	t_list			*temp;
	char			*buf;
	char			*str;
	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(BUFFER_SIZE));
	if (!buf)
		return (NULL);
	buf[BUFFER_SIZE] = '\0';
	head = ft_lstnew(buf, fd);
	if (!head)
		return (free(buf), NULL);
	if (head->cnt == 0)
		return(free(buf), NULL);
	temp = head;
	if (temp->nl)
	{
		str = ft_strdup(temp->content, 1);
		if(!str)
			return (ft_lstclear(&head), free(buf), NULL);
		
	}
	while (temp->nl == NULL && temp->cnt > 0)
	{
		if (ft_lstadd_back(&head, fd))
			return (ft_lstclear(&head), free(buf), NULL);
		str = ft_strjoin(temp->content, temp->next->content, temp->next->i_nl);
		printf("str->|%s|\n", str);
		if (!str)
			return(ft_lstclear(&head), free(buf), NULL);
		temp = temp->next;
	}
	if (clean(&head))
		return(ft_lstclear(&head), free(buf), NULL);
	return (free(buf), str);
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
	size_t	i;

	i = 0;
	while (s[i] != '\n' && s[i] != '\0' && s[i] != EOF)
		++i;
	if (s[i] == '\0' || s[i] == EOF)
		return (-1);
	return ((int) i);
}
