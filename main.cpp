#include <cstdio>
#include <iostream>
#include <vector>

typedef Word uint_32_t;
typedef RegVal uint32_t;
typedef RegId uint8_t;

static constexpr kRegFileSize = 32; //не понял, зачем именно так объявлять, еще на занятии прогуглил и так и не понял :D
static constexpr kWordSize = 4;

template<int high, int low> Word GetBits()
{
  return (word << low) & (1 << (high - low + 1) - 1);
}

template<> Word SignExtend(Word wrd)
{
  //не понял, как эта тема работает, как у вас было тоже вспомнить на смог :(
}

enum InsnId
{
  kAdd,
  kSub,
  kLb,
  kLh,
  kLw,
  kLbu,
  kLhu,
  kSb,
  kSh,
  kSw,
  kBeq,
  kBne,
  kBlt,
  kBge,
  kBltu,
  kBgeu,
  kInvalidId
};

class Instruction
{
  RegId m_rs1 {};
  RegId m_rs2 {};
  RegId m_rd {};
  Word m_imm {};
  InsnId m_insn {kInvalidId};
  bool m_branch {};

public:
  bool Decode(Word wrd)
  {

    if (GetBits<6, 0>(wrd) == 0x33)
    {
      m_rs1 = GetBits<19, 15>(wrd);
      m_rs2 = GetBits<24,20>(wrd);
      m_rd = GetBits<11, 7>(wrd);
      Word funct3 = GetBits<14,12>(wrd);
      Word funct7 = GetBits<31, 25>(wrd);

      if (funct3 == 0 && funct7 == 0)       m_insn = ;//ADD
      if (funct3 == 0 && funct7 == 0x20)    m_insn = ;//SUB
      if (funct3 == 0x3 && funct7 == 0)     m_insn = ;//XOR
      if (funct3 == 0x5 && funct7 == 0)     m_insn = ;//OR
    }

    if (GetBits<6, 0>(wrd) == 0x03)
    {
      m_rs1 = GetBits<19, 15>(wrd);
      m_rd = GetBits<11, 7>(wrd);
      Word funct3 = GetBits<14,12>(wrd);
      m_imm = GetBits<31, 20>(wrd);


      if (funct3 == 0x00)    m_insn = ;//LB
      if (funct3 == 0x01)    m_insn = ;//LH
      if (funct3 == 0x02)    m_insn = ;//LW
      if (funct3 == 0x04)    m_insn = ;//LBU
      if (funct3 == 0x05)    m_insn = ;//LHU

    }

    if (GetBits<6, 0>(wrd) == 0x63)
    {
      m_rs1 = GetBits<19, 15>(wrd);
      m_rs2 = GetBits<24,20>(wrd);
      m_rd = GetBits<11, 7>(wrd);
      Word funct3 = GetBits<14,12>(wrd);
      m_imm = (GetBits<31, 20>(wrd) << 5) | GetBits<11,7>(wrd);

      if (funct3 == 0x00)    m_insn = ;//BEQ
      if (funct3 == 0x01)    m_insn = ;//BNE
      if (funct3 == 0x04)    m_insn = ;//BLT
      if (funct3 == 0x05)    m_insn = ;//BGE
      if (funct3 == 0x06)    m_insn = ;//BLTU
    }

    if (GetBits<6, 0>(wrd) == 0x13)
    {
      m_rs1 = GetBits<19, 15>(wrd);
      m_rd = GetBits<11, 7>(wrd);
      Word funct3 = GetBits<14,12>(wrd);
      m_imm = GetBits<31, 20>(wrd);

      if (funct3 == 0x00)    m_insn = ;//ADDI
      if (funct3 == 0x02)    m_insn = ;//SLTI
      if (funct3 == 0x03)    m_insn = ;//SLTIU
      if (funct3 == 0x04)    m_insn = ;//XORI
      if (funct3 == 0x05)    m_insn = ;//ORI
      if (funct3 == 0x06)    m_insn = ;//ANDI
    }
  }

  RegId rs1() {return m_rs1;}
  RegId rs2() {return m_rs2;}
  RegId rd() {return m_rd;}
  Word imm() {return m_imm;}
  InsnId insn() {return m_insn;}
  bool branch() {return m_branch;}
};


class Hart
{
  RegVal m_reg[kRegFileSize] {};
  RegVal m_pc {};
  RegVal m_nextpc {};
  Memory* m_mem;

public:

  Memory* mem();
  void run();
};


class Memory
{

public:
  bool read(Word* result, ...);
  bool write(Word wrd, ...);
};

class BasicBlock
{
  //?? не разобрался в анордеред мэп
};

void Hart::run()
{
  bool complete = false;

  while(!complete)
  {
    std::vector<Instruction> BasicBlock;
    bool branch = false;

    while (!branch)
    {
      Word wrd;

      Instruction insn;

      //....
    }
  }
}

void(*InsnExecutor[])(Hart* hart, const Instruction& insn) = {
  add,
  sub,
  xor,
  or,
  lb,
  lh,
  ...};

void add(Hart* hart, const Instruction& insn);
void sub(Hart* hart, const Instruction& insn);
