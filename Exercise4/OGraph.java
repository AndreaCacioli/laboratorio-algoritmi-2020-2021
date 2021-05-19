import java.util.ArrayList;
import java.util.HashMap;

class OGraph<T extends Comparable<T> , E extends Comparable<E>>
{
    private HashMap<T, GNode<T, E>> nodes; //No need for order, just need it to be time-efficient
    private HashMap<E, GEdge<T, E>> edges;

    OGraph() //Creazione di un grafo vuoto – O(1)
    {
        nodes = new HashMap<>();
        edges = new HashMap<>();
    }

    public void add(T key)//Aggiunta di un nodo – O(1)
    {
        GNode<T, E> node = new GNode<T, E>(key);
        nodes.put(key, node); //O(1)
    }
    public void addConnection(T v1, T v2, E tag)//Aggiunta di un arco – O(1)
    {
        GNode<T, E> node1 = getValue(v1);
        GNode<T, E> node2 = getValue(v2);
        if(node1 == null || node2 == null)
        {
            System.err.println("Missing one node!");
            return;
        }
        GEdge<T, E> edge  = new GEdge<>();
        edge.start = node1;
        edge.end = node2;
        edge.tag = tag;
        node1.adjacenNodes.add(edge);
        edges.put(tag, edge);
    }

    public boolean isOriented()//Verifica se il grafo è diretto – O(1)
    {
        return true;
    }

    public boolean containsValue(T value) //Verifica se il grafo contiene un dato nodo – O(1)
    {
        return nodes.containsKey(value);
    }
    public GNode<T, E> getValue(T value) 
    {
        return nodes.get(value);
    }
    
    public boolean containsConnection(T v1, T v2) //Verifica se il grafo contiene un dato arco – O(1)  (*)
    {
       return findTag(v1, v2) != null;
    }
    
    public void delete(T v) //Cancellazione di un nodo – O(n)
    {
        for(GEdge<T, E> edge : edges.values())
        {
            if(edge.start.key.compareTo(v) == 0) //edge going out of v
            {
                edges.remove(edge.tag);
            }
            if(edge.end.key.compareTo(v) == 0) //edge entering in v
            {
                edge.start.adjacenNodes.remove(edge);
                edges.remove(edge.tag);
            }
        }
        nodes.remove(v);
    }
    
    public void deleteConnection(E tag) //Cancellazione di un arco – O(1)  (*)
    {
        GEdge<T, E> edge = edges.get(tag);
        edge.start.adjacenNodes.remove(edge);
        edges.remove(tag);
    }
    
    public int size() //Determinazione del numero di nodi – O(1)
    {
        return nodes.size();
    }

    public int connectionsNumber() //Determinazione del numero di archi – O(n) I did O(1)
    {
        return edges.size();
    }
    public ArrayList<T> getValues() //Recupero dei nodi del grafo – O(n)
    {
        ArrayList<T> ret = new ArrayList<>();
        for(T key : nodes.keySet())
        {
            ret.add(key);
        } 
        return ret;
    }
    public ArrayList<E> getTags() //Recupero degli archi del grafo – O(n)
    {
        ArrayList<E> ret = new ArrayList<>();
        for(E tag : edges.keySet())
        {
            ret.add(tag);
        }
        return ret;
    }
    
    public ArrayList<T> getAdjacents(T v1) //Recupero nodi adiacenti di un dato nodo – O(1)  (*)
    {
        ArrayList<T> ret = new ArrayList<>();
        GNode<T, E> n = nodes.get(v1);
        for(GEdge<T, E> g : n.adjacenNodes)
        {
            ret.add(g.end.key);
        } 
        return ret;
    }

    public E findTag(T v1, T v2) //Recupero etichetta associata a una coppia di nodi – O(1) (*)
    {
        GNode<T, E> n = nodes.get(v1); //O(1)
        for(GEdge<T, E> edge : n.adjacenNodes)
        {
            if(edge.start.key.compareTo(v1) == 0 && edge.end.key.compareTo(v2) == 0)
            {
                return edge.tag;
            }
        }
        return null;
    }

}