#include <gtest/gtest.h>

#include "Storage.h"

#define TEST_FILE_NAME STORAGE_MOUNT_POINT "/test.txt"
#define TEST_FILE_CONTENT "Hello, World!\n"

TEST(Storage, mount) {
    EXPECT_TRUE(mountFS());
}

TEST(Storage, createFileTest) {
    FILE* file = fopen(TEST_FILE_NAME, "w");
    EXPECT_NE(file, nullptr);
    fclose(file);
}

TEST(Storage, fileExistsTest) {
    EXPECT_TRUE(fileExists(TEST_FILE_NAME));
}

TEST(Storage, listDirTest) {
    size_t len;
    char** files = lsDir(STORAGE_MOUNT_POINT, &len);
    EXPECT_NE(files, nullptr);
    EXPECT_GT(len, 0);
    for (size_t i = 0; i < len; i++) {
        free(files[i]);
    }
    free(files);
}

TEST(Storage, writeToFileTest) {
    FILE* file = fopen(TEST_FILE_NAME, "w");
    EXPECT_NE(file, nullptr);
    fprintf(file, TEST_FILE_CONTENT);
    fclose(file);
}

TEST(Storage, readFileTest) {
    FILE* file = fopen(TEST_FILE_NAME, "r");
    EXPECT_NE(file, nullptr);
    char buffer[100];
    char* res = fgets(buffer, sizeof(buffer), file);
    EXPECT_NE(res, nullptr);
    EXPECT_STREQ(buffer, TEST_FILE_CONTENT);
    fclose(file);
}

TEST(Storage, deleteFileTest) {
    EXPECT_EQ(unlink(TEST_FILE_NAME), 0);
}

#ifdef __cplusplus
extern "C"
#endif
    int
    app_main() {
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
