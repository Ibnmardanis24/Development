BASE_DIR=../../../..

TEST_SRCS += bst_node_create_test.c
TEST_SRCS += bst_node_print_test.c
TEST_SRCS += bst_node_print_test_mt.c

TEST_INCLUDE += -I./include
TEST_INCLUDE += -I../../bst/include
TEST_INCLUDE += -I../../node/include
TEST_INCLUDE += -I$(BASE_DIR)/common/include
TEST_INCLUDE += -I$(BASE_DIR)/test_common/include

LIBS +=-L../../node/out/linux/ -lbst_node

# library flags
LDFLAGS += -L$(BASE_DIR)/common/$(OBJDIR) -lcommon

# Test library flags; testcases will be linked with both LDFLAGS and TEST_LDFLAGS
TEST_LDFLAGS += -L$(BASE_DIR)/test_common/$(OBJDIR) -ltest_common


include $(BASE_DIR)/build/Makefile.inc
