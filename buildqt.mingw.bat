@Echo off
set PATH=%PATH%;D:\Dev\deps\Qt\4.8.5\bin
qmake bonus.pro "CONFIG+=static" BOOST_LIB_SUFFIX=-mgw48-mt-s-1_55 BOOST_INCLUDE_PATH=D:/Dev/deps/boost_1_55_0 BOOST_LIB_PATH=D:/Dev/deps/boost_1_55_0/stage/lib BDB_INCLUDE_PATH=D:/Dev/deps/db-4.8.30.NC/build_unix BDB_LIB_PATH=D:/Dev/deps/db-4.8.30.NC/build_unix OPENSSL_INCLUDE_PATH=D:/Dev/deps/openssl-1.0.1e/include OPENSSL_LIB_PATH=D:/Dev/deps/openssl-1.0.1e MINIUPNPC_INCLUDE_PATH=D:/Dev/deps MINIUPNPC_LIB_PATH=D:/Dev/deps/miniupnpc
Echo Run mingw32-make -f Makefile.Release to build