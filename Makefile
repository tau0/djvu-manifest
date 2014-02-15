all:
	g++  djvudump.cpp -DHAVE_CONFIG_H GThreads.cpp DjVuMessage.cpp ByteStream.cpp GException.cpp GUnicode.cpp GString.cpp DjVuDumpHelper.cpp GURL.cpp Arrays.cpp GSmartPointer.cpp GOS.cpp GContainer.cpp DjVmDir.cpp DjVuInfo.cpp atomic.cpp IFFByteStream.cpp DjVuMessageLite.cpp BSByteStream.cpp XMLTags.cpp ZPCodec.cpp UnicodeByteStream.cpp BSEncodeByteStream.cpp DataPool.cpp

