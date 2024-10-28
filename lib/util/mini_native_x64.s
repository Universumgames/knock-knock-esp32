section .text
    global _max          ; Export the function

max(int, int):                               # @max(int, int)
        push    rbp
        mov     rbp, rsp
        mov     dword ptr [rbp - 8], edi
        mov     dword ptr [rbp - 12], esi
        mov     eax, dword ptr [rbp - 8]
        cmp     eax, dword ptr [rbp - 12]
        jle     .LBB0_2
        mov     eax, dword ptr [rbp - 8]
        mov     dword ptr [rbp - 4], eax
        jmp     .LBB0_3
.LBB0_2:
        mov     eax, dword ptr [rbp - 12]
        mov     dword ptr [rbp - 4], eax
.LBB0_3:
        mov     eax, dword ptr [rbp - 4]
        pop     rbp
        ret