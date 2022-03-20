#include <stdio.h>
#include <unistd.h>
#include <linux/limits.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define LIMIT "10"
#include <stdbool.h>

int sub_num = 0;
char cwd[PATH_MAX];
char cwd1[PATH_MAX];

int newlines(FILE *file)
{
	int c;
	int nl = 0;

	while ((c = fgetc(file)) != EOF)
	{
		if (c=='\n')
			nl++;
	}
	return nl;
}

char *readFile(char *fileName)
{
	FILE *file = fopen(fileName, "r");
	char *urls;
	size_t n = 0;
	int c;

	if (file == NULL)
		return NULL;

	urls = malloc(1000);

	while ((c = fgetc(file)) != EOF)
	{
		urls[n++] = (char) c;
	}

	urls[n] = '\0';

	return urls;
}

void get_memes(char sub[25]) 
{
	/*
	 * Declaring variables
	 */
	char *readFile(char *fileName);
	char imageurl[60];
	char imgname[90];
	int x = 0, n = 0, b = 0;
	char c;
	char *command;
	char *downloadimage;
	char url[77] = "https://www.reddit.com/r/";

	strcat(url, sub);

	strcat(url, "/hot.json?limit=");
	
	strcat(url, LIMIT);

	printf("URL called:\n");
	printf("%s\n", url);
	
	/*
	 * Creating the first command
	 */
	command = malloc(9999);
	strcat(command, "curl -H \"User-agent: 'your bot 0.1'\" \"");
	strcat(command, url);
	strcat(command, "\" > \"");
	strcat(command, cwd1);
	strcat(command, "/tmp.json\"\0");
	
	system(command);

	printf("command just executed:\n");
	printf("%s\n", command);

	/*
	 * Wiping the url and command
	 */
	command = "";

	system("./main.py");

	printf("Executed python script\n");

	FILE *imagefile = fopen("imagelist", "r");
	
	while ((c = fgetc(imagefile)) != EOF) {
		if ((c != '\n'))
		{
			if (c=='/')
				x++;
			if ((x==3) && (c != '/'))
				imgname[b++]=(int)c;
			imageurl[n++] = (int)c;
		}
		else if (c == '\n')
		{
			if (imgname[0] == '\0')
			{
				printf("We just got bullshitted\n");
			}
			else
			{
			printf("reached a newline\n");
			imgname[b] = '\0';
			downloadimage = malloc(600);
			b = 0;
			x = 0;
			n = 0;
			printf("The image name:\n");
			printf("%s\n", imgname);
			printf("The image url:\n");
			printf("%s\n", imageurl);

			/* Creating the curl command */

			strcat(downloadimage, "curl -H \"User-agent: 'your bot 0.1'\" \"");
			strcat(downloadimage, imageurl);
			strcat(downloadimage, "\" > \"");
			strcat(downloadimage, imgname);
			strcat(downloadimage, "\"\0");

			system(downloadimage);
			
			/* Freeing memory */
			printf("The command just executed:\n");
			printf("%s\n", downloadimage);
			downloadimage = "";
			}
		}
	}

	/*
	 *Clearing the lists
	 */
	fclose(imagefile);
	return;
}

int main()
{	
	void get_memes(char sub[25]);

	if (getcwd(cwd, sizeof(cwd)) != NULL){
		strcat(cwd1, cwd);
		strcat(cwd,"/subredditlist");
	}	
	FILE *fp = fopen(cwd, "r");
	if (fp == NULL)
	{
		printf("Problem");
		return 1;
	}
	size_t n = 0;
	int c;
	int x = 0, a = 0;
	int numofsubs = newlines(fp);
	char subreddits[numofsubs-1][25];
	
	fflush(stdout);
	/* 
	*Getting directory for the subreddit list
	*/

	printf("\nbefore\n");


	/* Getting the list of subreddits */

	
	rewind(fp);
	
	printf("here\n");

	while ((c = fgetc(fp)) != EOF) {
		if ((c != '\n') && (isalpha(c)))
		{
			subreddits[x][n] = c;
			n++;
		}
		else if (c == '\n')
		{
			subreddits[x][n] = '\0';
			n = 0;
			x++;
			printf("\n");
		}
	}
	
	fflush(stdout);


	printf("done\n");
	printf("subreddit1\n");
	printf("\n%s\n", subreddits[0]);
	printf("subreddit2\n");
	printf("\n%s\n", subreddits[1]);
	printf("subreddit3\n");
	printf("\n%s\n", subreddits[2]);
	printf("subreddit4\n");
	printf("\n%s\n", subreddits[3]);
	printf("subreddit5\n");
	printf("\n%s\n", subreddits[4]);

	fclose(fp);
	printf("File directory: %s\n", cwd);

	printf("Getting da memes!\n");	
	while (a < x){
		printf("This is the subreddit being scanned: ");
		printf("%s\n", subreddits[a]);
		get_memes(subreddits[a++]);
	}
	printf("DONE!\n");
	return 0;
}
