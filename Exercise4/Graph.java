import java.util.ArrayList;
import java.util.Collections;

class Graph<T extends Comparable<T>, E extends Comparable<E>> extends OGraph<T, E>
{
    /*
     * This class is used to represent a graph in which the edges are not pointing to either one of the nodes.
     * Instead two edges are created One pointing from A to B in one pointing from B to A
     * T is the type of the key stored, while E is the tag of the edge that connects two nodes
     */


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


    /*
     * 
     * An implementation of the kruskal's algorithm to find the minimum spanning tree.
     * This implementation uses a class to represent disjoint sets.
     * The final tree/forest is returned in the form of a graph.
     * 
     */
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

    public boolean hasCycleRecursive()
    {
        for(GNode<T,E> node : nodes.values())
        {
            node.visited = false;
            node.parent = null;
        }
        for(GNode<T,E> node : nodes.values())
        {
            if(!node.visited)
            {
                node.parent = node;
                if(cycleInTree(node)) return true;
            }
        }
        return false;
    }
    
    private boolean cycleInTree(GNode<T,E> node)
    {
        node.visited = true;
        for(GEdge<T,E> edge : node.adjacenNodes)
        {
            if(!edge.end.visited)
            {
                if(edge.end.parent == null) 
                {
                    edge.end.parent = node;
                }
                else return true;
            }
        }
        for(GEdge<T,E> edge : node.adjacenNodes)
        {
            if(!edge.end.visited)
            {
                if(cycleInTree(edge.end)) return true;
            }
        }
        return false;
    }
}