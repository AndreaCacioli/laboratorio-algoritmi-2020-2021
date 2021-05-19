import java.util.HashMap;
import java.util.ArrayList;

/*
 *
 *  This Class is aimed to represent a set in which one element is the representative of the hole set.
 *  The identification of a set is aided by a tree structure of its Nodes.
 *  A Path compression tecqnique is used to directly access the representative the next time a query on the key is performed
 * 
 */

class DSets<T extends Comparable<T>>
{
    private HashMap<T, Node<T>> values;//O(1) when T is given (always)
    private HashMap<Node<T>, Integer> indexes;//O(1) when Node is given (always)
    private ArrayList<Node<T>> elementsOfTheSet;//So we have direct access to data O(1)
    private Integer nextIndex = 0;

    //Space complexity O(3n) = O(n)

    DSets()
    {
        elementsOfTheSet = new ArrayList<>();
        indexes = new HashMap<>();
        values = new HashMap<>();
        nextIndex = 0;
    }

    public void makeSet(T key) //O(1) to create a new set
    {
        if(!values.containsKey(key))
        {
            Node<T> starter = new Node<T>(key);
            starter.setParent(starter);
            starter.setRank(0);
            indexes.put(starter, nextIndex);
            values.put(starter.getKey(), starter);
            nextIndex++;
        }
    }
 
    //A function that merges two sets using a Rank system
    public int union(T key1, T key2)//O(n) to find the key + O(α(n)) to get to the representative
    {
        Node<T> rep1 = findNode(key1);
        Node<T> rep2 = findNode(key2);
        if(rep1.equals(rep2))
        {
            return -1;
        } 
        else
        {
            if(rep1.getRank() >= rep2.getRank()) //Union by rank
            {
                rep2.setParent(rep1);
                if(rep1.getRank() == rep2.getRank()) rep1.rankUp();
            }
            else
            {
                rep1.setParent(rep2);
            }
            return 0;
        }
        
        
    }
    
    //This method will return the representative of the set in which key appears
    private Node<T> findNode(T key)//O(n) to find the key + O(α(n)) to get to the representative
    {
        Node<T> n = values.get(key);
        if(n == null) return null;

        Node<T> m = n;
        
        while(n != n.getParent())
        {
            n = n.getParent();
        } 
        m.setParent(n); //Path Compression
        return n;
    }

    public T find(T key)
    {
        Node<T> ret = findNode(key);
        if(ret == null) return null;
        return ret.getKey();
    }

    public int size()
    {
        return nextIndex;
    }

    public String toString()
    {
        String s = "";
        for (int i = 0; i < elementsOfTheSet.size(); i++) 
        {
            Node<T> node = elementsOfTheSet.get(i);

            if(node.getKey() == node.getParent().getKey())
            {
                s += node.getKey().toString() + "Representative!\n";
            }
            else 
            {
                s += node.getKey().toString() + " -> " + node.getParent().getKey().toString() + "\n";
            }
        }
        return s;
    }

}