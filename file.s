// write `message` to `./filename`

.data
  err_open_message:  .ascii "ERR: failed to open file\n"
  .equ err_open_message_len, .-err_open_message 
  err_write_message: .ascii "ERR: failed to write file\n"
  .equ err_write_message_len, .-err_write_message 
  filename: .asciz "output.txt"      // zero terminated ascii string
  message: .ascii "Hello, world!\n"  // ascii string
  .equ message_len, .-message

.bss
  .global fd
  .align 8
  fd: .space 8 // reserve 8 bytes, zero it (.skip to leave uninitialized)

.text
.global _start

_start:
main:
  mov x8, #56          // openat syscall
  mov x0, #-100        // AT_FDCWD
  adr x1, filename     // load address of filename into x1 | Can also be done with `ldr x1, =filename`
  mov x2, #0b1000001   // O_CREAT | O_WRONLY
  mov x3, #0b110100100 // 0o644
  svc #0               // syscall

  adr x10, fd   // load address of fd into x10
  str x0, [x10] // store file descriptor in fd

  cmp x0, #0
  blt err_open

  mov x8, #64         // write syscall
  adr x10, fd         // load address of fd
  ldr x0, [x10]       // load fd into x0
  adr x1, message     // load address of buffer
  mov x2, message_len // buffer length
  svc #0              // syscall

  cmp x0, #0
  blt err_open

  mov x8, #57   // close syscall
  adr x10, fd   // load address of fd
  ldr x0, [x10] // load fd into x0
  svc #0        // syscall

  mov x0, #0
  b exit

err_open:
  mov x8, #64
  mov x0, #1
  adr x1, err_open_message
  mov x1, err_open_message_len
  svc #0
  mov x0, #-1
  b exit

err_write:
  mov x8, #64
  mov x0, #1
  adr x1, err_write_message
  mov x1, err_write_message_len
  svc #0
  mov x0, #-2
  b exit

exit:
  mov x8, #93
  svc #0

