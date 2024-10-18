#include <gtest/gtest.h>

#ifdef __cplusplus
extern "C"
#endif
    int
    app_main() {
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}