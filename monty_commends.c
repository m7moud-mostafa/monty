#include "monty.h"

/**
 * my_atoi - my own atoi function
 * @arg: string to integer
 * Return: integer or zero when failure
 */
int my_atoi(char *arg)
{
	int n = 0;
	int length;
	char sign = 1;
	int i = 0;

	length = strlen(arg) - 1;
	if (arg[0] == '-')
		sign = -1;

	for (; length >= 0; length--)
	{
		if (!(arg[length] <= '9' && arg[length] >= '0'))
		{
			if (!(length == 0 && sign == -1 && arg[length] == '-'))
				return (-1);
		}
		if (sign == -1 && length == 0)
			n = -1 * n;
		else
		{
			n += i * (arg[length] - 48);
			i *= 10;
		}
	}
	return (n);
}

/**
 * pop - removes top element from the slack
 * @stack: Double pointer to the top of the stack
 * @line_number: Line number of the current operation
 */
void pop(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp;

	if (!stack || !(*stack))
	{
		fprintf(stderr, "L%i: can't pop an empty stack\n", line_number);
		exit(EXIT_FAILURE);
	}

	tmp = *stack;
	*stack = tmp->next;
	if (tmp->next)
		(*stack)->prev = NULL;
	free(tmp);
}

/**
 * swap - sqaps top two elements in the slack
 * @stack: Double pointer to the top of the stack
 * @line_number: Line number of the current operation
 */
void swap(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp;

	if (!stack || !(*stack) || !((*stack)->next))
	{
		fprintf(stderr, "L%i: can't swap, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}

	tmp = *stack;
	*stack = (*stack)->next;
	tmp->next = (*stack)->next;
	(*stack)->prev = tmp;
	tmp->prev = NULL;
	(*stack)->next = tmp;

	if (tmp->next)
		tmp->next->prev = tmp;

}
