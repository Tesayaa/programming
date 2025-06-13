import time


def quick_sort_standard(A):
    if len(A) > 0:
        _quick_sort_standard(A, 0, len(A) - 1)


def _quick_sort_standard(A, L, R):
    if L >= R:
        return

    print(f"\nСортировка с {L} по {R}")
    i, j = partition(A, L, R)

    if L < j:
        _quick_sort_standard(A, L, j)
    if i < R:
        _quick_sort_standard(A, i, R)


def partition(A, L, R):
    x = A[L]
    i = L
    j = R
    print(f"\nРазбиение: pivot = '{x}'\n")

    while i <= j:
        while i <= R and A[i] < x:
            draw_state(A, L, R, pivot=L, i=i, j=j)
            i += 1
        while j >= L and A[j] > x:
            draw_state(A, L, R, pivot=L, i=i, j=j)
            j -= 1
        if i <= j:
            draw_state(A, L, R, pivot=L, i=i, j=j, note=f"Обмен {A[i]} <-> {A[j]}")
            A[i], A[j] = A[j], A[i]
            i += 1
            j -= 1
        else:
            break

    draw_state(A, L, R, pivot=L, i=i, j=j, note="Конец разбиения")
    return (i, j)


def draw_state(A, L, R, pivot=None, i=None, j=None, note=""):
    output = ""
    for idx, ch in enumerate(A):
        mark = ch
        if idx == pivot:
            mark = f"({ch})"
        elif idx == i and idx == j:
            mark = f"¯_{ch}_¯"
        elif idx == i:
            mark = f"¯{ch}¯"
        elif idx == j:
            mark = f"_{ch}_"
        else:
            mark = f" {ch} "
        output += mark
    print(output)
    if note:
        print("  ", note)
    time.sleep(0.6)


if __name__ == "__main__":
    word = list("ПОПОВВАДИМАЛ                 ")
    print("Исходная строка:")
    draw_state(word, 0, len(word) - 1, note="Старт")

    quick_sort_standard(word)

    print("Отсортировано:")
    draw_state(word, 0, len(word) - 1, note="Готово")
