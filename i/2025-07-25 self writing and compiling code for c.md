## the basics
here i explained how to write basic c code: it's essentially the same as regular code but a bit more strict on data management. [[2025-07-23 self learning c]]

in order to compile any c code ourselves, we have to compile it. there's a lot of popular compilers out there. i used minGW https://www.mingw-w64.org/downloads/ check if you have it by writing this in the windows terminal. if it works we can continue.

```
gcc --version
```

next up we make a c file. i made `helloworld.c` and wrote a basic hello world script.

```c
#include <stdio.h>

int main()
{
	printf("Hello World!");
	return 0;
}
```

in our windows terminal we're gonna navigate to our `helloworld.c` and write this below to automatically make it an exe file in a default version of c that either your pc has or the version of gcc has.

```
gcc name_of_script.c -o name_of_excecutible
```

in order to specifically make it a c89 version, you have to specify that in the code. and we can do that with this:

```
gcc -std=c89 -pedantic -o helloworld helloworld.c
```

