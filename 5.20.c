/* vim: set sw=4 ts=4:
 * Author: Liu DongMiao <liudongmiao@gmail.com>
 * Created  : Tue 14 Aug 2012 03:45:46 PM CST
 * Modified : Tue 14 Aug 2012 04:02:14 PM CST
 */

/*
 * Expand ``dcl'' to handle declarations with function argument types,
 * qualifiers like ``const'', and so on.
 */

#undef UNDCL

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100
enum { NAME, PARENS, BRACKETS };

void dcl(void);
void dirdcl(void);

int gettoken(void);
int tokentype;				/* type of last token */
char token[MAXTOKEN];		/* last token string */
char name[MAXTOKEN];		/* identifier name */
char datatype[MAXTOKEN];	/* data type = char, int, etc. */
char out[1000];

#ifdef UNDCL
/* undcl: convert word descriptions to to declarations */
int main()
{
	int type;
	char temp[MAXTOKEN];

	while (gettoken() != EOF) {
		strcpy(out, token);
		while ((type = gettoken()) != '\n')
			if (type == PARENS || type == BRACKETS)
				strcat(out, token);
			else if (type == '*') {
				sprintf(temp, "*%s", out);
				strcpy(out, temp);
			} else if (type == NAME) {
				sprintf(temp, "%s %s", token, out);
				strcpy(out, temp);
			} else {
				printf("invalid input at %s\n", token);
				continue;
			}
		printf("%s\n", out);
	}
	return 0;
}
#else
int main()	/* convert declaration to words */
{
	while (gettoken() != EOF) {		/* 1st token on line */
		strcpy(datatype, token);	/* is the datatype */
		out[0] = '\0';
		dcl();						/* parse rest of line */
		if (tokentype != '\n') {
			printf("syntax error\n");
			continue;
		}
		printf("%s: %s %s\n", name, out, datatype);
	}
	return 0;
}
#endif

int gettoken(void)		/* return next token */
{
	int c, getch(void);
	void ungetch(int);

	char *p = token;
	while ((c = getch()) == ' ' || c == '\t')
		;
	if (c == '(') {
		if ((c = getch()) == ')') {
			strcpy(token, "()");
			return tokentype = PARENS;
		} else {
			if (c == '*') {
				ungetch(c);
				return tokentype = '(';
			}
			*p++ = '(';
			for (*p++ = c; p - token < MAXTOKEN && (*p++ = getch()) != ')'; )
				;
			*p = '\0';
			return tokentype = PARENS;
		}
	} else if (c == '[') {
		for (*p++ = c; (*p++ = getch()) != ']'; )
			;
		*p = '\0';
		return tokentype = BRACKETS;
	} else if (isalpha(c)) {
		for (*p++ = c; isalnum(c = getch()); )
			*p++ = c;
		*p = '\0';
		ungetch(c);
		return tokentype = NAME;
	} else
		return tokentype = c;
}

/* dcl: parse a declarator */
void dcl(void)
{
	int ns;
	for (ns = 0; gettoken() == '*'; )	/* count *'s */
		ns++;
	dirdcl();
	while (ns-- > 0)
		strcat(out, " pointer to");
}

/* dirdcl: parse a direct declarator */
void dirdcl(void)
{
	int type;

	if (tokentype == '(') {		/* ( dcl ) */
		dcl();
		if (tokentype != ')') {
			printf("error: missing )\n");
			return;
		}
	} else if (tokentype == NAME)	/* variable name */
		strcpy(name, token);
	else {
		printf("error: expected name or (dcl)\n");
		return;
	}
	while ((type = gettoken()) == PARENS || type == BRACKETS)
		if (type == PARENS) {
			strcat(out, " function");
			strcat(out, token);
			strcat(out, " returing");
		} else {
			strcat(out, " array");
			strcat(out, token);
			strcat(out, " of");
		}
}

int buf = EOF;
int getch(void)
{
	int tmp = buf;
	buf = EOF;
	return (tmp != EOF) ? tmp : getchar();
}

void ungetch(int c)
{
	if (buf != EOF) {
		printf("ungetch: too many characters\n");
	} else {
		buf = c;
	}
}
