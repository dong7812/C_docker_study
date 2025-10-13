
#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include <stdlib.h>

static int __test_failures = 0;
static int __test_count = 0;

#define TEST(name) static void name(void)
#define RUN_TEST(fn) do { \
    __test_count++; \
    printf("[ RUN      ] %s\n", #fn); \
    fn(); \
    printf("[     OK   ] %s\n", #fn); \
} while (0)

#define FAIL(msg) do { \
    __test_failures++; \
    fprintf(stderr, "  ✗ FAIL: %s (%s:%d)\n", msg, __FILE__, __LINE__); \
    exit(EXIT_FAILURE); \
} while (0)

#define ASSERT_TRUE(cond) do { \
    if (!(cond)) { \
        __test_failures++; \
        fprintf(stderr, "  ✗ ASSERT_TRUE failed: %s (%s:%d)\n", #cond, __FILE__, __LINE__); \
        exit(EXIT_FAILURE); \
    } \
} while (0)

#define ASSERT_EQ_INT(exp, act) do { \
    long long __e = (long long)(exp); \
    long long __a = (long long)(act); \
    if (__e != __a) { \
        __test_failures++; \
        fprintf(stderr, "  ✗ ASSERT_EQ_INT failed: expected=%lld actual=%lld (%s:%d)\n", \
                __e, __a, __FILE__, __LINE__); \
        exit(EXIT_FAILURE); \
    } \
} while (0)

#define ASSERT_NE_NULL(p) do { \
    if ((p) == NULL) { \
        __test_failures++; \
        fprintf(stderr, "  ✗ ASSERT_NE_NULL failed: %s is NULL (%s:%d)\n", #p, __FILE__, __LINE__); \
        exit(EXIT_FAILURE); \
    } \
} while (0)

static inline int test_summary(void) {
    if (__test_failures == 0) {
        printf("\nAll %d tests passed ✅\n", __test_count);
        return 0;
    } else {
        printf("\n%d tests failed ❌\n", __test_failures);
        return 1;
    }
}
#endif