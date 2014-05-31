#ifdef HAVE_CONFIG_H
# include "config.h"
#endif
#if NEED_GNUG_PRAGMAS
# pragma implementation
#endif

/** @name djvuinfo

    {\bf Synopsis}
    \begin{verbatim}
        djvudump <... iff_file_names ...>
    \end{verbatim}

    {\bf Description} --- File #"djvudump.cpp"# uses the facilities
    provided by \Ref{IFFByteStream.h} to display an indented
    representation of the chunk structure of an ``EA IFF 85'' file.
    Each line represent contains a chunk ID followed by the chunk
    size.  Additional information about the chunk is provided when
    program #djvuinfo.cpp# recognizes the chunk name and knows how to
    summarize the chunk data.  Furthermore, page identifiers are
    printed between curly braces when #djvudump# recognizes a bundled
    multipage document.  Lines are indented in order to reflect the
    hierarchical structure of the IFF files.

    {\bf Example}
    \begin{verbatim}
    % djvuinfo graham1.djvu
    graham1.djvu:
      FORM:DJVU [32553]
        INFO [5]            2325x3156, version 20, 300 dpi, gamma 2.2
	ANTa [34]	    Page annotation
	INCL [11]	    Indirection chunk (document.dir)
        Sjbz [17692]        JB2 data, no header
        BG44 [2570]         #1 - 74 slices - v1.2 (color) - 775x1052
        FG44 [1035]         #1 - 100 slices - v1.2 (color) - 194x263
        BG44 [3048]         #2 - 10 slices
        BG44 [894]          #3 - 4 slices
        BG44 [7247]         #4 - 9 slices
    \end{verbatim}

    {\bf References} ---
    EA IFF 85 file format specification:\\
    \URL{http://www.cica.indiana.edu/graphics/image_specs/ilbm.format.txt}
    or \URL{http://www.tnt.uni-hannover.de/soft/compgraph/fileformats/docs/iff.pre}

    @memo
    Prints the structure of an IFF file.
xxx
    @author
    L\'eon Bottou <leonb@research.att.com>
*/
//@{
//@}

#include "DjVuDumpHelper.h"
#include "ByteStream.h"
#include "GException.h"
#include "GOS.h"
#include "GString.h"
#include "GURL.h"
#include "DjVuMessage.h"

#include <locale.h>
#include <stdio.h>
#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>

const char *outputfile = 0;
FILE *outputf = stdout;

void
display(const GURL &url)
{
   DjVuDumpHelper helper;
   GP<ByteStream> ibs = ByteStream::create(url, "rb");
   GP<ByteStream> obs = helper.dump(ibs);
   GUTF8String str;
   size_t size = obs->size();
   char *buf = str.getbuf(obs->size());
   obs->seek(0);
   obs->readall(buf, size);
   GNativeString ns = str;
   fputs((const char*)ns, outputf);
}


void
usage()
{
  DjVuPrintErrorUTF8(
#ifdef DJVULIBRE_VERSION
          "DJVUDUMP --- DjVuLibre-" DJVULIBRE_VERSION "\n"
#endif
          "Describes DjVu and IFF85 files\n\n"
          "Usage: djvudump [-o outputfile] <iff_filenames>\n" );
  exit(1);
}

int
main(int argc, char **argv)
{
  setlocale(LC_ALL,"");
  setlocale(LC_NUMERIC,"C");

  // get output file name
  if (argc>2 && !strcmp(argv[1],"-o"))
    {
      outputfile = argv[2];
      argv += 2;
      argc -= 2;
    }

  // convert iff file name
  GArray<GUTF8String> dargv(0, argc-1);
  for(int i=0;i<argc;++i)
    dargv[i]=argv[i];
  if (argc <= 1)
    usage();
  if (outputfile && !(outputf = fopen(outputfile,"w")))
    {
      DjVuPrintErrorUTF8("djvudump: Cannot open output file.\n");
      exit(1);
    }
  G_TRY
    {
      for (int i=1; i<argc; i++)
        {
        const GURL::Filename::UTF8 url(dargv[i]);
        display(url);
        }
    }
  G_CATCH(ex)
  {
      ex.perror();
      exit(1);
  }
  G_ENDCATCH;
  return 0;
}

