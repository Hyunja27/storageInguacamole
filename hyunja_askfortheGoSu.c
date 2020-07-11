/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush-01.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spark <spark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 14:57:08 by spark             #+#    #+#             */
/*   Updated: 2020/07/12 01:58:35 by spark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int		**g_retmt;

int	num_check(int x, int y, int value);

int row_check(int y, int len)
{
	int top;
	int cnt;
	int index;

	index = 1;
	top = 0;
	cnt = 0;
	printf("row check start\n");
	while(index <= len)
	{
		if(g_retmt[y][index] > top)
		{
			top = g_retmt[y][index];
			cnt++;
		}
		index++;
	}
	if (cnt != g_retmt[y][0])
		return (0);
	index = len;
	top = 0;
	cnt = 0;
	while(index >= 1)
	{
		if(g_retmt[y][index] > top)
		{
			top = g_retmt[y][index];
			cnt++;
		}
		index--;
	}
	if (cnt != g_retmt[y][len + 1])
		return (0);
	printf("row check end\n");
	return (1);
}

int col_check(int x, int len)
{
	int top;
	int cnt;
	int index;

	index = 1;
	top = 0;
	cnt = 0;
	printf("col check start\n");
	while(index <= len)
	{
		if(g_retmt[index][x] > top)
		{
			top = g_retmt[index][x];
			cnt++;
		}
		index++;
	}
	if (cnt != g_retmt[index][x])
		return (0);
	index = len;
	top = 0;
	cnt = 0;
	while(index >= 1)
	{
		if(g_retmt[index][x] > top)
		{
			top = g_retmt[index][x];
			cnt++;
		}
		index--;
	}
	if (cnt != g_retmt[index][x])
		return (0);
	printf("col check end\n");
	return (1);
}


int		insert(int n, int index)
{
	int value;
	int result;
	int x;
	int y;

	x = (index % n) + 1; 
	y = (index / n) + 1;
	if(index == n*n)
		return 1;
	value = 0;
	while (value < n)
	{
		value++;
		if (num_check(y, x, value))
			continue;
		g_retmt[y][x] = value;
		if (x == n && !row_check(y, n))
			continue;
		if (y == n && !col_check(x, n))
			continue;
		result = insert(n, index + 1);
		if (result == 1)
			return (1);
	}
	if (result == 0)
		g_retmt[y][x] = 0;
	return (0);
}

int	num_check(int y, int x, int value)
{
	int index;

	printf("val to insert is :[%d]\n",value);
	index = 1;
	while (index < x)
	{
		if(value == g_retmt[y][index])
			return (1);
		index++;
	}	
	index = 1;
	while (index < y)
	{
		if(value == g_retmt[index][x])
			return (1);
		index++;
	}
	return (0);
}


int	num_cnt(char *str)
{
	int cnt;

	cnt = 0;
	while (*str)
	{
		if (*str != ' ')
			cnt++;
		str++;
	}

	return (cnt);
}

void	init_matrix(int len, char *arr)
{
	int i;
	int j;

	i = 1;
	j = 0;
	while ( i < len - 1)
	{
		g_retmt[0][i++] = (int)*(arr + j) - 48;
		j += 2;
	}
	i = 1;
	while ( i < len - 1)
	{
		g_retmt[len - 1][i++] = (int)*(arr + j) - 48;
		j += 2;
	}
	i = 1;
	while ( i < len - 1)
	{
		g_retmt[i++][0] = (int)*(arr + j) - 48;
		j += 2;
	}
	i = 1;
	while ( i < len - 1)
	{
		g_retmt[i++][len - 1] = (int)*(arr + j) - 48;
		j += 2;
	}
}

int	main(int ac, char **av)
{
	int len;
	int row_index;
	int col_index;
	int test1;
	int test2;

	test1 = 0;
	test2 = 0;
	row_index = 0;
	col_index = 0;
	len = num_cnt(av[1]);
	printf("num_cunt : [%d]\n",len);
	len = (num_cnt(av[1]) / 4) + 2;
	printf("len : [%d]\n",len - 2);
	printf("ac  : [%d]\n",ac);
	g_retmt = (int**)malloc(sizeof(int*) * (len));
	while (col_index < len)
		g_retmt[col_index++] = (int*)malloc(sizeof(int) * (len));	
	col_index = 0;
	while (col_index < len)
	{
		while (row_index < len)
		{
			g_retmt[col_index][row_index] = 0;
			row_index++;
		}
		col_index++;
		row_index = 0;
	}
	init_matrix(len, av[1]);
	insert(len - 2, 0);
	
	while (test1 < len)
	{
		while (test2 < len)
		{
			if (g_retmt[test1][test2] != 0)
				printf("%d ",g_retmt[test1][test2]);
			else
				printf("  ");
			test2++;
		}
		printf("\n");
		test2 = 0;
		test1++;
	}
}
