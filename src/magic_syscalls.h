/*
 * Copyright 2017, Intel Corporation
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in
 *       the documentation and/or other materials provided with the
 *       distribution.
 *
 *     * Neither the name of the copyright holder nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * magic_syscalls.h - internal interface used to send messages
 *  to libsyscall_intercept from testing code. Using this dirty trick
 *  avoids adding additional symbols to the public interface just
 *  for testing.
 *
 * If the need arises, this can be disabled by defining the
 * SYSCALL_INTERCEPT_WITHOUT_MAGIC_SYSCALLS macro during compilation.
 */

#ifndef INTERCEPT_MAGIC_SYSCALLS_H
#define INTERCEPT_MAGIC_SYSCALLS_H

#ifndef SYSCALL_INTERCEPT_WITHOUT_MAGIC_SYSCALLS


#include <syscall.h>
#include <unistd.h>

enum { SYSCALL_INT_MAGIC_WRITE_FD = 123 };

static const char start_log_message[] = "SYSCALL_INTERCEPT_TEST_START_LOG";
static const char stop_log_message[] = "SYSCALL_INTERCEPT_TEST_STOP_LOG";

static inline void
magic_syscall_start_log(const char *path, const char *trunc)
{
	syscall(SYS_write, SYSCALL_INT_MAGIC_WRITE_FD,
	    start_log_message, sizeof(start_log_message),
	    path, trunc);
}

static inline void
magic_syscall_stop_log(void)
{
	syscall(SYS_write, SYSCALL_INT_MAGIC_WRITE_FD,
	    stop_log_message, sizeof(stop_log_message));
}

int
handle_magic_syscalls(long nr, long arg0, long arg1,
			long arg2, long arg3,
			long arg4, long arg5);


#else /* SYSCALL_INTERCEPT_WITHOUT_MAGIC_SYSCALLS */


static inline void
magic_syscall_start_log(const char *path)
{
	(void) path;
}

static inline void
magic_syscall_stop_log(void)
{
}

static inline int
handle_magic_syscalls(long nr, long arg0, long arg1,
			long arg2, long arg3,
			long arg4, long arg5)
{
	(void) nr;
	(void) arg0;
	(void) arg1;
	(void) arg2;
	(void) arg3;
	(void) arg4;
	(void) arg5;

	return -1;
}


#endif /* SYSCALL_INTERCEPT_WITHOUT_MAGIC_SYSCALLS */

#endif
