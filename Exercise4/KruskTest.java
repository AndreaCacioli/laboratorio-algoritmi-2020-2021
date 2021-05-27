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
            br = new BufferedReader(new FileReader("./italian_dist_graph.csv"));
            while((row = br.readLine()) != null)
            {
                String[] fields = row.split(",");
                graph.add(fields[0]);
                graph.add(fields[1]);
                graph.addConnection(fields[0], fields[1], Double.parseDouble(fields[2]));
            }

            Double weight = (Double)0.0;
            var v = graph.getTags();

            System.out.println("Distanza volpiano - superga: " + graph.findTag("volpiano", "superga"));

            for(Double d : v)
            {
                weight += d;
            }
            System.out.println("Total Weight of the forest (before krusk) = " + weight/1000 + " Km");
            System.out.println("Nodes (before krusk): " + graph.size());
            System.out.println("Edges (before krusk): " + graph.connectionsNumber());

            graph = graph.krusk();
            v = graph.getTags();
            System.out.println("");

            System.out.println("Nodes (after krusk): " + graph.size());
            System.out.println("Edges (after krusk): " + graph.connectionsNumber());

            weight = 0.0;
            for(Double d : v)
            {
                weight += d;
            }
            System.out.println("Total Weight of the forest (after krusk) = " + weight/1000 + " Km");

        }catch(Exception e)
        {
            e.printStackTrace();
        }
        


    }
}
