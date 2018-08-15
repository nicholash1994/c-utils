#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

unsigned long get_sloc(FILE* file);
unsigned long get_slocr(DIR* dir);

int main(int argc, char** argv) {
	FILE* file;
	DIR* dir;
	struct stat file_st;
	/* set to 1 if non-whitespace character is found */
	/* in the current line of code */
	int non_whitespace = 0;
	unsigned long sloc = 0;
	char c;
	
	
	if (argc < 2) {
		sloc = get_sloc(stdin);
	}
	else {
		stat(argv[1], &file_st);
		if (S_ISREG(file_st.st_mode)) {
			file = fopen(argv[1], "r");
			sloc = get_sloc(file);
			fclose(file);
		}
		else if (S_ISDIR(file_st.st_mode)) {
			dir = opendir(argv[1]);
			chdir(argv[1]);
			sloc = get_slocr(dir);
			chdir("..");
			closedir(dir);
		}
		else {
			fprintf(stderr, "Error: %s is not a regular file!\n", argv[1]);
			return -1;
		}
	}

	printf("%lu lines of code!\n", sloc);
	
	return 0;

}

unsigned long get_sloc(FILE* file) {
	unsigned long sloc = 0;
	char c;
	int non_whitespace = 0;

	if (file == NULL) {
		fprintf(stderr, "Error: a file couldn't be opened!\n");
		return -1;
	}

	while ((c=fgetc(file)) != EOF)
		if (c != ' ' && c != '\t' && c != '\n')
			non_whitespace = 1;
		else if (c == '\n' && non_whitespace == 1) {
			sloc++;
			non_whitespace = 0;
		}
		else if (c == '\n')
			non_whitespace = 0;
	
	return sloc;
}

unsigned long get_slocr(DIR* dir) {
	struct dirent* entry;
	struct stat file_st;
	unsigned long sloc = 0;
	FILE* file;
	DIR* dir2;

	while (entry=readdir(dir)) {
		if (strcmp(entry->d_name, ".") == 0 ||
				strcmp(entry->d_name, "..") == 0)
			continue;
		stat(entry->d_name, &file_st);
		if (S_ISREG(file_st.st_mode)) {
			file = fopen(entry->d_name, "r");
			sloc += get_sloc(file);
			fclose(file);
		}
		else if (S_ISDIR(file_st.st_mode)) {
			dir2 = opendir(entry->d_name);
			chdir(entry->d_name);
			sloc += get_slocr(dir2);
			chdir("..");
			closedir(dir2);
		}
	}
	
	return sloc;
}
