import java.io.BufferedReader;
import java.io.FileReader;

class KruskTest 
{
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

            graph = graph.krusk();


            System.out.println("Nodes: " + graph.size());
            System.out.println("Edges: " + graph.connectionsNumber());

            Double weight = 0.0;
            var v = graph.getTags();
            for(Double d : v)
            {
                weight += d;
            }
            System.out.println("Total Weight of the forest = " + weight/1000 + " Km");

        }catch(Exception e)
        {
            e.printStackTrace();
        }
        


    }
}
