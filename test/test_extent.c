#include "pbc.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define COUNT 1000000

static void
read_file (const char *filename , struct pbc_slice *slice) {
	FILE *f = fopen(filename, "rb");
	if (f == NULL) {
		slice->buffer = NULL;
		slice->len = 0;
		return;
	}
	fseek(f,0,SEEK_END);
	slice->len = ftell(f);
	fseek(f,0,SEEK_SET);
	slice->buffer = malloc(slice->len);
	fread(slice->buffer, 1 , slice->len , f);
	fclose(f);
}

static void
dump(uint8_t *buffer, int sz) {
	int i , j;
	for (i=0;i<sz;i++) {
		printf("%02X ",buffer[i]);
		if (i % 16 == 15) {
			for (j = 0 ;j <16 ;j++) {
				char c = buffer[i/16 * 16+j];
				if (c>=32 && c<127) {
					printf("%c",c);
				} else {
					printf(".");
				}
			}
			printf("\n");
		}
	}

	printf("\n");
}

static void
test(struct pbc_env *env) {
	struct pbc_wmessage * c2r = pbc_wmessage_new(env, "msg.region.Client2Region");
	pbc_wmessage_integer(c2r, "msg_id", 1005, 0);
	struct pbc_wmessage * login = pbc_wmessage_message(c2r,
		"msg.region.basic.Login.login");

	pbc_wmessage_integer(login, "charID", 10, 0);
	pbc_wmessage_integer(login, "seed", 20, 0);

	struct pbc_slice slice;
	pbc_wmessage_buffer(c2r, &slice);
	dump(slice.buffer, slice.len);

	struct pbc_rmessage * read = pbc_rmessage_new(env, "msg.region.Client2Region", &slice);
	struct pbc_rmessage * readLogin = pbc_rmessage_message(read, "msg.region.basic.Login.login", 0);
	int charID = pbc_rmessage_integer(readLogin, "charID", 0, NULL);
	int seed = pbc_rmessage_integer(readLogin, "seed", 0, NULL);

	pbc_wmessage_delete(c2r);
	pbc_rmessage_delete(read);
}

int
main(int argc, char *argv[]) {
	_pbcM_memory();
	struct pbc_env * env = pbc_new();
	struct pbc_slice slice;
	read_file(argv[1], &slice);
	int ret = pbc_register(env, &slice);
	assert(ret == 0);
	test(env);
	pbc_delete(env);
	_pbcM_memory();

	return 0;
}
