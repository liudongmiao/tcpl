/* vim: set sw=4 ts=4:
 * Author: Liu DongMiao <liudongmiao@gmail.com>
 * Created  : Tue 14 Aug 2012 09:30:29 PM CST
 * Modified : Wed 15 Aug 2012 08:37:59 AM CST
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

int page = 1;

/* getword: get next word or character from input */
int getword(char *word, int lim)
{
	int c;
	char *w = word;

	while (!isalnum(c = getchar())) {
		if (c == EOF) {
			return EOF;
		} else if (c == '\n') {
			page++;
		}
	}

	*w++ = c;
	while (w - word < lim && (isalnum(*w = getchar()) || *w == '-'))
		w++;

	// remove the last -
	if (*(w - 1) == '-') {
		*(w - 1) = '\0';
	}

	if (*w == '\n') {
		page++;
	}

	*w = '\0';
	return word[0];
}

#define MAXWORD 100
struct tnode {				/* the tree node: */
	int last;				/* last page in *page */
	char *word;				/* points to the text */
	char *page;				/* points to the page */
	struct tnode *left;		/* left child */
	struct tnode *right;	/* right child */
};
struct tnode *addtree(struct tnode *, const char *);
void treeprint(struct tnode *);
void treefree(struct tnode *);

int main(int argc, char **argv)
{
	struct tnode *root;
	char word[MAXWORD] = {0};
	root = NULL;
	while (getword(word, MAXWORD) != EOF) {
		if (word[0]) {
			root = addtree(root, word);
		}
	}
	treeprint(root);
	treefree(root);
	return 0;
}

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, const char *w)
{
	int cond;
	char temp[BUFSIZ];
	if (p == NULL) {		/* a new word has arrived */
		/* make a new node */
		p = (struct tnode *)malloc(sizeof(struct tnode));
		p->word = strdup(w);
		sprintf(temp, "%d", page);
		p->page = strdup(temp);
		p->last = page;
		p->left = p->right = NULL;
	} else if ((cond = strcmp(w, p->word)) == 0) {
		if (page > p->last) {
			sprintf(temp, "%s, %d", p->page, page);
			free(p->page);
			p->page = strdup(temp);
			p->last = page;
		}
	} else if (cond < 0)		/* less than into left subtree */
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
		printf("%s: %s\n", p->word, p->page);
		treeprint(p->right);
	}
}

void treefree(struct tnode *p)
{
	if (p != NULL) {
		treefree(p->left);
		treefree(p->right);
		free(p->word);
		free(p->page);
		free(p);
	}
}
