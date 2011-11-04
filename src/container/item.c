/*!The Tiny Box Library
 * 
 * TBox is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 * 
 * TBox is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with TBox; 
 * If not, see <a href="http://www.gnu.org/licenses/"> http://www.gnu.org/licenses/</a>
 * 
 * Copyright (C) 2009 - 2011, ruki All rights reserved.
 *
 * \author		ruki
 * \file		item.c
 *
 */
/* /////////////////////////////////////////////////////////
 * includes
 */
#include "item.h"
#include "../libc/libc.h"
#include "../utils/utils.h"
#include "../platform/platform.h"

/* /////////////////////////////////////////////////////////
 * details
 */

// cstring
static tb_void_t tb_item_func_str_free(tb_item_func_t* func, tb_void_t* item)
{
	TB_ASSERT_RETURN(func);
	if (item) 
	{
		if (func->pool) tb_spool_free((tb_spool_t*)func->pool, item);
		else tb_free(item);
	}
}
static tb_void_t* tb_item_func_str_dupl(tb_item_func_t* func, tb_void_t const* item)
{
	TB_ASSERT_RETURN_VAL(func, TB_NULL);
	return func->pool? tb_spool_strdup((tb_spool_t*)func->pool, item) : tb_strdup(item);
}
#if 1
static tb_size_t tb_item_func_str_hash(tb_item_func_t* func, tb_void_t const* item, tb_size_t size)
{
	TB_ASSERT_RETURN_VAL(func && item && size, 0);

	tb_size_t h = 2166136261;
	tb_byte_t const* p = item;
	while (*p) h = 16777619 * h ^ (tb_size_t)(*p++);

	return (h & (size - 1));
}
#else
static tb_size_t tb_item_func_str_hash(tb_item_func_t* func, tb_void_t const* item, tb_size_t size)
{
	TB_ASSERT_RETURN_VAL(func && item && size, 0);
	return (tb_strlen(item) & (size - 1));
}
#endif
static tb_int_t tb_item_func_str_comp(tb_item_func_t* func, tb_void_t const* litem, tb_void_t const* ritem)
{
	TB_ASSERT_RETURN_VAL(func, 0);
	return tb_strcmp(litem, ritem);
}

static tb_char_t const* tb_item_func_str_cstr(tb_item_func_t* func, tb_void_t const* item, tb_char_t* data, tb_size_t maxn)
{
	TB_ASSERT_RETURN_VAL(func, "");
	return (tb_char_t const*)item;
}

// integer
static tb_void_t tb_item_func_int_free(tb_item_func_t* func, tb_void_t* item)
{
	TB_ASSERT_RETURN(func);
}
static tb_void_t* tb_item_func_int_dupl(tb_item_func_t* func, tb_void_t const* item)
{
	TB_ASSERT_RETURN_VAL(func, TB_NULL);
	return (tb_void_t*)item;
}
static tb_size_t tb_item_func_int_hash(tb_item_func_t* func, tb_void_t const* item, tb_size_t size)
{
	TB_ASSERT_RETURN_VAL(func && size, 0);
	return (((tb_size_t)item) ^ 0xdeadbeef) & (size - 1);
}
static tb_int_t tb_item_func_int_comp(tb_item_func_t* func, tb_void_t const* litem, tb_void_t const* ritem)
{
	TB_ASSERT_RETURN_VAL(func, 0);
	return (litem - ritem);
}
static tb_char_t const* tb_item_func_int_cstr(tb_item_func_t* func, tb_void_t const* item, tb_char_t* data, tb_size_t maxn)
{
	TB_ASSERT_RETURN_VAL(func && data, "");
	tb_int_t n = tb_snprintf(data, maxn, "%d", item);
	if (n > 0) data[n] = '\0';
	return (tb_char_t const*)data;
}

// pointer
static tb_void_t tb_item_func_ptr_free(tb_item_func_t* func, tb_void_t* item)
{
	TB_ASSERT_RETURN(func);
}
static tb_void_t* tb_item_func_ptr_dupl(tb_item_func_t* func, tb_void_t const* item)
{
	TB_ASSERT_RETURN_VAL(func, TB_NULL);
	return item;
}
static tb_size_t tb_item_func_ptr_hash(tb_item_func_t* func, tb_void_t const* item, tb_size_t size)
{
	TB_ASSERT_RETURN_VAL(func && size, 0);
	return (((tb_size_t)item) ^ 0xdeadbeef) & (size - 1);
}
static tb_int_t tb_item_func_ptr_comp(tb_item_func_t* func, tb_void_t const* litem, tb_void_t const* ritem)
{
	TB_ASSERT_RETURN_VAL(func, 0);
	return (litem - ritem);
}
static tb_char_t const* tb_item_func_ptr_cstr(tb_item_func_t* func, tb_void_t const* item, tb_char_t* data, tb_size_t maxn)
{
	TB_ASSERT_RETURN_VAL(func && data, "");
	tb_int_t n = tb_snprintf(data, maxn, "%x", item);
	if (n > 0) data[n] = '\0';
	return (tb_char_t const*)data;
}

