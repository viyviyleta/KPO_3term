.586
.MODEL FLAT, stdcall

includelib kernel32.lib  ; Подключаем библиотеку для ExitProcess

ExitProcess PROTO :DWORD

.STACK 4096

.CODE

getmin PROC ad:DWORD, len:DWORD
    mov esi, ad          ; Загружаем адрес массива
    mov ecx, len         ; Загружаем количество элементов
    mov eax, [esi]       ; Инициализируем минимальное значение первым элементом
    add esi, 4           ; Переходим к следующему элементу (начинаем со второго)

next_element:
    dec ecx              ; Уменьшаем счетчик
    jz end_getmin        ; Если счетчик 0, выходим из цикла

    mov ebx, [esi]       ; Загружаем следующий элемент массива
    cmp ebx, eax         ; Сравниваем с текущим минимумом
    jl new_min           ; Если меньше, обновляем минимум

skip:
    add esi, 4           ; Переходим к следующему элементу
    jmp next_element      ; Повторяем

new_min:
    mov eax, ebx         ; Обновляем минимум
    jmp skip             ; Переходим к следующему элементу

end_getmin:
    ret                   ; Возвращаемся, результат в EAX
getmin ENDP

END
