package main

import (
	"math"
	"math/rand"
	"fmt"
	"time"
	"os"
	"strconv"
)

func main() {

	if len(os.Args) != 2 {
		fmt.Println("Usage: $ go run ApproxPi NumberOfShots")
		return
	}

	i,err := strconv.Atoi(os.Args[1])
	if err != nil {
		// handle error
		fmt.Println(err)
		os.Exit(2)
	}
	numberOfTries := i

	rst := approxPi(numberOfTries)
	fmt.Println("Approximation of Pi", rst)
}

func approxPi(numberOfTries int) float64 {
	totalShots := 0.0
	shotsInTarget := 0.0
	rand.Seed(time.Now().UnixNano())

	for i := 0; i < numberOfTries; i++ {
		xCoord := generateRandom()
		yCoord := generateRandom()

		distance := calculateDistance(xCoord, yCoord)
		totalShots++

		if distance <= 1.0 {
			shotsInTarget++
		}
	}

	return (shotsInTarget / totalShots) * 4
}

func generateRandom() float64 {
	return rand.Float64()
}

func calculateDistance(xCoord float64, yCoord float64) float64 {
	return math.Sqrt((xCoord * xCoord) + (yCoord * yCoord))
}

