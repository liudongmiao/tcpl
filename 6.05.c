/* vim: set sw=4 ts=4:
 * Author: Liu DongMiao <liudongmiao@gmail.com>
 * Created  : Wed 15 Aug 2012 02:32:24 PM CST
 * Modified : Wed 15 Aug 2012 04:50:40 PM CST
 */

/* write a function ``undef'' that will remove a name and definition from the
 * table maintained by ``lookup'' and ``install''.
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct nlist {				/* table entry: */
	struct nlist *next;		/* next entry in chain */
	char *name;				/* define name */
	char *defn;				/* replacement text */
};

#define HASHSIZE 101
static struct nlist *hashtab[HASHSIZE];	/* pointer table */

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

int main()
{
	struct nlist *np;
	install("thom", "liudongmiao");
	np = lookup("thom");
	printf("thom=%s\n", np ? np->defn : NULL);

	printf("undef thom\n");
	undef("thom");

	np = lookup("thom");
	printf("thom=%s\n", np ? np->defn : NULL);
	return 0;
}
