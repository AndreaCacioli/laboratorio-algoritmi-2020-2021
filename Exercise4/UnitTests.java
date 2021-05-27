import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNull;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;
import org.junit.Test;

public class UnitTests
{

    //Oriented Graphs
    @Test
    public void test1()
    {
        OGraph<String, Integer> graph = new OGraph<>();
        graph.add("hi");
        graph.add("there");
        graph.addConnection("hi", "there", 5);
        assertTrue(graph.containsConnection("hi", "there"));
        assertTrue(graph.containsValue("hi"));
        assertTrue(graph.containsValue("there"));
        assertEquals( graph.findTag("hi", "there"), (Integer)5);
        graph.delete("there");
        graph.add("everyone");
        assertNull(graph.findTag("hi", "there"));
        assertNull(graph.findTag("hi", "everyone"));
        
    }

    @Test
    public void test2()
    {
        OGraph<String, Integer> graph = new OGraph<>();
        graph.add("hi");
        graph.add("there");
        graph.addConnection("hi", "there", 5);
        assertEquals(graph.connectionsNumber(), 1);
        assertTrue(graph.getValues().contains("hi"));
        assertTrue(graph.getValues().contains("there"));
        assertEquals(graph.getValues().size(), 2);

    }

    @Test
    public void test3()
    {
        OGraph<String, Integer> graph = new OGraph<>();
        graph.add("hi");
        graph.add("there");
        graph.addConnection("hi", "there", 5);
        graph.addConnection("there", "hi", 9);
        assertEquals(graph.connectionsNumber(), 2);
        assertTrue(graph.getTags().contains(5));
        assertTrue(graph.getTags().contains(9));
        assertEquals(graph.getTags().size(), 2);
    }

    @Test
    public void test4()
    {
        OGraph<String, Integer> graph = new OGraph<>();
        graph.add("hi");
        graph.add("there");
        graph.addConnection("hi", "there", 5);
        graph.addConnection("there", "hi", 9);
        assertEquals(graph.connectionsNumber(), 2);
        assertTrue(graph.getTags().contains(5));
        assertTrue(graph.getTags().contains(9));
        assertEquals(graph.getTags().size(), 2);
    }

    @Test
    public void test5()
    {
        OGraph<String, Integer> graph = new OGraph<>();
        graph.add("hi");
        graph.add("there");
        graph.add("hello");
        graph.addConnection("hi", "there", 5);
        graph.addConnection("hi", "hello", 9);
        assertEquals(graph.connectionsNumber(), 2);
        assertTrue(graph.getAdjacents("hi").contains("there"));
        assertTrue(graph.getAdjacents("hi").contains("hello"));
        assertEquals(graph.getAdjacents("hi").size(), 2);
    }

    @Test
    public void test6()
    {
        OGraph<String, Integer> graph = new OGraph<>();
        graph.add("hi");
        graph.add("there");
        graph.add("hello");
        graph.addConnection("hi", "there", 5);
        graph.addConnection("hi", "hello", 9);
        graph.addConnection("there", "hello", 10);
        assertEquals(graph.connectionsNumber(), 3);
        assertEquals(graph.findTag("hi", "there"), (Integer)5);
        assertEquals(graph.findTag("hi", "hello"), (Integer)9);
        assertEquals(graph.findTag("there", "hello"), (Integer)10);
        assertNull(graph.findTag("hi", "hi"));
        graph.deleteConnection("there", "hello");
        assertNull(graph.findTag("there", "hello"));
    }

    //Unoriented Graphs
    @Test
    public void test7()
    {
        Graph<String, Integer> graph = new Graph<>();
        graph.add("hi");
        graph.add("there");
        graph.add("hello");
        graph.addConnection("hi", "there", 5);
        graph.addConnection("hi", "hello", 9);
        graph.addConnection("there", "hello", 10);
        assertEquals(graph.connectionsNumber(), 3);
        assertEquals(graph.findTag("hi", "there"), (Integer)5);
        assertEquals(graph.findTag("there", "hi"), (Integer)5);
        assertEquals(graph.findTag("hello", "hi"), (Integer)9);
        assertNull(graph.findTag("hi", "hi"));
    }
    @Test
    public void test8()
    {
        Graph<String, Integer> graph = new Graph<>();
        graph.add("hi");
        graph.add("there");
        graph.add("hello");
        graph.addConnection("hi", "there", 5);
        graph.addConnection("hi", "hello", 9);
        graph.addConnection("there", "hello", 10);
        assertEquals(graph.connectionsNumber(), 3);
        assertEquals(graph.findTag("hi", "there"), (Integer)5);
        assertEquals(graph.findTag("there", "hi"), (Integer)5);
        assertEquals(graph.findTag("hello", "hi"), (Integer)9);
        graph.deleteConnection("there", "hi");
        assertFalse(graph.containsConnection("there", "hi"));
        assertFalse(graph.containsConnection("hi", "there"));
        assertNull(graph.findTag("hi", "hi"));
    }
    @Test
    public void test9()
    {
        Graph<String, Integer> graph = new Graph<>();
        graph.add("hi");
        graph.add("there");
        graph.add("hello");
        graph.add("how");
        graph.add("are");
        graph.add("you");
        graph.addConnection("hi", "there", 5);
        graph.addConnection("hi", "hello", 9);
        graph.addConnection("there", "hello", 10);
        graph.addConnection("how", "hi", 5);
        graph.addConnection("are", "you", 1);
        graph.addConnection("how", "hello", 9);
        assertEquals(graph.connectionsNumber(), 6);
        int sum = 0;
        for (int v : graph.getTags())
        {
            sum += v;
        }
        assertEquals(sum/2, 39);
        assertEquals(graph.findTag("hi", "there"), (Integer)5);
        assertEquals(graph.findTag("there", "hi"), (Integer)5);
        assertEquals(graph.findTag("hello", "hi"), (Integer)9);
        graph.delete("hello");
        assertTrue(graph.containsConnection("there", "hi"));
        assertTrue(graph.containsConnection("hi", "there"));
        assertNull(graph.findTag("hi", "hello"));
        assertNull(graph.findTag("hello", "there"));
        assertNull(graph.findTag("there", "hello"));
        assertNull(graph.findTag("how", "hello"));
        assertNull(graph.findTag("hello", "how"));
    }

    //Kruskall's algorithm
    @Test
    public void test10()
    {
        Graph<String, Integer> graph = new Graph<>();
        graph.add("hi");
        graph.add("there");
        graph.add("hello");
        graph.add("how");
        graph.add("are");
        graph.add("you");
        graph.addConnection("hi", "there", 5);
        graph.addConnection("hi", "hello", 9);
        graph.addConnection("there", "hello", 10);
        graph.addConnection("how", "hi", 5);
        graph.addConnection("are", "you", 1);
        graph.addConnection("how", "hello", 9);
        assertEquals(graph.connectionsNumber(), 6);
        int sum = 0;
        for (int v : graph.getTags())
        {
            sum += v;
        }
        assertEquals(sum/2, 39);
        assertTrue(graph.hasCycle());
        graph = graph.krusk();
        sum = 0;
        for (int v : graph.getTags())
        {
            sum += v;
        }
        assertEquals(sum/2, (int)20);
        assertEquals(graph.connectionsNumber(), 4);
        assertEquals(graph.size(), 6);
        assertFalse(graph.hasCycle()); //Checking that krusk successfully removes cycles
    }
}