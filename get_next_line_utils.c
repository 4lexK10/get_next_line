/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 15:50:04 by marvin            #+#    #+#             */
/*   Updated: 2023/12/04 15:50:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "get_next_line.h"

char	*ft_strjoin(char const *s1, char const *s2, int i_nl)
{
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	j = 0;
	str = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		++i;
	}
	while (s2[j] != '\0')
	{
		str[i + j] = s2[j];
		++j;
	}
	str[i + j] = '\0';
	return (str);
}

char	*ft_strdup(char const *s, int i_nl)
{
	char	*str;
	int		i;

	i = 0;
	if (i_nl > 0)
		while (s[i + i_nl] != '\0')
			++i;
	else
		while (s[i] != '\0')
			++i;
	str = (char *)malloc((size_t)(1 + i) * sizeof(char));
	if (!str)
		return (NULL);
	if (i_nl > 0)
		i = i_nl;
	else
		i = 0;
	while (s[i] != '\0')
	{
		str[i] = s[i];
		++i;
	}
	str[i] = '\0';
	return (str);
}

t_list	*lstnew(char *buf, int fd)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->cnt = read(fd, buf, BUFFER_SIZE);
	if (new_node->cnt < 0)
		return (free(new_node), NULL);
	if (new_node->cnt == 0 || new_node->cnt < BUFFER_SIZE)
		new_node->status = 1;
	new_node->status = 0;
	new_node->content = ft_strdup(buf, 0);
	if (!new_node->content)
		return (free(new_node), NULL);
	new_node->i_nl = find_next_line(new_node->content);
	new_node->nl = new_node->content + new_node->i_nl;
	if (new_node->i_nl == -1)
		new_node->nl = NULL;
	new_node->next = NULL;
	return (new_node);
}

void	ft_lstclear(t_list **lst)
{
	t_list	*temp;
	t_list	*prev;

	temp = *lst;
	*lst = NULL;
	while (temp != NULL)
	{
		prev = temp;
		temp = temp->next;
		free(prev->content);
		free(prev);
	}
}

int	ft_lstadd_back(t_list **lst, int fd)
{
	t_list	*temp;
	t_list	*new;
	char	*buf;

	temp = *lst;
	while (temp->next != NULL)
		temp = temp->next;
	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (1);
	new = ft_lstnew(buf, fd);
	temp->next = new;
	return (0);
}
