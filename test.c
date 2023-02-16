// #include <stdio.h>
// #include <stdlib.h>

// int main () {
//    printf("PATH : %s\n", getenv("PATH"));
//    printf("HOME : %s\n", getenv("$PWD"));
//    printf("ROOT : %s\n", getenv("./"));

//    return(0);
// }
#include <stdio.h>
#include <dirent.h>

// int main()
// {
//     DIR *folder;
//     struct dirent *entry;
//     int files = 0;

//     folder = opendir(".");
//     if(folder == NULL)
//     {
//         perror("Unable to read directory");
//         return(1);
//     }

//     while( (entry=readdir(folder)) )
//     {
//         files++;
//         printf("File %3d: %s\n",
//                 files,
//                 entry->d_name
//               );
//     }

//     closedir(folder);

//     return(0);
// }
     #include <stdio.h>
           #include <stdlib.h>
           #include <unistd.h>
		   
int main(int argc, char *argv[])
{
	char *newargv[] = { NULL, "hello", "world", NULL };
	char *newenviron[] = { NULL };

	if (argc != 2) {
		fprintf(stderr, "Usage: %s <file-to-exec>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	newargv[0] = argv[1];
	execve(argv[1], newargv, newenviron);
	perror("execve");   /* execve() ne retourne qu'en cas d'erreur */
	exit(EXIT_FAILURE);
}
