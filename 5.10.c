/* vim: set sw=4 ts=4:
 * Author: Liu DongMiao <liudongmiao@gmail.com>
 * Created  : Thu 09 Aug 2012 08:27:43 PM CST
 * Modified : Mon 13 Aug 2012 03:05:10 PM CST
 */

/*
 * Write the program ``expr'', which evaluates a reverse Polish expression from
 * the command line, where each operator or operand is a separate argument. For
 * example,
 * 	``expr 2 3 4 + *''
 * evaluates 2 * (3 + 4).
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXOP 100
#define NUMBER '0'

int getop(char [], char *);
void push(double);
double pop(void);

/* reverse Polish calculator */
int main(int argc, char *argv[])
{
	double op2;
	char s[MAXOP];

	while (*++argv) {
		switch (getop(s, *argv))  {
			case NUMBER:
				push(atof(s));
				break;
			case '+':
				push(pop() + pop());
				break;
			case '*':
				push(pop() * pop());
				break;
			case '-':
				op2 = pop();
				push(pop() - op2);
				break;
			case '/':
				op2 = pop();
				if (op2 != 0.0)
					push(pop() / op2);
				else
					printf("error: zero divisor\n");
				break;
			case '%':
				op2 = pop();
				if ((int)op2 != 0)
					push((int)pop() % (int)op2);
				else
					printf("error: zero modulus\n");
				break;
			default:
				printf("error: unknown command %s\n", s);
				break;
		}
	}
	printf("%.8g\n", pop());
	return 0;
}

#define MAXVAL 100	/* maximum depth of val stack */
int sp = 0;			/* next free stack position */
double val[MAXVAL];	/* value stack */

/* push: push f onto value stack */
void push(double f)
{
	if (sp < MAXVAL)
		val[sp++] = f;
	else
		printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void)
{
	if (sp > 0)
		return val[--sp];
	else {
		printf("error: stack empty\n");
		return 0.0;
	}
}

/* getop: get next character or numeric operand */
int getop(char s[], char *line)
{
	int i, c;
	while ((s[0] = c = *line++) == ' ' || c == '\t')
		;
	s[1] = '\0';
	if (!isdigit(c) && c != '.' && c != '-')
		return c;
	i = 0;
	if (c == '-') {
		c = *line++;
		if (!isdigit(c) && c != '.') {
			return '-';
		}
		s[++i] = c;
	}
	if (isdigit(c))		/* collect integer part */
		while (isdigit(s[++i] = c = *line++))
			;
	if (c == '.')		/* collect fraction part */
		while (isdigit(s[++i] = c = *line++))
			;
	s[i] = '\0';
	return NUMBER;
}
