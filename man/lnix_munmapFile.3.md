LNIX_MMAPFILE 3 "January 2014" lib*nix "libnix Manual"
======================================================

NAME
----

lnix_munmapFile - unmap a file mapped into memory using lib*nix

LIBRARY
-------

lib*nix (libnix, -lnix)

SYNOPSIS
--------

`#include <libnix.h>`

`int lnix_munmapFile` `(lnix_mapFileStruct` **mapfile*`);`

DESCRIPTION
-----------

The `lnix_munmapFile`() function unmaps the file specified by *mapfile*. It
should be used when a file mapped into memory by `lnix_mmapFile`() is no
longer needed.

RETURN VALUES
-------------

If successful, `lnix_munmapFile` will return zero. Otherwise, it will return
a nonzero value as specified below.

ERRORS
------

`-1`
	`munmap` returned an error; check *errno* for the specific error (`munmap`(2)).

EXAMPLE
-------

`Unloading a mapfile after it is no longer in use.`

	// Unload the mapfile
	assert (lnix_munmapFile (&mapfile));

SEE ALSO
--------

`lnix_mremapFile`(3), `lnix_munmapFile`(3), `mmap`(2), `open`(2), `flock`(2), `stat`(2)


AUTHOR(S)
---------

Written for the OmniC Project `lib*nix` (`https://github.com/omnic/libnix`)

by Haneef Mubarak (`https://github.com/haneefmubarak`)
