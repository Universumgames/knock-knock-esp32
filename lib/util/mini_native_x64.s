.global _max

_max:
    cmp rdi, rsi        // Compare rdi with rsi
    jge end             // If rdi >= rsi, jump to end
    mov rdi, rsi        // Otherwise, move rsi into rdi (rdi = max(a, b))
end:
    mov rax, rdi        // Move result into rax (return register)
    ret                 // Return, result is in rax
