// lib*nix
// the *nix library
//
// Copyright 2013 Haneef Mubarak
// All Rights Reserved

#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>

#include <assert.h>

#include <unistd.h>

#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/file.h>

#include <fcntl.h>

#pragma pack(push,1)

typedef struct {
	void	*addr;
	size_t	len;
	int	m_prot;
	int	m_flag;
	int	o_flag;
	int	lock;
	int	fd;
	off_t	offset;
} mapFileStruct;

typedef struct {
	mapFileStruct	*file;
	size_t	linecount;
	char	**line;
} sourceFileStruct;

#pragma pack(pop)

int mmapFile		(char *filename, mapFileStruct *mapfile);
int mremapFile		(off_t newSize, mapFileStruct *mapfile);
int munmapFile		(mapFileStruct *mapfile);

int getlines		(char *string, char ***lines, size_t *linecount);
int getSourceFile	(mapFileStruct *mapfile, sourceFileStruct *sourcefile);
