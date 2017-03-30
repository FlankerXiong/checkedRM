#ifndef _PAR_H_
#define _PAR_H_
class Par
{
	public:
		char *parent;
		char *absolutePath;
		char *par;
		bool isLegal;
		bool canAccess;
	public:
		Par();
		~Par();
};
#endif
