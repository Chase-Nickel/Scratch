.data
  .equ MEM_SIZE, 14

.text
.global _start

_start:

main:
  // mmap
  mov x8, #222
  mov x0, #0
  mov x1, MEM_SIZE
  mov x2, #0b011
  mov x3, #0b100010  // MAP_ANON | MAP_PRIVATE
  mov x4, #0
  mov x5, #0
  svc #0
  sub sp, sp, #16
  str x0, [sp]

  // write bytes
  ldr x0, [sp]
  ldr x1, =0x48656c6c6f2c2057
  rev x1, x1
  str x1, [x0]

  ldr x1, =0x6f726c64210a
  rev x1, x1
  str x1, [x0, 8]

  // print bytes
  mov x8, #64
  mov x0, #1
  ldr x1, [sp]
  mov x2, #18
  svc #0

  // munmap
  mov x8, #215
  ldr x0, [sp]
  mov x1, MEM_SIZE
  svc #0

  // exit
  add sp, sp, #16
  mov x8, #93
  mov x0, #0
  svc #0
  
