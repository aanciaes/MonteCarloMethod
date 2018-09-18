package main

import (
	"os"
	"fmt"
	"strconv"
	"sync"
	"math/rand"
	"math"
)

var wg sync.WaitGroup
var mu sync.Mutex

var shotsInTarget = 0.0
var totalShots = 0.0

func main() {
	if len(os.Args) != 3 {
		fmt.Println("Usage: $ go run ApproxPi NumberOfShots NumberOfThreads")
		return
	}

	numberOfThreads := convertToInt(os.Args[2])
	numberOfTriesPerThread := convertToInt(os.Args[1]) / numberOfThreads

	wg.Add(numberOfThreads)

	for i:=0; i<numberOfThreads; i++ {
		go approxPiThread(numberOfTriesPerThread)
	}

	wg.Wait()
	fmt.Println("Approximation of Pi", (shotsInTarget/totalShots)*4)
}

func approxPiThread (numberOfShots int) {
	localTotalShots := 0.0
	localInTarget := 0.0

	for i := 0; i < numberOfShots; i++ {
		xCoord := rand.Float64()
		yCoord := rand.Float64()

		distance := math.Sqrt((xCoord*xCoord)+(yCoord*yCoord))
		localTotalShots++

		if distance <= 1.0 {
			localInTarget++
		}
	}

	setGlobals(localTotalShots, localInTarget)
	wg.Done()
}

func setGlobals (localTotal float64, localInTarget float64) {
	mu.Lock()

	totalShots += localTotal
	shotsInTarget += localInTarget

	mu.Unlock()
}

func convertToInt (stringNumber string) int {
	i,err := strconv.Atoi(stringNumber)
	if err != nil {
		// handle error
		fmt.Println(err)
		os.Exit(2)
	}

	return i
}