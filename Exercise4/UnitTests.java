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

}