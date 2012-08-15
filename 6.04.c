/* vim: set sw=4 ts=4:
 * Author: Liu DongMiao <liudongmiao@gmail.com>
 * Created  : Wed 15 Aug 2012 08:53:51 AM CST
 * Modified : Wed 15 Aug 2012 01:31:33 PM CST
 */

/*
 * Write a program that prints the distinct words in its input sorted into
 * decreasing order of frequency of occurrence. Precede each word by its count.
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

/* getword: get next word or character from input */
int getword(char *word, int lim)
{
	int c;
	char *w = word;

	while (!isalnum(c = getchar())) {
		if (c == EOF) {
			return EOF;
		}
	}

	*w++ = c;
	while (w - word < lim && (isalnum(*w = getchar()) || *w == '-'))
		w++;

	// remove the last -
	if (*(w - 1) == '-') {
		*(w - 1) = '\0';
	}

	*w = '\0';
	return word[0];
}

#define MAXWORD 100
int words = 0;
struct tnode {				/* the tree node: */
	char *word;				/* points to the text */
	int count;				/* number of occurrences */
	struct tnode *left;		/* left child */
	struct tnode *right;	/* right child */
};
struct tnode *addtree(struct tnode *, const char *);
void treeprint(struct tnode *);
void treefree(struct tnode *);
// struct tnode *addtree2(struct tnode *, const struct tnode *);
struct tnode *walktree(struct tnode *, const struct tnode *);

int main(int argc, char **argv)
{
	struct tnode *root;
	struct tnode *sort;
	char word[MAXWORD] = {0};
	root = NULL;
	while (getword(word, MAXWORD) != EOF) {
		if (word[0]) {
			root = addtree(root, word);
		}
	}
	sort = NULL;
	sort = walktree(sort, root);
	treeprint(sort);
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
		words++;
	} else if ((cond = strcmp(w, p->word)) == 0)
		p->count++;			/* repeated word */
	else if (cond < 0)		/* less than into left subtree */
		p->left = addtree(p->left, w);
	else					/* greater than into right subtree */
		p->right = addtree(p->right, w);
	return p;
}

/* TODO: how to merge addtree2 and walktree ? */
struct tnode *addtree2(struct tnode *p, const struct tnode *t)
{
	int cond = 0;

	if (p == NULL) {
		p = (struct tnode *)malloc(sizeof(struct tnode));
		p->count = t->count;
		p->word = t->word;
		p->left = NULL;
		p->right = NULL;
	} else if (p->count == t->count) {
		if ((cond = strcmp(p->word, t->word)) < 0) {
			p->left = addtree2(p->left, t);
		} else if (cond > 0) {
			p->right = addtree2(p->right, t);
		}
	} else if ((cond = p->count - t->count) < 0) {
		p->left = addtree2(p->left, t);
	} else if (cond > 0) {
		p->right = addtree2(p->right, t);
	}

	return p;
}

struct tnode *walktree(struct tnode *p, const struct tnode *s)
{
	if (s != NULL) {
		p = walktree(p, s->left);
		p = addtree2(p, s);
		p = walktree(p, s->right);
	}
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

void treefree(struct tnode *p)
{
	if (p != NULL) {
		treefree(p->left);
		treefree(p->right);
		free(p->word);
		free(p);
	}
}
