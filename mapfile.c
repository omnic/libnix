// lib*nix mapfile
// memory mapping of files

#include "libnix.h"

int lnix_mmapFile (char *filename, lnix_mapFileStruct *mapfile) {
	int  x;

	struct stat statbuf;

	mapfile->fd = -1;
	if ((mapfile->fd = open (filename, mapfile->o_flag)) == -1) {
		return -1;	// open failed
	}

	if (flock (mapfile->fd, mapfile->lock) == -1) {
		do {
			x = close (mapfile->fd);
		} while ((x != 0) && (errno == EINTR));

		return -2;	// locking failed
	}

	if (!fstat (mapfile->fd, &statbuf) == 0) {
		do {
			x = close (mapfile->fd);
		} while ((x != 0) && (errno == EINTR));

		return -3;	// fstat failed
	}

	mapfile->len = statbuf.st_size;
	mapfile->addr = mmap (NULL, mapfile->len, mapfile->m_prot,
				mapfile->m_flag, mapfile->fd,
				mapfile->offset);
	if (!(mapfile->addr)) {
		do {
			x = close (mapfile->fd);
		} while ((x != 0) && (errno == EINTR));

		return -4;	// mmap failed
	}

	return 0;
}

int lnix_munmapFile (lnix_mapFileStruct *mapfile) {
	int x;

	if (!munmap (mapfile->addr, mapfile->len)) {
		return -1;	// munmap failed
	}

	do {
		x = close (mapfile->fd);
	} while ((x != 0) && (errno == EINTR));

	return 0;
}

int lnix_mremapFile (off_t newSize, lnix_mapFileStruct *mapfile) {
	int status = 0;

	if (!ftruncate (mapfile->fd, newSize)) {
		return -1;	// ftruncate failed
	}

	void *addr = mmap (NULL, newSize, mapfile->m_prot,
				mapfile->m_flag, mapfile->fd,
				mapfile->offset);
	if (!addr) {
		return -2;	// mmap new range failed
	}

	if (!munmap (mapfile->addr, mapfile->len)) {
		status = 1;	// munmap old range failed
	}

	mapfile->addr = addr;
	mapfile->len = newSize;

	return status;
}
