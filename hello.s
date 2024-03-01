.data
  str: .ascii "Hello, World!\n"
  .equ str_len, . - str

.text
.global _start 

_start:
  mov x8, #64      // write syscall
  mov x0, #1       // stdout
  adr x1, str 
  mov x2, str_len
  svc #0           // syscall

  mov x8, #93 // exit syscall
  mov x0, #0  // ret val
  svc #0      // syscall

