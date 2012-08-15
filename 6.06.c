/* vim: set sw=4 ts=4:
 * Author: Liu DongMiao <liudongmiao@gmail.com>
 * Created  : Wed 15 Aug 2012 04:52:23 PM CST
 * Modified : Wed 15 Aug 2012 04:52:23 PM CST
 */

/*
 * Implement a simple version of the ``#define'' processor (i.e., no arguments)
 * suitable for use with C programs, based on the routines of this section. You
 * may also find ``getch'' and ``ungetch'' helpful.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

struct nlist {				/* table entry: */
	struct nlist *next;		/* next entry in chain */
	char *name;				/* define name */
	char *defn;				/* replacement text */
};

#define HASHSIZE 101
static struct nlist *hashtab[HASHSIZE];	/* pointer table */
int undef(char *s);
struct nlist *install(char *name, char *defn);
struct nlist *lookup(char *s);

enum { SPACE, COMMENT, QUOTE, SINGLE, CODE, NEWLINE };

int getword(char *word, int lim)
{
	int c, getch(void);
	void ungetch(int);
	char *w = word;

	while (isspace(*w = c = getch())) {
		w++;
		if (c == '\n') {
			break;
		}
	}

	if (w - word > 0) {
		*w = '\0';
		if (c != '\n') {
			ungetch(c);
			return SPACE;
		} else {
			return NEWLINE;
		}
	}

	// remove comments ?
	if (c == '/') {
		if ((*++w = c = getch()) == EOF) {
			return EOF;
		} else if (c == '/') {
			while ((*++w = c = getch()) != EOF) {
				if (c == '\\') {
					if ((*++w = c = getch()) == EOF) {
						return EOF;
					}
				} else if (c == '\n') {
					*w = '\0';
					ungetch(c);
					break;
				}
			}
		} else if (c == '*') {
			while ((*++w = c = getchar()) != EOF) {
				if (c == '*') {
					if ((*++w = c = getch()) == EOF) {
						return EOF;
					} else if (c == '/') {
						break;
					}
				}
			}
		}
		*++w = '\0';
		return COMMENT;
	} else if (c == '"') {
		while ((*++w = c = getch()) != EOF) {
			if (c == '\\') {
				if ((*++w = c = getch()) == EOF) {
					return EOF;
				}
			} else if (c == '"') {
				break;
			}
		}
		*++w = '\0';
		return QUOTE;
	} else if (c == '\'') {
		if ((*++w = c = getchar()) == EOF) {
			return EOF;
		} else if (c == '\\') {
			if ((*++w = c = getchar()) == EOF) {
				return EOF;
			}
		}
		*++w = c = getchar();
		*++w = '\0';
		return SINGLE;
	} else if (isalpha(c) || c == '_') {
		while (w - word < lim && (*++w = c = getch()) != EOF) {
			if (!isalnum(c) && c != '_') {
				break;
			}
		}
		ungetch(c);
		*w = '\0';
		return CODE;

	} else if (c != EOF) {
		while (w - word < lim && (*++w = c = getch()) != EOF) {
			if (isspace(c) || c == '/' || c == '\'' || c == '"') {
				break;
			}
			if (c == '\\') {
				*++w = c = getch();
				continue;
			}
		}
		ungetch(c);
		*w = '\0';
		return CODE;
	}

	return EOF;
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

enum { FALSE, TRUE };

int main()
{
	char word[BUFSIZ];
	int type = NEWLINE;
	int define = FALSE;
	while ((type = getword(word, BUFSIZ)) != EOF) {
		while (type == SPACE) {
			printf("%s", word);
			type = getword(word, BUFSIZ);
		}

		/* # define */
		if (strcmp(word, "#") == 0) {
			printf("%s", word);
			type = getword(word, BUFSIZ);
			while (type == SPACE) {
				printf("%s", word);
				type = getword(word, BUFSIZ);
			}
			printf("%s", word);
			if (strcmp(word, "define") == 0) {
				define = TRUE;
			}
		/* define */
		} else if (strcmp(word, "#define") == 0) {
			printf("%s", word);
			define = TRUE;
		}

		if (define) {
			char *name, *defn;
			while ((type = getword(word, BUFSIZ)) == SPACE)
				printf("%s", word);
			if (type == EOF) {
				break;
			}
			printf("%s", word);
			name = strdup(word);
			while ((type = getword(word, BUFSIZ)) == SPACE)
				printf("%s", word);
			if (type == EOF) {
				break;
			}
			printf("%s", word);
			defn = strdup(word);
			install(name, defn);
			define = FALSE;
		} else if (type == EOF) {
			break;
		} else {
			struct nlist *np;
			np = lookup(word);
			if (np) {
				printf("%s", np->defn);
			} else {
				printf("%s", word);
			}
		}

	}
	return 0;
}

/* hash: from hash value to string s*/
unsigned hash(char *s)
{
	unsigned hashval;

	for (hashval = 0; *s != '\0'; s++)
		hashval = *s + 31 * hashval;
	return hashval % HASHSIZE;
}

/* lookup: look for s in hashtab */
struct nlist *lookup(char *s)
{
	struct nlist *np;
	for (np = hashtab[hash(s)]; np != NULL; np = np->next)
		if (strcmp(s, np->name) == 0)
			return np;
	return NULL;
}

/* install: put (name, defn) in hashtab */
struct nlist *install(char *name, char *defn)
{
	struct nlist *np;
	unsigned hashval;
	if ((np = lookup(name)) == NULL) {
		np = (struct nlist *)malloc(sizeof(*np));
		if (np == NULL || (np->name = strdup(name)) == NULL)
			return NULL;
		hashval = hash(name);
		np->next = hashtab[hashval];
		hashtab[hashval] = np;
	} else
		free((void *)np->defn);
	if ((np->defn = strdup(defn)) == NULL)
		return NULL;
	return np;
}

/* undef: undefine name in hashtab */
int undef(char *s)
{
	struct nlist *np, *prev;
	unsigned hashval;

	hashval = hash(s);
	for (prev = np = hashtab[hashval]; np != NULL; prev = np, np = np->next) {
		if (strcmp(s, np->name) == 0) {
			// s is the first entry
			if (prev == np) {
				hashtab[hashval] = np->next;
			} else {
				prev->next = np->next;
			}

			free(np->name);
			free(np->defn);
			free(np);
			return 0;
		}
	}

	return 1;
}
