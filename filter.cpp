#include "filter.h"
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <limits.h>
#include "functions.h"
#include <stdio.h>
bool checkAPath( Par *p,int n,const char * toBeCheck)
{
	struct dirent *dp;
	DIR * dfd;
	if((dfd = opendir(toBeCheck))== 0 )
	{
		return false;
	}
	char *path = new char[PATH_MAX+1];
	
	while((dp  = readdir(dfd))!= 0)
	{
		if ((strcmp(dp->d_name, ".") == 0) || (strcmp(dp->d_name, "..") == 0) || (dp->d_name[0]=='.'))
				continue; //skip self and parent and hidden
		if(strcmp(toBeCheck,"/")==0)
		{
			sprintf(path,"/%s",dp->d_name);
		}
		else{
			sprintf(path,"%s/%s",toBeCheck,dp->d_name);
		}
		int w;
		for(w=0;w< n; w++)
		{
			if(strcmp(p[w].absolutePath,path) == 0)
				break;
		}
		if(w >= n)
		{
			delete[] path;
			closedir(dfd);
			return false;
		}
	}
	delete[] path;
	closedir(dfd);
	return true;
}

bool checkKeyWord( Par *p ,int n)
{

	for(int i=0;i<n;i++)
	{
		char * home = getAPath("~");
		if((strcmp(p[i].absolutePath,"/home")==0) || 
					(strcmp(p[i].absolutePath,home)==0) ||
					(strcmp(p[i].absolutePath,"/root")==0))
		{
			delete[] home;
			return true;
		}
		delete[] home;

		int length = strlen(p[i].absolutePath);
		int k;
		for( k =0 ; k < length ; k++ )
		{
			if(p[i].absolutePath[k]!='/' &&
					p[i].absolutePath[k]!='.' &&
					p[i].absolutePath[k]!= '~' &&
					p[i].absolutePath[k]!='*')
				break;
		}
		if(k>=length)
			return true;
	}
	return false;
}
bool checkEveryPar( Par *p ,int n)
{
	for(int i = 0; i < n ; i++)
	{
		if(p[i].isLegal && checkAPath(p,n,p[i].parent))
			return true;
	}
	return false;
}
