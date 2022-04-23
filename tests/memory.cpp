
#include <gtest/gtest.h>

#include "../src/game/primitives.h"
#include "../src/game/memory.h"
#include "../src/game/hardware_registers.h"
#include "../src/game/hardware_definitions.h"

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

TEST(Memory, choose_segment_of_memory_OAM) {
  gameboy::MemorySegment segment;
  
  segment  = gameboy::Memory::choose_segment(0xFE00);

  EXPECT_EQ(segment, gameboy::MemorySegment::OAM);

  segment  = gameboy::Memory::choose_segment(0xFE9F);

  EXPECT_EQ(segment, gameboy::MemorySegment::OAM);

  segment  = gameboy::Memory::choose_segment(0xFEA0);

  EXPECT_NE(segment, gameboy::MemorySegment::OAM);
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

  mem.SetInAddr(0xff06, 0x50);
  mem.SetInAddr(0xffff, 0xf0);

  EXPECT_EQ(mem.GetInAddr(0xff06), 0x50);
  EXPECT_EQ(mem.GetInAddr(0xffff), 0xf0);
}

TEST(Memory, get_and_set_in_vram) {
  gameboy::Memory mem;

  mem.SetInAddr(0x8000, 0x50);
  mem.SetInAddr(0x9FFF, 0x60);

  EXPECT_EQ(mem.GetInAddr(0x8000), 0x50);
  EXPECT_EQ(mem.GetInAddr(0x9FFF), 0x60);
}

TEST(Memory, get_and_set_in_OAM) {
  gameboy::Memory mem;

  mem.SetInAddr(0xFE00, 0x50);
  mem.SetInAddr(0xFE9F, 0x60);

  EXPECT_EQ(mem.GetInAddr(0xFE00), 0x50);
  EXPECT_EQ(mem.GetInAddr(0xFE9F), 0x60);
}

TEST(Memory, get_and_set_in_wram0) {
  gameboy::Memory mem;

  mem.SetInAddr(0xC000, 0x50);
  mem.SetInAddr(0xCFFF, 0x60);

  EXPECT_EQ(mem.GetInAddr(0xC000), 0x50);
  EXPECT_EQ(mem.GetInAddr(0xCFFF), 0x60);
}

TEST(Memory, get_and_set_in_wramN) {
  gameboy::Memory mem;

  mem.SetInAddr(0xD000, 0x50);
  mem.SetInAddr(0xDFFF, 0x60);

  EXPECT_EQ(mem.GetInAddr(0xD000), 0x50);
  EXPECT_EQ(mem.GetInAddr(0xDFFF), 0x60);
}

TEST(Memory, get_and_set_in_cartridge_ram) {
  gameboy::Memory mem;

  mem.SetInAddr(0xA000, 0x50);
  mem.SetInAddr(0xBFFF, 0x60);

  EXPECT_EQ(mem.GetInAddr(0xA000), 0x50);
  EXPECT_EQ(mem.GetInAddr(0xBFFF), 0x60);
}

TEST(Memory, writing_to_DMA) {
  gameboy::Memory mem;
  Address source = 0x3000;
  Byte source_high_byte = 0x30;
  Byte value_in_source = 0x5;

  for (Address i = source; i <= 0x309F; i++) {
    mem.SetInAddr(i, value_in_source);
  }

  mem.SetInAddr(rDMA, source_high_byte);

  for (Address add = OAM_START_LOCATION; add <= OAM_END_LOCATION; add++) {
    EXPECT_EQ(mem.GetInAddr(add), value_in_source);
  }
}

TEST(Memory, writing_to_DMA_random_data) {
  gameboy::Memory mem;
  Address source = 0x3000;
  Byte source_high_byte = 0x30;

  for (Address i = source; i <= 0x309F; i++) {
    if (i % 2 == 0) {
      mem.SetInAddr(i, 2);
    } else {
      mem.SetInAddr(i, 3);
    }
  }

  mem.SetInAddr(rDMA, source_high_byte);

  for (Address add = OAM_START_LOCATION; add <= OAM_END_LOCATION; add++) {
    if (add % 2 == 0) {
      EXPECT_EQ(mem.GetInAddr(add), 2);
    } else {
      EXPECT_EQ(mem.GetInAddr(add), 3);
    }
  }
}