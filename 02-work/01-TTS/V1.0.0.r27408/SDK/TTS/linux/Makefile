## common Makefile ##
#CC=arm-hisiv200-linux-gnueabi-g++
#AR=ar


INC_PATH= -I.\
          -I../include\

SRC_PATH=../src
OBJ_PATH=.
TARGET=Demo
BUILD_PATH=../lib
TARGET_PATH=../bin/linux

CPPFLAGS1=-Wall -O2 -rdynamic -fPIC -g -D__LINUX__
CPPFLAGS= $(CPPFLAGS1) -L$(BUILD_PATH) -lhci_tts -lhci_sys -lhci_curl -lpthread -lrt -ldl
SRC_FILE=$(shell cd $(SRC_PATH)&&echo *.cpp)
SRC:=$(foreach n,$(SRC_FILE),$(SRC_PATH)/$(n))

OBJ_FILE=$(SRC_FILE:.cpp=.o)
OBJ:=$(foreach n,$(OBJ_FILE),$(OBJ_PATH)/$(n))
	          
DEP_FILE=$(SRC_FILE:.cpp=.d)
DEP:=$(foreach n,$(DEP_FILE),$(OBJ_PATH)/$(n))

$(TARGET):$(SRC)
	. /usr/local/oecore-x86_64/environment-setup-armv7a-vfp-neon-oe-linux-gnueabi
	$(CXX) -o $(TARGET)  $(SRC_PATH)/common/*.cpp $(SRC_PATH)/*.cpp $(INC_PATH) $(CPPFLAGS) 
	-mv $@ $(TARGET_PATH)
clean:
	-rm -f $(OBJ)
	-rm -f $(TARGET)

cleanall:
	-rm -f $(OBJ)
	-rm -f $(TARGET)


