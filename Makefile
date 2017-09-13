
CC = emcc
CXX = em++

ifndef RABIT
	RABIT = xgboost/rabit
endif

CFLAGS = -Wall -Wconversion -O3 -fPIC --memory-init-file 0
BUILD_DIR=dist
EXPORTED_FUNCTIONS="['_hello_world']"

all:
	cd xgboost; make config=make/minimum.mk; cd ..;
	mkdir -p $(BUILD_DIR)/wasm; $(CC) $(CFLAGS) js-interfaces.c xgboost/lib/libxgboost.bc -o $(BUILD_DIR)/wasm/xgboost.js --pre-js src/wasmPreJS.js -s -s BINARYEN_ASYNC_COMPILATION=1 -s NO_FILESYSTEM=1 -s BINARYEN=1 -s "BINARYEN_METHOD='native-wasm'" -s ALLOW_MEMORY_GROWTH=1 -s EXPORTED_FUNCTIONS=$(EXPORTED_FUNCTIONS)


#asm: js-interfaces.c svm.o libsvm/svm.h
#	mkdir -p $(BUILD_DIR)/asm; $(CC) $(CFLAGS) js-interfaces.c svm.o -o $(BUILD_DIR)/asm/libsvm.js --pre-js src/asmPreJS.js -s ALLOW_MEMORY_GROWTH=1 -s EXPORTED_FUNCTIONS=$(EXPORTED_FUNCTIONS)

#clean:
#	rm -f *~ js-interfaces.o ./svm.o