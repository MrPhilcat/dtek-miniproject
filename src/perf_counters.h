// Used for testing

#ifndef PERF_COUNTERS_H
#define PERF_COUNTERS_H

#include <stdint.h>

// Struct to hold all counter values
typedef struct {
    uint32_t cycles;
    uint32_t instructions;
    uint32_t mem_instr;
    uint32_t icache_misses;
    uint32_t dcache_misses;
    uint32_t icache_stalls;
    uint32_t dcache_stalls;
    uint32_t hazard_stalls;
    uint32_t alu_stalls;
} perf_counters_t;

// Inline assembly to read CSRs
static inline uint32_t read_csr(int csr_num) {
    uint32_t value;
    switch(csr_num) {
        case 0: asm volatile("csrr %0, mcycle" : "=r"(value)); break;
        case 1: asm volatile("csrr %0, minstret" : "=r"(value)); break;
        case 3: asm volatile("csrr %0, mhpmcounter3" : "=r"(value)); break;
        case 4: asm volatile("csrr %0, mhpmcounter4" : "=r"(value)); break;
        case 5: asm volatile("csrr %0, mhpmcounter5" : "=r"(value)); break;
        case 6: asm volatile("csrr %0, mhpmcounter6" : "=r"(value)); break;
        case 7: asm volatile("csrr %0, mhpmcounter7" : "=r"(value)); break;
        case 8: asm volatile("csrr %0, mhpmcounter8" : "=r"(value)); break;
        case 9: asm volatile("csrr %0, mhpmcounter9" : "=r"(value)); break;
        default: value = 0;
    }
    return value;
}

static inline void get_counters(perf_counters_t* c) {
    c->cycles = read_csr(0);         // Total CPU cycles
    c->instructions = read_csr(1);   // Total instructions executed[cite: 4]
    c->mem_instr = read_csr(3);      // Memory instructions[cite: 4]
    c->icache_misses = read_csr(4);  // I-cache misses[cite: 4]
    c->dcache_misses = read_csr(5);  // D-cache misses[cite: 4]
    c->icache_stalls = read_csr(6);  // I-cache stall cycles[cite: 4]
    c->dcache_stalls = read_csr(7);  // D-cache stall cycles[cite: 4]
    c->hazard_stalls = read_csr(8);  // Data hazard stall cycles[cite: 4]
    c->alu_stalls = read_csr(9);     // ALU stall cycles[cite: 4]
}

#endif