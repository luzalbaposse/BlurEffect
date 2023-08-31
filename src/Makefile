# ************************************************************************* #
#   LTD - Tecnologia Digital 2 - Trabajo Practico 2                         #
# ************************************************************************* #

BUILD_DIR = build
LIBS_OBJS = libbmp.o utils.o
OBJS = $(addprefix $(BUILD_DIR)/, $(LIBS_OBJS))

.PHONY: all clean

all: Blur_S Blur_P2H Blur_P2V Blur_P4H Blur_P4V Blur_P4B

Blur_S: Blur_S.c common.c
	mkdir -p build
	make -C lib
	gcc $(OBJS) $^ -o $@ -lm

Blur_P2H: Blur_P2H.c common.c
	mkdir -p build
	make -C lib
	gcc $(OBJS) $^ -o $@ -lm -lpthread

Blur_P2V: Blur_P2V.c common.c
	mkdir -p build
	make -C lib
	gcc $(OBJS) $^ -o $@ -lm -lpthread

Blur_P4H: Blur_P4H.c common.c
	mkdir -p build
	make -C lib
	gcc $(OBJS) $^ -o $@ -lm -lpthread

Blur_P4V: Blur_P4V.c common.c
	mkdir -p build
	make -C lib
	gcc $(OBJS) $^ -o $@ -lm -lpthread

Blur_P4B: Blur_P4B.c common.c
	mkdir -p build
	make -C lib
	gcc $(OBJS) $^ -o $@ -lm -lpthread

clean:
	rm -fr $(BUILD_DIR)/*
	rm -f Blur_S Blur_P2H Blur_P2V Blur_P4H Blur_P4V Blur_P4B
