#include <iostream>
#include <string.h>
#include <limits.h> 
#include <stdlib.h>
#include "functions.h"
#include "filter.h"

using namespace std;
void action(int argc, char * argv[])
{
	char * cmd = new char [(PATH_MAX*2)* (argc-1)+ 20];
	strcpy(cmd,"rm ");
	int w = 3;
	for(int i= 1; i < argc ;i++)
	{
		int k;
		int length = strlen(argv[i]);
		for(k=0;k<length;k++,w++)
		{
			if((argv[i][k]<'a' || argv[i][k] > 'z')&&
					(argv[i][k]<'A' || argv[i][k] >'Z') &&
					(argv[i][k] <'0' || argv[i][k] >'9') &&
					argv[i][k] != '.' && argv[i][k] !='/' &&
					argv[i][k] != '*')
				cmd[w++] = '\\';
			cmd[w] = argv[i][k];
		}
		cmd[w++] = ' ';
	}
	cmd[w++] = 0;
	//cout<< cmd <<endl;
	system(cmd);
}
bool confirm()
{
	cout<<"This operation may be harmful to system! Please confirm!(y/n)";
	while(1)
	{
		char t = cin.get();
		if( t == 'y' || t == 'Y')
			return true;
		else if(t=='N' || t == 'n')
			return false;
		else
			cout<<"Please input y or n!"<<endl;
	}
}

int main(int argc,char *argv[])
{
	Par * pars = new Par[argc-1];
	int k = findFirstPath(argc, argv);
	if(k == 0)
	{
		cout<<"Error! Abort!"<<endl;
		delete[] pars;
		return -1;
	}

	for(int i=k ;i< argc ;i++)
	{
		setPar(argv[i],&pars[i-k]);
		if(pars[i-k].isLegal && !pars[i-k].canAccess)
		{
			cout<<"Permission Denied! Abort!\n";
			delete[] pars;
			return -2;
		}
	}
	if(checkKeyWord(pars,argc - k) || checkEveryPar(pars,argc-k)){
		if(confirm())
			action(argc,argv);
		else{
			cout<<"Abort!"<<endl;
		}
		return 0;
	}
	action(argc,argv);
	return 0;

}
