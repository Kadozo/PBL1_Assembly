sub	sp, sp, #16
mov	w8, #2
str	w8, [sp, #12]
mov	w8, #3
str	w8, [sp, #8]
ldr	w8, [sp, #12]
ldr	w9, [sp, #8]
mul	w8, w8, w9
str	w8, [sp, #4]
add 	sp, sp, #16
ret