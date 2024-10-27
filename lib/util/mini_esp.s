// Created by Tom Arlt

.global _max

_max:
    // Arguments: R0 = a, R1 = b
    cmp r0, r1           // Compare R0 with R1
    bge end              // If R0 >= R1, branch to end
    mov r0, r1           // Otherwise, move R1 into R0 (R0 = max(a, b))
end:
    ret                 // Return, result is in R0