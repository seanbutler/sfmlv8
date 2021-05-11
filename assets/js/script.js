

function Process(n) {
    if (n===undefined)
    {
        return -1;
    }


    if (n == 0) {
        return 0;
    }
    else if (n == 1) {
        return 1;
    }

    return Process(n - 1) + Process(n - 2);
}

Process(32);

