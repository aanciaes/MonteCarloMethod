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
(only multi-threaded)

Build with `$ gcc -Wall -Werror ThreadApproxPi.c -o ThreadApproxPi`

Run with `$ ./ThreadApproxPi NumberOfShots NumberOfThreads`

## GO

### Serial
Build with `$ go build ApproxPi.go`

Run with `$ go run ApproxPi NumberOfShots`

### Multi-Threaded
Build with `$ go build ThreadApproxPi.go`

Run with `$ go run ThreadApproxPi.go NumberOfShots NumberOfThreads`
