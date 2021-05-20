import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNull;
import org.junit.Test;

public class UnitTests
{

    @Test
    public void test1()
    {
        OGraph<String, Integer> graph = new OGraph<>();
        graph.add("hi");
        graph.add("there");
        graph.addConnection("hi", "there", 5);
        assertEquals(graph.containsConnection("hi", "there"), true);
        assertEquals(graph.containsValue("hi"), true);
        assertEquals(graph.containsValue("there"), true);
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
        assertEquals(graph.getValues().contains("hi"), true);
        assertEquals(graph.getValues().contains("there"), true);
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
        assertEquals(graph.getTags().contains(5), true);
        assertEquals(graph.getTags().contains(9), true);
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
        assertEquals(graph.getTags().contains(5), true);
        assertEquals(graph.getTags().contains(9), true);
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
        assertEquals(graph.getAdjacents("hi").contains("there"), true);
        assertEquals(graph.getAdjacents("hi").contains("hello"), true);
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
        assertEquals(graph.containsConnection("there", "hi"),false);
        assertEquals(graph.containsConnection("hi", "there"),false);
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
        assertEquals(graph.findTag("hi", "there"), (Integer)5);
        assertEquals(graph.findTag("there", "hi"), (Integer)5);
        assertEquals(graph.findTag("hello", "hi"), (Integer)9);
        graph.delete("hello");
        assertEquals(graph.containsConnection("there", "hi"),true);
        assertEquals(graph.containsConnection("hi", "there"),true);
        assertNull(graph.findTag("hi", "hello"));
        assertNull(graph.findTag("hello", "there"));
        assertNull(graph.findTag("there", "hello"));
        assertNull(graph.findTag("how", "hello"));
        assertNull(graph.findTag("hello", "how"));
    }
}