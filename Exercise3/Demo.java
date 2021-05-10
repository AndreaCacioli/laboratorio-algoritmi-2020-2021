class Demo
{
    /*
    *   A class to test the Union-Find data Structure
    */
    public static void main(String[] Args)
    {
        DSets<Integer> d = new DSets<Integer>();

        d.makeSet(1);
        d.makeSet(2);
        d.makeSet(2);
        d.makeSet(1);
        d.makeSet(3);
        d.makeSet(4);
        d.makeSet(5);

        System.out.println(d.size());
        //System.out.println(d.toString());

        d.union(1, 2);
        d.union(3, 4);

        System.out.println(d.find(2));
        System.out.println(d.find(4));
        System.out.println(d.find(5));

        d.union(4, 2);
        System.out.println("1 -> " + d.find(1));
        
        d.union(5, 3);
        System.out.println("5 -> " + d.find(5));
        
    }
}