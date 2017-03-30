#include "functions.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
int findFirstPath(int argc, char ** argv)
{
	if(argc < 2) return 0;

	int i = 1;
	for(; i < argc; i++)
	{
		if(argv[i] == 0)
			return 0;
		else if(argv[i][0] != '-' )
			return i;

	}
	return i;
}

char * getAPath(const char * p)
{

	FILE* result = NULL;
	char * cmd = new char[PATH_MAX+25];
	sprintf(cmd,"cd %s 2>&1;pwd ;",p);
	char * path = new char[PATH_MAX +1] ;

	if((result = popen(cmd,"r")) == NULL)
		strcpy(path,"/");
	else
	{
		fgets(path,PATH_MAX,result);
		pclose(result);
		if(path[0]!='/')
		{
			strcpy(path,"/");
		}
	}
	if(path[strlen(path) - 1] =='\n')
		path[strlen(path)-1] = 0;
	delete[] cmd;
	return path;
}

void  pathConvert(char * originalPath ,char * newPath,int length)
{
	FILE* result = NULL;
	char *cmd = new char[PATH_MAX+25];
	strcpy(cmd,"cd ");
	strcat(cmd,originalPath);
	strcat(cmd, " 2>&1;");
	strcat(cmd,"pwd ;");

	if((result = popen(cmd,"r")) == NULL)
	{
		strcpy(newPath,originalPath);
	}
	else
	{
		fgets(newPath,length,result);
		if(newPath[0]!='/')
			strcpy(newPath,originalPath);
		pclose(result);
	}
	if(newPath[strlen(newPath) - 1] =='\n')
		newPath[strlen(newPath)-1] = 0;
	delete[] cmd;
}
char *getFileName(char *path)
{
	char *buf =new char[PATH_MAX];
	char *name =new char[PATH_MAX];
	strcpy(buf,path);
	int i = strlen(buf);
	char * t = buf;
	for(;i >=0; i--)
	{
		if(buf[i]=='/')
			buf[i] = 0;
		else
			break;
	}
	for(;i>=0;i--)
	{
		if(buf[i]=='/')
		{
			t = &buf[i+1];
			break;
		}
			
	}
	strcpy(name,t);
	delete[] buf;
	return name;
}
char *getFilePath(char *path)
{
	char *buf = new char[PATH_MAX+1];
	strcpy(buf,path);
	int length = strlen(buf);
	int i;
	for(i = length-1 ; i>=0;i--)
	{
		if(buf[i]!='/')
			break;
	}
	if(i<0)
	{
		strcpy(buf,"/");
		return buf;
	}

	for(; i>=0 ;i--)
	{
		if(buf[i]=='/'&& i != 0){
			buf[i] = 0;
			return buf;
		}
		else if(buf[i]=='/'&&i==0)
		{
			break;
		}
	}

	if(i<0)
		strcpy(buf,".");
	else
		strcpy(buf,"/");
	return buf;
}
bool isDir(char * path)
{
	struct stat st;
	st.st_mode = 0;
	if(0!=stat(path,&st))
	{
		return false;
	}
	else{
		if(S_ISDIR(st.st_mode))
			return true;
		else
			return false;
	}
}
bool isLegal(char * path)
{
	if(access(path,F_OK)==0)
		return true;
	else 
		return false;
}
bool canAccess(char * path)
{
	char *buf = NULL;
	if(!isDir(path))
	{
		buf =getFilePath(path);
	}
	else
	{
		buf = new char[PATH_MAX+1];
		strcpy(buf,path);
	}
	if(access(buf,X_OK)==0)
	{
		delete[] buf;
		return true;
	}
	else
	{
		delete[] buf;
		return false;
	}
}
char * getAbsolutePath(char * path)
{
	char *buf = new char[PATH_MAX*2];
	if(!isDir(path))
	{
		//file
		char *temp = getFilePath(path);
		pathConvert(temp,buf,PATH_MAX*2);
		delete[] temp;
		temp = getFileName(path);
		if(strcmp(buf,"/")!=0)
			strcat(buf,"/");
		strcat(buf,temp);
		delete[] temp;
	}
	else {
		//directory
		pathConvert(path,buf,PATH_MAX*2);
	}
	return buf;
}
char *getParent(char * path)
{
	char *parent = new char[PATH_MAX];
	strcpy(parent,path);
	int i;
	for(i=strlen(parent);i>=0;i--)
	{
		if(parent[i] == '/'){
			parent[i] = 0;
			break;
		}
	}
	if(i==0)
	{
		strcpy(parent,"/");
		return parent;
	}
	else
		return parent;
}
void setPar(char *par ,  Par *a)
{
	if(!isLegal(par))
	{
		a->isLegal = false;
		a->canAccess = false;
		char *t =new char[strlen(par)+1];
		strcpy(t,par);
		a->par = t;

		t = new char[strlen(par)+1];
		strcpy(t,par);
		a->parent = t;

		t = new char[strlen(par)+1];
		strcpy(t,par);
		a->absolutePath = t;
	}
	else{
		a->isLegal = true;
		a->canAccess = canAccess(par);		
		a->par = new char[strlen(par)+1];
		strcpy(a->par,par);
		
		a->absolutePath = getAbsolutePath(par);

		a->parent = getParent(a->absolutePath);
	}
}
