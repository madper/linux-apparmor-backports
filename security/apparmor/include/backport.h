/*
 * AppArmor security module
 *
 * This file contains AppArmor file mediation function definitions.
 *
 * Copyright 2014 Canonical Ltd.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, version 2 of the
 * License.
 *
 *
 * This is a file of helper macros, defines for backporting newer versions
 * of apparmor to older kernels
 */
#ifndef __AA_BACKPORT_H
#define __AA_BACKPORT_H

#include <linux/fs.h>

/* 4.8 backport
 * 078cd8279e659989b103359bb22373cc79445bde use current_time()
 * and 3cd886666ff19e9796a519e16d94fc94f79c8a4c current_time() api
 */
static inline struct timespec current_time(struct inode *inode)
{
	struct timespec now = current_kernel_time();

	if (unlikely(!inode->i_sb)) {
		WARN(1, "current_time() called with uninitialized super_block in the inode");
		return now;
	}

	return timespec_trunc(now, inode->i_sb->s_time_gran);
}

#endif /* __AA_BACKPORT_H */
