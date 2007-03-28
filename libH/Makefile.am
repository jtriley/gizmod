lib_LTLIBRARIES=libH.la
libH_la_LDFLAGS=-version-info ${VERSION}
INCLUDES=-I@top_srcdir@/	
libH_includedir=$(includedir)/H
libH_include_HEADERS=Debug.hpp Exception.hpp stringconverter.hpp SharedMemory.hpp UtilTime.hpp UtilMath.hpp
libH_la_SOURCES=Debug.cpp Exception.cpp stringconverter.cpp UtilTime.cpp UtilMath.cpp
libH_la_LIBADD=$(PTHREADLIB) $(BOOST_LDFLAGS) $(BOOST_PROGRAM_OPTIONS_LIB)
