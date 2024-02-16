/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarunota <jarunota@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 22:29:19 by jarunota          #+#    #+#             */
/*   Updated: 2024/02/16 15:52:43 by jarunota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

//calculates the length

size_t	ft_strlen(const char	*s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

//searches for the first occurrence of the character

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (unsigned char)c)
		return ((char *)s);
	return (NULL);
}

//duplicates

char	*ft_strdup(const char *s1)
{
	char	*str;
	size_t	len;
	size_t	i;

	len = ft_strlen(s1);
	str = (char *)malloc(len + 1);
	i = 0;
	if (!str)
		return (NULL);
	if (len + 1 > 0)
	{
		while (s1[i] && i < len)
		{
			str[i] = s1[i];
			i++;
		}
		str[i] = '\0';
	}
	return (str);
}

//connect two strings

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	size_s1;	
	char	*tab;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	size_s1 = ft_strlen(s1);
	tab = (char *)malloc(size_s1 + ft_strlen(s2) + 1);
	if (!tab)
		return (NULL);
	while (s1[i])
	{
		tab[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		tab[size_s1 + i] = s2[i];
		i++;
	}
	tab[size_s1 + i] = '\0';
	return (tab);
}

//creates a substring 

char	*ft_substr(char const *s, size_t start, size_t len)
{
	char	*str;
	size_t	i;

	if (!s || start >= ft_strlen(s) || !*s)
		return (NULL);
	if (ft_strlen(s) - start < len)
		len = ft_strlen(s) - start;
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
