#include <gtest/gtest.h>
#include <limits.h>
// #include "../src/cpu.c"
// #include "../src/io.c"
// #include "../src/opcodes.c"
// #include "../src/debug.c"

#include "../src/cpu.h"
#include "../src/io.h"
#include "../src/opcodes.h"
#include "../src/debug.h"

TEST(CpuTests, InitCpu) {
  struct cpu cpu;
  init_cpu(&cpu);
  EXPECT_EQ(cpu.I, 0);
  EXPECT_EQ(cpu.pc, (uint16_t)0x200);
  EXPECT_EQ(cpu.delay_timer, 0);
  EXPECT_EQ(cpu.sound_timer, 0);
  EXPECT_EQ(*(cpu.stack.stack + 15), 0);
  EXPECT_EQ(*(cpu.V + 15), 0);
  EXPECT_EQ(*(cpu.display), 0);
  EXPECT_EQ(*(cpu.display + 2047), 0);
  EXPECT_EQ(*(cpu.keyboard + 15), 0);
}

TEST(CpuTests, stack_pop){
  struct stack my_stack;
  int my_val;
  for(int i = 0; i < 4; i++)
    my_stack.stack[i] = i * 2;
  my_stack.stack_pointer = 3;
  my_val = stack_pop(&my_stack);
  EXPECT_EQ(my_val, 4);
  my_val = stack_pop(&my_stack);
  EXPECT_EQ(my_val, 2);
  my_val = stack_pop(&my_stack);
  EXPECT_EQ(my_val, 0);
  EXPECT_EQ(my_stack.stack_pointer, 0);
  EXPECT_DEATH({stack_pop(&my_stack);}, "");
}

TEST(CpuTests, stack_push){
  struct stack my_stack;
  int my_val;
  memset(my_stack.stack, 0, sizeof(my_stack.stack));
  my_stack.stack_pointer = 0;
  EXPECT_EQ(my_stack.stack[0], 0);
  my_val = stack_push(&my_stack, 99);
  EXPECT_EQ(my_val, 1);
  EXPECT_EQ(my_stack.stack_pointer, 1);
  EXPECT_EQ(my_stack.stack[0], 99);
  my_val = stack_push(&my_stack, 1);
  EXPECT_EQ(my_stack.stack_pointer, 2);
  EXPECT_EQ(my_stack.stack[1], 1);
  EXPECT_EQ(my_val, 1);
  my_val = stack_push(&my_stack, 152);
  EXPECT_EQ(my_stack.stack_pointer, 3);
  EXPECT_EQ(my_stack.stack[2], 152);
  my_stack.stack_pointer = 14;
  my_val = stack_push(&my_stack, 9);
  EXPECT_EQ(my_stack.stack[14],9);
}

TEST(CpuTests, stack_push_and_pop) {
  struct stack my_stack;
  memset(my_stack.stack, 0, sizeof(my_stack.stack));
  my_stack.stack_pointer = 0;

  stack_push(&my_stack, 4);
  int expected[16] = {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  EXPECT_EQ(my_stack.stack_pointer, 1);
  EXPECT_TRUE(0 == memcmp(my_stack.stack, expected, 16));

  int value = stack_pop(&my_stack);
  EXPECT_EQ(value, 4);

  stack_push(&my_stack, 18);
  stack_push(&my_stack, 9);
  stack_push(&my_stack, 1);
  value = stack_pop(&my_stack);
  EXPECT_EQ(value, 1);
  value = stack_pop(&my_stack);
  EXPECT_EQ(value, 9);
  value = stack_pop(&my_stack);
  EXPECT_EQ(value, 18);
  EXPECT_DEATH({stack_pop(&my_stack);}, "");

  memset(&my_stack.stack, 0, 16);
  my_stack.stack_pointer = 15;
  stack_push(&my_stack, 4);
  int expected2[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4};
  EXPECT_TRUE(0 == memcmp(my_stack.stack, expected2, 16));
  EXPECT_DEATH({stack_push(&my_stack, 96);}, "");
}
