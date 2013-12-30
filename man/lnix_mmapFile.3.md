LNIX_MMAPFILE 3 "December 2013" lib*nix "libnix Manual"
======================================================

NAME
----

lnix_mmapFile - map a file into memory

LIBRARY
-------

lib*nix (libnix, -lnix)

SYNOPSIS
--------

`#include <libnix.h>`

`int lnix_mmapFile` `(char` **filename*`,` `lnix_mapFileStruct` **mapfile*`);`

DESCRIPTION
-----------

The `lnix_mmapFile`() function maps the file specified by the *filename* into
memory using the parameters specified in the *mapfile*. It also stores the
result into *mapfile*, meaning that `lnix_mremapFile`() can be called on the
same *mapfile* to change the size of the file. When the file is no longer
needed in memory, a quick call to `lnix_munmapFile` will unmap the file from
memory.

RETURN VALUES
-------------

If successful, `lnix_mmapFile` will return zero. Otherwise, it will return a
nonzero value as specified below.

ERRORS
------

`-1`
	Could not `open` the file specified by *filename*.

`-2`
	Was not able to `lock` the file with the flags in *mapfile*`->`*lock*.

`-3`
	Could not `stat` the file; check *errno* for the specific error (`stat`(2)).

`-4`
	`mmap` returned an error; check *errno* for the specific error (`mmap`(2)).

EXAMPLE
-------

`Loading an existing read-only file (which in this case contains text)
into memory with an exclusive lock.`

	// Initialize the struct with values
	lnix_mapFileStruct mapfile;
	mapfile.m_prot = PROT_READ;
	mapfile.m_flag = MAP_FILE | MAP_SHARED;
	mapfile.o_flag = O_RDONLY;
	mapfile.lock   = LOCK_EX;
	mapfile.offset = 0;
	// Call lnix_mmapFile()
	assert (lnix_mmapFile("/path/to/file", &mapfile);
	// Use the resultant memory range
	char *text = mapfile->addr;

SEE ALSO
--------

`lnix_mremapFile`(3), `lnix_munmapFile`(3), `mmap`(2), `open`(2), `flock`(2), `stat`(2)


AUTHOR(S)
---------

Written for the OmniC Project `lib*nix` (`https://github.com/omnic/libnix`)

by Haneef Mubarak (`https://github.com/haneefmubarak`)
