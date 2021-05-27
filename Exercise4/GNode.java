import java.util.ArrayList;

class GNode<T extends Comparable<T>, E extends Comparable<E>>
{

    /*
    *  This class represents a note used it in the graph class.
    *   Although all the variables are public the glass itself is only a part of the graph class and will be heading to the file user.
    *   The types used in this class have to be comparable in order to ensure that the final class will be able to compare them 
    *   T is the type of the key stored, while E is the tag of the edge that connects two nodes
    */

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