# MonteCarloMethod
Monte Carlo method for approximation of Pi written in multiple languages for practise

## Java

### Serial
Build `$ javac ApproxPi.java`

Run with  `$ java ApproxPi NumberOfShots`

### Multi-Threaded
Build with `$ javac -cp . ThreadApproxPi.java`

Run with `$ java ThreadApproxPi NumberOfShots NumberOfThreads`

## C

Build with `$ gcc -Wall main.c -o main`

Run with `$ ./main NumberOfShots NumberOfThreads`

## GO

Build with `go build ApproxPi.go`

Run with `go run ApproxPi NumberOfShots`
