#include "monty.h"


/**
 * main - Entry point for Monty bytecode interpreter
 * @argc: Argument count
 * @argv: Argument vector
 * Return: EXIT_SUCCESS on success, or EXIT_FAILURE on failure
 */
int main(int argc, char **argv)
{
	char line[MAX_LINE_LENGTH];
	FILE *stream;
	unsigned int line_number = 1;
	stack_t *stack = NULL;


	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}

	stream = fopen(argv[1], "r");
	if (stream == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	while (fgets(line, sizeof(line), stream) != NULL)
	{
		/* Here write the code to execute the line */
		execute_line(line, line_number, &stack);
		line_number++;
	}

	fclose(stream);

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
 * Return: -1 when failure
 */
int execute_line(char *line, unsigned int line_number, stack_t **stack)
{
	char *opcode;
	char *arg;
	int i = 0;
	instruction_t instructions[] = {
								{"pall", pall},
								{NULL, NULL}
	};

	opcode = strtok(line, " \n");
	arg = strtok(NULL, " \n");

	if (opcode == NULL)
		return (0);

	if (strcmp(opcode, "push") == 0)
	{
		push(stack, arg, line_number);
		return (0);
	}

	while (instructions[i].opcode != NULL)
	{
		if (strcmp(instructions[i].opcode, opcode) == 0)
		{
			instructions[i].f(stack, line_number);
			return (0);
		}
		i++;
	}
	fprintf(stderr, "L%i: unknown instruction %s\n", line_number, opcode);
	exit(EXIT_FAILURE);
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
	stack_t *ptr;

	(void)line_number;
	if (!stack || !(*stack))
		return;

	ptr = *stack;
	while (ptr)
	{
		printf("%i\n", ptr->n);
		ptr = ptr->next;
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
	int int_arg;
	stack_t *h;
	int i;

	if (!arg)
	{
		fprintf(stderr, "L%i: usage: push integer\n", line_number);
		exit(EXIT_FAILURE);
	}

	for (i = 0; arg[i] != '\0'; i++)
	{
		if (!(arg[i] >= '0' && arg[i] <= '9'))
		{
			fprintf(stderr, "L%i: usage: push integer\n", line_number);
			exit(EXIT_FAILURE);
		}
	}

	int_arg = atoi(arg);
	if (int_arg == 0 && arg[0] != '0')
	{
		fprintf(stderr, "L%i: usage: push integer\n", line_number);
		exit(EXIT_FAILURE);
	}

	h = malloc(sizeof(stack_t));
	if (!h)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}
	h->n = int_arg;
	h->prev = NULL;
	h->next = *stack;
	if (*stack != NULL)
	{
		(*stack)->prev = h;
	}
	*stack = h;
}
