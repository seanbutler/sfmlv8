
function fibo(n) {
    if (n == 0) {
        return 0;
    }
    else if (n == 1) {
        return 1;
    }

    return fibo(n - 1) + fibo(n - 2);
}

fibo(32);

