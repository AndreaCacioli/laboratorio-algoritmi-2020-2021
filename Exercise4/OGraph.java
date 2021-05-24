import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;

class OGraph<T extends Comparable<T> , E extends Comparable<E>>
{
    protected HashMap<T, GNode<T, E>> nodes; //No need for order, just need it to be time-efficient

    OGraph() //Creazione di un grafo vuoto – O(1)
    {
        nodes = new HashMap<>();
    }

    public void add(T key)//Aggiunta di un nodo – O(1)
    {
        if(!containsValue(key))
        {
            GNode<T, E> node = new GNode<T, E>(key);
            nodes.put(key, node); //O(1)
        }
    }
    public void addConnection(T v1, T v2, E tag)//Aggiunta di un arco – O(1)
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
            GEdge<T, E> edge  = new GEdge<>(node1,node2,tag);
            node1.adjacenNodes.add(edge);
        }
        
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
        if(containsValue(v))
        {
           GNode<T,E> nodeToBeCancelled = nodes.get(v);
           nodes.remove(v);
           for(GNode<T,E> node : nodes.values())//O(n)
           {
               for(GEdge<T,E> edge: node.adjacenNodes)//O(1)
               {
                    if(edge.end.key.compareTo(nodeToBeCancelled.key) == 0)
                    {
                        node.adjacenNodes.remove(edge);
                        break;
                    }
                    
               }
           }
           
        }
        else
        {
            System.err.println("Cannot delete a node which is not in the graph");
        }
        
    }
    
    public void deleteConnection(T v1, T v2) //Cancellazione di un arco – O(1)  (*)
    {
       GNode<T,E> node = nodes.get(v1);
       if(node == null) 
       {
           System.out.println(v1 + "could not be found!");
           return;
       }

       for(GEdge<T,E> edge : node.adjacenNodes)
       {
           if(edge.end.key.compareTo(v2) == 0)
           {
               node.adjacenNodes.remove(edge);
               break;
           }
       } 
    }
    
    public int size() //Determinazione del numero di nodi – O(1)
    {
        return nodes.size();
    }

    public int connectionsNumber() //Determinazione del numero di archi – O(n) 
    {
        int sum = 0;
        for(GNode<T,E> node : nodes.values())
        {
            sum += node.adjacenNodes.size();
        }
        return sum; //We could make it an O(1) by adding just one variable and updating it everytime one adds a connection and decreasing it when one is deleted
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
        for(GNode<T,E> node : nodes.values())
        {
            for(GEdge<T,E> edge : node.adjacenNodes)
            {
                ret.add(edge.tag);
            }
        }
        return ret;
    }

    protected ArrayList<GEdge<T,E>> getEdges() //Recupero degli archi del grafo – O(n)
    {
        ArrayList<GEdge<T,E>> ret = new ArrayList<>();
        for(GNode<T,E> node : nodes.values())
        {
            for(GEdge<T,E> edge : node.adjacenNodes)
            {
                ret.add(edge);
            }
        }
        return ret;
    }
    
    public ArrayList<T> getAdjacents(T v1) //Recupero nodi adiacenti di un dato nodo – O(1)  (*)
    {
        ArrayList<T> ret = new ArrayList<>();
        if(containsValue(v1))
        {
            GNode<T, E> n = nodes.get(v1);
            for(GEdge<T, E> g : n.adjacenNodes)
            {
                ret.add(g.end.key);
            } 
        }
        return ret;
        
    }

    public E findTag(T v1, T v2) //Recupero etichetta associata a una coppia di nodi – O(1) (*)
    {
        GEdge<T,E> edge = findEdge(v1, v2);
        if(edge == null) return null;
        return edge.tag;
    }

    protected GEdge<T,E> findEdge(T v1, T v2) 
    {
        GNode<T, E> n = nodes.get(v1); //O(1)
        if(n == null) return null;

        for(GEdge<T, E> edge : n.adjacenNodes)
        {
            if(edge.start.key.compareTo(v1) == 0 && edge.end.key.compareTo(v2) == 0)
            {
                return edge;
            }
        }
        return null;
    }

    public boolean hasCycle()
    {
        DSets<T> sets = new DSets<>(); 
        for(GNode<T,E> node : nodes.values())
        {
            sets.makeSet(node.key); //Creating every node's own set
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
                return true;
            }
        }
        return false;
    }

    protected void removeDuplicates(ArrayList<GEdge<T,E>> edges)
    {
        for(int i = 0; i < edges.size(); i++)
        {
            int j;
            for(j = i;j < edges.size() && edges.get(j).tag == edges.get(i).tag ;j++) //The array needs to be sorted
            {
                if(edges.get(j).start.key.compareTo(edges.get(i).end.key) == 0 && edges.get(j).end.key.compareTo(edges.get(i).start.key) == 0)
                {
                    edges.remove(j);
                    break;
                }
            }
        }
    }

    public String toString()
    {
        String s = new String();
        for(GNode<T,E> node : nodes.values())
        {
            s += node.key.toString() + " -> ";
            for(GEdge<T,E> edge : node.adjacenNodes)
            {
                s += edge.end.key.toString() + " d: (" +  edge.tag +") | ";
            }
            s += "\n";
        }
        return s;
    }

}