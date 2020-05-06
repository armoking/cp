package main

import (
    "bufio"
    ."fmt"
    "os"
)

func main() {
    in := bufio.NewReader(os.Stdin)
    out := bufio.NewWriter(os.Stdout)
    defer out.Flush()

    var t int
    Fscan(in, &t)

    for test := 0; test < t; test++ {
        var a, b, q int
        Fscan(in, &a, &b, &q)
        var reminders []int64
        n := int64(a * b)

        for i := 1; i < int(n); i++ {
            if (i % a) % b != (i % b) % a {
                reminders = append(reminders, int64(i))
            }
        }

        length := len(reminders)

        var l, r, L, R, ans int64

        for subtest := 0; subtest < q; subtest++ {
            Fscan(in, &l, &r)
            l--
            L = l / n
            R = r / n
            l = l % n
            r = r % n
            ans = (R - L) * int64(length)
            left := 0
            right := length - 1
            mid := 0
            lBigger := 0
            rBigger := 0
            for ; left <= right; {
                mid = (left + right) / 2
                if reminders[mid] <= l {
                    lBigger = mid + 1
                    left = mid + 1
                } else {
                    right = mid - 1
                }
            }

            left = 0
            right = length - 1
            for ; left <= right ; {
                mid = (left + right) / 2
                if reminders[mid] <= r {
                    rBigger = mid + 1
                    left = mid + 1
                } else {
                    right = mid - 1
                }
            }

            ans += int64(rBigger - lBigger)

            Fprint(out, ans, " ")
        }
        Fprint(out, "\n")
    }

}
