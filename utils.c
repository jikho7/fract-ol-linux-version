/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdefayes <jdefayes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 17:05:01 by jdefayes          #+#    #+#             */
/*   Updated: 2023/02/06 18:31:37 by jdefayes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx/mlx.h"

static int	ft_size(int nb);

int	fra_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	return (0);
}

int	fra_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*fra_itoa(int n)
{
	char	*dest;
	int		size;
	char	*temp;

	size = (ft_size(n) + 1);
	dest = malloc(sizeof(char) * size);
	if (dest == NULL)
		return (NULL);
	if (n < 0)
	{
		n = (n * -1);
		dest[size - size] = '-';
	}
	dest[size-- - 1] = '\0';
	while (n >= 1)
	{
		dest[size-- - 1] = (n % 10) + '0';
		n = n / 10;
	}
	temp = dest;
	free(dest);
	return (temp);
}

static int	ft_size(int nb)
{
	int	size;

	size = 1;
	if (nb == 0)
		return (2);
	if (nb < 0)
	{
		size++;
		nb = nb * -1;
	}
	while (nb >= 10)
	{
		nb = nb / 10;
		size++;
	}
	return (size);
}
