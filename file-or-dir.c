/*
 * Kade Samson - October 4th, 2024
 * This program determines if a command-line path argument is valid or invalid, 
 * where: 
 *  - Valid paths can be files or directories.
 *  - If the path is to a file, the file cannot already exist but must be creatable AND writeable.
 *  - If the path is to a directory, the directory must already exist AND be writeable.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <dirent.h>


void
usage(char *program_name, char *err)
{
	fprintf(stderr, "%s: %s\n", program_name, err);
	fprintf(stderr, "%s [file | directory]\n", program_name);
}

/* Verify path is a non-existent writeable file or an existent writeable dir. */
bool
is_valid_target(char *path)
{
	union target {
		DIR *dir;
		FILE *file;
	} path_target;
	struct stat statbuf;

	/* The user entered the path of a file to create. */
	if (stat(path, &statbuf) == -1) {
		/* Attempt to open the file for writing. */
		path_target.file = fopen(path, "w");
		if (path_target.file == NULL) {
			fprintf(stderr, "Error: File \"%s\" is not writeable\n", path);
			return false;
		}
		return true;
	}

	/* The file already exists :( */
	if (S_ISREG(statbuf.st_mode)) {
		fprintf(stderr, "Error: File \"%s\" already exists\n", path);
		return false;
	}

	/* Path points to a non-existent directory. */
	if (!S_ISDIR(statbuf.st_mode)) {
		fprintf(stderr, "Error: Directory \"%s\" does not exist\n", path);
		return false;
	}

	return true;
}

int
main(int argc, char *argv[])
{
	if (argc < 2) {
		usage(argv[0], "No path provided");
		exit(1);
	}

	printf("Path is \"%s\"\n", argv[1]);
	if (!is_valid_target(argv[1]))
		exit(1);

	return 0;
}
