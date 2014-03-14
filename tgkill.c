/* Copyright (c) 2014, Andreas Kohn
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * * Redistributions of source code must retain the above copyright notice, this
 *  list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/signal.h>

int
main(int argc, char *argv[])
{
	int sig = SIGTERM;
	int tgid = -1;
	int tid;

	if (argc == 1) {
		printf("Usage: %s [-SIGNUM] [<tgid>] <tid>\n", argv[0]);
		return 1;
	} else if (argc == 2) {
		tid = atoi(argv[1]);
	} else if (argc == 3) {
		tgid = atoi(argv[1]);
		tid = atoi(argv[2]);
	} else if (argc == 4) {
		sig = -atoi(argv[1]);
		tgid = atoi(argv[2]);
		tid = atoi(argv[3]);
	}

#if defined(DEBUG)
	printf("DEBUG: Killing thread %d of thread group %d with signal %d\n", tid, tgid, sig);
#endif

	return syscall(SYS_tgkill, tgid, tid, sig);
}
