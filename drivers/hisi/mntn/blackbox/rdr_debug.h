/*
 * blackbox header file (blackbox: kernel run data recorder.)
 *
 * Copyright (c) 2013 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef __BB_DEBUG_H__
#define __BB_DEBUG_H__

#include <linux/types.h>

static inline int rdr_debug_init(void)
{
	return 0;
}
static inline void hisi_syserr_loop_test(void)
{
	return;
}

#endif /* End #define __BB_DEBUG_H__ */
