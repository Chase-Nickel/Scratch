// write `message` to `./filename`

.data
  err_open_message:  .ascii "ERR: failed to open file\n"
  .equ err_open_message_len, .-err_open_message 
  err_write_message: .ascii "ERR: failed to write file\n"
  .equ err_write_message_len, .-err_write_message 
  filename: .asciz "output.txt"
  message: .ascii "Hello, world!\n"
  .equ message_len, .-message

.bss
  .global fd
  .align 8
  fd: .space 8
  .global argc
  .align 8
  argc: .space 8
  .global argv
  .align 16
  argv: .space 16

.text
.global _start

_start:
main:
  adr x10, argc
  ldr x9, [sp]
  str x9, [x10]

  adr x10, argv
  ldr x9, [sp, 16]
  str x9, [x10]

  mov x8, #56          // openat
  mov x0, #-100        // AT_FDCWD
  adr x1, filename
  mov x2, #0b1000001   // O_CREAT | O_WRONLY
  mov x3, #0b110100100 // 0o644
  svc #0

  adr x10, fd
  str x0, [x10]

  cmp x0, #0
  blt err_open

  mov x8, #64 // write
  adr x10, fd
  ldr x0, [x10]
  ldr x1, =argv
  ldr x1, [x1] // TODO: figure out argv: pointing to what should be argv[1]. How to index?
  ldr x1, [x1]
  adr x10, argc
  ldr x2, [x10]
  svc #0

  cmp x0, #0
  blt err_open

  mov x8, #57 // close
  adr x10, fd
  ldr x0, [x10]
  svc #0

  mov x0, #0
  b exit

err_open:
  mov x8, #64 // write
  mov x0, #1
  adr x1, err_open_message
  mov x1, err_open_message_len
  svc #0
  mov x0, #-1
  b exit

err_write:
  mov x8, #64 // write
  mov x0, #1
  adr x1, err_write_message
  mov x1, err_write_message_len
  svc #0
  mov x0, #-2
  b exit

exit:
  mov x8, #93 // exit
  svc #0

