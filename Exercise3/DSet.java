import java.util.LinkedList;

/*
 *
 *  This Class is aimed to represent a set in which one element is the representative of the hole set.
 *  The identification of a set is aided by a tree structure of its Nodes.
 *  A Path compression tecqnique is used to directly access the representative the next time a query on the key is performed
 * 
 */

class DSet<T>
{
    private LinkedList<Node<T>> elementsOfTheSet;

    protected LinkedList<Node<T>> getElementsOfTheSet()
    {
        return elementsOfTheSet;
    }

    DSet()
    {
        makeSet(null);
    }
    DSet(T key)
    {
        elementsOfTheSet = new LinkedList<Node<T>>();
        makeSet(key);
    }

    public void makeSet(T key)
    {
        Node<T> starter = new Node<T>(key);
        starter.setParent(starter);
        starter.setRank(0);
        elementsOfTheSet.add(starter); 
    }
 
    //A function that merges two sets using a Rank system
    public void Union(DSet<T> d)
    {
        Node<T> representative1 = findNode(elementsOfTheSet.get(0).getKey());
        Node<T> representative2 = d.findNode(d.getElementsOfTheSet().get(0).getKey());
        if(representative1.getRank() >= representative2.getRank())
        {
            this.elementsOfTheSet.addAll(d.getElementsOfTheSet()); //Get all elements
            representative2.setParent(representative1);//winner becomes new representative
            if(representative1.getRank() == representative2.getRank()) representative1.rankUp();//Increase rank if equal
            d = null; //No need to keep d in memory
        }
        else
        {
            d.elementsOfTheSet.addAll(this.getElementsOfTheSet()); //Get all elements
            representative1.setParent(representative2);//winner becomes new representative
        }
        
    }
    
    //This method will return the representative of the set in which key appears
    private Node<T> findNode(T key)
    {
        for(int i = 0; i < elementsOfTheSet.size(); i++)
        {
            if(elementsOfTheSet.get(i).getKey() == key)
            {
                Node<T> n = elementsOfTheSet.get(i);
                Node<T> starter = n; //Used for Path Compression
                while(n.getParent() != n)
                {
                    n = n.getParent();
                }
                starter.setParent(n); //Path Compression
                return n;
            }
        }
        return null;
    }

    public T find(T key)
    {
        return findNode(key).getKey();
    }

    public String toString()
    {
        String s = "\n";
        for (Node<T> node : elementsOfTheSet) 
        {
            s += node.getKey().toString() + " -> " + node.getParent().getKey().toString() + "\n";
        }
        return s;
    }

}