class Demo
{
    /*
    *   A class to test the Union-Find data Structure
    */
    public static void main(String[] Args)
    {
        DSet<Integer> d = new DSet<Integer>(1);
        DSet<Integer> d1 = new DSet<Integer>(2);
        DSet<Integer> d2 = new DSet<Integer>(3);
        DSet<Integer> d3 = new DSet<Integer>(4);
        DSet<Integer> d4 = new DSet<Integer>(5);

        System.out.println(d);
        System.out.println(d1);
        System.out.println(d2);

        d.Union(d1);
        d2.Union(d3);
        d2.Union(d4);
        d2.Union(d);

        System.out.println(d2);

        d2.find(2);

        System.out.println(d2);

    }
}