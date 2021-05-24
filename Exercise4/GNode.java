import java.util.ArrayList;

class GNode<T extends Comparable<T>, E extends Comparable<E>>
{
    public T key;
    public ArrayList<GEdge<T, E>> adjacenNodes;
    //public boolean visited;
    //public int timeEndVisit;

    GNode(T key)
    {
        this.key = key;
        adjacenNodes = new ArrayList<>();
        //visited = false;
        //timeEndVisit = Integer.MAX_VALUE;
    }


}