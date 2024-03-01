.text
.global _start

_start:

main:
  mov x1, #5
  mov x2, #3
  bl pow

  mov x8, #93
  mov x0, #0
  svc #0

/* @in
 * x1 : a
 * x2 : b
 * @out
 * x0 : a ** b
 * @clobber
 * x2
 */
pow:
  mov x0, #1
  pow_loop:
  cbz x2, pow_exit
  mul x0, x0, x1
  sub x2, x2, #1
  b pow_loop
  pow_exit:
  ret

/* @in
 * x1 : dividend
 * x2 : divisor
 * @out
 * x0 : x1 % x2
 */
mod:
  udiv x0, x1, x2
  msub x0, x2, x0, x1
  ret

