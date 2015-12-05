all: follow-acomics

main.o: main.cpp
	clang++ -c main.cpp -std=c++11 \
	-Icasablanca/Release/include/cpprest \
	-Icasablanca/Release/include \
	-I/usr/local/include/

follow-acomics: main.o
	clang++  -o follow-acomics main.o -lcrypto -lssl \
	-Lcasablanca/build.release/Binaries \
	-L/usr/local/opt/openssl/lib \
	-l cpprest \
	-L/usr/local/lib \
	-l boost_system -l boost_system-mt -l boost_chrono -l boost_thread-mt \
	-lpthread \
	-lstdc++ \
	-framework Security \
	-framework CoreFoundation