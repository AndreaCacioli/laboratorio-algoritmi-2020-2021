import java.io.BufferedReader;
import java.io.FileReader;

class KruskTest 
{
    /*
    * This class has been created to test out the functionalities provided by the graph library.
    * In this class a file called Italian_dist_graph.csv is first scanned and then used to create a graph containing Italian cities and the distance relative to one another.
    * Then the kruskal's algorithm is used to find the minimum spanning forest of the graph.
    */ 
    public static void main(String[] args) 
    {
        Graph<String, Double> graph = new Graph<>();
        BufferedReader br;
        String row;
        try
        {
            if(args.length != 1)
            {
                System.err.println("This is a program to test kruskal's algorithm.\n\n\tPlease provide a path to a standard csv file with the following format:\n\n\t\t STRING1,STRING2,DISTANCE(double)\n\nExample Usage:\n\n\tjava KruskTest [path to file]\n");
                return;
            }
            br = new BufferedReader(new FileReader(args[0]));
            while((row = br.readLine()) != null)
            {
                String[] fields = row.split(",");
                graph.add(fields[0]);
                graph.add(fields[1]);
                graph.addConnection(fields[0], fields[1], Double.parseDouble(fields[2]));
            }

            Double weight = (Double)0.0;
            var v = graph.getTags();

            for(Double d : v)
            {
                weight += d;
            }
            System.out.println("Nodes (before krusk):\t" + graph.size());
            System.out.println("Edges (before krusk):\t" + graph.connectionsNumber());
            System.out.println("The graph has cycle (D-Set):\t" + graph.hasCycle());
            System.out.println("The graph has cycle (Recursively):\t" + graph.hasCycleRecursive());
            System.out.println("Total Weight of the forest (before krusk) =\t" + weight/1000 + " Km");

            graph = graph.krusk();
            v = graph.getTags();
            System.out.println("");
            weight = 0.0;
            for(Double d : v)
            {
                weight += d;
            }

            System.out.println("Nodes (after krusk):\t" + graph.size());
            System.out.println("Edges (after krusk):\t" + graph.connectionsNumber());
            System.out.println("The graph has cycle (D-Set):\t" + graph.hasCycle());
            System.out.println("The graph has cycle (Recursively):\t" + graph.hasCycleRecursive());
            System.out.println("Total Weight of the forest (after krusk) = " + weight/1000 + " Km");

        }catch(Exception e)
        {
            e.printStackTrace();
        }
        


    }
}
