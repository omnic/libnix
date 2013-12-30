// lib*nix textfile
// processing of memory mapped text files

#include "libnix.h"

int lnix_getlines (char *string, char ***lines, size_t *linecount) {
	int ptrcount = 256, countscale = 256;
	char *start, *end;

	size_t limit = strlen (string);

	if (!(*lines = malloc (ptrcount * sizeof (char *)))) {
		return 1;	// insufficient memory
	}

	start = string;
	*linecount = 0;

	while ((end = strchr (start, '\n'))) {
		if (!((*lines)[*linecount] = strndup (start, (end - start)))) {
			return 1;	// insufficient memory
		}

		(*linecount)++;
		// Check that we have more memory
		if (*linecount == ptrcount) {
			// Make sure our scaling is fast enough
			while ((ptrcount >= (countscale * 4)) && (countscale < 65536)) {
				countscale = countscale * 4;
			}

			ptrcount += countscale;

			// Make sure our realloc works
			if (!(*lines = realloc (*lines, ptrcount * sizeof (char *)))) {
				return 1;	//insufficient memory
			}
		}

		// setup for round two
		start = end + 1;
	}

	return 0;
}

int lnix_getSourceFile (lnix_mapFileStruct *mapfile, lnix_sourceFileStruct *sourcefile) {
	sourcefile->file = mapfile;

	char *data = mapfile->addr;
	char ***lines = &sourcefile->line;
	size_t *linecount = &sourcefile->linecount;

	return lnix_getlines (data, lines, linecount);
}
