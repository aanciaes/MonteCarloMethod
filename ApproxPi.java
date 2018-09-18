import java.util.Random;

public class ApproxPi {

    private static final double RADIUS = 1.0;


    public static void main(String[] args) {

        if (args.length != 1) {
            System.out.println("Usage: $ java ApproxPi numberOfTries");
            System.exit(1);
        }

        System.out.println("Approximation of Pi: " + approxPi(Integer.parseInt(args[0])));
    }


    private static double approxPi(int numberOfTries) {
        double totalShots = 0;
        double shotsInTarget = 0;
        Random r = new Random();

        for (int i = 0; i < numberOfTries; i++) {
            double xCoor = generateRandom(r);
            double yCoor = generateRandom(r);

            double distance = calculateDistanceToPoint(xCoor, yCoor);
            totalShots++;

            if (distance <= 1.0) {
                shotsInTarget++;
            }
        }

        return (shotsInTarget / totalShots) * 4;
    }

    private static double generateRandom(Random r) {
        int minRange = 0;

        return minRange + (RADIUS - minRange) * r.nextDouble();
    }

    private static double calculateDistanceToPoint(double xCoord, double yCoord) {
        return Math.sqrt((xCoord * xCoord) + (yCoord * yCoord));
    }
}