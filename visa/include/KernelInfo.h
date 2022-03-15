/*========================== begin_copyright_notice ============================

Copyright (C) 2021 Intel Corporation

SPDX-License-Identifier: MIT

============================= end_copyright_notice ===========================*/

#ifndef KERNELINFO_
#define KERNELINFO_


#include <string>
#include <map>

class VarInfo
{
public:
    enum AddressModel {
        GLOBAL = 0,
        LOCAL = 1
    };

    enum MemAccess {
        NONE = 0,
        BLOCKED = 1,
        STATEFUL = 2,
        STATELESS = 3,
        ATOMIC = 4
    };

    int lineNb;
    const char* srcFilename;
    int size;
    short type;
    AddressModel addrModel;
    MemAccess memoryAccess;
    bool isSpill;
    bool isUniform;
    bool isConst;
    bool promoted2GRF;

    // BankConflictInfo
    int bc_count;
    int bc_sameBank;
    int bc_twoSrc;
};

struct LSCSendStats {
    // Store
    int countLSC_STORE = 0;
    int countLSC_STORE_STRIDED = 0;
    int countLSC_STORE_QUAD = 0;
    int countLSC_STORE_BLOCK2D = 0;
    int countLSC_STORE_UNCOMPRESSED = 0;
    // Load
    int countLSC_LOAD = 0;
    int countLSC_LOAD_STRIDED = 0;
    int countLSC_LOAD_QUAD = 0;
    int countLSC_LOAD_BLOCK2D = 0;

    bool hasAnyLSCSend = false;
};

struct HDCSendStats {
    // Data Cache0 Messages
      // Store
    int countDC_OWORD_BLOCK_WRITE = 0;
    int countDC_DWORD_SCATTERED_WRITE = 0;
    int countDC_BYTE_SCATTERED_WRITE = 0;
    int countDC_QWORD_SCATTERED_WRITE = 0;
    // Load
    int countDC_OWORD_BLOCK_READ = 0;
    int countDC_ALIGNED_OWORD_BLOCK_READ = 0;
    int countDC_DWORD_SCATTERED_READ = 0;
    int countDC_BYTE_SCATTERED_READ = 0;
    int countDC_QWORD_SCATTERED_READ = 0;

    // Data Cache1 Messages
      // Store
    int countDC1_UNTYPED_SURFACE_WRITE = 0;
    int countDC1_MEDIA_BLOCK_WRITE = 0;
    int countDC1_TYPED_SURFACE_WRITE = 0;
    int countDC1_A64_BLOCK_WRITE = 0;
    int countDC1_A64_UNTYPED_SURFACE_WRITE = 0;
    int countDC1_A64_SCATTERED_WRITE = 0;
    // Load
    int countDC1_UNTYPED_SURFACE_READ = 0;
    int countDC1_MEDIA_BLOCK_READ = 0;
    int countDC1_TYPED_SURFACE_READ = 0;
    int countDC1_A64_SCATTERED_READ = 0;
    int countDC1_A64_UNTYPED_SURFACE_READ = 0;
    int countDC1_A64_BLOCK_READ = 0;

    // Data Cache2 Messages
      // Store
    int countDC2_UNTYPED_SURFACE_WRITE = 0;
    int countDC2_A64_UNTYPED_SURFACE_WRITE = 0;
    int countDC2_A64_SCATTERED_WRITE = 0;
    int countDC2_BYTE_SCATTERED_WRITE = 0;
    // Load
    int countDC2_UNTYPED_SURFACE_READ = 0;
    int countDC2_A64_SCATTERED_READ = 0;
    int countDC2_A64_UNTYPED_SURFACE_READ = 0;
    int countDC2_BYTE_SCATTERED_READ = 0;

    // URB Messages
      // Store
    int countURB_WRITE_HWORD = 0;
    int countURB_WRITE_OWORD = 0;
    int countURB_SIMD8_WRITE = 0;
    // Load
    int countURB_READ_HWORD = 0;
    int countURB_READ_OWORD = 0;
    int countURB_SIMD8_READ = 0;

    bool hasAnyHDCSend = false;
};

class KERNEL_INFO
{
public:
    std::map<int, VarInfo*> variables;

    int numReg;
    int numTmpReg;
    int bytesOfTmpReg;
    int numSpillReg;
    int numFillReg;
    int precentGRFUsage;

    struct HDCSendStats hdcSends;
    struct LSCSendStats lscSends;

    int countUniformStores;
    int countUniformLoads;

    int countSIMD1;
    int countSIMD2;
    int countSIMD4;
    int countSIMD8;
    int countSIMD16;
    int countSIMD32;

    KERNEL_INFO()
    {
        numReg = 0;
        numTmpReg = 0;
        bytesOfTmpReg = 0;
        numSpillReg = 0;
        numFillReg = 0;
        precentGRFUsage = 0;

        countUniformStores = 0;
        countUniformLoads = 0;

        countSIMD1 = 0;
        countSIMD2 = 0;
        countSIMD4 = 0;
        countSIMD8 = 0;
        countSIMD16 = 0;
        countSIMD32 = 0;
    }
    ~KERNEL_INFO()
    {
        for (auto i = variables.begin(); i != variables.end(); ++i)
        {
            delete i->second;
        }
        variables.clear();
    }
};

#endif
