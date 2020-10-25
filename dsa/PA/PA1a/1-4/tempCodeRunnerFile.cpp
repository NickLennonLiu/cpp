ch(reference, 1, n + 1, p - 1),
            middle = binSearch(reference, 1, n + 1, q - 1);
        printf("%u %u\n", low, middle - low);
    }
    return 0;
}