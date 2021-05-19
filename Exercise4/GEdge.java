class GEdge<T extends Comparable<T>, E extends Comparable<E>>
{
    /*
    *   A class used to represent an edge of a graph.
    *       tag also represents the weight of the edge
    */ 
    public GNode<T, E> start;
    public GNode<T, E> end;
    public E tag;
}