.global max
.global min

max:
    bge a0, a1, end_max
    mv a0, a1
end_max:
    ret


min:
    ble a0, a1, end_min
    mv a0, a1
end_min:
    ret
