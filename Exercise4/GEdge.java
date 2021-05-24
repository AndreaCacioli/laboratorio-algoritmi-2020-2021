class GEdge<T extends Comparable<T>, E extends Comparable<E>> implements Comparable<GEdge<T,E>>
{
    /*
    *   A class used to represent an edge of a graph.
    *   T is the type of the key stored, while E is the tag of the edge that connects two nodes
    *       tag also represents the weight of the edge
    */ 
    public GNode<T, E> start;
    public GNode<T, E> end;
    public E tag;

    public GEdge(GNode<T,E> s, GNode<T,E> e, E t)
    {
        start = s;
        end = e;
        tag = t;
    }

    public int compareTo(GEdge<T,E> edge)
    {
        return tag.compareTo(edge.tag);
    }
    public String toString()
    {
        return tag.toString();
    }
}