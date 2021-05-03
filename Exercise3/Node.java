class Node<T>
{
    private T key;
    private Node<T> parent; //This will point to itself when the node is a representative of the set
    private int rank;
    
    Node()
    {
        key = null;
        parent  = this;
        rank = 0; 
    }
    Node(T k)
    {
        key = k;
        parent  = this;
        rank = 0; 
    }
    public int getRank()
    {
        return rank;
    }
    public T getKey()
    {
        return key;
    }
    public Node<T> getParent()
    {
        return parent;
    }
    public void setParent(Node<T> n)
    {
        parent = n;
    }
    public void setRank(int r)
    {
        rank = r;
    }
    public void rankUp()
    {
        rank++;
    }
}