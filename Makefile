
CC = emcc
CXX = em++

ifndef RABIT
	RABIT = xgboost/rabit
endif

ifndef DMLC_CORE
	DMLC_CORE = xgboost/dmlc-core
endif

CFLAGS = -std=c++11 -O2 -Wall -fPIC --memory-init-file 0
CFLAGS += -I$(DMLC_CORE)/include -I$(RABIT)/include -I$(GTEST_PATH)/include
BUILD_DIR=dist
EXPORTED_FUNCTIONS="['_create_model', '_set_param', '_train', '_predict', '_free_memory_model']"
COMPILED_FILES = xgboost/lib/libxgboost.so

all:
	cd xgboost; make config=make/minimum.mk; cd ..;
	mkdir -p $(BUILD_DIR)/wasm;
	$(CXX) $(CFLAGS) js-interfaces.c $(COMPILED_FILES) -o $(BUILD_DIR)/wasm/xgboost.js --pre-js src/wasmPreJS.js -s BINARYEN_ASYNC_COMPILATION=1 -s NO_FILESYSTEM=1 -s BINARYEN=1 -s "BINARYEN_METHOD='native-wasm'" -s ALLOW_MEMORY_GROWTH=1 -s EXPORTED_FUNCTIONS=$(EXPORTED_FUNCTIONS) -s ASSERTIONS=1 -s SAFE_HEAP=1
	mkdir -p $(BUILD_DIR)/asm;
	$(CXX) $(CFLAGS) js-interfaces.c $(COMPILED_FILES) -o $(BUILD_DIR)/asm/xgboost.js --pre-js src/asmPreJS.js -s ALLOW_MEMORY_GROWTH=1 -s EXPORTED_FUNCTIONS=$(EXPORTED_FUNCTIONS)


#asm: js-interfaces.c svm.o libsvm/svm.h
#

#clean:
#	rm -f *~ js-interfaces.o ./svm.o