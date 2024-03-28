#include "monty.h"


/**
 * main - Entry point for Monty bytecode interpreter
 * @argc: Argument count
 * @argv: Argument vector
 * Return: EXIT_SUCCESS on success, or EXIT_FAILURE on failure
 */
int main(int argc, char **argv)
{
	FILE *file;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	unsigned int line_number = 0;
	stack_t *stack = NULL;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\\n");
		exit(EXIT_FAILURE);
	}

	file = fopen(argv[1], "r");
	if (!file)
	{
		fprintf(stderr, "Error: Can't open file %s\\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	while ((read = getline(&line, &len, file)) != -1)
	{
		line_number++;
		execute_line(line, &stack, line_number);
	}

	free(line);
	fclose(file);

	/* Free stack */
	while (stack != NULL)
	{
		stack_t *temp = stack;

		stack = stack->next;
		free(temp);
	}

	return (0);
}

/**
 * execute_line - Executes an opcode
 * @line: Line from the file
 * @stack: Double pointer to the top of the stack
 * @line_number: Current line number
 */
void execute_line(char *line, stack_t **stack, unsigned int line_number)
{
	char *opcode;
	char *arg;

	opcode = strtok(line, " \n");
	arg = strtok(NULL, " \n");

	if (opcode == NULL)
		return;

	if (strcmp(opcode, "push") == 0)
	{
		push(stack, arg, line_number);
	}
	else if (strcmp(opcode, "pall") == 0)
	{
		pall(stack, line_number);
	}

}


/**
 * pall - Prints all the values on the stack
 * @stack: Double pointer to the top of the stack
 * @line_number: Line number of the current operation (unused)
 *
 * Description: Prints all values on the stack, starting from the top
 */
void pall(stack_t **stack, unsigned int line_number)
{
	stack_t *temp = *stack;

	(void)line_number;

	while (temp != NULL)
	{
		printf("%d\\n", temp->n);
		temp = temp->next;
	}
}

/**
 * push - Pushes an element to the stack
 * @stack: Double pointer to the top of the stack
 * @line_number: Line number of the current operation
 * @arg: argument
 * Description: Pushes an integer onto the stack
 */
void push(stack_t **stack, char *arg, unsigned int line_number)
{
	int num;
	stack_t *new_node;

	num = atoi(arg);
	if (arg == NULL || (arg[0] != '0' && num == 0))
	{
		fprintf(stderr, "L%d: usage: push integer\\n", line_number);
		exit(EXIT_FAILURE);
	}

	new_node = malloc(sizeof(stack_t));
	if (new_node == NULL)
	{
		fprintf(stderr, "Error: malloc failed\\n");
		exit(EXIT_FAILURE);
	}

	new_node->n = num;
	new_node->prev = NULL;
	new_node->next = *stack;

	if (*stack != NULL)
		(*stack)->prev = new_node;

	*stack = new_node;
}
