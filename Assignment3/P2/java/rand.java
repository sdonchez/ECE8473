public class rand // equivalent to the internals of java.util.Random
{
  public static long seed;

  private static long multiplier = 0x5DEECE66DL;
  private static long addend = 0xBL;
  private static long mask = (1L << 48) - 1;

  public static void initialScramble( long init)
  {
    seed = (init ^ multiplier) & mask;
  }

  private static int next( int bits)
  {
    seed = (seed * multiplier + addend) & mask;

    return (int)(seed >>> (48 - bits));
  }

  public static int nextInt()
  {
    return next(32);
  }

  public static long hashCode( char s[]) // similar to java.lang.String hashCode
  {
    long h = 0; for( int i = 0; i < s.length; i++) h = 31 * h + s[i];

    return h;
  }

  public static void main( String args[])
  {
    String a = args[0]; // would be argv[1] in C

    long init = hashCode( a.toCharArray()); initialScramble( init);

    System.out.println( "a = " + a + ", init = " + init + ", seed = " + seed);

    for( int i = 0; i < 10; ++i) System.out.println( nextInt());
  }

}
