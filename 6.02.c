/* vim: set sw=4 ts=4:
 * Author: Liu DongMiao <liudongmiao@gmail.com>
 * Created  : Tue 14 Aug 2012 09:30:29 PM CST
 * Modified : Tue 14 Aug 2012 11:01:52 PM CST
 */

/* Write a program that reads a C program and prints in alphabetical order each
 * group of variable names that are identical in the first 6 characters, but
 * different somewhere thereafter. Don't count words within strings and
 * comments. Make 6 a parameter that can be set from the command line.
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

/* getword: get next word or character from input */
int getword(char *word, int lim)
{
	int c, getch(void);
	void ungetch(int);
	char *w = word;

#ifdef ORIGINAL
	while (isspace(c = getch()))
		;
	if (c != EOF)
		*w++ = c;
	if (!isalpha(c)) {
		*w = '\0';
		return c;
	}

	for (; --lim > 0; w++)
		if (!isalnum(*w = getch())) {
			ungetch(*w);
			break;
		}
#else
	while (isspace(c = getch()))
		;
	if (c == '/') {
		if ((c = getch()) == EOF) {
			return EOF;
		} else if (c == '/') {
			while ((c = getch()) != EOF) {
				if (c == '\\') {
					if ((c = getch()) == EOF) {
						return EOF;
					}
				} else if (c == '\n') {
					break;
				}
			}
		} else if (c == '*') {
			while ((c = getchar()) != EOF) {
				if (c == '*') {
					if ((c = getch()) == EOF) {
						return EOF;
					} else if (c == '/') {
						break;
					}
				}
			}
		}
		return '\0';
	} else if (c == '"') {
		while ((c = getch()) != EOF) {
			if (c == '\\') {
				if ((c = getch()) == EOF) {
					return EOF;
				}
			} else if (c == '"') {
				break;
			}
		}
		return '\0';
	} else if (c == '\'') {
		if ((c = getchar()) == EOF) {
			return EOF;
		} else if (c == '\\') {
			if ((c = getchar()) == EOF) {
				return EOF;
			}
		}
		c = getchar();
		return '\0';
	} else if (isalpha(c) || (c == '_')) {
		*w++ = c;
		while (w - word < lim && (*w = getch()) != EOF && (isalnum(*w) || *w == '_'))
			w++;
	} else if (c == EOF) {
		return EOF;
	}
#endif
	*w = '\0';
	return word[0];
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

#define MAXWORD 100
struct tnode {				/* the tree node: */
	char *word;				/* points to the text */
	int count;				/* number of occurrences */
	struct tnode *left;		/* left child */
	struct tnode *right;	/* right child */
};
struct tnode *addtree(struct tnode *, const char *);
void treeprint(struct tnode *);
void treenprint(struct tnode *, int);
void treefree(struct tnode *);

int main(int argc, char **argv)
{
	int n = 6;
	struct tnode *root;
	char word[MAXWORD] = {0};
	root = NULL;
	if (argc > 1) {
		n = atoi(*++argv);
	}
	while (getword(word, MAXWORD) != EOF) {
		if (word[0]) {
			root = addtree(root, word);
		}
	}
	treenprint(root, n);
	treefree(root);
	return 0;
}

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, const char *w)
{
	int cond;
	if (p == NULL) {		/* a new word has arrived */
		/* make a new node */
		p = (struct tnode *)malloc(sizeof(struct tnode));
		p->word = strdup(w);
		p->count = 1;
		p->left = p->right = NULL;
	} else if ((cond = strcmp(w, p->word)) == 0)
		p->count++;			/* repeated word */
	else if (cond < 0)		/* less than into left subtree */
		p->left = addtree(p->left, w);
	else					/* greater than into right subtree */
		p->right = addtree(p->right, w);
	return p;
}

/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p)
{
	if (p != NULL) {
		treeprint(p->left);
		printf("%4d %s\n", p->count, p->word);
		treeprint(p->right);
	}
}

void treenprint(struct tnode *p, int n)
{
	static int printprev = 1;
	static struct tnode *prev;
	if (p == NULL || n == 0) {
		treeprint(p);
		return;
	}

	treenprint(p->left, n);
	if (prev != NULL) {
		if (strncmp(prev->word, p->word, n) == 0) {
			if (printprev) {
				printf("%4d %s\n", prev->count, prev->word);
			}
			printf("%4d %s\n", p->count, p->word);
			printprev = 0;
		} else {
			printprev = 1;
		}
	}
	prev = p;
	treenprint(p->right, n);
}

void treefree(struct tnode *p)
{
	if (p != NULL) {
		treefree(p->left);
		treefree(p->right);
		free(p->word);
		free(p);
	}
}
