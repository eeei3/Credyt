#include <stdio.h>
#include <unistd.h>
#include <linux/limits.h>
#include <stdlib.h>
#include <string.h>
#define LIMIT 10
#define CURL "curl -H \"User-agent: 'your bot 0.1'\" \""
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <pthread.h>
#include <stdarg.h>
/*#include <main.h>*/
unsigned int sub_num = 0;
char cwd[PATH_MAX], cwd1[PATH_MAX];
struct stat sb;

int newlines(FILE *file)
{
	unsigned int c;
	unsigned int nl = 0;

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
	unsigned int c;
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
void *work (void *command)
{
	system(command);

	return NULL;
}

void *get_memes (void *sub) 
{
	/*
	 * Declaring variables
	 */
	unsigned int THREADS = 5;
	pthread_t imgworkers[THREADS];
	char *readFile(char *fileName);
	char imageurl[60], imgname[90];
	register unsigned int x = 0, n = 0, b = 0, t = 0, m = 0, u = 60, h = 90;
	char c;
	char *command, *downloadimage, *lim;
	char url[77] = "https://www.reddit.com/r/";
	lim = malloc(100);
	snprintf(lim, 200, "%d", LIMIT);
	strcat(url, (char *) sub);
	strcat(url, "/hot.json?limit=");
	strcat(url, lim);
	/*
	 * Creating the first command
	 */
	command = (char *) malloc(9999);
	strcat(command, CURL);
	strcat(command, url);
	strcat(command, "\" > \"");
	strcat(command, cwd1);
	strcat(command, "/tmp.json\" 2>/dev/null\0");
	system(command);
	/*
	 * Wiping the url and command
	 */
	command = NULL;
	system("./main.py");
	FILE *imagefile = fopen("imagelist", "r");
	printf("Downloading the images\n");	
	while ((c = fgetc(imagefile)) != EOF) {
		if ((c != '\n'))
		{
			if (c=='/') x++;
			if ((x==3) && (c != '/'))
				imgname[b++]=(int)c;
			if ((c != '@') && (c != '\t'))
				imageurl[n++] = (int)c;
		}
		else if (c == '\n')
		{
			if (imgname[0] == '\0');
			else
			{
			imageurl[n] = '\0', imgname[b] = '\0';
			downloadimage = (char *) malloc(900);
			b = 0, x = 0, n = 0;
			/* Creating the curl command */
			if (imageurl[7] == 'v')
				;
			else if ((strstr(imgname, ".jpg") != NULL) || (strstr(imgname, ".png") != NULL) || (strstr(imgname, ".gif") != NULL))
				{
				strcpy(downloadimage, "curl -H \"User-agent: 'your bot 0.1'\" \"");
				strncat(downloadimage, imageurl, 60);
				strcat(downloadimage, "\" > \"images/");
				strncat(downloadimage, (char *) sub, 25);
				strncat(downloadimage, "/", 4);
				strncat(downloadimage, imgname, 90);
				strcat(downloadimage, "\" 2> /dev/null\0");
				if (t != THREADS)
					pthread_create(&imgworkers[t++], NULL, work, downloadimage);
				else
				{
					t = 0;
					for (; t < THREADS; t++)
					{
						pthread_join(imgworkers[t], NULL);
					}
					t = 0;
				} 
				/* Freeing memory */
				}
			printf("%s\n", downloadimage);
			m = 0;
			while (m < u)
				imageurl[m++] = '\0';
			m = 0;
			while ( m < h)
				imgname[m++] = '\0';
			m = 0;
			fflush(stdout);
			}
		}
	}
	printf("Images done downloading\n");
	/*
	 *Clearing the lists
	 */
	fclose(imagefile);
	free(command);
	free(lim);
	free(downloadimage);
	command = NULL;
	downloadimage = NULL;
	lim = NULL;
	return NULL;
}
int main()
{	
	if (stat("images", &sb) == 0 && S_ISDIR(sb.st_mode))
	{
		system("rm -r images/*");
	}
	else
	{
		system("mkdir images");
	}
	if (getcwd(cwd, sizeof(cwd)) != NULL){
		strcat(cwd1, cwd);
		strcat(cwd,"/subredditlist");
	}	
	FILE *fp = fopen(cwd, "r");
	if (fp == NULL)
	{
		return 1;
	}
	size_t n = 0;
	unsigned int x = 0, a = 0, c;
	unsigned int numofsubs = newlines(fp);
	char subreddits[numofsubs-1][26];
	char *foldercommand = malloc(900);
	/* 
	*Getting directory for the subreddit list
	*/
	/* Getting the list of subreddits */
	rewind(fp);
	while ((c = fgetc(fp)) != EOF) {
		if (c != '\n')
		{
			subreddits[x][n++] = c;
		}
		else if (c == '\n')
		{
			subreddits[x++][n] = '\0';
			n = 0;
		}
	}
	fclose(fp);
	while (a < x){
		if (subreddits[a] == NULL)
		{
			;
		}
		else
		{
		strcat(foldercommand, "mkdir images/");
		strcat(foldercommand, subreddits[a]);
		system(foldercommand);
		get_memes(subreddits[a++]);
		strcpy(foldercommand, "");
		}
		}

	free(foldercommand);
	foldercommand = NULL;
	return 0;
}
