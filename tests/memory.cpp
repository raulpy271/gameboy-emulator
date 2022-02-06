
#include <gtest/gtest.h>

#include "../src/game/primitives.h"
#include "../src/game/memory.h"

TEST(Memory, choose_segment_of_memory_rom) {
  gameboy::MemorySegment segment;
  
  segment  = gameboy::Memory::choose_segment(0x0);

  EXPECT_EQ(segment, gameboy::MemorySegment::CARTRIDGE_ROM);

  segment  = gameboy::Memory::choose_segment(0x7fff);

  EXPECT_EQ(segment, gameboy::MemorySegment::CARTRIDGE_ROM);
}

TEST(Memory, choose_segment_of_memory_vram) {
  gameboy::MemorySegment segment;
  
  segment  = gameboy::Memory::choose_segment(0x8000);

  EXPECT_EQ(segment, gameboy::MemorySegment::VRAM);

  segment  = gameboy::Memory::choose_segment(0x9fff);

  EXPECT_EQ(segment, gameboy::MemorySegment::VRAM);
}