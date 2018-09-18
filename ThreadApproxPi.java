import java.util.HashSet;
import java.util.Random;
import java.util.Set;
import java.util.concurrent.CountDownLatch;

public class ThreadApproxPi {

    private static final double RADIUS = 1.0;

    private static volatile double totalShots = 0;
    private static volatile double shotsInTarget = 0;

    private static CountDownLatch latch;


    public static void main(String[] args) throws InterruptedException {

        if (args.length != 2) {
            System.out.println("Usage: $ java ApproxPi numberOfTries numberOfThreads");
            System.exit(1);
        }

        int numberOfThreads = Integer.parseInt(args[1]);
        int numberOfTriesForEachThread = Integer.parseInt(args[0]) / numberOfThreads;
        //Set<Thread> threads = new HashSet();
        latch = new CountDownLatch(numberOfThreads);

        //Add new threads
        for (int i = 0; i < numberOfThreads; i++) {
            new Thread(new ApproxPiThread(numberOfTriesForEachThread)).start();
        }



        /*//Start threads
        for (Thread t : threads) {
            t.start();
        }*/

        latch.await();
        System.out.println("Approximation of Pi " + (shotsInTarget / totalShots) * 4);
    }

    private synchronized static void incrementTotalShots (int num) {
        totalShots = totalShots + num;
    }

    private synchronized static void incrementTargetShots (int num) {
        shotsInTarget = shotsInTarget + num;
    }


    @SuppressWarnings("Duplicates")
    static class ApproxPiThread implements Runnable {

        private int numberOfTries;
        private int localTotal;
        private int localTarget;

        public ApproxPiThread(int numberOfTries) {
            this.numberOfTries = numberOfTries;
            this.localTotal = 0;
            this.localTarget = 0;
        }

        @Override
        public void run() {
            try {
                approxPi(numberOfTries);
            } finally {
                latch.countDown();
            }
        }

        private void approxPi(int numberOfTries) {
            Random r = new Random();

            for (int i = 0; i < numberOfTries; i++) {
                double xCoor = generateRandom(r);
                double yCoor = generateRandom(r);

                double distance = calculateDistanceToPoint(xCoor, yCoor);
                localTotal++;

                if (distance <= 1.0) {
                    localTarget++;
                }
            }
            incrementTotalShots(localTotal);
            incrementTargetShots(localTarget);
        }

        private double generateRandom(Random r) {
            int minRange = 0;

            return minRange + (RADIUS - minRange) * r.nextDouble();
        }

        private double calculateDistanceToPoint(double xCoord, double yCoord) {
            return Math.sqrt((xCoord * xCoord) + (yCoord * yCoord));
        }
    }
}