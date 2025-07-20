CXX = g++
VERSION = -std=c++23
FLAG = -Wall -DBOOST_LOG_DYN_LINK
INCLUDE = -I./ -I./include/
SRC = *.cpp stb.c src/glad.c
LIB_FOR_GL = -lm -ldl -lGL ./glfw-3.4/build/src/libglfw3.a
LIB_BOOST = -lboost_log_setup -lboost_log -lboost_thread -lboost_system -lpthread

TARGET = ./main
.SILENT:

.PHONY: all clean

all:
	${CXX} ${VERSION} ${FLAG} ${INCLUDE} ${SRC} -o main  ${LIB_FOR_GL} ${LIB_BOOST} && ${TARGET}

clean:
	$(RM) ${TARGET}