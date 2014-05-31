#ifndef _DJVUDUMPHELPER_H
#define _DJVUDUMPHELPER_H
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#if NEED_GNUG_PRAGMAS
# pragma interface
#endif


/** @name DjVuDupmHelper.h
    This file contains code capable of generating information on
    DjVu documents without actually decoding them. The code has
    been extracted from a command line utility \Ref{djvudump.cpp}
    for use in the DjVu plugin.
    @memo
    DjVu Dump Helper.
    @author
    L\'eon Bottou <leonb@research.att.com> -- as a separate program.\\
    Andrei Erofeev <eaf@geocities.com> -- as a class.
*/
//@{



#include "GSmartPointer.h"

#ifdef HAVE_NAMESPACES
namespace DJVU {
# ifdef NOT_DEFINED // Just to fool emacs c++ mode
}
#endif
#endif

class DataPool;
class ByteStream;

/** DjVuDumpHelper.
    This class can dump information on any DjVu file without decoding it.
    Based upon old \Ref{djvudump.cpp} code.
 */

class DJVUAPI DjVuDumpHelper
{
public:
      /// Default constructor
   DjVuDumpHelper(void) {}
      /// Destructor
   ~DjVuDumpHelper(void) {}
      /** Interprets the file passed in the \Ref{DataPool}, and returns
	  the results in \Ref{ByteStream}. */
   GP<ByteStream>	dump(const GP<DataPool> & pool);
      /** Interprets the file passed in the \Ref{ByteStream}, and returns
	  the results in \Ref{ByteStream}. */
   GP<ByteStream>	dump(GP<ByteStream> str);
};


//@}

// ----- THE END

#ifdef HAVE_NAMESPACES
}
# ifndef NOT_USING_DJVU_NAMESPACE
using namespace DJVU;
# endif
#endif
#endif
