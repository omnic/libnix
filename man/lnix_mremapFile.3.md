LNIX_MREMAPFILE 3 "January 2014" lib*nix "libnix Manual"
========================================================

NAME
----

lnix_mremapFile - resize and remap a mapped file in one go

LIBRARY
-------

lib*nix (libnix, -lnix)

SYNOPSIS
--------

`#include <libnix.h>`

`int lnix_mremapFile` `(off_t` *newSize*`,  lnix_mapFileStruct` **mapfile*`);`

DESCRIPTION
-----------
The `lnix_mremapFile`() function resizes the file specified by *mapfile* to
the size specified by *newSize*, after which it remaps the file.

RETURN VALUES
-------------

If successful, `lnix_mremapFile` will return zero. Otherwise, it will return
a nonzero value as specified below.

ERRORS
------

`-1`
	`ftruncate` returned an error; check *errno* for the specific error (`ftruncate`(2)).

`-2`
	Failed to remap the new range; `mmap` failed; check *errno* for the specific error (`mmap`(2)).

`1`
	Non-critical error: failed to unmap the old page range.

EXAMPLE
-------

`Resizing a mapfile on the fly.`

	// Increase filesize by 64k while also checking for critical errors
	assert (lnix_mremapfile (mapfile->len + 65536, mapfile) >= 0);

SEE ALSO
--------

`lnix_mmapFile`(3), `lnix_munmapFile`(3), `mmap`(2), `open`(2), `flock`(2), `stat`(2)


AUTHOR(S)
---------

Written for the OmniC Project `lib*nix` (`https://github.com/omnic/libnix`)

by Haneef Mubarak (`https://github.com/haneefmubarak`)
