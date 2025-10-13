CC      := gcc
CFLAGS  := -std=c11 -Wall -Wextra -O0 -g
INC     := -Ilinked_list -I.

SRC_ALL    := $(wildcard linked_list/*.c)
# main()이 들어있는 파일도 포함해도 되지만, UNIT_TEST가 정의되면 main이 빠짐
SRC_IMPL := linked_list/ll_all.c

TEST_SRC   := tests/test_all.c
TEST_BIN   := build/test_linked_list
RUN_BIN    := build/app            # (선택) 실제 실행용

.PHONY: all test run clean
all: test

# 단위 테스트: main()이 매크로 가드로 빠짐
test: CFLAGS += -DUNIT_TEST
test: $(TEST_BIN)
	@echo "==== RUN TEST ===="
	@$(TEST_BIN)

$(TEST_BIN): $(SRC_IMPL) $(TEST_SRC) test.h
	@mkdir -p build
	$(CC) $(CFLAGS) $(INC) $(SRC_IMPL) $(TEST_SRC) -o $(TEST_BIN)

# (선택) 실행 바이너리: UNIT_TEST 미정의 → main() 포함
# run: $(RUN_BIN)
# 	@$(RUN_BIN)

# $(RUN_BIN): $(SRC_IMPL)
# 	@mkdir -p build
# 	$(CC) $(CFLAGS) $(INC) $(SRC_IMPL) -o $(RUN_BIN)

clean:
	rm -rf build