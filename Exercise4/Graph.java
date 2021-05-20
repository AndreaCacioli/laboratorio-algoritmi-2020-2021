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
            GEdge<T, E> edge1  = new GEdge<>();
            GEdge<T, E> edge2  = new GEdge<>();
            edge1.start = node1;
            edge2.start = node2;
            edge1.end = node2;
            edge2.end = node1;
            edge1.tag = tag;
            edge2.tag = tag;
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
        super.deleteConnection(v2, v1); //We could optimize it by manually removing each edge from each node but since O(2n) = O(n) I'm leaving it like this
    }
    @Override
    public int connectionsNumber() 
    {
        return super.connectionsNumber()/2;
    }
}