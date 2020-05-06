package main

import (
    "bufio"
    ."fmt"
    "os"
    "sort"
)

const (
    QMAX = int(1e4 + 1e3 + 1)
    RMAX = int(1e3 + 1)
    INF = int(1e9 + 1)
)

type Pair struct {
    a, b int
}

var (
    d [QMAX]int
    depth[QMAX][RMAX]int
    queries[QMAX][]Pair
)

var in = bufio.NewReader(os.Stdin)
var out = bufio.NewWriter(os.Stdout)

func solve() int {
    _, m := readInt(), readInt()
    d := readIntArray(m)
    g := readInt()
    r := readInt()
    sort.Ints(d)

    for i := 0; i < QMAX; i++ {
        for j := 0; j < RMAX; j++ {
            depth[i][j] = INF
        }
    }
    depth[0][g] = 0

    cnt := 1
    queries[0] = append(queries[0], Pair{0, g})

    for ; cnt > 0; {
        for index := 0; index < QMAX; index++ {
            for query := 0; query < len(queries[index]); query++ {
                w, v := queries[index][query].a, queries[index][query].b
                cnt--

                i := v / (g + 1)
                rem := v % (g + 1)

                if depth[i][rem] < w { continue }

                for j := i - 1; j < i + 2; j += 2 {
                    if j < 0 || j >= m { continue }

                    dist := d[i] - d[j]
                    if dist < 0 { dist = -dist }

                    if dist > rem { continue }

                    nxt := rem - dist
                    w := rem - nxt
                    if nxt == 0 && j + 1 != m { w += r }

                    if nxt == 0 { nxt = g }

                    if depth[j][nxt] > depth[i][rem] + w {
                        depth[j][nxt] = depth[i][rem] + w
                        if j + 1 == m { return depth[j][nxt] }
                        queries[(index + w) % QMAX] = append(queries[(index + w) % QMAX], Pair{depth[j][nxt], j * (g + 1) + nxt})
                        cnt++
                    }
                }
            }
            queries[index] = []Pair{}
        }
    }
    return -1
}

func readInt() int {
    var x int
    Fscan(in, &x)
    return x
}

func readIntArray(n int) []int {
    arr := make([]int, n)
    for i:= 0; i < n; i++ { arr[i] = readInt() }
    return arr
}

func readString() string {
    var x string
    Fscan(in, &x)
    return x
}

func readLong() int64 {
    var x int64
    Fscan(in, &x)
    return x
}

func main() {
    defer out.Flush()
    Fprintln(out, solve())
}
