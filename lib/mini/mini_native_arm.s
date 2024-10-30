; Created by Tom Arlt
#include "mini.h"

.global _max

_max:
    ; Arguments: R0 = a, R1 = b
    cmp W0, W1           ; Compare R0 with R1
    bge end              ; If R0 >= R1, branch to end
    mov W0, W1           ; Otherwise, move R1 into R0 (R0 = max(a, b))
end:
    ret                  ; Return, result is in R0
