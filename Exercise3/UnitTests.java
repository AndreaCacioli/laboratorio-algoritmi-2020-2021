import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNull;
import org.junit.Test;

public class UnitTests 
{
    @Test
    public void singletonInt()
    {
        DSets<Integer> set = new DSets<Integer>();
        set.makeSet(5);
        assertEquals(set.find(5), (Integer)5);
    }

    @Test
    public void singletonStr()
    {
        DSets<String> set = new DSets<String>();
        set.makeSet("Test");
        assertEquals(set.find("Test"), "Test");
    }
    @Test
    public void failFindInt()
    {
        DSets<Integer> set = new DSets<Integer>();
        assertNull("10 is not in the set\n", set.find(10));
    }
    @Test
    public void failFindStr()
    {
        DSets<String> set = new DSets<String>();
        assertNull("Miao is not in the set\n", set.find("Miao"));
    }

    @Test
    public void manySetsFindStr()
    {
        DSets<String> set = new DSets<String>();
        set.makeSet("Test");
        set.makeSet("key");
        set.makeSet("value");
        assertEquals(set.find("Test"), "Test");
        assertEquals(set.find("key"), "key");
        assertEquals(set.find("value"), "value");
    }
    @Test
    public void manySetsUnionStr()
    {
        DSets<String> set = new DSets<String>();
        set.makeSet("Test");
        set.makeSet("key");
        set.makeSet("value");
        set.union("Test","key");
        assertEquals(set.find("Test"), "Test");
        assertEquals(set.find("key"), "Test");
        assertEquals(set.find("value"), "value");
    }
    @Test
    public void manySetsUnionStr2()
    {
        DSets<String> set = new DSets<String>();
        set.makeSet("Test");
        set.makeSet("key");
        set.makeSet("value");
        assertEquals(set.union("Test","key"),0);
        set.makeSet("Magnet");
        assertEquals(set.union("value", "Magnet"),0);
        assertEquals(set.find("Test"), "Test");
        assertEquals(set.find("key"), "Test");
        assertEquals(set.find("value"), "value");
        assertEquals(set.find("Magnet"), "value");
        assertEquals(set.union("Test", "key"), -1);
    }



}
