#include<stdio.h>
#include <dlfcn.h>
#include<stdlib.h>



int main()
{
	void (*pr)(void);
	void* handle;
	handle=dlopen("./libN.so",RTLD_LAZY);
    if (!handle) 
    {
        printf("%s\n", dlerror());
        exit(1);
    }
	pr=dlsym(handle,"lib1Func");
	(*pr)();
	dlclose(handle); 
	return 0;
}