; Created by Tom Arlt
#include "mini.h"

.global _max
.global _min

_max:
    ; Arguments: R0 = a, R1 = b
    cmp r0, r1           ; Compare R0 with R1
    bge end_max              ; If R0 >= R1, branch to end
    mov r0, r1           ; Otherwise, move R1 into R0 (R0 = max(a, b))
end_max:
    ret                  ; Return, result is in R0


_min:
    ; Arguments: R0 = a, R1 = b
    cmp r0, r1           ; Compare R0 with R1
    ble end_min              ; If R0 <= R1, branch to end
    mov r0, r1           ; Otherwise, move R1 into R0 (R0 = min(a, b))
end_min:
    ret                  ; Return, result is in R0
