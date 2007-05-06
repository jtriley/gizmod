lib_LTLIBRARIES=libH.la
libH_la_LDFLAGS=-version-info ${VERSION}
INCLUDES=-I@top_srcdir@/	
libH_includedir=$(includedir)/H
libH_include_HEADERS=Debug.hpp Exception.hpp stringconverter.hpp SharedMemory.hpp UtilTime.hpp UtilMath.hpp FileEventWatcher.hpp DynamicBuffer.hpp Util.hpp SignalHandler.hpp Average.hpp Socket.hpp SocketServer.hpp SocketException.hpp SocketEventWatcher.hpp SocketInterface.hpp SocketClient.hpp
libH_la_SOURCES=Debug.cpp Exception.cpp stringconverter.cpp UtilTime.cpp UtilMath.cpp FileEventWatcher.cpp Util.cpp SignalHandler.cpp Average.cpp Socket.cpp SocketServer.cpp SocketException.cpp SocketEventWatcher.cpp SocketInterface.cpp SocketClient.cpp
libH_la_LIBADD=$(BOOST_LDFLAGS) $(BOOST_PROGRAM_OPTIONS_LIB) $(BOOST_FILESYSTEM_LIB) $(BOOST_THREAD_LIB) $(BOOST_PYTHON_LIB) ${BOOST_SERIALIZATION_LIB}
