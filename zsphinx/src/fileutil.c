/*
 * fileutil.c
 *
 *  Created on: Apr 2, 2014
 *      Author: Volodymyr Varchuk
 */


#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include "types_.h"
#include "lists.h"
#include "fileutil.h"

#define MAX_BUFF 1024

void reverse_ (char s[])
{
	int c, i, j;
	for (i = 0, j = strlen(s)-1; i < j; i++, j--)
	{
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

char *getext_ (const char *fname)
{
	if (fname == NULL)
		return NULL;
	int len = strlen (fname);
	int i;
	char *ext = NULL;
	i = 0;
	if (len == 0)
		return  NULL;

	ext = (char *) malloc ( sizeof (char) * strlen (fname) );
	while ((fname [len] != '.') && (fname [len] != '/') && len != 0)
	{
		if ((fname [len] != '\n') && (fname [len] != '\0'))
			ext[i++] = fname [len--];
		else
			len--;
	}
	ext[i] = '\0';
	reverse_ (ext);
	return ext;
}

int get_file_list (char *path, SingleList_t *pList, SingleList_t *pFileTypeList)
{
	static int a;
	DIR *dir;
	struct dirent *entry;
	dir = opendir(path);
	int len;
	if(dir == 0)
	{
		return -1;
	}
	while((entry = readdir(dir)))
	{

		if(entry->d_type == DT_DIR)
		{
			if (strcmp (entry->d_name, ".") != 0 && strcmp (entry->d_name, "..") != 0)
			{
				char *newpath = NULL;
				newpath = (char *)  malloc ( sizeof ( char ) * ( strlen (entry->d_name) + strlen (path) + 2 ) );
				if ( strcmp (path, "/") == 0 )
					sprintf ( newpath, "/%s", entry->d_name );
				else
					sprintf ( newpath, "%s/%s", path, entry->d_name );
				get_file_list (newpath, pList, pFileTypeList);
				free (newpath);
			}
		}
		if ( entry->d_type == DT_REG )
		{
			char *filePath = NULL;
			filePath = (char *) malloc ( sizeof ( char ) * ( strlen (entry->d_name) + strlen (path) + 2 ) );
			sprintf( filePath, "%s/%s", path,  entry->d_name);
			int i = 0;
			char *fileExt = NULL;
			fileExt = getext_( filePath );
			for ( i = 0; i < pFileTypeList->count; i++)
				if ( strcmp ( fileExt , pFileTypeList->list[i]) == 0 )
				{
					char *freeFilePath = filePath;
					if ( filePath[0] == '/' && filePath[1] == '/' )
						filePath++;
					addToList( filePath, pList );
					free ( freeFilePath );
				}
			free (fileExt);
		}
	}
	closedir(dir);
	return 0;
}


int print_dir_tree (char *path)
{
//	static int a;
	DIR *dir;
	struct dirent *entry;
	dir = opendir(path);
	int len;
	if(dir == 0)
	{
		return -1;
	}
	while((entry = readdir(dir)))
	{
		if ( strcmp (path, "/") == 0 )
			printf ("/%s D_TYPE = %d\n", entry->d_name, entry->d_type);
		else
			printf ("%s/%s D_TYPE = %d\n", path, entry->d_name, entry->d_type);

		if(entry->d_type == DT_DIR)
		{
			if (strcmp (entry->d_name, ".") != 0 && strcmp (entry->d_name, "..") != 0)
			{
				char *newpath = NULL;
				newpath = (char *)  malloc ( sizeof ( char ) * ( strlen (entry->d_name) + strlen (path) + 2 ) );
				if ( strcmp (path, "/") == 0 )
					sprintf ( newpath, "/%s", entry->d_name );
				else
					sprintf ( newpath, "%s/%s", path, entry->d_name );
				print_dir_tree (newpath);
				free (newpath);
			}
		}
	}
	closedir(dir);
	return 0;
}

void print_file (char *fileName)
{
	FILE *f;
	int MAX_BUFF = 1024;
	int bread = 0;
	char buff[ MAX_BUFF ];

	f = fopen ( fileName, "r" );
	if ( f == NULL )
	{
		printf ("Cannot open file %s\n", fileName);
		return;
	}
	else
		printf ("%s - OK\n", fileName);

	while ( (bread = fread ( buff, 1, MAX_BUFF, f )) > 0 )
	{
		fwrite ( buff, 1, bread, stdout );
	}
	fclose (f);
}

int save_from_stdin ( char *filename )
{
	int data_size = 0;
	char buff [ MAX_BUFF ];
	int bread = 0, bwrite = 0;

	int fd;
	fd = open ( filename, O_WRONLY | O_CREAT | O_TRUNC, S_IROTH | S_IWOTH | S_IRUSR | S_IWUSR );
	if (fd <= 0)
		return 0;
	while ( ( bread = read ( 0, buff, MAX_BUFF ) ) > 0 )
	{
		bwrite = write ( fd, buff, bread );
		data_size += bwrite;
	}
	close (fd);
	return data_size;
}










