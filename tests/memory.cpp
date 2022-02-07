
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

TEST(Memory, choose_segment_of_memory_cartridge_ram) {
  gameboy::MemorySegment segment;
  
  segment  = gameboy::Memory::choose_segment(0xA000);

  EXPECT_EQ(segment, gameboy::MemorySegment::CARTRIDGE_RAM);

  segment  = gameboy::Memory::choose_segment(0xBFFF);

  EXPECT_EQ(segment, gameboy::MemorySegment::CARTRIDGE_RAM);
}

TEST(Memory, choose_segment_of_memory_wram) {
  gameboy::MemorySegment segment;
  
  segment  = gameboy::Memory::choose_segment(0xC000);

  EXPECT_EQ(segment, gameboy::MemorySegment::WRAM_0);

  segment  = gameboy::Memory::choose_segment(0xCFFF);

  EXPECT_EQ(segment, gameboy::MemorySegment::WRAM_0);

  segment  = gameboy::Memory::choose_segment(0xD000);

  EXPECT_EQ(segment, gameboy::MemorySegment::WRAM_N);

  segment  = gameboy::Memory::choose_segment(0xDFFF);

  EXPECT_EQ(segment, gameboy::MemorySegment::WRAM_N);
}

TEST(Memory, choose_segment_of_memory_io_reg_and_hram_and_ie) {
  gameboy::MemorySegment segment;
  
  segment  = gameboy::Memory::choose_segment(0xFF00);

  EXPECT_EQ(segment, gameboy::MemorySegment::IO_REG_and_HRAM_and_IE);

  segment  = gameboy::Memory::choose_segment(0xFFFF);

  EXPECT_EQ(segment, gameboy::MemorySegment::IO_REG_and_HRAM_and_IE);
}

TEST(Memory, get_and_set_in_io_reg_and_ie) {
  gameboy::Memory mem;

  mem.SetInAddr(0xff00, 0x50);
  mem.SetInAddr(0xffff, 0xf0);

  EXPECT_EQ(mem.GetInAddr(0xff00), 0x50);
  EXPECT_EQ(mem.GetInAddr(0xffff), 0xf0);
}