// memory
static tb_void_t tb_item_func_mem_free(tb_item_func_t* func, tb_void_t* item)
{
	TB_ASSERT_RETURN(func);
	if (func->pool)
	{
	}
	else
	{
		if (item) tb_free(item);
	}
}
static tb_void_t* tb_item_func_mem_dupl(tb_item_func_t* func, tb_void_t const* item)
{
	TB_ASSERT_RETURN_VAL(func && func->priv, TB_NULL);
		
	if (func->pool)
	{
	}
	else
	{
		tb_size_t 	step = (tb_size_t)func->priv;
		tb_void_t* 	data = tb_malloc(step);
		TB_ASSERT_RETURN_VAL(data, TB_NULL);

		return tb_memcpy(data, item, step);
	}
	return TB_NULL;
}
static tb_size_t tb_item_func_mem_hash(tb_item_func_t* func, tb_void_t const* item, tb_size_t size)
{
	TB_ASSERT_RETURN_VAL(func && func->priv && item && size, 0);

	if (func->pool)
	{
	}
	else
	{
		tb_size_t step = (tb_size_t)func->priv;
		tb_size_t h = 2166136261;
		tb_byte_t const* p = item;
		tb_byte_t const* e = p + step;
		while (p < e && *p) h = 16777619 * h ^ (tb_size_t)(*p++);

		return (h & (size - 1));
	}
	return 0;
}
static tb_int_t tb_item_func_mem_comp(tb_item_func_t* func, tb_void_t const* litem, tb_void_t const* ritem)
{
	TB_ASSERT_RETURN_VAL(func, 0);
	if (func->pool)
	{
	}
	else
	{
		tb_size_t step = (tb_size_t)func->priv;
		return tb_memcmp(litem, ritem, step);
	}
	return 0;
}
static tb_char_t const* tb_item_func_mem_cstr(tb_item_func_t* func, tb_void_t const* item, tb_char_t* data, tb_size_t maxn)
{
	TB_ASSERT_RETURN_VAL(func && item && data, "");

	if (func->pool)
	{
	}
	else
	{
		tb_size_t 	step = (tb_size_t)func->priv;
		tb_int_t 	n = tb_snprintf(data, maxn, "0x%x", tb_crc_encode(TB_CRC_MODE_32_IEEE_LE, 0, item, step));
		if (n > 0) data[n] = '\0';
		return (tb_char_t const*)data;
	}
	return "";
}
/* /////////////////////////////////////////////////////////
 * implemention
 */
tb_item_func_t tb_item_func_str(tb_spool_t* spool)
{
	tb_item_func_t func;
	func.hash = tb_item_func_str_hash;
	func.comp = tb_item_func_str_comp;
	func.dupl = tb_item_func_str_dupl;
	func.cstr = tb_item_func_str_cstr;
	func.free = tb_item_func_str_free;
	func.pool = spool;
	func.priv = TB_NULL;
	return func;
}
tb_item_func_t tb_item_func_int()
{
	tb_item_func_t func;
	func.hash = tb_item_func_int_hash;
	func.comp = tb_item_func_int_comp;
	func.dupl = tb_item_func_int_dupl;
	func.cstr = tb_item_func_int_cstr;
	func.free = tb_item_func_int_free;
	func.pool = TB_NULL;
	func.priv = TB_NULL;
	return func;
}
tb_item_func_t tb_item_func_ptr()
{
	tb_item_func_t func;
	func.hash = tb_item_func_ptr_hash;
	func.comp = tb_item_func_ptr_comp;
	func.dupl = tb_item_func_ptr_dupl;
	func.cstr = tb_item_func_ptr_cstr;
	func.free = tb_item_func_ptr_free;
	func.pool = TB_NULL;
	func.priv = TB_NULL;
	return func;
}
tb_item_func_t tb_item_func_mem(tb_size_t size, tb_gpool_t* gpool)
{
	tb_item_func_t func;
	func.hash = tb_item_func_mem_hash;
	func.comp = tb_item_func_mem_comp;
	func.dupl = tb_item_func_mem_dupl;
	func.cstr = tb_item_func_mem_cstr;
	func.free = tb_item_func_mem_free;
	func.pool = gpool;
	func.priv = (tb_size_t)size;
	return func;
}

