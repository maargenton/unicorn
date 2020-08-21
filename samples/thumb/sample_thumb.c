// sample_thumb.c

#include <stdint.h>
#include <string.h>
#include <unicorn/unicorn.h>


uint8_t code [] = {
    0x09,0x49,0x00,0x23,0x5A,0x00,0x41,0xF8,0x23,0x20,0x01,0x33,0x64,0x2B,0xF9,0xD1,
    0x00,0x23,0x51,0xF8,0x23,0x20,0x02,0xEB,0x43,0x02,0x41,0xF8,0x23,0x20,0x01,0x33,
    0x64,0x2B,0xF6,0xD1,0xF4,0xE7,0x00,0xBF,0x34,0x00,0x00,0x20
};

static void hook_code(uc_engine *uc, uint64_t address, uint32_t size, void *user_data)
{
    printf("Code 0x%"PRIx64 ", block size = 0x%x\n", address, size);
}

void hook_mem(uc_engine *uc, uc_mem_type type,
        uint64_t address, int size, int64_t value, void *user_data) {

    if ( type == UC_MEM_READ) {
        printf("  Read 0x%"PRIx64 ", block size = 0x%x\n", address, size);
    } else {
        printf("  Write 0x%"PRIx64 ", block size = 0x%x\n", address, size);
    }
}


static void test_thumb2(void)
{
    uc_engine *uc;
    uc_err err;
    uc_hook trace1, trace2;


    uint32_t base_addr = 0x20000000;
    uint32_t sp = base_addr + 64*1024;

    printf("Emulate THUMB code\n");

    // Initialize emulator in ARM mode
    err = uc_open(UC_ARCH_ARM, UC_MODE_THUMB, &uc);
    if (err) {
        printf("Failed on uc_open() with error returned: %u (%s)\n",
                err, uc_strerror(err));
        return;
    }

    uc_mem_map(uc, base_addr, 64 * 1024, UC_PROT_ALL);
    uc_mem_write(uc, base_addr, code, sizeof(code));
    uc_reg_write(uc, UC_ARM_REG_SP, &sp);

    uc_hook_add(uc, &trace1, UC_HOOK_CODE, hook_code, NULL, 1, 0);
    uc_hook_add(uc, &trace2, UC_HOOK_MEM_READ | UC_HOOK_MEM_WRITE, hook_mem, NULL, 1, 0);

    err = uc_emu_start(uc, base_addr | 1, base_addr + 64*1024, 0, 10000);
    if (err) {
        printf("Failed on uc_emu_start() with error returned: %u\n", err);
    }

    // now print out some registers
    printf(">>> Emulation done. Below is the CPU context\n");

    uc_reg_read(uc, UC_ARM_REG_SP, &sp);
    printf(">>> SP = 0x%x\n", sp);

    uc_close(uc);
}

int main(int argc, char **argv, char **envp)
{
    printf("==========================\n");
    test_thumb2();

    return 0;
}
