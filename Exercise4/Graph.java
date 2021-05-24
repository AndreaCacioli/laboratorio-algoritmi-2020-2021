import java.util.ArrayList;
import java.util.Collections;

class Graph<T extends Comparable<T>, E extends Comparable<E>> extends OGraph<T, E>
{
    
    @Override
    public void addConnection(T v1, T v2, E tag) 
    {
        if(!containsConnection(v1, v2))
        {
            if(v1.compareTo(v2) == 0)
            {
                System.err.println("Cannot add a connection from a node to itself!");
                return;
            }
            GNode<T, E> node1 = getValue(v1);
            GNode<T, E> node2 = getValue(v2);
            if(node1 == null || node2 == null)
            {
                System.err.println("Missing one node!");
                return;
            }
            GEdge<T, E> edge1  = new GEdge<>(node1,node2,tag);
            GEdge<T, E> edge2  = new GEdge<>(node2,node1,tag);
            node1.adjacenNodes.add(edge1);
            node2.adjacenNodes.add(edge2); 
        }
    }
    

    @Override
    public boolean isOriented() 
    {
        return false;
    }

    @Override
    public boolean containsConnection(T v1, T v2) 
    {
        return findTag(v1, v2) != null || findTag(v2, v1) != null;
    }

    @Override
    public void deleteConnection(T v1, T v2)  
    {
        super.deleteConnection(v1, v2);
        super.deleteConnection(v2, v1); 
    }
    
    @Override
    public int connectionsNumber() 
    {
        return super.connectionsNumber()/2;
    }

    public Graph<T,E> krusk()
    {
        Graph<T,E> startingGraph = new Graph<>(); //Creating a copy of the initial graph so that the calling object is not modified
        DSets<T> sets = new DSets<>(); 
        for(GNode<T,E> node : nodes.values())
        {
            startingGraph.add(node.key);
            sets.makeSet(node.key); //Creating every node's own set
        }
        for(GNode<T,E> node: nodes.values())
        {
            for(GEdge<T,E> edge : node.adjacenNodes)
            {
                startingGraph.addConnection(edge.start.key, edge.end.key, edge.tag);
            }
        }

        ArrayList<GEdge<T,E>> edges = getEdges();
        Collections.sort(edges); //The edges will be sorted by tag(representing the cost)

        removeDuplicates(edges);

        for(int i = 0; i < edges.size(); i++)
        {
            GEdge<T,E> edge = edges.get(i);
            int outcome = sets.union(edge.start.key, edge.end.key);

            if(outcome == -1)
            {
                startingGraph.deleteConnection(edge.start.key, edge.end.key);
                startingGraph.deleteConnection(edge.end.key, edge.start.key);
            }
        }

        return startingGraph;
    }

    
}