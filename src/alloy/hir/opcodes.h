/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2013 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */

#ifndef ALLOY_HIR_OPCODES_H_
#define ALLOY_HIR_OPCODES_H_

#include <cstdint>

namespace alloy {
namespace hir {

enum CallFlags {
  CALL_TAIL = (1 << 1),
  CALL_POSSIBLE_RETURN = (1 << 2),
};
enum BranchFlags {
  BRANCH_LIKELY = (1 << 1),
  BRANCH_UNLIKELY = (1 << 2),
};
enum RoundMode {
  // to zero/nearest/etc
  ROUND_TO_ZERO = 0,
  ROUND_TO_NEAREST,
  ROUND_TO_MINUS_INFINITY,
  ROUND_TO_POSITIVE_INFINITY,
};
enum LoadFlags {
  LOAD_NO_ALIAS = (1 << 1),
  LOAD_ALIGNED = (1 << 2),
  LOAD_UNALIGNED = (1 << 3),
  LOAD_VOLATILE = (1 << 4),
};
enum StoreFlags {
  STORE_NO_ALIAS = (1 << 1),
  STORE_ALIGNED = (1 << 2),
  STORE_UNALIGNED = (1 << 3),
  STORE_VOLATILE = (1 << 4),
};
enum PrefetchFlags {
  PREFETCH_LOAD = (1 << 1),
  PREFETCH_STORE = (1 << 2),
};
enum ArithmeticFlags {
  ARITHMETIC_SET_CARRY = (1 << 1),
  ARITHMETIC_UNSIGNED = (1 << 2),
  ARITHMETIC_SATURATE = (1 << 3),
};
#define PERMUTE_MASK(sel_x, x, sel_y, y, sel_z, z, sel_w, w)            \
  ((((x)&0x3) << 0) | (sel_x << 2) | (((y)&0x3) << 8) | (sel_y << 10) | \
   (((z)&0x3) << 16) | (sel_z << 18) | (((w)&0x3) << 24) | (sel_w << 26))
enum Permutes {
  PERMUTE_IDENTITY = PERMUTE_MASK(0, 0, 0, 1, 0, 2, 0, 3),
};
#define SWIZZLE_MASK(x, y, z, w) \
  ((((x)&0x3) << 0) | (((y)&0x3) << 2) | (((z)&0x3) << 4) | (((w)&0x3) << 6))
enum Swizzles {
  SWIZZLE_XYZW_TO_XYZW = SWIZZLE_MASK(0, 1, 2, 3),
  SWIZZLE_XYZW_TO_YZWX = SWIZZLE_MASK(1, 2, 3, 0),
  SWIZZLE_XYZW_TO_ZWXY = SWIZZLE_MASK(2, 3, 0, 1),
  SWIZZLE_XYZW_TO_WXYZ = SWIZZLE_MASK(3, 0, 1, 2),
};
enum PackType {
  PACK_TYPE_D3DCOLOR = 0,
  PACK_TYPE_FLOAT16_2 = 1,
  PACK_TYPE_FLOAT16_4 = 2,
  PACK_TYPE_SHORT_2 = 3,
  PACK_TYPE_S8_IN_16_LO = 4,
  PACK_TYPE_S8_IN_16_HI = 5,
  PACK_TYPE_S16_IN_32_LO = 6,
  PACK_TYPE_S16_IN_32_HI = 7,
};

enum Opcode {
  OPCODE_COMMENT,
  OPCODE_NOP,
  OPCODE_SOURCE_OFFSET,
  OPCODE_TRACE_SOURCE,
  OPCODE_DEBUG_BREAK,
  OPCODE_DEBUG_BREAK_TRUE,
  OPCODE_TRAP,
  OPCODE_TRAP_TRUE,
  OPCODE_CALL,
  OPCODE_CALL_TRUE,
  OPCODE_CALL_INDIRECT,
  OPCODE_CALL_INDIRECT_TRUE,
  OPCODE_CALL_EXTERN,
  OPCODE_RETURN,
  OPCODE_RETURN_TRUE,
  OPCODE_SET_RETURN_ADDRESS,
  OPCODE_BRANCH,
  OPCODE_BRANCH_TRUE,
  OPCODE_BRANCH_FALSE,
  OPCODE_ASSIGN,
  OPCODE_CAST,
  OPCODE_ZERO_EXTEND,
  OPCODE_SIGN_EXTEND,
  OPCODE_TRUNCATE,
  OPCODE_CONVERT,
  OPCODE_ROUND,
  OPCODE_VECTOR_CONVERT_I2F,
  OPCODE_VECTOR_CONVERT_F2I,
  OPCODE_LOAD_VECTOR_SHL,
  OPCODE_LOAD_VECTOR_SHR,
  OPCODE_LOAD_CLOCK,
  OPCODE_LOAD_LOCAL,
  OPCODE_STORE_LOCAL,
  OPCODE_LOAD_CONTEXT,
  OPCODE_STORE_CONTEXT,
  OPCODE_LOAD,
  OPCODE_STORE,
  OPCODE_PREFETCH,
  OPCODE_MAX,
  OPCODE_VECTOR_MAX,
  OPCODE_MIN,
  OPCODE_VECTOR_MIN,
  OPCODE_SELECT,
  OPCODE_IS_TRUE,
  OPCODE_IS_FALSE,
  OPCODE_COMPARE_EQ,
  OPCODE_COMPARE_NE,
  OPCODE_COMPARE_SLT,
  OPCODE_COMPARE_SLE,
  OPCODE_COMPARE_SGT,
  OPCODE_COMPARE_SGE,
  OPCODE_COMPARE_ULT,
  OPCODE_COMPARE_ULE,
  OPCODE_COMPARE_UGT,
  OPCODE_COMPARE_UGE,
  OPCODE_DID_CARRY,
  OPCODE_DID_OVERFLOW,
  OPCODE_DID_SATURATE,
  OPCODE_VECTOR_COMPARE_EQ,
  OPCODE_VECTOR_COMPARE_SGT,
  OPCODE_VECTOR_COMPARE_SGE,
  OPCODE_VECTOR_COMPARE_UGT,
  OPCODE_VECTOR_COMPARE_UGE,
  OPCODE_ADD,
  OPCODE_ADD_CARRY,
  OPCODE_VECTOR_ADD,
  OPCODE_SUB,
  OPCODE_VECTOR_SUB,
  OPCODE_MUL,
  OPCODE_MUL_HI,  // TODO(benvanik): remove this and add INT128 type.
  OPCODE_DIV,
  OPCODE_MUL_ADD,
  OPCODE_MUL_SUB,
  OPCODE_NEG,
  OPCODE_ABS,
  OPCODE_SQRT,
  OPCODE_RSQRT,
  OPCODE_POW2,
  OPCODE_LOG2,
  OPCODE_DOT_PRODUCT_3,
  OPCODE_DOT_PRODUCT_4,
  OPCODE_AND,
  OPCODE_OR,
  OPCODE_XOR,
  OPCODE_NOT,
  OPCODE_SHL,
  OPCODE_VECTOR_SHL,
  OPCODE_SHR,
  OPCODE_VECTOR_SHR,
  OPCODE_SHA,
  OPCODE_VECTOR_SHA,
  OPCODE_ROTATE_LEFT,
  OPCODE_VECTOR_ROTATE_LEFT,
  OPCODE_BYTE_SWAP,
  OPCODE_CNTLZ,
  OPCODE_INSERT,
  OPCODE_EXTRACT,
  OPCODE_SPLAT,
  OPCODE_PERMUTE,
  OPCODE_SWIZZLE,
  OPCODE_PACK,
  OPCODE_UNPACK,
  OPCODE_COMPARE_EXCHANGE,
  OPCODE_ATOMIC_EXCHANGE,
  OPCODE_ATOMIC_ADD,
  OPCODE_ATOMIC_SUB,
  __OPCODE_MAX_VALUE,  // Keep at end.
};

enum OpcodeFlags {
  OPCODE_FLAG_BRANCH = (1 << 1),
  OPCODE_FLAG_MEMORY = (1 << 2),
  OPCODE_FLAG_COMMUNATIVE = (1 << 3),
  OPCODE_FLAG_VOLATILE = (1 << 4),
  OPCODE_FLAG_IGNORE = (1 << 5),
  OPCODE_FLAG_HIDE = (1 << 6),
  OPCODE_FLAG_PAIRED_PREV = (1 << 7),
};

enum OpcodeSignatureType {
  // 3 bits max (0-7)
  OPCODE_SIG_TYPE_X = 0,
  OPCODE_SIG_TYPE_L = 1,
  OPCODE_SIG_TYPE_O = 2,
  OPCODE_SIG_TYPE_S = 3,
  OPCODE_SIG_TYPE_V = 4,
};

enum OpcodeSignature {
  OPCODE_SIG_X = (OPCODE_SIG_TYPE_X),
  OPCODE_SIG_X_L = (OPCODE_SIG_TYPE_X) | (OPCODE_SIG_TYPE_L << 3),
  OPCODE_SIG_X_O = (OPCODE_SIG_TYPE_X) | (OPCODE_SIG_TYPE_O << 3),
  OPCODE_SIG_X_O_V =
      (OPCODE_SIG_TYPE_X) | (OPCODE_SIG_TYPE_O << 3) | (OPCODE_SIG_TYPE_V << 6),
  OPCODE_SIG_X_O_V_V = (OPCODE_SIG_TYPE_X) | (OPCODE_SIG_TYPE_O << 3) |
                       (OPCODE_SIG_TYPE_V << 6) | (OPCODE_SIG_TYPE_V << 9),
  OPCODE_SIG_X_S = (OPCODE_SIG_TYPE_X) | (OPCODE_SIG_TYPE_S << 3),
  OPCODE_SIG_X_V = (OPCODE_SIG_TYPE_X) | (OPCODE_SIG_TYPE_V << 3),
  OPCODE_SIG_X_V_L =
      (OPCODE_SIG_TYPE_X) | (OPCODE_SIG_TYPE_V << 3) | (OPCODE_SIG_TYPE_L << 6),
  OPCODE_SIG_X_V_L_L = (OPCODE_SIG_TYPE_X) | (OPCODE_SIG_TYPE_V << 3) |
                       (OPCODE_SIG_TYPE_L << 6) | (OPCODE_SIG_TYPE_L << 9),
  OPCODE_SIG_X_V_O =
      (OPCODE_SIG_TYPE_X) | (OPCODE_SIG_TYPE_V << 3) | (OPCODE_SIG_TYPE_O << 6),
  OPCODE_SIG_X_V_S =
      (OPCODE_SIG_TYPE_X) | (OPCODE_SIG_TYPE_V << 3) | (OPCODE_SIG_TYPE_S << 6),
  OPCODE_SIG_X_V_V =
      (OPCODE_SIG_TYPE_X) | (OPCODE_SIG_TYPE_V << 3) | (OPCODE_SIG_TYPE_V << 6),
  OPCODE_SIG_X_V_V_V = (OPCODE_SIG_TYPE_X) | (OPCODE_SIG_TYPE_V << 3) |
                       (OPCODE_SIG_TYPE_V << 6) | (OPCODE_SIG_TYPE_V << 9),
  OPCODE_SIG_V = (OPCODE_SIG_TYPE_V),
  OPCODE_SIG_V_O = (OPCODE_SIG_TYPE_V) | (OPCODE_SIG_TYPE_O << 3),
  OPCODE_SIG_V_V = (OPCODE_SIG_TYPE_V) | (OPCODE_SIG_TYPE_V << 3),
  OPCODE_SIG_V_V_O =
      (OPCODE_SIG_TYPE_V) | (OPCODE_SIG_TYPE_V << 3) | (OPCODE_SIG_TYPE_O << 6),
  OPCODE_SIG_V_V_O_V = (OPCODE_SIG_TYPE_V) | (OPCODE_SIG_TYPE_V << 3) |
                       (OPCODE_SIG_TYPE_O << 6) | (OPCODE_SIG_TYPE_V << 9),
  OPCODE_SIG_V_V_V =
      (OPCODE_SIG_TYPE_V) | (OPCODE_SIG_TYPE_V << 3) | (OPCODE_SIG_TYPE_V << 6),
  OPCODE_SIG_V_V_V_O = (OPCODE_SIG_TYPE_V) | (OPCODE_SIG_TYPE_V << 3) |
                       (OPCODE_SIG_TYPE_V << 6) | (OPCODE_SIG_TYPE_O << 9),
  OPCODE_SIG_V_V_V_V = (OPCODE_SIG_TYPE_V) | (OPCODE_SIG_TYPE_V << 3) |
                       (OPCODE_SIG_TYPE_V << 6) | (OPCODE_SIG_TYPE_V << 9),
};

#define GET_OPCODE_SIG_TYPE_DEST(sig) (OpcodeSignatureType)(sig & 0x7)
#define GET_OPCODE_SIG_TYPE_SRC1(sig) (OpcodeSignatureType)((sig >> 3) & 0x7)
#define GET_OPCODE_SIG_TYPE_SRC2(sig) (OpcodeSignatureType)((sig >> 6) & 0x7)
#define GET_OPCODE_SIG_TYPE_SRC3(sig) (OpcodeSignatureType)((sig >> 9) & 0x7)

typedef struct {
  uint32_t flags;
  uint32_t signature;
  const char* name;
  Opcode num;
} OpcodeInfo;

#define DEFINE_OPCODE(num, name, sig, flags) extern const OpcodeInfo num##_info;
#include <alloy/hir/opcodes.inl>
#undef DEFINE_OPCODE

}  // namespace hir
}  // namespace alloy

#endif  // ALLOY_HIR_OPCODES_H_
