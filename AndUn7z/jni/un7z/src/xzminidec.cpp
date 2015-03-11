/*
 * Simple XZ decoder command line tool
 *
 * Author: Lasse Collin <lasse.collin@tukaani.org>
 *
 * This file has been put into the public domain.
 * You can do whatever you want with this file.
 */

/*
 * This is really limited: Not all filters from .xz format are supported,
 * only CRC32 is supported as the integrity check, and decoding of
 * concatenated .xz streams is not supported. Thus, you may want to look
 * at xzdec from XZ Utils if a few KiB bigger tool is not a problem.
 */

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "xz.h"
#include <sys/stat.h>

static uint8_t in[BUFSIZ];
static uint8_t out[BUFSIZ];

int main(int argc, char **argv)
{
	struct xz_buf b;
	struct xz_dec *s;
	enum xz_ret ret;
	const char *msg;

	const int ERROR = 0;
	const int CLEAN = 1;
	int result = -1;

#ifdef TENCENT
	if (argc != 3 || strcmp(argv[1], "--help") == 0) {
		fputs("Usage: xzminidec compressed.xz decompressedRawFile\n", stdout);
		return 0;
	}
#else
	if (argc >= 2 && strcmp(argv[1], "--help") == 0) {
		fputs("Uncompress a .xz file from stdin to stdout.\n"
				"Arguments other than `--help' are ignored.\n",
				stdout);
		return 0;
	}
#endif

#ifdef TENCENT
    /* Usage: xzminidec compressed.xz decompressedRawFile */
    const char *infilename = argv[1];
    const char *outfilename = argv[2];

    FILE * compressFile = fopen(infilename, "rb");
	if(compressFile == NULL)
	{
		printf("Open xz compressed file error\n");
		return 0;
	}
	
    FILE * decompressFile = fopen(outfilename, "wb+");
	if(decompressFile == NULL)
	{
		printf("Create the decompressed file error\n");
		return 0;
	}
	
#endif
		xz_crc32_init();
#ifdef XZ_USE_CRC64
		xz_crc64_init();
#endif

	/*
	 * Support up to 64 MiB dictionary. The actually needed memory
	 * is allocated once the headers have been parsed.
	 */
	s = xz_dec_init(XZ_DYNALLOC, 1 << 26);
	if (s == NULL) {
		msg = "Memory allocation failed\n";
		result =  ERROR;
	}

	b.in = in;
	b.in_pos = 0;
	b.in_size = 0;
	b.out = out;
	b.out_pos = 0;
	b.out_size = BUFSIZ;

	int cleanExit = 1;
	while (result && cleanExit) {
		if (b.in_pos == b.in_size) {
            //get the input data.
			b.in_size = fread(in, 1, sizeof(in), compressFile);
			b.in_pos = 0;
		}

		ret = xz_dec_run(s, &b);

		if (b.out_pos == sizeof(out)) {
            //output data.
			if (fwrite(out, 1, b.out_pos, decompressFile) != b.out_pos) {
				msg = "Write error\n";
				result =  ERROR;
				break;
			}

			b.out_pos = 0;
		}

		if (ret == XZ_OK)
			continue;

#ifdef XZ_DEC_ANY_CHECK
		if (ret == XZ_UNSUPPORTED_CHECK) {
			fputs(argv[0], stderr);
			fputs(": ", stderr);
			fputs("Unsupported check; not verifying "
					"file integrity\n", stderr);
			continue;
		}
#endif

        //output data.
		if (fwrite(out, 1, b.out_pos, decompressFile) != b.out_pos
				|| fflush(decompressFile)) {
			msg = "Write error\n";
			result =  ERROR;
			break;
		}

		switch (ret) {
		case XZ_STREAM_END:
			xz_dec_end(s);
            cleanExit = 0;
            result = CLEAN;
			break;

		case XZ_MEM_ERROR:
			msg = "Memory allocation failed\n";
			result = ERROR;
			break;

		case XZ_MEMLIMIT_ERROR:
			msg = "Memory usage limit reached\n";
			result = ERROR;
			break;

		case XZ_FORMAT_ERROR:
			msg = "Not a .xz file\n";
			result = ERROR;
			break;


		case XZ_OPTIONS_ERROR:
			msg = "Unsupported options in the .xz headers\n";
			result = ERROR;
			break;

		case XZ_DATA_ERROR:
		case XZ_BUF_ERROR:
			msg = "File is corrupt\n";
			result = ERROR;
			break;

		default:
			msg = "Bug!\n";
			result = ERROR;
			break;

		}
	}

#ifdef TENCENT
	if(result == CLEAN)
	{
		fclose(compressFile);

		fflush(decompressFile);
		fclose(decompressFile);

		struct stat st;
		stat(infilename, &st);
		int infile_size = st.st_size;
		stat(outfilename, &st);
		int outfile_size = st.st_size;

		printf("%s\t%d\t%s\t%d\n", infilename, infile_size, outfilename, outfile_size);

		return 0;
	}
#endif
	else if(result == ERROR)
	{

		xz_dec_end(s);

		fclose(compressFile);
		fflush(decompressFile);
		fclose(decompressFile);

		fputs(argv[0], stderr);
		fputs(": ", stderr);
		fputs(msg, stderr);
		return 1;
	}
	else
		return 0;
}
