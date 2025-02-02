# ========================== begin_copyright_notice ============================
#
# Copyright (C) 2022 Intel Corporation
#
# SPDX-License-Identifier: MIT
#
# =========================== end_copyright_notice =============================

#===----------------------------------------------------------------------===//
#
# This file defines all of the Internal-specific intrinsics, which correspond to
# vISA instructions.
#
# Comment lines with a triple slash ### introduction are extracted and
# appended to docs/Targets/Internal/InternalLangRef.rst to give the Internal backend
# language reference in docs/autogenerated/Targets/Internal/InternalLangRef.rst.
#
#===------------------------------------------------------------------------===#

#------------ Currently Supported Types ----------------------
#PointerTypes = ["ptr_private", "ptr_global", "ptr_constant", "ptr_local", "ptr_generic"]
#FloatingPointTypes = ["half", "float", "double"]
#IntegerTypes = ["bool", "char", "short", "int", "long"]
#AdditionalTypes = ["vararg"]
#IntrinsicsProperties = ["None", "NoMem", "ReadArgMem", "ReadMem", "ReadWriteArgMem", "NoReturn", "NoDuplicate", "Convergent"]
#IntrinsicsProperties may be specified as a comma separated list(e.g., "Convergent,NoMem")
#
# EX. "blah": {"result" : {return_type}, "arguments" : [arg1_type, arg2_type.....], "attributes" : Property }
#
# The "any" type can be followed by a default type if a type is not explicitly specified : Ex. "any:int"
#
# 0 - LLVMMatchType<0>
# 1 - LLVMMatchType<1>
# {int} - LLVMMatchType<{int}>

Imported_Intrinsics = \
{

## ``llvm.vc.internal.jump.table`` : CMC internal, no VISA
## ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
##
## * arg0: integer BasicBlock index in the full set of destinations
## * arg1-N: the full set of switch labels
##
## * Return value: selected label
##
## The intrinsic is a helper for switch jump tables generation. Arg0
## will be used by visa switchjmp as index. Return value and arg1-N are
## used to make ir semantically legal.
##
    "jump_table" : { "result" : "anyptr",
                     "arguments" :  ["anyint", "vararg"],
                     "attributes" :  "NoMem"
                   },

## ``llvm.vc.internal.read.variable.region`` : read a vISA variable region
## ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
##
## * arg0: ptr pointer to a global variable that corresponds to a vISA variable
##         (overloaded)
## * arg1: i32 vstride in elements, constant
## * arg2: i32 width in elements, constant
## * arg3: i32 stride in elements, constant
## * arg4: i32 offset in elements, constant
##
## * Return value: iN, fN, vXiN, vXfN the read value (overloaded)
##
## This corresponds to MOV instruction or a general source operand in visa.
## Utilizes technique of using global variable in LLVM IR for predefined
## vISA variables.
##
    "read_variable_region" : { "result": "any",
                               "arguments" : ["anyptr", "int", "int", "int",
                                              "int"],
                               "attributes" : "ReadMem",
                              },

## ``llvm.vc.internal.write.variable.region`` : write a vISA variable region
## ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
##
## * arg0: ptr pointer to a global variable that corresponds to a vISA variable
##         (overloaded)
## * arg1: iN, fN, vXiN, vXfN value to write (overloaded)
## * arg2: i32 stride in elements, constant
## * arg3: i32 offset in elements, constant
## * arg4: i1 or vXi1 mask (overloaded)
##
## This corresponds to MOV instruction or a general destination operand in visa.
## Utilizes technique of using global variable in LLVM IR for predefined
## vISA variables.
##
    "write_variable_region" : { "result": "void",
                                "arguments" : ["anyptr", "any", "int",
                                               "int", "anyint"],
                                "attributes" : "WriteMem",
                              },

}
